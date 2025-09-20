# lru_cache

Small C++ repo demonstrating a doubly-linked list and an LRU cache built on top of it.

## Contents
- [include/linked_list.hpp](include/linked_list.hpp) — definitions for [`Node`](include/linked_list.hpp) and [`LinkedList`](include/linked_list.hpp).
- [src/linked_list.cpp](src/linked_list.cpp) — implementation of `LinkedList` (e.g. [`LinkedList::insertAtTail`](src/linked_list.cpp), [`LinkedList::moveToTail`](src/linked_list.cpp)).
- [include/lru_cache.hpp](include/lru_cache.hpp) — definition of [`LRUCache`](include/lru_cache.hpp).
- [src/lru_cache.cpp](src/lru_cache.cpp) — implementation of cache logic (e.g. [`LRUCache::store`](src/lru_cache.cpp), [`LRUCache::get`](src/lru_cache.cpp)).
- Tests:
  - [src/test/test_linked_list.cpp](src/test/test_linked_list.cpp)
  - [src/test/test_lru_cache.cpp](src/test/test_lru_cache.cpp)
- Helper scripts:
  - [test_linked_list.sh](test_linked_list.sh)
  - [test_lru_cache.sh](test_lru_cache.sh)

## Prerequisites
- A C++ compiler (g++ / clang++) with C++17 support.
- Bash to run the provided test scripts.

## Quick build & run
Make the test scripts executable and run them:

chmod +x test_linked_list.sh test_lru_cache.sh
./test_linked_list.sh
./test_lru_cache.sh

Alternatively, build manually:

g++ -I include src/linked_list.cpp src/test/test_linked_list.cpp -o test_linked_list
./test_linked_list

g++ -std=c++17 -O2 -Wall -Wextra -I include src/lru_cache.cpp src/linked_list.cpp src/test/test_lru_cache.cpp -o test_lru_cache
./test_lru_cache

## What to look at
- Linked list node & API: see [`Node`](include/linked_list.hpp) and [`LinkedList`](include/linked_list.hpp) in [include/linked_list.hpp](include/linked_list.hpp).
- LRU behavior: the cache uses the linked list to maintain recency. See [`LRUCache`](include/lru_cache.hpp) and its implementation in [src/lru_cache.cpp](src/lru_cache.cpp).

## Notes
- Tests print the list state; the shell scripts validate expected outputs.
- The repository is minimal and intended for learning / demonstration purposes.
