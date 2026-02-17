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


    void operator=(const Thing& rhs){ }

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

int main() {
    simpleFunc();
    return 0;
}

ostream& operator<<(ostream& os, const Thing& rhs){
    os << *(rhs.p);
    return os;
}
