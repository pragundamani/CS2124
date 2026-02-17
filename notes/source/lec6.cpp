#include <iostream>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);  
public: 
    Person(const string& name) : name(name), spouse(nullptr) { }
    
    bool marries(Person& bethrothed){
        if (spouse == nullptr && bethrothed.spouse == nullptr){
            spouse = &bethrothed;
            bethrothed.spouse = this; //this is a pointer which holds the address
            //a reference is an alias for something a pointer is the memory address
            cout << name << " married " << bethrothed.name << endl;
            return true;
        }
        return false;
    }
    
private:
    string name;
    // bool isMarried;
    // Person spouse; //Cannot have a class that has an instance of itself
    // it becomes a circular dependency that breaks
    // A reference: Person spouse; 
    Person* spouse; //Pointers are primitives so they can be put in
    //1. at the ^ definition 
    //2. in the init list
    //3. in the constructor body 
};

int main() {
    Person john("John");
    Person mary("Mary");
    
    cout << john << endl;
    cout << mary << endl;
    
    int x =17;
    cout << "Where is x?  " << &x << endl;
    int* p = &x;   //c++ style
    // int *q = &x;  //c style
    // int * r = &x;//weird documentation style
    // cout << p << endl << q << endl << r << endl;
   
    //to access something in memory
    // do *p like this
    cout << "Whats in x: " << x << " or " << *p << endl;
    
    // to modify
    *p = 42;
    cout << "Whats in x: " << x << " or " << *p << endl;
    
    //memory addr size
    cout << "size of x: " << sizeof(x) << " size of p: " << sizeof(p) << endl;
    // int is smaller         4 bytes                      8 bytes
    
    // cout << "size of a Person: " << sizeof(john)
         // << " size of addr for Person: " << sizeof(&john) << endl;
         
    //int* q; //undefined
    int* q = nullptr;
    cout << q << endl;
    
    john.marries(mary);
    cout << john << endl;
    cout << mary << endl;
    
    Person sally("Sally");
    sally.marries(john);
    cout << john << endl << sally << endl << mary << endl; 
}

ostream& operator<<(ostream& os, const Person& rhs){
    os << "Name " << rhs.name;
    if (rhs.spouse == nullptr){
        os << "; single;";
    }
    else{
        // os << " Married to " << *(rhs.spouse).name; // works but dont
        os << " Married to " << rhs.spouse->name; 
        //arrow operator is cleaner syntax
    }
    return os;
}