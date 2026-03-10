#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Account {
    int id;
    int balance;
};

Account* addAccounts(ifstream& file){
    file.open("Accoutns.txt")
    if (!file){
        cerr << "file not found";
        exit(1);
    }

    string temp;
    int id = 0;
    int bal = 0; 
    int count = 0;
    Account* store[10];
    while (file >> temp){
        file >> id >> temp >> bal;
        store[count] = Account(id, 
    }
} 
