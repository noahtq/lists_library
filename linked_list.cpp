//
// Created by Noah Turnquist on 5/17/24.
//

#include "linked_list.h"

Lists::Node::Node(Data new_data)
    : data(new_data), next(nullptr), prev(nullptr) {}

void Lists::LinkedList::appendNode(Data new_data) {
    Node* new_node = new Node(new_data);

    if (!head) {
        head = new_node;
        tail = new_node;
    } else {
        new_node->set_prev(tail);
        tail->set_next(new_node);
        tail = new_node;
    }
    sz++;
}

void Lists::LinkedList::emptyList() {
    Node* walker = head;
    while (walker != nullptr) {
        Node* link = walker->get_next();
        delete walker;
        walker = link;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0;
}

