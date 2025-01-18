/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>


#include "split.h"

// #define DEBUG

void printList(Node*& list);

Node* makeList(int*& input, int n);

void deleteList(Node*& input);

std::vector<int> intVecFromList(Node*& in);

int main(int argc, char* argv[])
{
    // int* test = new int[6] {5, 4, 3, 2, 1, 0};
    //
    // Node* list = makeList(test, 6);
    //
    // Node* odd;
    // Node* even = odd = nullptr;

#ifdef DEBUG
    printList(list);
    std::cout << "list" << std::endl;

#endif

    // split(list, odd, even);

#ifdef DEBUG

    printList(odd);
    std::cout << "odd" << std::endl;
    printList(even);
    std::cout << "even" << std::endl;


    printList(list);
    std::cout << "main list" << std::endl;
#endif

    // delete [] test;
    //
    // deleteList(list);
    // deleteList(odd);
    // deleteList(even);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



TEST(SplitTests, allEmpty)
{

    Node* inList = nullptr;

    Node* odds = nullptr;
    Node* evens = nullptr;

    split(inList, odds, evens);

    std::vector<int> emptyVec;

    std::vector<int> oddsVec = intVecFromList(odds);
    std::vector<int> evensVec = intVecFromList(evens);



    ASSERT_EQ(oddsVec, emptyVec) << "Odds are not empty!";
    ASSERT_EQ(evensVec, emptyVec) << "Evens are not empty!";


}

TEST(SplitTests, noEvens) {
    Node* inList = nullptr;

    int* listWithNoEvens = new int[4]{1, 3, 5, 7};

    inList = makeList(listWithNoEvens, 4);

    Node* odds = nullptr;
    Node* evens = nullptr;

    split(inList, odds, evens);


    ASSERT_EQ(evens, nullptr) << "No evens were found!";
    ASSERT_NE(odds, nullptr) << "There were odds!";


    deleteList(inList);
    deleteList(odds);
    deleteList(evens);
    delete [] listWithNoEvens;


}




void printList(Node*& in) {
    std::cout << "[";
    int index = 0;

    Node* list = in;

    while (list != nullptr) {
        std::cout << "i:" << index << " v:" << list->value;

        if (list->next != nullptr) {
            std::cout << ", ";
        }

        index++;
        list = list->next;
    }
    std::cout << "]" << std::endl;
}

Node* makeList(int*& input, int n) {

    Node* head = new Node(input[0], nullptr);

    Node* cur = head;
    for (int i = 1; i < n; i++) {
        Node* next = new Node(input[i], nullptr);
        cur -> next = next;
        cur = cur -> next;
    }

    return head;
}

std::vector<int> intVecFromList(Node*& in) {

    std::vector<int> returnVec;

    Node* cur = in;
    while (true) {
        if (cur == nullptr) {
            break;
        }

        returnVec.push_back(cur->value);
        cur = cur -> next;
    }

    return returnVec;
}


void deleteList(Node*& input) {

    Node* cur = input;
    while (cur != nullptr) {
        Node* next = cur -> next;
        delete cur;
        cur = next;
    }

}

