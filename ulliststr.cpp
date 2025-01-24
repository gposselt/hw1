#include <cstddef>
#include <stdexcept>
#include <cmath>
#include "ulliststr.h"

#include <memory>

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

std::string const& ULListStr::back() const {

  return this->tail_->val[this->tail_->last - 1];
}

std::string const& ULListStr::front() const {

  return this->head_->val[this->head_->first];
}



void ULListStr::push_back(const std::string& val) {


  this->size_ += 1;


  //if there is space, put it in the existing tail item
  if (this->tail_ != nullptr && this->tail_->last < ARRSIZE) {

    size_t lastIndex = this->tail_->last;
    this->tail_->val[lastIndex] = val;
    this->tail_->last += 1;

    return;
  }

  Item* newLast = new Item;

  //add the val to the list
  newLast->val[0] = val;
  newLast->last += 1;

  if (this->tail_ == nullptr && this->head_ == nullptr) {
    this->tail_ = this->head_ = newLast;

    return;
  }
  //                         this is always true, just here for readability
  if (this->tail_ == nullptr /* && this->head_ != nullptr*/) {
    //this will only happen if the end of the list was not properly updated, and here mostly to make the compiler happy
    this->tail_ = this->head_;
  }

  //update pointers in Item objects
  newLast->prev = this->tail_;
  newLast->next = nullptr;
  this->tail_->next = newLast;

  //update tail pointer in the List object
  this->tail_ = newLast;
}

void ULListStr::pop_back() {
  //nothing to return
  if (this->tail_ == nullptr && this->head_ == nullptr) {
    return;
  }

  //                         this is always true, just here for readability
  if (this->tail_ == nullptr /* && this->head_ != nullptr*/) {
    this->tail_ = this->head_;
  }

  //handle empty last item
  if (this->tail_->last == 0 || this->tail_->last == this->tail_->first) {
    auto tail = this->tail_;

    tail->prev->next = nullptr;
    this->tail_ = tail->prev;

    delete tail;
  }

  size_t newBack = this->tail_->last - 1;
  this->tail_->val[newBack] = std::string();
  this->tail_->last = newBack;

  this->size_ -= 1;


}

void ULListStr::push_front(const std::string& val) {

  //we ***ARE*** adding to the list, so we can increment size in front
  this->size_ += 1;

  //nothing in the list yet, add a new element to add things to
  if (this->head_ == nullptr && this->tail_ == nullptr) {
    this->head_ = this->tail_ = new Item;
  }

  //                         this is always true, just here so I remember
  if (this->head_ == nullptr /* && this->tail_ != nullptr*/) {
    this->head_ = this->tail_;
  }

  auto head = this->head_;

  // bool nextItemHasSpace = head->next != nullptr &&

  //delete empty items and make sure there is space to put the value in the new head
  if (head->first == head->last && (head->next != nullptr && head->next->first != 0)) {

    head->next->prev = nullptr;
    this->head_ = head->next;

    delete head;
    head = this->head_;
  }

  //make new head if there is no space in current head
  if (head->first == 0 && head->last != 0) {

    auto newHead = new Item;

    newHead->next = head;
    head->prev = newHead;

    this->head_ = head = newHead;
  }



  //add to the end
  if (head->last == 0 && head->first == 0) {
    head->last = ARRSIZE;
    head->first = ARRSIZE - 1;
    head->val[head->first] = val;
    return;
  }

  if (head->first != 0) {
    head->first = head->first - 1;
    head->val[head->first] = val;
    return;
  }

}

void ULListStr::pop_front() {

  if (this->head_ == nullptr && this->tail_ == nullptr) {
    return;
  }

  this->size_ -= 1;

  if (this->head_ == nullptr) {
    this->head_ = this->tail_;
  }

  auto head = this->head_;

  if (head->first == head->last && head->last != 0 && head->next != nullptr) {

    this->head_ = head->next;
    head_->next->prev = nullptr;

    delete head;

    head = this->head_;

  }

  head->val[head->first] = std::string();

  head->first += 1;



}


std::string* ULListStr::getValAtLoc(size_t loc) const {

  if (this->tail_ == nullptr && this->head_ == nullptr) {
    return nullptr;
  }

  if (loc >= this->size_) {
    return nullptr;
  }

  //we could want to iterate backwards because it will be faster
  if (loc > this->size_/2 + 1) {

    //iterationVariable is the index of the last item in the array
    size_t iterationVariable = this->size_;
    Item* currentItem = this->tail_;

    if (!currentItem) {
      return nullptr;
    }

    iterationVariable -= currentItem->last - currentItem->first;

    while (true) {

      if (iterationVariable <= loc) {
        return currentItem->val + currentItem->first + (loc - iterationVariable)/* - 1*/;
      }

      currentItem = currentItem->prev;
      iterationVariable -= currentItem->last - currentItem->first;


    }

  }else {
    size_t iterationVariable = 0;
    Item* currentItem = this->head_;
    while (true) {

      if (iterationVariable + (currentItem->last - currentItem->first) > loc) {
        return currentItem->val + (currentItem->first + (loc - iterationVariable));
      }

      iterationVariable += currentItem->last - currentItem->first;
      currentItem = currentItem->next;

    }
  }


  // }

}


//not my code anymore

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


