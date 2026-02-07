#include <iostream>
using namespace std;
// the main difference between a class and a struct is the default access, structs are public classes are private

// class Date {
//     friend ostream& operator<<(ostream& os, const Date& rhs);
// public:
//     Date(int m, int d, int y): month(m), day(d), year(y) {}
// private:
//     int month, day, year;
// };

// class Person {
//     friend ostream& operator<<(ostream& os, const Person& rhs);
// public:
//     class Date { //this is now publicly listed as a nested class
//         //public nesting is for specifying what particular version of the class is being used in case
//         // there are many
//         friend ostream& operator<<(ostream& os, const Date& rhs);
//         public:
//             Date(int m, int d, int y): month(m), day(d), year(y) {}
//         private:
//             int month, day, year;
//     };

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);

    class Date { //this is now publicly listed as a nested class
        //public nesting is for specifying what particular version of the class is being used in case
        // there are many
        friend ostream& operator<<(ostream& os, const Date& rhs); //{
        //     os << rhs.month << "/" << rhs.day << "/" << rhs.year;
        //     return os;
        // }
        public:
            Date(int m, int d, int y): month(m), day(d), year(y) {}
        private:
            int month, day, year;


    friend ostream& operator<<(ostream& os, const Person::Date& rhs);
    };

    public:

    Person(const string& name , int m, int d, int y)
    : name(name), bday(m,d,y) /*creates a constructor where it takes values from the person init*/
    { }
private:
    string name;
    Person::Date bday; // default constructor called here
    // c++ provides a default constructor if you don't provide one
    // but if you provide any constructor, c++ does not provide a default constructor
};


// what is a default constructor? a constructor that takes no arguments



int main(){
    //Person john("John");
    Person john("John", 2, 4, 2026); //this would still work since it is in person
    cout << john << endl;

    // Person::Date independenceDay(7, 4, 1776); this would not work because is a private class
    // cout << independenceDay << endl;

    return 0;
}

ostream& operator<<(ostream& os, const Person& rhs) {
    os << rhs.name << " born " << rhs.bday;
    return os;
}

// ostream& operator<<(ostream& os, const Date& rhs) {
//     os << rhs.month << "/" << rhs.day << "/" << rhs.year;
//     return os;
// }

//  the :: means scope resolution operator
ostream& operator<<(ostream& os, const Person::Date& rhs) {
    os << rhs.month << "/" << rhs.day << "/" << rhs.year;
    return os;
}
