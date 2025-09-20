#pragma once
#include <iostream>

class Node {
public:
    int value, key;
    Node* next;
    Node* prev;

    Node(int k, int v, Node* nxt, Node* prv){
        key = k;
        value = v;
        next = nxt;
        prev = prv;
    }

};


class LinkedList {
    private:
        Node *head, *tail;
        int nodesCount;

    public:
        LinkedList();
        ~LinkedList();

        Node* insertAtHead(int key, int val);
        Node* insertAtTail(int key, int val);
        
        bool removeFromHead();
        Node* popFromHead();
        bool removeFromTail();
        Node* popFromTail();

        bool removeIndex(int index);
        bool removeNode(Node* node);

        bool moveToTail(Node *Node);

        void printList();
        int size();
};