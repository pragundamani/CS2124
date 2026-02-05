// lec 4 notes

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

// in struct everything is by default public
// in class everything by default is private
class Person {
    // by marking it as a friend we make it same acces rights as a method
    // use friend very sparingly (dont break encapsulation)
    friend ostream& operator<<(ostream& os /*any name*/, const Person& aPerson);
public:
    // Person(const string& aName)/*this spot is called the initialization list*/ {
        //all non primitives are constructed at that point ^^
    //if you dont make an initialization list all non-primitives and contructed

     // Person(const string& aName) : name(aName)/*init list*/{
    //                 init list  \/ is parameter
    Person(const string& name) : name(name){
         //                            /\ compiler searches scope for name (or other variable)
        //no return type on constructors
       // name = aName;

    }

    //a method is a function defined within an object
    void eating() const { //no need to repeat type within method's name like  personEating
        cout << name << " eating\n";
    }
    // void setName(const string& aName){
    //     name = aName;
    // }

    //by putting keyword const compiler knows its safe
    const string& getName() const { return name; } //no compile since called on an immutable object
    // if there is no reason to modify anything within a method mark it is as const
    // its only in methods

private:
    string name;
};

void personEating(const Person& aPerson){
    // cout << aPerson.name << " eating\n";
    cout << aPerson.getName() << " eating\n";
}

//ostream is not copy-able so it is always passed by reference
ostream& operator<<(ostream& os /*any name*/, const Person& aPerson){
    os << "Person: " << aPerson.getName();
    return os;
}

int main(){
   Person john("John");
//   john.name = "John";
//   personEating(john);
//   john.setName("John"); not allowing names to be changed

  //john.personEating(john) the way we would have had to do it
  john.eating();

  personEating(john);

  // Person mary;

  // operator<<(cout, john);
  (cout << john) << endl;

  return 0;
}
