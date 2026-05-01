/*
  Linked list base: the Node type as struct
 */
#include <iostream>
using namespace std;

struct Node {
    int data = 0;
    Node* next = nullptr;
};

void listDisplay(Node* hp) {
    //while( hp->next != nullptr) // wrong test
}

int main() {
    Node* myList = nullptr;   // empty list

    myList = new Node{17};   // Singleton

    myList->next = new Node{28}; // Adding to the end

    cout << myList->data << ' ' << myList->next->data << endl;
    listDisplay(myList);
}
