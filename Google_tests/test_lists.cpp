//
// Created by Noah Turnquist on 5/22/24.
//

#include "gtest/gtest.h"
#include "../lists.h"

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

class LinkedListTest: public testing::Test {
protected:
    void SetUp() override {
        //List 1
        int_list.appendNode(2);
        int_list.appendNode(1);
        int_list.appendNode(5);

        //Same as list 1
        int_list2.appendNode(2);
        int_list2.appendNode(1);
        int_list2.appendNode(5);

        //Shorter than list 1
        int_list3.appendNode(2);
        int_list3.appendNode(1);

        //Same length as list 1 but different elements
        int_list4.appendNode(2);
        int_list4.appendNode(6);
        int_list4.appendNode(5);

        //List 1
        golfer_list.appendNode(sheffler);
        golfer_list.appendNode(fleetwood);
        golfer_list.appendNode(rahm);

        //Same as list 1
        golfer_list2.appendNode(sheffler);
        golfer_list2.appendNode(fleetwood);
        golfer_list2.appendNode(rahm);

        //Shorter than list 1
        golfer_list3.appendNode(sheffler);
        golfer_list3.appendNode(rahm);

        //Same length as list 1 but different elements
        golfer_list4.appendNode(sheffler);
        golfer_list4.appendNode(rahm);
        golfer_list4.appendNode(rahm);
    }

    Lists::LinkedList<int> int_list;
    Lists::LinkedList<int> int_list2;
    Lists::LinkedList<int> int_list3;
    Lists::LinkedList<int> int_list4;

    Lists::LinkedList<Golfer> golfer_list;
    Lists::LinkedList<Golfer> golfer_list2;
    Lists::LinkedList<Golfer> golfer_list3;
    Lists::LinkedList<Golfer> golfer_list4;

    Lists::LinkedList<double> empty_list;

    Golfer sheffler = {1, "Scottie", "Sheffler", "American"};
    Golfer fleetwood = {11, "Tommy", "Fleetwood", "Englist"};
    Golfer rahm = {3, "John", "Rahm", "Spanish"};
    Golfer woods = {100, "Tiger", "Woods", "American"};
};

/*
Test the default constructor for linkedlist template, also tests getter
methods as those are needed to get the values of the instance variables
*/
TEST_F(LinkedListTest, LinkedListDefaultConstructorTestAndGetterTest) {
    const Lists::LinkedList<double> double_list;
    ASSERT_EQ(double_list.get_head(), nullptr);
    ASSERT_EQ(double_list.get_tail(), nullptr);
    ASSERT_EQ(double_list.size(), 0);
}

/*
Test the LinkedList template equal and not equal operators
The operators should return true if the lists are the same length
 and all nodes in the same positions are equal.
The not equal operator should be the logical opposite.
*/
TEST_F(LinkedListTest, LinkedListTestEqualityOperators) {
    //Check equal lists are equal
    ASSERT_TRUE(int_list == int_list2);
    ASSERT_TRUE(golfer_list == golfer_list2);

    //Check a shorter list with same elements return false
    ASSERT_FALSE(int_list == int_list3);
    ASSERT_FALSE(golfer_list == golfer_list3);

    //Check same length list with different elements returns false
    ASSERT_FALSE(int_list == int_list4);
    ASSERT_FALSE(golfer_list == golfer_list4);
}

/*
Test comparison operators for linked list
Should only be comparing size of the list (i.e number of nodes)
and not be concerned with what is in the nodes or the type
*/
TEST_F(LinkedListTest, LinkedListTestComparisonOperators) {
    ASSERT_TRUE(int_list > int_list3);
    ASSERT_FALSE(int_list3 > int_list);

    ASSERT_TRUE(int_list >= int_list3);
    ASSERT_FALSE(int_list3 >= int_list);
    ASSERT_TRUE(int_list >= int_list4);

    ASSERT_FALSE(int_list < int_list3);
    ASSERT_TRUE(int_list3 < int_list);

    ASSERT_FALSE(int_list <= int_list3);
    ASSERT_TRUE(int_list3 <= int_list);
    ASSERT_TRUE(int_list <= int_list4);
}

/*
Test the copy constructor
We have already established an invariant with the above
equality tests that the equality operators work
therefore we can use those to ensure the two lists are
equal or not equal.
To make sure we are copying and not referencing or moving
we also check that the memory addresses of some nodes
aren't equal.
*/
TEST_F(LinkedListTest, LinkedListTestCopyConstructor) {
    Lists::LinkedList<int> int_copy = int_list;
    Lists::LinkedList<Golfer> golfer_copy = golfer_list;

    ASSERT_TRUE(int_copy == int_list);
    ASSERT_TRUE(golfer_copy == golfer_list);

    //Compare addresses of head nodes and make sure they are not equal
    ASSERT_NE(int_copy.get_head(), int_list.get_head());
    ASSERT_NE(golfer_copy.get_head(), golfer_list.get_head());
 }

/*
Test the copy operator
Should behave in same way as copy constructor except it should
also remove and overwrite nodes that were already in list
being copied to.
*/
TEST_F(LinkedListTest, LinkedListTestCopyOperator) {
    Lists::LinkedList<int> int_copy;
    int_copy.appendNode(10);
    int_copy = int_list;
    Lists::LinkedList<Golfer> golfer_copy;
    golfer_copy.appendNode(sheffler);
    golfer_copy = golfer_list;

    ASSERT_TRUE(int_copy == int_list);
    ASSERT_TRUE(golfer_copy == golfer_list);

    //Compare addresses of head nodes and make sure they are not equal
    ASSERT_NE(int_copy.get_head(), int_list.get_head());
    ASSERT_NE(golfer_copy.get_head(), golfer_list.get_head());
}

/*
 Test move constructor
 Should move all of the nodes to a new list in the same order.
 The old list should be uninitialized (set to default).
 The address of the nodes in the new list should match the old list
 as nodes should be in the same memory location on the heap.
 */
TEST_F(LinkedListTest, LinkedListTestMoveConstructor) {
    //Save addresses of head nodes to make sure they aren't changed when moved
    auto int_head_addr = reinterpret_cast<uintptr_t>(int_list.get_head());
    auto golfer_head_addr = reinterpret_cast<uintptr_t>(golfer_list.get_head());

    //Make copies of lists so we can make sure the data in the lists
    //are identical
    const Lists::LinkedList<int> int_copy = int_list;
    const Lists::LinkedList<Golfer> golfer_copy = golfer_list;

    const Lists::LinkedList<int> int_move = std::move(int_list);
    const Lists::LinkedList<Golfer> golfer_move = std::move(golfer_list);

    ASSERT_TRUE(int_move == int_copy);
    ASSERT_TRUE(golfer_move == golfer_copy);

    ASSERT_EQ(int_list.get_head(), nullptr);
    ASSERT_EQ(int_list.get_tail(), nullptr);
    ASSERT_EQ(int_list.size(), 0);

    ASSERT_EQ(reinterpret_cast<uintptr_t>(int_move.get_head()), int_head_addr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(golfer_move.get_head()), golfer_head_addr);
}

/*
Test the node in list method - argument is node pointer
Should return true if there is a node in the list with the same data
Otherwise return false
*/
TEST_F(LinkedListTest, LinkedListTestNodeInListMethod) {
    Lists::Node<int> int_first(2);
    Lists::Node<int>* int_first_p = &int_first;
    Lists::Node<int> int_middle(1);
    Lists::Node<int>* int_middle_p = &int_middle;
    Lists::Node<int> int_last(5);
    Lists::Node<int>* int_last_p = &int_last;
    Lists::Node<int> int_not_in_list(10);
    Lists::Node<int>* int_not_in_list_p = &int_not_in_list;

    Lists::Node<Golfer> golfer_first(sheffler);
    Lists::Node<Golfer>* golfer_first_p = &golfer_first;
    Lists::Node<Golfer> golfer_middle(fleetwood);
    Lists::Node<Golfer>* golfer_middle_p = &golfer_middle;
    Lists::Node<Golfer> golfer_last(rahm);
    Lists::Node<Golfer>* golfer_last_p = &golfer_last;
    Lists::Node<Golfer> golfer_not_in_list(woods);
    Lists::Node<Golfer>* golfer_not_in_list_p = &golfer_not_in_list;

    ASSERT_TRUE(int_list.nodeInList(int_first_p));
    ASSERT_TRUE(int_list.nodeInList(int_middle_p));
    ASSERT_TRUE(int_list.nodeInList(int_last_p));
    ASSERT_FALSE(int_list.nodeInList(int_not_in_list_p));

    ASSERT_TRUE(golfer_list.nodeInList(golfer_first_p));
    ASSERT_TRUE(golfer_list.nodeInList(golfer_middle_p));
    ASSERT_TRUE(golfer_list.nodeInList(golfer_last_p));
    ASSERT_FALSE(golfer_list.nodeInList(golfer_not_in_list_p));

    //Test with an empty list
    Lists::Node<double> d(5.5);
    Lists::Node<double>* d_p = &d;

    ASSERT_FALSE(empty_list.nodeInList(d_p));
}

//Test the insertion operator <<
//TODO: Write this test

/*
Test find node method - find node by target data
Should return a pointer to the first node in list with the target data
Should return nullptr if no node with that data exists
*/
TEST_F(LinkedListTest, LinkedListTestFindNodeMethod) {
    Lists::Node<int>* int_first = int_list.findNode(2);
    const int first = int_first->get_data();
    Lists::Node<int>* int_middle = int_list.findNode(1);
    const int middle = int_middle->get_data();
    Lists::Node<int>* int_last = int_list.findNode(5);
    const int last = int_last->get_data();
    Lists::Node<int>* int_not_in_list = int_list.findNode(-2);

    Lists::Node<Golfer>* golfer_first = golfer_list.findNode(sheffler);
    const std::string name_first = golfer_first->get_data().first_name;
    Lists::Node<Golfer>* golfer_middle = golfer_list.findNode(fleetwood);
    const std::string name_middle = golfer_middle->get_data().first_name;
    Lists::Node<Golfer>* golfer_last = golfer_list.findNode(rahm);
    const std::string name_last = golfer_last->get_data().first_name;
    Lists::Node<Golfer>* golfer_not_in_list = golfer_list.findNode(woods);

    ASSERT_EQ(first, 2);
    ASSERT_EQ(middle, 1);
    ASSERT_EQ(last, 5);
    ASSERT_EQ(int_not_in_list, nullptr);

    ASSERT_EQ(name_first, "Scottie");
    ASSERT_EQ(name_middle, "Tommy");
    ASSERT_EQ(name_last, "John");
    ASSERT_EQ(golfer_not_in_list, nullptr);

    //Test with empty list
    Lists::Node<double>* d = empty_list.findNode(5.5);
    ASSERT_EQ(d, nullptr);
}

/*
Test AppendNode method
Test with an already filled list and an empty list
Iterate over the list forward and backward to make sure
both the prev and next links are set correctly
*/
TEST_F(LinkedListTest, LinkedListTestAppendNode) {

    //Append to already filled lists

    int_list.appendNode(11);

    const int int_size = int_list.size();
    ASSERT_EQ(int_size, 4);

    constexpr int int_expected_values[] = {2, 1, 5, 11};
    const Lists::Node<int>* walker = int_list.get_head();
    for (int i = 0; i < 4; i++) {
        int node_data = walker->get_data();
        ASSERT_EQ(node_data, int_expected_values[i]);
        walker = walker->get_next();
    }

    walker = int_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        int node_data = walker->get_data();
        ASSERT_EQ(node_data, int_expected_values[i]);
        walker = walker->get_prev();
    }

    golfer_list.appendNode(woods);
    const int golfer_size = golfer_list.size();
    ASSERT_EQ(golfer_size, 4);

    const Golfer golfer_expected_values[] = {sheffler, fleetwood, rahm, woods};
    const Lists::Node<Golfer>* golf_walker = golfer_list.get_head();
    for (int i = 0; i < 4; i++) {
        Golfer node_data = golf_walker->get_data();
        ASSERT_TRUE(node_data == golfer_expected_values[i]);
        golf_walker = golf_walker->get_next();
    }

    golf_walker = golfer_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        Golfer node_data = golf_walker->get_data();
        ASSERT_TRUE(node_data == golfer_expected_values[i]);
        golf_walker = golf_walker->get_prev();
    }

    //Append to empty list

    empty_list.appendNode(6.7);
    int empty_size = empty_list.size();
    ASSERT_EQ(empty_size, 1);

    Lists::Node<double>* empty_head = empty_list.get_head();
    Lists::Node<double>* empty_tail = empty_list.get_tail();

    ASSERT_DOUBLE_EQ(empty_head->get_data(), 6.7);
    ASSERT_DOUBLE_EQ(empty_tail->get_data(), 6.7);
    ASSERT_EQ(empty_head->get_next(), nullptr);
    ASSERT_EQ(empty_head->get_prev(), nullptr);
}

/*
Testing insertNode method - no node parameter just new_data
Should behave the same as appendNode
*/
TEST_F(LinkedListTest, LinkedListTestInsertNodeNoNodeParameter) {
    //Insert to already filled lists

    int_list.insertNode(11);

    const int int_size = int_list.size();
    ASSERT_EQ(int_size, 4);

    constexpr int int_expected_values[] = {2, 1, 5, 11};
    const Lists::Node<int>* walker = int_list.get_head();
    for (int i = 0; i < 4; i++) {
        int node_data = walker->get_data();
        ASSERT_EQ(node_data, int_expected_values[i]);
        walker = walker->get_next();
    }

    walker = int_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        int node_data = walker->get_data();
        ASSERT_EQ(node_data, int_expected_values[i]);
        walker = walker->get_prev();
    }

    golfer_list.insertNode(woods);
    const int golfer_size = golfer_list.size();
    ASSERT_EQ(golfer_size, 4);

    const Golfer golfer_expected_values[] = {sheffler, fleetwood, rahm, woods};
    const Lists::Node<Golfer>* golf_walker = golfer_list.get_head();
    for (int i = 0; i < 4; i++) {
        Golfer node_data = golf_walker->get_data();
        ASSERT_TRUE(node_data == golfer_expected_values[i]);
        golf_walker = golf_walker->get_next();
    }

    golf_walker = golfer_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        Golfer node_data = golf_walker->get_data();
        ASSERT_TRUE(node_data == golfer_expected_values[i]);
        golf_walker = golf_walker->get_prev();
    }

    //Insert to empty list

    empty_list.insertNode(6.7);
    int empty_size = empty_list.size();
    ASSERT_EQ(empty_size, 1);

    Lists::Node<double>* empty_head = empty_list.get_head();
    Lists::Node<double>* empty_tail = empty_list.get_tail();

    ASSERT_DOUBLE_EQ(empty_head->get_data(), 6.7);
    ASSERT_DOUBLE_EQ(empty_tail->get_data(), 6.7);
    ASSERT_EQ(empty_head->get_next(), nullptr);
    ASSERT_EQ(empty_head->get_prev(), nullptr);
}

/*
Test insert node method - function overload with prev_node parameter
*/
TEST_F(LinkedListTest, LinkedListTestInsertNodePrevNodeParameter) {
    //Should throw exception if list is empty since we know the prev_node
    //can't be found in an empty list
    Lists::Node prev_double(5.5);
    Lists::Node<double>* prev_double_p = &prev_double;
    ASSERT_THROW(empty_list.insertNode(prev_double_p, 21.1), std::out_of_range);

    //Should throw out_of_range error if the previous node is not in list
    //This is on a list with some nodes already
    Lists::Node prev_int(18);
    Lists::Node<int>* prev_int_p = &prev_int;
    Lists::Node prev_golfer(woods);
    Lists::Node<Golfer>* prev_golfer_p = &prev_golfer;

    ASSERT_THROW(int_list.insertNode(prev_int_p, 27), std::out_of_range);
    ASSERT_THROW(golfer_list.insertNode(prev_golfer_p, sheffler), std::out_of_range);

    //Test inserting at end of list - again iterating over each list
    //forward and backward to make sure all links were setup correctly
    Lists::Node<int>* real_prev_int = int_list.findNode(5);
    Lists::Node<Golfer>* real_prev_golfer = golfer_list.findNode(rahm);

    int_list.insertNode(real_prev_int, 17);
    golfer_list.insertNode(real_prev_golfer, woods);

    int int_expected_values[] = {2, 1, 5, 17};
    Lists::Node<int>* int_walker = int_list.get_head();
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values[i]);
        int_walker = int_walker->get_next();
    }

    int_walker = int_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values[i]);
        int_walker = int_walker->get_prev();
    }

    Golfer golfer_expected_values[] = {sheffler, fleetwood, rahm, woods};
    Lists::Node<Golfer>* golfer_walker = golfer_list.get_head();
    for (int i = 0; i < 4; i++) {
        ASSERT_TRUE(golfer_walker->get_data() == golfer_expected_values[i]);
        golfer_walker = golfer_walker->get_next();
    }

    golfer_walker = golfer_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        ASSERT_EQ(golfer_walker->get_data(), golfer_expected_values[i]);
        golfer_walker = golfer_walker->get_prev();
    }

    //Inserting into middle of list
    Lists::Node<int>* middle_int_node = int_list.findNode(1);
    Lists::Node<Golfer>* middle_golfer_node = golfer_list.findNode(fleetwood);

    int_list.insertNode(middle_int_node, -5);
    golfer_list.insertNode(middle_golfer_node, sheffler);

    int int_expected_values_middle[] = {2, 1, -5, 5, 17};
    int_walker = int_list.get_head();
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values_middle[i]);
        int_walker = int_walker->get_next();
    }

    int_walker = int_list.get_tail();
    for (int i = 4; i >= 0; i--) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values_middle[i]);
        int_walker = int_walker->get_prev();
    }

    Golfer golfer_expected_values_middle[] = {sheffler, fleetwood, sheffler, rahm, woods};
    golfer_walker = golfer_list.get_head();
    for (int i = 0; i < 5; i++) {
        ASSERT_TRUE(golfer_walker->get_data() == golfer_expected_values_middle[i]);
        golfer_walker = golfer_walker->get_next();
    }

    golfer_walker = golfer_list.get_tail();
    for (int i = 4; i >= 0; i--) {
        ASSERT_EQ(golfer_walker->get_data(), golfer_expected_values_middle[i]);
        golfer_walker = golfer_walker->get_prev();
    }
}

/*
Test insert node beginning. Should insert a node at the beginning of list
Only takes one parameter which is the data to be inserted
Should throw error if list is empty and suggest using an append instead.
*/
TEST_F(LinkedListTest, LinkedListTestInsertNodeBeginning) {
    //Empty list, should throw out_of_range exception
    ASSERT_THROW(empty_list.insertNodeBeginning(2.75), std::out_of_range);

    //Test with already filled lists
    int_list.insertNodeBeginning(10);
    golfer_list.insertNodeBeginning(woods);

    int int_expected_values[] = {10, 2, 1, 5};
    Lists::Node<int>* int_walker = int_list.get_head();
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values[i]);
        int_walker = int_walker->get_next();
    }

    int_walker = int_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        ASSERT_EQ(int_walker->get_data(), int_expected_values[i]);
        int_walker = int_walker->get_prev();
    }

    Golfer golfer_expected_values[] = {woods, sheffler, fleetwood, rahm};
    Lists::Node<Golfer>* golfer_walker = golfer_list.get_head();
    for (int i = 0; i < 4; i++) {
        ASSERT_TRUE(golfer_walker->get_data() == golfer_expected_values[i]);
        golfer_walker = golfer_walker->get_next();
    }

    golfer_walker = golfer_list.get_tail();
    for (int i = 3; i >= 0; i--) {
        ASSERT_EQ(golfer_walker->get_data(), golfer_expected_values[i]);
        golfer_walker = golfer_walker->get_prev();
    }
}

/*
Test the empty list method
Should deallocate memory from heap being used for the nodes
and should reset list to default
*/
TEST_F(LinkedListTest, LikedListTestEmptyListMethod) {
    Lists::Node<int>* int_head = int_list.get_head();
    Lists::Node<int>* int_tail = int_list.get_tail();

    Lists::Node<Golfer>* golfer_head = golfer_list.get_head();
    Lists::Node<Golfer>* golfer_tail = golfer_list.get_tail();

    int int_prev_data_head = int_head->get_data();
    int int_prev_data_tail = int_tail->get_data();

    Golfer golfer_prev_data_head = golfer_head->get_data();
    Golfer golfer_prev_data_tail = golfer_tail->get_data();

    empty_list.emptyList();
    int_list.emptyList();
    golfer_list.emptyList();

    int int_now_data_head = int_head->get_data();
    int int_now_data_tail = int_tail->get_data();

    Golfer golfer_now_data_head = golfer_head->get_data();
    Golfer golfer_now_data_tail = golfer_tail->get_data();

    //Check for memory leaks - not the most elegant way of checking for memory
    //leaks but it's the best solution right now as MacOS doesn't have a lot
    //of memory leak checking options
    ASSERT_NE(int_prev_data_head, int_now_data_head);
    ASSERT_NE(int_prev_data_tail, int_now_data_tail);

    ASSERT_FALSE(golfer_prev_data_head == golfer_now_data_head);
    ASSERT_FALSE(golfer_prev_data_tail == golfer_now_data_tail);

    //Check that lists were reset
    ASSERT_EQ(empty_list.get_head(), nullptr);
    ASSERT_EQ(empty_list.get_tail(), nullptr);
    ASSERT_EQ(empty_list.size(), 0);

    ASSERT_EQ(int_list.get_head(), nullptr);
    ASSERT_EQ(int_list.get_tail(), nullptr);
    ASSERT_EQ(int_list.size(), 0);

    ASSERT_EQ(golfer_list.get_head(), nullptr);
    ASSERT_EQ(golfer_list.get_tail(), nullptr);
    ASSERT_EQ(golfer_list.size(), 0);
}