#!/opt/homebrew/bin/bash

echo "=== Build ==="
g++ -I include src/linked_list.cpp src/test/test_linked_list.cpp -o test_linked_list \
  || { echo "❌ Build failed"; exit 1; }

# Run
echo "=== Run ==="
output="$(./test_linked_list 2>&1)"; status=$?
rm ./test_linked_list
[ $status -eq 0 ] || { echo "❌ Program exited with $status"; printf "%s\n" "$output"; exit 1; }

fail=0
ok(){ echo "✅ $1"; }
ko(){ echo "❌ $1"; fail=$((fail+1)); }

# Basic expectations
grep -q "^There are no elements in this linked list yet!" <<<"$output" && ok "empty-list message" || ko "empty-list message"
grep -q "^Total elements: 10$"                                 <<<"$output" && ok "initial count = 10" || ko "initial count = 10"
grep -q "^0) Key: 0, Value: 0$"                                 <<<"$output" && ok "initial head: (0,0)" || ko "initial head: (0,0)"
grep -q "^9) Key: 9, Value: 9$"                                 <<<"$output" && ok "initial tail: (9,9)" || ko "initial tail: (9,9)"

# After head/tail removals
grep -q "^Total elements: 8$"                                   <<<"$output" && ok "count = 8 after removals" || ko "count = 8 after removals"

# Two stages with 6 elements
[ "$(grep -c "^Total elements: 6$" <<<"$output")" -eq 2 ] && ok "two stages with count = 6" || ko "two stages with count = 6"

# Verify final block exact order of keys: 1 2 4 7 8 6 (and that 5 is gone)
last6_line="$(awk '/^Total elements: 6$/{last=NR} END{print last}' <<<"$output")"
final_keys="$(awk -v L="$last6_line" '
  NR<L && /Key:/ {gsub(/,/, "", $3); a[++n]=$3}
  END {for(i=n-5;i<=n;i++) printf "%s%s", a[i], (i<n?" ":"")}
' <<<"$output")"

[ "$final_keys" = "1 2 4 7 8 6" ] && ok "final order is 1 2 4 7 8 6" || ko "final order (got: $final_keys)"
[[ "$final_keys" != *"5"* ]] && ok "key 5 removed in final state" || ko "key 5 still present in final state"


# Summary
if ((fail==0)); then
  echo "🎉 All checks passed"
  exit 0
else
  echo "❌ $fail check(s) failed"
  exit 1
fi