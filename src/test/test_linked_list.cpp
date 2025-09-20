#include "linked_list.hpp"
#include <unordered_map>

int main(){
    LinkedList list = LinkedList();
    std::unordered_map<int, Node*> map; // <key, node>

    //empty
    list.printList();

    //insert 10 elements
    for(int i = 0; i < 10; i++) map[i] = list.insertAtTail(i, i);
    list.printList();

    //check head and tail removal
    list.removeFromHead();
    list.removeFromTail();
    list.printList();

    //check remove by index and specfic node pointer
    list.removeIndex(2);
    list.removeNode(map[5]);
    list.printList();

    //check moving a node to tail
    list.moveToTail(map[6]);
    list.printList();
}