#include "linked_list.hpp"
#include <map>

class LRUCache {
    private:
        LinkedList lru_order = LinkedList();
        std::map<int, Node*> cache;
        int size;

    public:
        LRUCache(int size);
        ~LRUCache();

        void store(int key, int val);
        int get(int key);

        void printCache();
};