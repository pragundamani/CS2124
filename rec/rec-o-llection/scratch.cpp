#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int currNum;
    int sumTotal = 0;

    ifstream mixedFile("mixed.txt");

    if (!mixedFile){
        cout << "file not opening";
        return 1;
    }

    while (mixedFile >> currNum){
        cout << "Read: " << currNum << endl;
        sumTotal += currNum;
    }

    cout << "Sum = " << sumTotal << endl;
}
