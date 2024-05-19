//
// Created by Noah Turnquist on 5/17/24.
//

#include "linked_list.h"

Lists::Node::Node(Data new_data)
    :data(new_data), next(nullptr), prev(nullptr) {}

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

//Copy constructor
Lists::LinkedList::LinkedList(const LinkedList &list) {
    Node* walker = list.get_head();
    while (walker != nullptr) {
        this->appendNode(walker->get_data());
        walker = walker->get_next();
    }
}

//Copy operator for LinkedList class
//Make copies of all nodes in linked list and add those copies to the new list
Lists::LinkedList& Lists::LinkedList::operator=(const LinkedList& list) {
    //TODO: once equality operators have been implemented, update this function to check and make sure that no operation is performed if we're assigning the list to itself
    Node* walker = list.get_head();
    while (walker != nullptr) {
        this->appendNode(walker->get_data());
        walker = walker->get_next();
    }
    return *this;
}

//Move constructor
Lists::LinkedList::LinkedList(LinkedList &&list) noexcept
:head(list.get_head()), tail(list.get_tail()), sz(list.size()) {
    list.sz = 0;
    list.head = nullptr;
    list.tail = nullptr;
}

bool Lists::operator==(const Data& a, const Data& b) {
    if (a.ranking != b.ranking) return false;
    if (a.first_name != b.first_name) return false;
    if (a.last_name != b.last_name) return false;
    if (a.nationality != b.nationality) return false;
    return true;
}

bool Lists::operator!=(const Data& a, const Data& b) {
    if (a.ranking != b.ranking) return true;
    if (a.first_name != b.first_name) return true;
    if (a.last_name != b.last_name) return true;
    if (a.nationality != b.nationality) return true;
    return false;
}

bool Lists::operator==(const LinkedList& a, const LinkedList& b) {
    if (a.size() != b.size()) {
        return false;
    }
    Node* a_walker = a.get_head();
    Node* b_walker = b.get_head();
    while (a_walker != nullptr && b_walker != nullptr) {
        if (!(*a_walker == *b_walker)) return false;
        a_walker = a_walker->get_next();
        b_walker = b_walker->get_next();
    }
    return true;
}

bool Lists::operator!=(const LinkedList& a, const LinkedList& b) {
    if (a.size() != b.size()) {
        return true;
    }
    Node* a_walker = a.get_head();
    Node* b_walker = b.get_head();
    while (a_walker != nullptr && b_walker != nullptr) {
        if (!(*a_walker == *b_walker)) return true;
        a_walker = a_walker->get_next();
        b_walker = b_walker->get_next();
    }
    return false;
}

