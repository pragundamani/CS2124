#include <iostream>
using namespace std;

struct Node{
    int data = 0;
    Node* next = nullptr;
};

void listDisplay(const Node* hp){ //const prevents modifications
    //while(hp->next != nullptr) //wrong test
    while(hp != nullptr){
        cout << hp->data << " -> ";
        hp = hp->next;
    }
    cout << endl;
}

void listDisplay2(const Node* hp){
    const Node* curr = hp;
    while(curr != nullptr){
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

Node* listFindTail(Node* hp){
    while (hp == nullptr || hp-> next != nullptr){
        hp = hp->next;
    }
    return hp;
}

void listAddTail(Node* hp, int data){
    Node* tail = listFindTail(hp);
    tail->next = new Node{data};
}

void listAddHead(Node*& hp, int data){
    //step 1 create node for data
    Node* p = new Node{data};
    
    //step 2 make new node point to original head
    p->next = hp;
    
    //step 3 set head poitner to point to new node
    hp = p;
}

void listRemoveHead(Node*& hp){
    
}

int main(){
    Node* mylist = nullptr; //empty lsit being created
    
    mylist = new Node{17}; //singleton

    mylist->next = new Node{28}; //Adding to end
    
    Node* thelist = nullptr;
    listDisplay(mylist);
    //listDisplay(thelist);
}
