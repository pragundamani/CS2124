/*
  Linked list base: the Node type as struct
  26S - Sec C
 */
#include <iostream>
using namespace std;

struct Node {
    int data = 0;
    Node* next = nullptr;
};

/*
  display
  size
  add head, tail, "anywhere"
  remove head, tail, "anywhere"
  clear, duplicate
 */

void listDisplay(const Node* hp) {
    //void listDisplay(Node* hp) {
    //while( hp->next != nullptr) // wrong test
    while (hp != nullptr) {
        cout << hp->data << ' ';
        hp = hp->next;
    }
    cout << endl;
}

void listDisplay2(const Node* hp) {
    //Node* curr = hp;
    const Node* curr = hp;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

Node* listFindTail(Node* hp) {
//Node* listFindTail(const Node* hp) {
//const Node* listFindTail(const Node* hp) {
    if (hp == nullptr) return nullptr;
    while (hp->next != nullptr) {
        hp = hp->next;
    }
    return hp;
}

//void listAddTail(Node* hp, int data) {
void listAddTail(Node*& hp, int data) {
    if (hp == nullptr) {
        hp = new Node{data};
    } else {
        Node* tail = listFindTail(hp);
        tail->next = new Node{data};
    }
}

void listAddHead(Node*& hp, int data) {
    // // Create a node for the data
    // Node* p = new Node{data};

    // // Make the new node "point" to the original head
    // p->next = hp;

    // Node* p = new Node{data, hp};

    // // Set our head pointer to point to the new node
    // hp = p;

    hp = new Node{data, hp};
}

void listRemoveHead(Node*& hp) {
    if (hp == nullptr) return;

    Node* second = hp->next;

    // free up the head
    delete hp;

    // make the head pointer pont to what was the second node
    //hp = hp->next;
    hp = second;

}

int main() {
    Node* myList = nullptr;   // empty list

    myList = new Node{17};   // Singleton

    myList->next = new Node{28}; // Adding to the end

    cout << myList->data << ' ' << myList->next->data << endl;
    listDisplay(myList);
}
