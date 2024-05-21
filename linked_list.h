//
// Created by Noah Turnquist on 5/17/24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

namespace Lists {

    template <typename T> class Node {
    private:
        T data;
        Node* next;
        Node* prev;
    public:
        //Constructors
        explicit Node(T new_data);

        //Getters and setters
        [[nodiscard]] Node* get_next() const {return next;}
        [[nodiscard]] Node* get_prev() const {return prev;}
        [[nodiscard]] T get_data() const {return data;}

        void set_next(Node* new_next) {next = new_next;}
        void set_prev(Node* new_prev) {prev = new_prev;}
        void set_data(T& new_data) {data = new_data;}
    };

    template<typename T>
    Node<T>::Node(T new_data)
    :data(new_data), next(nullptr), prev(nullptr) {}

    template<typename T>
    bool operator==(const Node<T>& a, const Node<T>& b) {return a.get_data() == b.get_data();}
    template<typename T>
    bool operator!=(const Node<T>& a, const Node<T>& b) {return a.get_data() != b.get_data();}

    template <typename T> class LinkedList {
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        int sz = 0;
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
        void appendNode(T new_data);
        void emptyList();

        //Destructor
        ~LinkedList() {emptyList();}
    };

    //Copy constructor
    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList &list) {
        Node<T>* walker = list.get_head();
        while (walker != nullptr) {
            this->appendNode(walker->get_data());
            walker = walker->get_next();
        }
    }

    // //Copy operator for LinkedList class
    //Make copies of all nodes in linked list and add those copies to the new list
    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList& list) {
        if (&list != this) {
            Node<T>* walker = list.get_head();
            while (walker != nullptr) {
                this->appendNode(walker->get_data());
                walker = walker->get_next();
            }
        }
        return *this;
    }

    // //Move constructor
    template <typename T>
    LinkedList<T>::LinkedList(LinkedList &&list) noexcept
    :head(list.get_head()), tail(list.get_tail()), sz(list.size()) {
        list.sz = 0;
        list.head = nullptr;
        list.tail = nullptr;
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
