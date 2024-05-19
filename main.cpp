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
    LinkedList golfer_copy2 = golfers2;
    golfer_copy2.appendNode(fleetwood);
    LinkedList golfers3;
    golfers3.appendNode(sheffler);
    golfers3.appendNode(sheffler);
    golfers3.appendNode(sheffler);

    std::cout << (golfers2 == golfer_copy) << std::endl;
    std::cout << (golfers2 == golfer_copy2) << std::endl;
    std::cout << (golfers2 == golfers3) << std::endl;

    std::cout << (golfers2 != golfer_copy) << std::endl;
    std::cout << (golfers2 != golfer_copy2) << std::endl;
    std::cout << (golfers2 != golfers3) << std::endl;

    return 0;
}
