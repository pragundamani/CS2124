/*
 Pragun Damani: pd2752
 hw01.cpp
 Spring 2026
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//prototypes
char decryptChar(char Encrypted, int key);
void decryptString(string& s, int key);
int fileRead(vector<string>& encryptedStrings);
void printDecrypted(const vector<string>& encryptedStrings);

int main(){
    vector<string> encryptedStrings; //init strings vector
    int key = fileRead(encryptedStrings); //store key from txt file

    //init for loop through vector decided not to use
    // since ranged for works
    // for(size_t index = 0; index<encryptedStrings.size(); index++){
        // cout << encryptedStrings[index];
        // decryptString(encryptedStrings[index], key);
    // }

    //using ranged for since index is not needed
    for (string& stringToDecrypt : encryptedStrings){
        // cout << stringToDecrypt;
        decryptString(stringToDecrypt, key);
    }

    printDecrypted(encryptedStrings);

    return 0; 
}

//using int as const to not change
char decryptChar(char encryptedChar, const int key){
    char returnChar = encryptedChar; //init return var

    if (encryptedChar>='A' && encryptedChar <= 'Z'){
        //queue logic wrap
        //(current - shift + len)%len and using 'A' to convert char <-> num
        returnChar = 'A' + (encryptedChar - 'A' - key + 26) % 26;
        // cout << returnChar;
    }
    return returnChar;
}

//using int as const to not change
void decryptString(string& encryptedString, const int key){ 
    //for loop to go through each char
    for(char& encryptedChar: encryptedString){
        encryptedChar = decryptChar(encryptedChar, key);
    }
    // cout << encryptedString;
}

int fileRead(vector<string>& encryptedStrings){
    ifstream encrypted("encrypted.txt"); //file to read
    int key = 0; //created var key
    string fileLine; //created temp var for string storage
    if (!encrypted){
        cerr << "file not opened";
        exit(1);
    }
    encrypted >> key; //put the key from encrypted into the var
    // cout << key;
    while(getline(encrypted,fileLine)){
        encryptedStrings.push_back(fileLine);
        // cout << fileLine;
    }
    encrypted.close();
    return key;
}

void printDecrypted(const vector<string>& encryptedStrings){
    //create for loop to print strings from vector
    for(size_t index = encryptedStrings.size()-1; index > 0 ; index--){
        cout << encryptedStrings[index];
        if (index>1){
            cout << endl;
        }
    }
}
