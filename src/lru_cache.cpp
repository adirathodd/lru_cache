#include "lru_cache.hpp"
#include <stdexcept>

LRUCache::LRUCache(int size){
    if(size <= 0){
        throw std::invalid_argument("LRUCache size must be greater than 0!");
    }
    this->size = size;
}

LRUCache::~LRUCache(){
    this->cache.clear();
}

int LRUCache::get(int key){
    if(this->cache.find(key) == this->cache.end()){
        return -1;
    }

    Node* node = this->cache.at(key);
    this->lru_order.moveToTail(node);

    return node->value;
}

void LRUCache::store(int key, int value){
    // if key already exists
    if (this->cache.find(key) != this->cache.end()){
        Node* existing = this->cache.at(key);
        existing->value = value;
        this->lru_order.moveToTail(existing);
        return;
    }

    // evict from head if we are full capacity before adding
    if (this->lru_order.size() == this->size){
        Node* removed = this->lru_order.popFromHead();
        if(removed){
            this->cache.erase(removed->key);
            delete removed;
        }
    }

    // add to cache
    Node *node = lru_order.insertAtTail(key, value);
    this->cache[key] = node;
}

void LRUCache::printCache(){
    this->lru_order.printList();
}