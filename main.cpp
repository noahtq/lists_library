#include <iostream>
#include "linked_list.h"

using namespace Lists;

int main() {


    Data sheffler = {1, "Scottie", "Sheffler", "American"};
    Data fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
    Data rahm = {3, "John", "Rahm", "Spanish"};

    LinkedList golfers;
    golfers.appendNode(sheffler);
    golfers.appendNode(fleetwood);
    golfers.appendNode(rahm);

    LinkedList golfers2 = std::move(golfers);
    LinkedList golfer_copy;
    golfer_copy = golfers2;

    std::cout << golfer_copy.size() << std::endl;

    return 0;
}
