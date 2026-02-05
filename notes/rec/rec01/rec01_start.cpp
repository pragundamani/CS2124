/*
  rec01_start.cpp
  fall 2025
*/
#include <iostream>
#include <vector>
using namespace std;

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "hello\n";

    // Task 2  Printing hello ...  Using "using namespace"
    cout << "hello\n";

    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << x;


    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pi = 3.14159;

    cout << sizeof(y) << " bytes for y\n";
    cout << sizeof(z) << " bytes for z\n";
    cout << sizeof(pi) << " bytes for pi\n";

    // Task 5  Attempt to assign the wrong type of thing to a variable
    bool wrongTypeOfThing;
    wrongTypeOfThing = 8;
    // x = "felix";
    // compiletime? my compiler seems to let it go and run the rest of the
    // "sensible" part of code?

    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y>=10) {
        if (y<=20){
            cout << "yes" << y <<"lies in between 10 and 20 \n";
        }
    }
    if (y>=10 || y<=20) cout << "yes" << y << "does lie between 10 and 20 \n";


    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    //    a) First with a for loop
    for (int num = 10; num<21; num++){
        cout << num << " ";
    }
    cout << "\n";
    //    b) Then with a while loop
    int num = 10;
    while (num<21){
        cout << num << " ";
        num++;
    }
    cout << "\n";
    //    c) Finally with a do-while loop
    num = 10;
    do {
        cout << num << " ";
        num++;
    }
    while (num<21);


    // Task 8  Looping to successfully open a file, asking user for the name
    //         When testing, be sure to try providing the wrong name


    // Task 9 Looping, reading file word by word,
    //        displaying each word as you go


    // Task 10 Open a file of integers, read it in, and display the sum.
    //         Of course, check if the open succeeded


    // Task 11 Open and read a file of integers and words. Display the sum.
    //         Of course, check if the open succeeded


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints


    // Task 13 Displaying the vector THREE times
    //         a) using the indices,

    //         b) using a "ranged for"

    //         c) using indices again but backwards


    // Task 14. Initialize a vector with the primes less than 20.


} // main
