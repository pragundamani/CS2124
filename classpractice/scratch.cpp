// scratch file
#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Word{
    string token;
    vector<int> positions;
};

size_t findWord(const string& token, const vector<Word>& words) {
   for (size_t index = 0; index < words.size(); index++) {
       if (token == words[index].token) {
           return index;
       }
   }
   return words.size();
}

int main(){
    ifstream textStream("text.txt");
    if (!textStream){
        cerr << "failed to open";
        exit(1);
    }

    vector<Word> words;
    int pos = 0;
    string token;


    //loop over file
    while (textStream >> token){
        //check if token seen
        size_t where = findWord(token, words);

        //if seen note position
        if (where<words.size()) {
            //add to positions
            words[where].positions.push_back(pos); //words sub location pushback item
        }
        //if new, create Word object before adding it to vector
        else {
            Word newWord;
            newWord.token = token;
            newWord.positions.push_back(pos);
            words.push_back(newWord);
        }
        //bump the position
        pos++;
    }
   for (Word item: words) {
       cout << item.token;
   } 

    return 0;
}
