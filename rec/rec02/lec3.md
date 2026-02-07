notes 
``` c++
/*
  words.cpp
  Sec 
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Word {
    string token;
    vector<int> positions;
};

size_t findWord(const string& token, const vector<Word>& words) {
    for (size_t index = 0; index < words.size(); ++index) {
        if (token == words[index].token) {
            return index;
        }
    }
    return words.size();
}

int main() {

    ifstream textStream("jabberwocky");
    if (!textStream) {
	cerr << "failed to open jabberwocky\n";
	exit(1);
    }

    vector<Word> words;
    int pos = 0;
    string token;

    // Loop over the file reading tokens
    while (textStream >> token) {

        //   Have we seen that token
        size_t where = findWord(token, words);

        //   If we have
        if (where < words.size()) {
            //       just add the current postion
            words[where].positions.push_back(pos);
        } else {
            //   If we haven't

            //      Create a new Word object for that token and
            //      position and add it.
            Word aWord;
            aWord.token = token;
            aWord.positions.push_back(pos);
            //words.emplace_back(aWord);
            words.push_back(aWord);
        }

        // bump the position
        ++pos;
    }

}
```