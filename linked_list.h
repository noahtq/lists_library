//
// Created by Noah Turnquist on 5/17/24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

namespace Lists {
    struct Data {
        int ranking;
        std::string first_name;
        std::string last_name;
        std::string nationality;
    };

    class Node {
    private:
        Data data;
        Node* next;
        Node* prev;
    public:
        //Constructors
        Node(Data new_data);

        //Getters and setters
        [[nodiscard]] Node* get_next() const {return next;}
        [[nodiscard]] Node* get_prev() const {return prev;}
        [[nodiscard]] Data get_data() const {return data;}

        void set_next(Node* new_next) {next = new_next;}
        void set_prev(Node* new_prev) {prev = new_prev;}
        void set_data(Data new_data) {data = new_data;}
    };

    class LinkedList {
    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int sz = 0;
    public:
        //Constructors
        LinkedList() = default;

        //Getters and setters
        [[nodiscard]] int size() const {return sz;}
        [[nodiscard]] Node* get_head() const {return head;}
        [[nodiscard]] Node* get_tail() const {return tail;}

        //Methods
        void appendNode(Data new_data);
        void emptyList();

        //Destructor
        ~LinkedList() {emptyList();}
    };


}

#endif //LINKED_LIST_H
