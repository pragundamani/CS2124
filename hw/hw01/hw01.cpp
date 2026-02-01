/*
 Pragun Damani: pd2752
 hw01.cpp
 Spring 2026
 */
 // Read encrypted.txt (no prompt); first int = rotation (-25..25)
 // Store remaining lines in vector<string> (keep order)
 // Decrypt ONLY 'A'–'Z' with Caesar wraparound; others unchanged
 // Lines are reversed → print vector backwards
 // Functions required:
 //   char decryptChar(char c, int key);
 //   void decryptString(string& s, int key);
 // Output: print the fully DECRYPTED text to standard output
 // Print ONLY decoded lines (no extra text, prompts, or labels)
 // Good style: comments, prototypes, clean formatting
 // Submit a single file: hw01.cpp


#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

char decryptChar(char Encrypted, int key);
void decryptString(string& s, int key);
int fileRead(vector<string>& encyptedStrings);
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

    return 0; //end of program
}

char decryptChar(char encryptedChar, int key){
    char returnChar = encryptedChar; //init return var

    if (encryptedChar>='A' && encryptedChar <= 'Z'){

        //queue logic wrap
        //(current - shift + len)%len and using 'A' to convert char <-> num
        returnChar = 'A' + (encryptedChar - 'A' - key + 26) % 26;
        // cout << returnChar;
    }

    return returnChar;
}

void decryptString(string& encryptedString, int key){
    //for loop to go through each char
    for(char encryptedChar: encryptedString){
        encryptedChar = decryptChar(encryptedChar, key);
    }
    // cout << encryptedString;
}

int fileRead(vector<string>& encyptedStrings){
    ifstream encrypted("encrypted.txt"); //file to read
    int key = 0; //created var key
    string fileLine; //created temp var for string storage

    encrypted >> key; //put the key from encrypted into the var
    // cout << key;
    while(getline(encrypted,fileLine)){
        encyptedStrings.push_back(fileLine);
        // cout << fileLine;
    }

    return key;
}

void printDecrypted(const vector<string>& encryptedStrings){
    for(size_t index = (encryptedStrings.size()-1) ; index>0 ; index--){
        cout << encryptedStrings[index];
    }
}
