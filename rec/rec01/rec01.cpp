/*
Pragun Damani pd2752
  rec01.cpp
  spring 2026
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
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
    int placeholder = 0;
    string userFile; 
    ifstream fileName;
    cout << "\n enter filename \n";
    cin >> userFile;
    fileName.open(userFile);
    while(!fileName){
        cout << "file not found";
        cin >> userFile;
        fileName.open(userFile);
    }
    cout << "found";
    
    // Task 9 Looping, reading file word by word,
    //        displaying each word as you go
    string word;
    while(fileName >> word){
        cout << "\n" << word << "\n";
    }
    fileName.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    //         Of course, check if the open succeeded
    int sumTotal = 0;
    int currNum = 0;
    ifstream intFile("integers.txt");
    if (!intFile){
        cout << "file not opening";
    }
    while(intFile >> currNum){
        sumTotal = sumTotal + currNum;
    }
    cout << sumTotal << "\n \n";

    // Task 11 Open and read a file of integers and words. Display the sum.
    //         Of course, check if the open succeeded
    sumTotal = 0;
    ifstream mixedFile("mixed.txt");
    if (!mixedFile){
        cout << "file not opening";
    }
    while(mixedFile >> currNum){
        sumTotal = sumTotal + currNum;
    }
    cout << sumTotal;


    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> intVector;
    int countHund = 10;
    while(countHund<101){
        intVector.push_back(countHund);
        countHund++;
    }

    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t ind = 0; ind < sizeof(intVector); ind++){
        cout << "\n" << intVector[ind];
    }

    //         b) using a "ranged for"
    for (int num : intVector){
        cout << "\n" << num;
    }


    //         c) using indices again but backwards
    for (int ind = 90; ind>=0; ind--){
        cout << "\n" << intVector[ind];
    }


    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> primeVector = {2, 3, 5, 7, 11, 13, 17, 19};
    for(int prime:primeVector){
        cout << "\n" << prime;
    }
} // main
