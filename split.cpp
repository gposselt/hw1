/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */
void addToEnd(Node* in, Node* next);

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  //base case, if the in is null there are no more entries in the list
  if ( in == nullptr)
    return;


  Node* toAdd = in;

  in = in->next;

  toAdd->next = nullptr;

  if (toAdd->value % 2 == 0) {// if in is even

    if (evens != nullptr)

      addToEnd(evens, toAdd);
    else
      evens = toAdd;


  }else {// int % 2 is 1 or 0, no need for another if here

    if (odds  != nullptr)
      addToEnd(odds, toAdd);

    else
      odds = toAdd;
  }






  split(in, odds, evens);
}

/* If you needed a helper function, write it here */
void addToEnd(Node* in, Node* toAdd) {

  Node* cur = in;
  while (true ) {
    if (cur ->next == nullptr) {
      break;
    }
    cur = cur -> next;
  }

  cur -> next = toAdd;
}
