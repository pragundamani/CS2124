/*
 * Pragun Damani
 * rec12.cpp
 * SPring 2026
 */

// Doubly linked list
//  Test code

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
using namespace std;

class List {
  friend ostream &operator<<(ostream &os, const List &rhs);
  struct Node {
    Node *next = nullptr;
    Node *prev = nullptr;
    int data = 0;
  };

public:
  // task 1
  List() {
    sizeList = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
  }
  void push_back(int data) {
    Node *item = new Node;
    item->data = data;
    item->next = tail;
    item->prev = tail->prev;
    tail->prev->next = item;
    tail->prev = item;
    ++sizeList;
  }
  void pop_back() {
    if (sizeList == 0) {
      cerr << "Empty list ";
    }
    Node *prevHold = tail->prev->prev;
    tail->prev->prev->next = tail;
    delete tail->prev;
    tail->prev = prevHold;
    --sizeList;
  }

  int front() const { return head->next->data; }
  int &front() { return head->next->data; }

  int back() const { return tail->prev->data; }
  int &back() { return tail->prev->data; }

  size_t size() const { return sizeList; }

  // Task 2
  void push_front(int data) {
    Node *item = new Node;
    item->data = data;
    item->prev = head;
    item->next = head->next;
    head->next->prev = item;
    head->next = item;
    ++sizeList;
  }
  void pop_front() {
    if (sizeList == 0) {
      cerr << "Empty list ";
    }
    Node *prevHold = head->next->next;
    head->next->next->prev = head;
    delete head->next;
    head->next = prevHold;
    --sizeList;
  }

  void clear() {
    size_t listSize = sizeList;
    for (size_t i = 0; i < listSize; ++i) {
      pop_back();
    }
  }
  // task 3
  int &operator[](size_t index) {
    if (index >= sizeList) {
      cerr << "List smaller than index ";
    }
    Node *trav = head->next;
    for (size_t ind = 0; ind < index; ind++) {
      trav = trav->next;
    }
    return trav->data;
  }
  int operator[](size_t index) const {
    if (index >= sizeList) {
      cerr << "List smaller than index ";
    }
    Node *trav = head->next;
    for (size_t ind = 0; ind < index; ind++) {
      trav = trav->next;
    }
    return trav->data;
  }

  // task 4
  class iterator {
    friend bool operator==(const iterator &lhs, const iterator &rhs) {
      return lhs.loc == rhs.loc;
    }
    friend class List;

    // friend bool operator!=(const List::iterator &lhs,
    //  const List::iterator &rhs);

  public:
    iterator(Node *item) { loc = item; }

    iterator &operator++() {
      loc = loc->next;
      return *this;
    }

    iterator &operator--() {
      loc = loc->prev;
      return *this;
    }

    int &operator*() const { return loc->data; }

  private:
    Node *loc;
  };

  iterator begin() { return iterator(head->next); }
  iterator end() { return iterator(tail); }

  // task 5
  iterator insert(iterator iter, int data) {
    Node *prevItem = iter.loc->prev;
    Node *item = new Node;
    prevItem->next = item;
    item->data = data;
    item->prev = prevItem;
    item->next = iter.loc;
    iter.loc->prev = item;
    ++sizeList;
    return iterator(item);
  }

  // task 6
  iterator erase(iterator iter) {
    Node *prevItem = iter.loc->prev;
    Node *nextItem = iter.loc->next;
    prevItem->next = nextItem;
    nextItem->prev = prevItem;
    delete iter.loc;
    --sizeList;
    return iterator(nextItem);
  }

private:
  Node *head;
  Node *tail;
  size_t sizeList;
};

// Task 1
void printListInfo(const List &myList) {
  cout << "size: " << myList.size() << ", front: " << myList.front()
       << ", back(): " << myList.back() << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
void changeFrontAndBackConst(const List &theList) {
  // theList.front() = 17;
  // theList.back() = 42;
}

void changeFrontAndBack(List &theList) {
  theList.front() = 17;
  theList.back() = 42;
}

// Task 4
void printListSlow(const List &myList) {
  for (size_t i = 0; i < myList.size(); ++i) {
    cout << myList[i] << ' ';
  }
  cout << endl;
}

// Task 8
void doNothing(List aList) {
  cout << "In doNothing\n";
  printListInfo(aList);
  cout << endl;
  cout << "Leaving doNothing\n";
}

// protos
bool operator!=(const List::iterator &lhs, const List::iterator &rhs);

int main() {

  // Task 1
  cout << "\n------Task One------\n";
  List myList;
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    cout << "myList.push_back(" << i * i << ");\n";
    myList.push_back(i * i);
    printListInfo(myList);
  }
  cout << "===================\n";

  cout << "Modify the first and last items, and display the results\n";
  changeFrontAndBack(myList);
  printListInfo(myList);
  cout << "===================\n";

  cout << "Remove the items with pop_back\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.pop_back();
  }
  cout << "===================\n";

  // Task 2
  cout << "\n------Task Two------\n";
  cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    cout << "myList2.push_front(" << i * i << ");\n";
    myList.push_front(i * i);
    printListInfo(myList);
  }

  cout << "===================\n";
  cout << "Remove the items with pop_front\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.pop_front();
  }
  printListInfo(myList);
  cout << "===================\n";

  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i) {
    myList.push_back(i * i);
  }
  printListInfo(myList);
  cout << "Now clear\n";
  myList.clear();
  cout << "Size: " << myList.size() << ", list: " << myList << endl;
  cout << "===================\n";

  // Task 3
  cout << "\n------Task Three------\n";
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  for (int i = 0; i < 10; ++i)
    myList.push_back(i * i);
  cout << "Display elements with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i)
    cout << myList[i] << ' ';
  cout << endl;
  cout << "Add one to each element with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i)
    myList[i] += 1;
  cout << "And print it out again with op[]\n";
  for (size_t i = 0; i < myList.size(); ++i)
    cout << myList[i] << ' ';
  cout << endl;
  cout << "Now calling a function, printListSlow, to do the same thing\n";

  printListSlow(myList);
  cout << "Finally, for this task, using the index operator to modify\n"
       << "the data in the third item in the list\n"
       << "and then using printListSlow to display it again\n";
  myList[2] = 42;
  printListSlow(myList);

  // Task 4
  cout << "\n------Task Four------\n";
  cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i)
    myList.push_back(i * i);
  printListInfo(myList);
  cout << "Now display the elements in a ranged for\n";
  for (int x : myList)
    cout << x << ' ';
  cout << endl;
  cout << "And again using the iterator type directly:\n";
  // Note you can choose to nest the iterator class or not, your choice.
  // for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
  for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    cout << *iter << ' ';
  }
  cout << endl;
  cout << "WOW!!! (I thought it was cool.)\n";

  // Task 5
  cout << "\n------Task Five------\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i)
    myList.insert(myList.end(), i * i);
  printListInfo(myList);
  cout << "Filling an empty list with insert at begin(): "
       << "i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i)
    myList.insert(myList.begin(), i * i);
  printListInfo(myList);
  // ***Need test for insert other than begin/end***
  cout << "===================\n";

  // Task 6
  cout << "\n------Task Six------\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i)
    myList.insert(myList.end(), i * i);
  cout << "Erasing the elements in the list, starting from the beginning\n";
  while (myList.size()) {
    printListInfo(myList);
    myList.erase(myList.begin());
  }
  // ***Need test for erase other than begin/end***
  cout << "===================\n";

  /*
  // Task 7
  cout << "\n------Task Seven------\n";
  cout << "Copy control\n";
  cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
  myList.clear();
  for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
  printListInfo(myList);
  cout << "Calling doNothing(myList)\n";
  doNothing(myList);
  cout << "Back from doNothing(myList)\n";
  printListInfo(myList);

  cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
  List listTwo;
  for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
  printListInfo(listTwo);
  cout << "listTwo = myList\n";
  listTwo = myList;
  cout << "myList: ";
  printListInfo(myList);
  cout << "listTwo: ";
  printListInfo(listTwo);
  cout << "===================\n";
  */
}

ostream &operator<<(ostream &os, const List &rhs) {
  List::Node *out = rhs.head;
  while (out != rhs.tail->prev) {
    out = out->next;
    os << out->data << " - ";
  }
  os << "|";
  return os;
}

bool operator!=(const List::iterator &lhs, const List::iterator &rhs) {
  // return lhs.loc != rhs.loc;
  return !(lhs == rhs);
}
