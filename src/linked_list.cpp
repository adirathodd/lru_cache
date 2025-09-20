#include "linked_list.hpp"

// Constructor
LinkedList::LinkedList(){
    head = new Node(-1, -1, nullptr, nullptr);
    tail = new Node(-1, -1, nullptr, nullptr);

    this->head->next = this->tail;
    this->tail->prev = this->head;
    this->nodesCount = 0;
}

// Deconstructor
LinkedList::~LinkedList(){
    Node* curr = this->head;
    Node *next;
    while(curr){
        next = curr->next;
        delete curr;
        curr = next;
    }
}

// Insertions
Node* LinkedList::insertAtHead(int key, int val){
    Node *node = new Node(key, val, this->head->next, this->head);
    node->next->prev = node;
    this->head->next = node;
    this->nodesCount++;

    return node;
}

Node* LinkedList::insertAtTail(int key, int val){
    Node *node = new Node(key, val, this->tail, this->tail->prev);
    node->prev->next = node;
    this->tail->prev = node;
    this->nodesCount++;

    return node;
}

// Removals
bool LinkedList::removeFromHead(){
    if (this->nodesCount == 0) return false;
    Node* remove = head->next;
    this->head->next = remove->next;
    remove->next->prev = head;
    delete remove;
    this->nodesCount--;

    return true;
}

Node* LinkedList::popFromHead(){
    if (this->nodesCount == 0) return nullptr;
    Node* remove = head->next;
    this->head->next = remove->next;
    remove->next->prev = head;
    this->nodesCount--;

    remove->prev = nullptr;
    remove->next = nullptr;
    return remove;
}

bool LinkedList::removeFromTail(){
    if(this->nodesCount == 0) return false;
    Node* remove = tail->prev;
    this->tail->prev = remove->prev;
    remove->prev->next = tail;
    delete remove;
    this->nodesCount--;

    return true;
}

Node* LinkedList::popFromTail(){
    if(this->nodesCount == 0) return nullptr;
    Node* remove = tail->prev;
    this->tail->prev = remove->prev;
    remove->prev->next = tail;
    this->nodesCount--;

    remove->next = nullptr;
    remove->prev = nullptr;

    return remove;
}

bool LinkedList::removeIndex(int index){
    if(this->nodesCount == 0 || index >= this->nodesCount || index < 0) return false;
    Node* curr = head;
    for (int i = 0; i < index; i++) curr = curr->next;
    Node* remove = curr->next;
    curr->next = curr->next->next;
    curr->next->prev = curr;
    delete remove;
    this->nodesCount--;

    return true;
}

bool LinkedList::removeNode(Node* node){
    if(node == nullptr || this->nodesCount == 0) return false;
    if(node == this->head || node == this->tail) return false;
    if(node->prev == nullptr || node->next == nullptr) return false;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    this->nodesCount--;

    return true;
}

// move any node to tail
bool LinkedList::moveToTail(Node *node){
    if(node == nullptr || this->nodesCount == 0) return false;
    if(node == this->head || node == this->tail) return false;
    if(node->prev == nullptr || node->next == nullptr) return false;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    node->next = this->tail;
    node->prev = this->tail->prev;

    this->tail->prev = node;
    node->prev->next = node;

    return true;
}


// information
void LinkedList::printList(){
    if(nodesCount == 0){
        std::cout << "There are no elements in this linked list yet!\n" << std::endl;
        return;
    }
    Node *curr = this->head->next;
    int index = 0;
    while(curr->next != nullptr){
        std::cout << index++ << ") Key: " << curr->key << ", Value: " << curr->value << std::endl;
        curr = curr->next;
    }
    std::cout << "\nTotal elements: " << this->nodesCount << "\n" << std::endl;
}

int LinkedList::size(){
    return nodesCount;
}