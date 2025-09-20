#!/opt/homebrew/bin/bash
# Verifies output of src/test/test_lru_cache.cpp

set -u

# --- build ---
gxx="${CXX:-g++-15}"
command -v "$gxx" >/dev/null 2>&1 || gxx="${CXX:-g++}"

echo "=== Build ==="
"$gxx" -std=c++17 -O2 -Wall -Wextra \
  -I include src/lru_cache.cpp src/linked_list.cpp src/test/test_lru_cache.cpp \
  -o test_lru_cache || { echo "❌ Build failed"; exit 1; }

# --- run ---
echo "=== Run ==="
output="$(./test_lru_cache 2>&1)"; rc=$?
rm -f ./test_lru_cache
[ $rc -eq 0 ] || { echo "❌ Program exited with $rc"; printf "%s\n" "$output"; exit 1; }

ok(){ echo "✅ $1"; }
ko(){ echo "❌ $1"; failed=$((failed+1)); }
failed=0

# --- basic checks ---
# Expect exactly 4 "Total elements: 5" blocks
if [ "$(grep -c '^Total elements: 5$' <<<"$output")" -eq 4 ]; then
  ok "found 4 blocks with total=5"
else
  ko "expected 4 blocks with total=5"
fi

# Expect retrieval line for key 2
grep -q '^Key: 2, Value: 2$' <<<"$output" && ok "retrieval of key 2 returns 2" || ko "retrieval of key 2 missing/incorrect"

# Expect update of key 3 to value 10 somewhere after the update
grep -q '^[0-9]\+) Key: 3, Value: 10$' <<<"$output" && ok "key 3 updated to value 10" || ko "key 3 not updated to 10"

# --- order checks per block ---
# Extract each printed list (sequence of keys) per "Total elements: 5"
# Prints one line per block like: "0 1 2 3 4"
mapfile -t blocks < <(awk '
  /^[0-9]+\) Key:/ {
    gsub(/,/, "", $3); seq = seq (seq?" ":"") $3
  }
  /^Total elements: 5$/ { print seq; seq="" }
' <<<"$output")

exp0="0 1 2 3 4"
exp1="0 1 3 4 2"
exp2="0 1 4 2 3"
exp3="1 4 2 3 6"

if [ "${#blocks[@]}" -ge 4 ]; then
  [[ "${blocks[0]}" == "$exp0" ]] && ok "initial order: $exp0" || ko "initial order (got: ${blocks[0]:-<none>})"
  [[ "${blocks[1]}" == "$exp1" ]] && ok "after get(2): $exp1"    || ko "after get(2) order (got: ${blocks[1]:-<none>})"
  [[ "${blocks[2]}" == "$exp2" ]] && ok "after store(3,10): $exp2" || ko "after store(3,10) order (got: ${blocks[2]:-<none>})"
  [[ "${blocks[3]}" == "$exp3" ]] && ok "after store(6,6): $exp3"  || ko "after store(6,6) order (got: ${blocks[3]:-<none>})"
else
  ko "could not parse 4 printed blocks (found ${#blocks[@]})"
fi

# Ensure key 0 is evicted in final block
[[ "${blocks[3]:-}" != *"0"* ]] && ok "final block evicts key 0" || ko "key 0 still present in final block"

# --- summary ---
if ((failed==0)); then
  echo "🎉 All checks passed"
  exit 0
else
  echo "❌ $failed check(s) failed"
  exit 1
fi