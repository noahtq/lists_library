#include <iostream>
#include "linked_list.h"

using namespace Lists;

int main() {


    Data sheffler = {1, "Scottie", "Sheffler", "American"};
    Data fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
    Data rahm = {3, "John", "Rahm", "Spanish"};

    LinkedList golfer_copy;
    {
        LinkedList golfers;
        golfers.appendNode(sheffler);
        golfers.appendNode(fleetwood);
        golfers.appendNode(rahm);

        golfer_copy = golfers;

        LinkedList golfer_copy2(golfers);
        int a = 3;
        ;
    }


    return 0;
}
