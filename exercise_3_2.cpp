#include "exercise_3_2.hpp"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
}

void LinkedList::add_to_front(std::string name) {
    auto ptr_to_new = std::make_unique<Node>();
    ptr_to_new->name = name;
    ptr_to_new->next = std::move(head);
    head = std::move(ptr_to_new);
}

void LinkedList::add_to_back(std::string name){
    auto ptr_to_new = std::make_unique<Node>();
    ptr_to_new->name = name;
    ptr_to_new->next = nullptr;
    if (head == nullptr) {
        head = std::move(ptr_to_new);
    } else {
        // use .get() here bc once curr is destroyed, still want unique_ptrs defined by next to exist, but we want curr to still be a pointer to Nodes
        // in other words, we want a ptr to move down the Nodes, but not a unique_ptr bc that destroys the next ptrs
        Node* curr = head.get(); // head is a ptr to first Node, this essentially makes curr = Node (but as a pointer)
        while (curr->next != nullptr) {
            curr = (curr->next).get();
        }
        curr->next = std::move(ptr_to_new);
    }
}

// assumes index in bounds?
void LinkedList::add_at_index(std::string name, int index) {
    auto ptr_to_new = std::make_unique<Node>();
    ptr_to_new->name = name;
    if (index == 0) {
        ptr_to_new->next = std::move(head);
        head = std::move(ptr_to_new);
    } else {
        Node* curr = head.get();
        for(int i = 0; i < index-1; i++) {
            curr = (curr->next).get();
        }
        // must set new's next before setting new as next of curr (same with head in if above)
        // works bc prev node still points to curr, which we replace with new
        ptr_to_new->next = std::move(curr->next);
        curr->next = std::move(ptr_to_new);
    }
}

void LinkedList::remove_from_front() {
    if (head == nullptr) {
        return;
    }

    head = std::move(head->next);
}

void LinkedList::remove_from_back() {
    // 0 nodes
    if (head == nullptr) {
        return;
    }

    // 1 node
    if (head->next == nullptr) {
        head = nullptr;
        return;
    }

    // 2+ nodes
    // instructions suggested unique ptr for curr, but doesn't that decouple all the links for the LinkedList?
    // auto curr = std::make_unique<Node>();
    // curr = std::move(head->next);
    // while ((curr->next)->next != nullptr) { // look 2 nodes down
    //     curr = std::move(curr->next);
    // }
    // curr->next = nullptr;

    // doesn't follow exercise 3_2 instructions but works (didn't use a unique ptr for curr)
    Node* curr = head.get(); // ptr to same Node obj that head pts to
    while ((curr->next)->next != nullptr) { // look 2 nodes down
        curr = (curr->next).get();
    }
    // set next Node of 2nd to last node to nullptr, ending list
    // does this preserve the last Node object?
    curr->next = nullptr;
}

// assumes index in bounds?
void LinkedList::remove_at_index(int index) {
    if (head == nullptr) {
        return;
    }

    if (index == 0) {
        head = std::move(head->next);
    }
    else {
        Node* curr = head.get();
        for (int i = 0; i < index - 1; i++) {
            curr = (curr->next).get();
        }
        curr->next = std::move(curr->next->next);
    }
}

void LinkedList::print_names() {
    Node* ptr = head.get();
    while (ptr != nullptr) {
        std::cout << ptr->name << "\t";
        // std::cout << ptr << "\t";
        ptr = ptr->next.get();
    }
    std::cout << std::endl;
    return;
}
