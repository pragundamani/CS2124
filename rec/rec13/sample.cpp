// rec13.cpp
// Eliot Kominer

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// task 9
void printListIter(const list<int>& intList) {
    for (list<int>::const_iterator i = intList.begin(); i != intList.end(); ++i) {
        cout << *i << " ";
    }
}

// task 10
void printListIterRanged(const list<int>& intList) {
    for (int elem : intList) {
        cout << elem << " ";
    }
}

// task 11
void printListIterAuto(const list<int>& intList) {
    for (auto i = intList.begin(); i != intList.end(); ++(++i)) {
        cout << *i << " ";
    }
}

// task 12
list<int>::const_iterator findItemList(const list<int>& intList, int search) {
    for (list<int>::const_iterator i = intList.begin(); i != intList.end(); ++i) {
        if (*i == search) {
            return i;
        }
    }
    return intList.end();
}

// task 13
auto findItemListAuto(const list<int>& intList, int search) {
    for (auto i = intList.begin(); i != intList.end(); ++i) {
        if (*i == search) {
            return i;
        }
    }
    return intList.end();
}

// task 15
bool isEven(int num) {
    return num % 2 == 0;
}

// task 19
list<int>::const_iterator ourFind(const list<int>::const_iterator& iter_begin,
    const list<int>::const_iterator& iter_end, int target) {
    cout << "In ourFind function (not template)" << endl;
    for (list<int>::const_iterator iter = iter_begin; iter != iter_end; ++iter){
        if (*iter == target) {
            return iter;
        }
    }
    return iter_end;
}

// task 20
template<typename T, typename targetType>
T ourFind(const T& orig_list_begin, const T& orig_list_end, targetType target){
    cout << "In ourFind function (template)" << endl;
    for (auto iter = orig_list_begin; iter != orig_list_end; ++iter){
        if (*iter == target) return iter;
    }
    return orig_list_end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec = {1,2,3,4,5,6};
    for (int elem : vec) {
        cout << elem << " ";
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> intList(vec.begin(), vec.end());
    for (int elem : intList) {
        cout << elem << " ";
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());
    cout << "Vector:" << endl;
    for (int elem : vec) {
        cout << elem << " ";
    }
    cout << endl << "List:" << endl;
    for (int elem : intList) {
        cout << elem << " ";
    }

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vec.size(); i += 2) {
        cout << vec[i] << " ";
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

    // code will not compile
    // for (size_t i = 0; i < intList.size(); i += 2) {
    //     cout << intList[i] << " ";
    // }

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = vec.begin(); i != vec.end(); i += 2) {
        cout << *i << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator i = intList.begin(); i != intList.end(); ++(++i)) {
        cout << *i << " ";
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    intList.sort();
    for (int elem : intList) {
        cout << elem << " ";
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListIter(intList); // using list<int>::const_iterator

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListIterRanged(intList);

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printListIterAuto(intList);

    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator iter = findItemList(intList, 2);
    cout << "Found item: " << *iter << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    auto iter2 = findItemListAuto(intList, 2);
    cout << "Found item: " << *iter2 << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto iter3 = find(intList.begin(), intList.end(), 2);
    cout << "Found item: " << *iter3 << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    auto iter4 = find_if(intList.begin(), intList.end(), isEven);
    if (iter4 != intList.end()) {
        cout << "First even num: " << *iter4 << endl;
    }

    cout << "=======\n";

    // 16. Lambda
    cout << "Task 16:\n";
    cout << "Testing with lambda functions:" << endl;
    [] { cout << "Hello Lambda!" << endl; } ();

    int result = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;



    auto iter5 = find_if(intList.begin(),
        intList.end(),
        [] (int num) { return num % 2 == 0; });
    cout << "First even num with lambda in find_if: " << *iter5 << endl;

    cout << "=======\n";

    // 17. Lambda capture
    cout << "Task 17:\n";
    cout << "What's the value?";
    int value;
    cin >> value;

    auto iter6 = find_if(intList.begin(),
        intList.end(),
        [value] (int num) { return num % value == 0; });

    if (iter6 != intList.end()) {
        cout << "The number is: " << *iter6 << endl;
    }


    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[intList.size()];
    cout << "Array: ";
    copy(intList.begin(), intList.end(), arr);
    for (int* i = arr; i != arr + intList.size(); i++){ // print out array
        cout << *i << " ";
    }
    cout << endl;
    int* findInt = find(arr, arr+intList.size(), 2);
    cout << "Found it:  " << *findInt << endl;

    int* find_first_even = find_if(arr, arr+intList.size(), isEven);
    cout << "Found it:  " << *find_first_even << endl;
    cout << endl;

    delete[] arr;


    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    auto findIter = ourFind(intList.begin(), intList.end(), 6);
    if (findIter != intList.end()) {
        cout << *findIter << endl;
    }

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    vector<int>::iterator findVec = ourFind(vec.begin(), vec.end(), 6);
    if (findVec != vec.end()) {
        cout << *findVec << endl;
    }

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs;
    ifs.open("pooh-nopunc.txt");
    string word;
    vector<string> words;
    while (ifs >> word) {
        bool already_added = false; // checking if word is already in vector
        for (const string& vect_word : words) {
            if (vect_word == word) {
                already_added = true;
                break;
            }
        }
        if (!already_added) {
            words.push_back(word);
        }

        if (find(words.begin(), words.end(), word) == words.end()) {
            words.push_back(word);
        }
    }
    ifs.close();
    for (const string& elem : words) {
        cout << elem << " ";
    }
    cout << "Vector Size: " << words.size() << endl;

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream ifs2;
    ifs2.open("pooh-nopunc.txt");
    set<string> all_added_words;
    while (ifs2 >> word){
        all_added_words.insert(word);
    }
    ifs2.close();
    cout << "Set Size: " << all_added_words.size() << endl;


    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream ifs3("pooh-nopunc.txt");
    int pos = 0;
    while (ifs3 >> word){
        wordMap[word].push_back(pos);
        // keep track of word position
        ++pos;
    }
    ifs3.close();
    for (const auto& pair : wordMap){
        cout << pair.first << ":  ";
        for (int pos : pair.second){
            cout << pos << ", ";
        }
        cout << endl;
    }

    cout << "=======\n";
}
