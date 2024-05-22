#include <iostream>

#include "lists.h"

using namespace Lists;

struct Golfer {
    int ranking;
    std::string first_name;
    std::string last_name;
    std::string nationality;
};

bool operator==(const Golfer& a, const Golfer& b) {
    if (a.ranking != b.ranking) return false;
    if (a.first_name != b.first_name) return false;
    if (a.last_name != b.last_name) return false;
    if (a.nationality != b.nationality) return false;
    return true;
}

bool operator!=(const Golfer& a, const Golfer& b) {
    if (a.ranking != b.ranking) return true;
    if (a.first_name != b.first_name) return true;
    if (a.last_name != b.last_name) return true;
    if (a.nationality != b.nationality) return true;
    return false;
}

int main() {

    try {
        Golfer sheffler = {1, "Scottie", "Sheffler", "American"};
        Golfer fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
        Golfer rahm = {3, "John", "Rahm", "Spanish"};

        LinkedList<Golfer> list;
        list.appendNode(sheffler);
        list.appendNode(fleetwood);
        list.appendNode(rahm);

        Node<Golfer>* n = list.get_head();

        LinkedList<Golfer> c_list;
        // c_list.insertNode(n, rahm);
        c_list.insertNode(rahm);

        LinkedList<int> int_list;
        int_list.appendNode(2);
        int_list.appendNode(1);
        int_list.appendNode(5);

        Node<int>* target = int_list.findNode(5);

        int_list.insertNode(target, 7);
        int_list.insertNodeBeginning(8);

        std::cout << int_list << std::endl;
        std::cout << list << std::endl;

        int x = 5;
    } catch (std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
