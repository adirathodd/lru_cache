#include "lru_cache.hpp"

int main(){
    LRUCache lru = LRUCache(5);

    //populate cache
    for(int i = 0; i < 5; i++) lru.store(i, i);
    lru.printCache();

    //check retrieval
    int val = lru.get(2);
    std::cout << "Key: " << 2 << ", Value: " << val << "\n" << std::endl;

    //check 2 is at the end of list
    lru.printCache();

    //check 3 is updated with 10 and also at the end
    lru.store(3, 10);
    lru.printCache();

    // check 6 is added to end of the list and 0 is removed
    lru.store(6, 6);
    lru.printCache();

    //check retrieval of invalid key
    val = lru.get(0);
    std::cout << "Key: " << 0 << ", Value: " << val << "\n" << std::endl;

}