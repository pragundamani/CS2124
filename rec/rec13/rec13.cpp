// pd2752
// Pragun Damani
// rec13.cpp

#include <algorithm> // task 3
#include <fstream>
#include <iostream>
#include <list>   // task 2
#include <map>    // task 23
#include <set>    // task 22
#include <string> // task 21
#include <vector> // task 1
using namespace std;

// task 9
void printListIter(const list<int> &intList) {
  // for (list<int>::iterator iter = intList.begin(); iter != intList.end();
  // ++iter) {
  //     cout << *iter << ' ';
  // }
  for (list<int>::const_iterator iter = intList.begin(); iter != intList.end();
       ++iter) {
    cout << *iter << ' ';
  }
}

// task 10
void printListRanged(const list<int> &intList) {
  for (int value : intList) {
    cout << value << ' ';
  }
}

// task 11
void printAlternateListAuto(const list<int> &intList) {
  for (auto iter = intList.begin(); iter != intList.end(); ++(++iter)) {
    cout << *iter << ' ';
  }
}

// task 12
list<int>::const_iterator findItemList(const list<int> &intList, int target) {
  for (list<int>::const_iterator iter = intList.begin(); iter != intList.end();
       ++iter) {
    if (*iter == target) {
      return iter;
    }
  }
  return intList.end();
}

// task 13
auto findItemListAuto(const list<int> &intList, int target) {
  for (auto iter = intList.begin(); iter != intList.end(); ++iter) {
    if (*iter == target) {
      return iter;
    }
  }
  return intList.end();
}

// task 15
bool isEven(int value) { return value % 2 == 0; }

// task 19
list<int>::const_iterator ourFind(list<int>::const_iterator begin,
                                  list<int>::const_iterator end, int target) {
  cout << "In ourFind function (not template)\n";
  for (list<int>::const_iterator iter = begin; iter != end; ++iter) {
    if (*iter == target) {
      return iter;
    }
  }
  return end;
}

// task 20
template <typename Iterator, typename TargetType>
Iterator ourFind(Iterator begin, Iterator end, TargetType target) {
  cout << "In ourFind function (template)\n";
  for (Iterator iter = begin; iter != end; ++iter) {
    if (*iter == target) {
      return iter;
    }
  }
  return end;
}

int main() {
  // 1. Create a vector with some values and display using ranged for
  cout << "Task 1:\n";
  vector<int> vec = {1, 2, 3, 4, 5, 6};
  for (int value : vec) {
    cout << value << ' ';
  }
  cout << "\n=======\n";

  // 2. Initalize a list as a copy of values from the vector
  cout << "Task 2:\n";
  list<int> intList(vec.begin(), vec.end());
  for (int value : intList) {
    cout << value << ' ';
  }
  cout << "\n=======\n";

  // 3. Sort the original vector.  Display both the vector and the list
  cout << "Task 3:\n";
  sort(vec.begin(), vec.end());
  cout << "Vector:" << '\n';
  for (int value : vec) {
    cout << value << ' ';
  }
  cout << '\n' << "List:" << '\n';
  for (int value : intList) {
    cout << value << ' ';
  }
  cout << "\n=======\n";

  // 4. print every other element of the vector.
  cout << "Task 4:\n";
  for (size_t index = 0; index < vec.size(); index += 2) {
    cout << vec[index] << ' ';
  }
  cout << "\n=======\n";

  // 5. Attempt to print every other element of the list using the
  //    same technique.
  cout << "Task 5:\n";
  // for (size_t index = 0; index < intList.size(); index += 2) {
  //     cout << intList[index] << ' ';
  // }
  cout << "\n=======\n";

  //
  // Iterators
  //

  // 6. Repeat task 4 using iterators.  Do not use auto;
  cout << "Task 6:\n";
  for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter += 2) {
    cout << *iter << ' ';
  }
  cout << "\n=======\n";

  // 7. Repeat the previous task using the list.  Again, do not use auto.
  //    Note that you cannot use the same simple mechanism to bump
  //    the iterator as in task 6.
  cout << "Task 7:\n";
  for (list<int>::iterator iter = intList.begin(); iter != intList.end();) {
    cout << *iter << ' ';
    ++iter;
    if (iter != intList.end()) {
      ++iter;
    }
  }
  cout << "\n=======\n";

  // 8. Sorting a list
  cout << "Task 8:\n";
  intList.sort();
  for (int value : intList) {
    cout << value << ' ';
  }
  cout << "\n=======\n";

  // 9. Calling the function to print the list
  cout << "Task 9:\n";
  printListIter(intList);
  cout << '\n';
  cout << "=======\n";

  // 10. Calling the function that prints the list, using ranged-for
  cout << "Task 10:\n";
  printListRanged(intList);
  cout << '\n';
  cout << "=======\n";

  //
  // Auto
  //

  // 11. Calling the function that, using auto, prints alterate
  // items in the list
  cout << "Task 11:\n";
  printAlternateListAuto(intList);
  cout << '\n';
  cout << "=======\n";

  // 12.  Write a function find that takes a list and value to search for.
  //      What should we return if not found
  cout << "Task 12:\n";
  list<int>::const_iterator listFound = findItemList(intList, 2);
  if (listFound != intList.end()) {
    cout << "Found item: " << *listFound << endl;
  } else {
    cout << "2 not found" << endl;
  }
  listFound = findItemList(intList, 99);
  if (listFound != intList.end()) {
    cout << "Found item: " << *listFound << endl;
  } else {
    cout << "99 not found" << endl;
  }
  cout << "=======\n";

  // 13.  Write a function find that takes a list and value to search for.
  //      What should we return if not found
  cout << "Task 13:\n";
  auto listFoundAuto = findItemListAuto(intList, 2);
  if (listFoundAuto != intList.end()) {
    cout << "Found item: " << *listFoundAuto << endl;
  } else {
    cout << "2 not found" << endl;
  }
  listFoundAuto = findItemListAuto(intList, 99);
  if (listFoundAuto != intList.end()) {
    cout << "Found item: " << *listFoundAuto << endl;
  } else {
    cout << "99 not found" << endl;
  }
  cout << "=======\n";

  //
  // Generic Algorithms
  //

  // 14. Generic algorithms: find
  cout << "Task 14:\n";
  list<int>::iterator genericFound = find(intList.begin(), intList.end(), 2);
  if (genericFound != intList.end()) {
    cout << "Found item: " << *genericFound << endl;
  } else {
    cout << "2 not found" << endl;
  }
  genericFound = find(intList.begin(), intList.end(), 99);
  if (genericFound != intList.end()) {
    cout << "Found item: " << *genericFound << endl;
  } else {
    cout << "99 not found" << endl;
  }
  cout << "=======\n";

  // 15. Generic algorithms: find_if
  cout << "Task 15:\n";
  vector<int>::iterator evenVec = find_if(vec.begin(), vec.end(), isEven);
  if (evenVec != vec.end()) {
    cout << "First even in vector: " << *evenVec << endl;
  } else {
    cout << "No even value in vector" << endl;
  }
  list<int>::iterator evenList =
      find_if(intList.begin(), intList.end(), isEven);
  if (evenList != intList.end()) {
    cout << "First even in list: " << *evenList << endl;
  } else {
    cout << "No even value in list" << endl;
  }
  cout << "=======\n";

  // 16. Lambda
  cout << "Task 16:\n";
  cout << "Testing with lambda functions:" << endl;
  [] { cout << "Hello Lambda!\n"; }();
  int result = [](int a, int b) { return a + b; }(4, 5);
  cout << "the result is: " << result << endl;
  list<int>::iterator evenListLambda = find_if(
      intList.begin(), intList.end(), [](int value) { return value % 2 == 0; });
  cout << "First even num with lambda in find_if: " << *evenListLambda << endl;
  cout << "=======\n";

  // 17. Lambda capture
  cout << "Task 17:\n";
  cout << "What's the value?";
  int value;
  cin >> value;
  list<int>::iterator divisible =
      find_if(intList.begin(), intList.end(),
              [value](int number) { return number % value == 0; });
  if (divisible != intList.end()) {
    cout << "The number is: " << *divisible << endl;
  }
  cout << "=======\n";

  // 18. Generic algorithms: copy to an array
  cout << "Task 18:\n";
  int *array = new int[intList.size()];
  cout << "Array: ";
  copy(intList.begin(), intList.end(), array);
  for (int *ptr = array; ptr != array + intList.size(); ++ptr) {
    cout << *ptr << ' ';
  }
  cout << endl;
  int *foundInArray = find(array, array + intList.size(), 2);
  if (foundInArray != array + intList.size()) {
    cout << "Found item: " << *foundInArray << endl;
  } else {
    cout << "2 not found in array" << endl;
  }
  foundInArray = find(array, array + intList.size(), 99);
  if (foundInArray != array + intList.size()) {
    cout << "Found item: " << *foundInArray << endl;
  } else {
    cout << "99 not found in array" << endl;
  }
  delete[] array;
  cout << "=======\n";

  //
  // Templated Functions
  //

  // 19. Implement find as a function for lists
  cout << "Task 19:\n";
  list<int>::const_iterator ourListFound =
      ourFind(intList.begin(), intList.end(), 6);
  if (ourListFound != intList.end()) {
    cout << *ourListFound << endl;
  }
  cout << "=======\n";

  // 20. Implement find as a templated function
  cout << "Task 20:\n";
  vector<int>::iterator ourVecFound = ourFind(vec.begin(), vec.end(), 6);
  if (ourVecFound != vec.end()) {
    cout << *ourVecFound << endl;
  }
  list<int>::const_iterator ourListFoundAgain =
      ourFind(intList.begin(), intList.end(), 6);
  if (ourListFoundAgain != intList.end()) {
    cout << *ourListFoundAgain << endl;
  }
  cout << "=======\n";

  //
  // Associative collections
  //

  // 21. Using a vector of strings, print a line showing the number
  //     of distinct words and the words themselves.
  cout << "Task 21:\n";
  ifstream ifs("pooh-nopunc.txt");
  string word;
  vector<string> distinctWords;
  while (ifs >> word) {
    if (find(distinctWords.begin(), distinctWords.end(), word) ==
        distinctWords.end()) {
      distinctWords.push_back(word);
    }
  }
  ifs.close();
  cout << "Vector Size: " << distinctWords.size() << endl;
  for (const string &wordSeen : distinctWords) {
    cout << wordSeen << ' ';
  }
  cout << "\n=======\n";

  // 22. Repeating previous step, but using the set
  cout << "Task 22:\n";
  ifstream ifs2("pooh-nopunc.txt");
  set<string> distinctSet;
  while (ifs2 >> word) {
    distinctSet.insert(word);
  }
  ifs2.close();
  cout << "Set Size: " << distinctSet.size() << endl;
  for (const string &wordSeen : distinctSet) {
    cout << wordSeen << ' ';
  }
  cout << endl;
  cout << "=======\n";

  // 23. Word co-occurence using map
  cout << "Task 23:\n";
  ifstream ifs3("pooh-nopunc.txt");
  map<string, vector<int>> wordMap;
  int position = 0;
  while (ifs3 >> word) {
    wordMap[word].push_back(position);
    ++position;
  }
  ifs3.close();
  for (const auto &entry : wordMap) {
    cout << entry.first << ":  ";
    for (int pos : entry.second) {
      cout << pos << ", ";
    }
    cout << endl;
  }
  cout << "=======\n";
}
