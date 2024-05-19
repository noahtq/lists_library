#include <iostream>
#include "linked_list.h"

using namespace Lists;

int main() {


    Data sheffler = {1, "Scottie", "Sheffler", "American"};
    Data fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
    Data rahm = {3, "John", "Rahm", "Spanish"};

    {
        LinkedList golfers;
        golfers.appendNode(sheffler);
        golfers.appendNode(fleetwood);
        golfers.appendNode(rahm);

        golfers.emptyList();
    }


    return 0;
}
