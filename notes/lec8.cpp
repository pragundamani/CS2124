/*
PD
lec8.cpp
Spring 2026
*/

#include <iostream>

using namespace std;

class Thing{
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x) {p = new int(x); }
    void setValue(int val) { *p = val; }
    int getValue() const {return *p; }

    //simple clean up
    // void cleanUp() {delete p;}

    //
    // Copy Control
    //

    //destructor
    ~Thing() {delete p;} //class destructor, deletes memory after use

    //copy constructor
    Thing(const Thing& someOther){
        //p = new int(*someOther.p);
        p = new int(*someOther.p);
    }

    //??? operator=()) return object being called

    //our thing object is responsible for memory on the heap
    //local variables are on the call stack
    //when its on the heap a delete would free it up from the heap

    Thing& operator=(const Thing& rhs){
        //if return type is just Thing it makes a copy
                        //so we return it by reference

        //step0 test for self assignment?
        if (&rhs != this){
            //step1 free up resources
            delete p;  //do not call the destructor
            //step2 allocate and copy (to make deep copy not shallow)
            p = new int(*rhs.p);
            //do not call copy constructor (you will make temp instance)
        }
        //step3 return self
        return *this;
    }

    //difference between assignment operator and copy constructor?
    //copy contstructor intializes a new object that has no data (at first)
    //assignment operator changes the value to something that already has data
    
private:
    int* p;
}; //destructor called at this point

// void doNothing(Thing another){ } creates a copy of Thing object
//                                ^ calls destructor at this point
void doNothing(Thing another) { }

// c++ tries to optimise for speed so when making copy of the object
// it creates a shallow copy which leads to a double delete at the end of initial doNothing()
//img0

void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;
    //memory leak occurs if we don't delete aThing.p from heap
    // aThing.cleanUp();
    doNothing(aThing);

    //copy constructors
    Thing something = aThing;
    Thing something2(aThing);

    something.setValue(28);
    aThing = something;

    //if we follow cout operator
    // operator=(aThing, something)
    aThing.operator=(something); //to reassign it needs to be a method
    //dont worry why
    // img1
}

class Member {
friend ostream& operator<<(ostream& os, const Member& m);
public:
    Member(const string& val) : val(val) {}

    //copy control
    ~Member(){ //the system provides a default constructor unless you write of your own
        //3 phases of destructor
        //phase 1: does what you ask
        //phase 2: at the end of destructor it calls destructors for 
                                     //all the non primitive classes
    }

private:
    string val;
};


int main() {
    simpleFunc();
    return 0;
}

ostream& operator<<(ostream& os, const Thing& rhs){
    os << *(rhs.p);
    return os;
}

ostream& operator<<(ostream& os, const Member& m) {
        os << "Member: " << m.val;
        return os;
    }