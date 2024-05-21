#include <iostream>

#include "linked_list.h"

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

    Golfer sheffler = {1, "Scottie", "Sheffler", "American"};
    Golfer fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
    Golfer rahm = {3, "John", "Rahm", "Spanish"};

    LinkedList<Golfer> list;
    list.appendNode(sheffler);
    list.appendNode(fleetwood);
    list.appendNode(rahm);

    LinkedList<Golfer> list2;
    list2.appendNode(sheffler);
    list2.appendNode(rahm);

    std::cout << (list == list2) << std::endl;

    LinkedList<int> int_list;
    int_list.appendNode(2);
    int_list.appendNode(3);
    int_list.appendNode(4);

    LinkedList<int> int_list2;
    int_list2.appendNode(2);
    int_list2.appendNode(3);
    int_list2.appendNode(3);

    std::cout << (int_list == int_list2) << std::endl;

    LinkedList<int> int_list3 = int_list;
    LinkedList<int> int_list4;
    int_list4 = int_list;

    LinkedList<int> int_list5 = std::move(int_list);

    LinkedList<Golfer> golfers2 = std::move(list);
    LinkedList<Golfer> golfers3 = golfers2;
    LinkedList<Golfer> golfers4;
    golfers4 = golfers2;

    return 0;
}
