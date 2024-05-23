//
// Created by Noah Turnquist on 5/17/24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>

namespace Lists {

    template <typename T> class Node {
    private:
        T data;
        Node* next;
        Node* prev;

    public:
        //Constructors
        explicit Node(T new_data);
        Node();

        //Getters and setters
        [[nodiscard]] Node* get_next() const {return next;}
        [[nodiscard]] Node* get_prev() const {return prev;}
        [[nodiscard]] T get_data() const {return data;}

        void set_next(Node* new_next) {next = new_next;}
        void set_prev(Node* new_prev) {prev = new_prev;}
        void set_data(T new_data) {data = new_data;}
    };

    template<typename T>
    bool operator==(const Node<T>& a, const Node<T>& b) {return a.get_data() == b.get_data();}
    template<typename T>
    bool operator!=(const Node<T>& a, const Node<T>& b) {return a.get_data() != b.get_data();}

    template <typename T> class LinkedList {
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        int sz = 0;

        //Private helper functions
        void helperInsert(Node<T>* prev_node, T new_data);

    public:
        //Constructors
        LinkedList() = default;

        // Copy constructor and operator
         LinkedList(const LinkedList& list);
         LinkedList& operator=(const LinkedList& list);

        //Move Constructor
        LinkedList(LinkedList&& list) noexcept;

        //Getters and setters
        [[nodiscard]] int size() const {return sz;}
        [[nodiscard]] Node<T>* get_head() const {return head;}
        [[nodiscard]] Node<T>* get_tail() const {return tail;}

        //Methods
        bool nodeInList(const Node<T>* target_node);
        Node<T>* findNode(const T& target_data);
        void appendNode(T new_data);
        void insertNode(T new_data);
        void insertNode(Node<T>* prev_node, T new_data);
        void insertNodeBeginning(T new_data);
        void emptyList();

        //Destructor
        ~LinkedList() {emptyList();}
    };

    /* ------------------------------------------------------------------------ */

    template<typename T>
    Node<T>::Node(T new_data)
    :data(new_data), next(nullptr), prev(nullptr) {}

    template<typename T>
    Node<T>::Node()
    :data(NULL), next(nullptr), prev(nullptr) {}

    //Copy constructor
    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList &list) {
        Node<T>* walker = list.get_head();
        while (walker != nullptr) {
            this->appendNode(walker->get_data());
            walker = walker->get_next();
        }
    }

    //Copy operator for LinkedList class
    //Make copies of all nodes in linked list and add those copies to the new list
    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList& list) {
        if (&list != this) {
            this->emptyList();
            Node<T>* walker = list.get_head();
            while (walker != nullptr) {
                this->appendNode(walker->get_data());
                walker = walker->get_next();
            }
        }
        return *this;
    }

    //Move constructor
    template <typename T>
    LinkedList<T>::LinkedList(LinkedList &&list) noexcept
    :head(list.get_head()), tail(list.get_tail()), sz(list.size()) {
        list.sz = 0;
        list.head = nullptr;
        list.tail = nullptr;
    }

    template <typename T>
    bool LinkedList<T>::nodeInList(const Node<T>* target_node) {
        Node<T>* walker = head;
        while (walker != nullptr) {
            if (walker->get_data() == target_node->get_data()) {
                return true;
            }
            walker = walker->get_next();
        }
        return false;
    }

    //Assumes the datatype can be printed
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* walker = list.get_head();
        while (walker != nullptr) {
            os << walker->get_data();
            if (walker != list.get_tail()) {
                os << ' ';
            }
            walker = walker->get_next();
        }
        return os;
    }

    template <typename T>
    Node<T>* LinkedList<T>::findNode(const T& target_data) {
        Node<T>* walker = head;
        while (walker != nullptr) {
            if (walker->get_data() == target_data) {
                return walker;
            }
            walker = walker->get_next();
        }
        return nullptr;
    }

    template <typename T>
    void LinkedList<T>::appendNode(T new_data) {
        Node<T>* new_node = new Node(new_data);

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

    //Private helper node
    template<typename T>
    void LinkedList<T>::helperInsert(Node<T>* prev_node, T new_data) {
        if (sz < 1) {
            throw std::out_of_range("List is empty, can't insert node. Try using .appendNode() instead.");
        }
        Node<T>* new_node = new Node(new_data);

        if (prev_node == nullptr) { //Beginning of list
            Node<T>* next_node = head;
            new_node->set_next(next_node);
            new_node->set_prev(nullptr);
            next_node->set_prev(new_node);
            head = new_node;
        } else if (prev_node->get_next() == nullptr) { //End of list
            new_node->set_next(nullptr);
            new_node->set_prev(prev_node);
            prev_node->set_next(new_node);
            tail = new_node;
        } else { //Somewhere other than beginning or end
            Node<T>* next_node = prev_node->get_next();
            new_node->set_next(next_node);
            new_node->set_prev(prev_node);
            prev_node->set_next(new_node);
            next_node->set_prev(new_node);
        }
    }

    //Insertion with no previous node specified will be considered an append
    template<typename T>
    void LinkedList<T>::insertNode(T new_data) {
        this->appendNode(new_data);
    }

    template<typename T>
    void LinkedList<T>::insertNode(Node<T>* prev_node, T new_data) {
        if (sz < 1) {
            throw std::out_of_range("List is empty, can't insert node. Try using .appendNode() instead.");
        }
        if (nodeInList(prev_node)) {
            helperInsert(prev_node, new_data);
        } else {
            throw std::out_of_range("Previous node could not be found in list");
        }
    }

    template<typename T>
    void LinkedList<T>::insertNodeBeginning(T new_data) {
        helperInsert(nullptr, new_data);
    }

    template <typename T>
    void LinkedList<T>::emptyList() {
        Node<T>* walker = head;
        while (walker != nullptr) {
            Node<T>* link = walker->get_next();
            delete walker;
            walker = link;
        }
        head = nullptr;
        tail = nullptr;
        sz = 0;
    }

    template <typename T>
    bool operator==(const LinkedList<T>& a, const LinkedList<T>& b) {
        if (a.size() != b.size()) {
            return false;
        }
        Node<T>* a_walker = a.get_head();
        Node<T>* b_walker = b.get_head();
        while (a_walker != nullptr && b_walker != nullptr) {
            if (!(*a_walker == *b_walker)) return false;
            a_walker = a_walker->get_next();
            b_walker = b_walker->get_next();
        }
        return true;
    }

    template <typename T>
    bool operator!=(const LinkedList<T>& a, const LinkedList<T>& b) {
        if (a.size() != b.size()) {
            return true;
        }
        Node<T>* a_walker = a.get_head();
        Node<T>* b_walker = b.get_head();
        while (a_walker != nullptr && b_walker != nullptr) {
            if (!(*a_walker == *b_walker)) return true;
            a_walker = a_walker->get_next();
            b_walker = b_walker->get_next();
        }
        return false;
    }

    template <typename T>
    bool operator<(const LinkedList<T>& a, const LinkedList<T>& b) {return a.size() < b.size();}

    template <typename T>
    bool operator<=(const LinkedList<T>& a, const LinkedList<T>& b) {return a.size() <= b.size();}

    template <typename T>
    bool operator>(const LinkedList<T>& a, const LinkedList<T>& b) {return a.size() > b.size();}

    template <typename T>
    bool operator>=(const LinkedList<T>& a, const LinkedList<T>& b) {return a.size() >= b.size();}

}

#endif //LINKED_LIST_H
