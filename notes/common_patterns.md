# C++ Common Patterns and Practical Examples

## String Operations

### String Basics
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    // Declaration and initialization
    string s1 = "Hello";
    string s2("World");
    string s3(5, 'A');  // "AAAAA"
    
    // concatenation
    string s4 = s1 + " " + s2;
    cout << s4 << "\n"; // Hello World
    
    // length
    cout << s1.size() << "\n";     // 5
    cout << s1.length() << "\n";   // 5 (same as size)
    
    // access characters
    cout << s1[0] << "\n"; // H
    
    // empty check
    if(s1.empty()){
        cout << "String is empty\n";
    }
    
    return 0;
}
```

### String Comparison
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1 = "apple";
    string s2 = "banana";
    
    // comparison
    if(s1 == "apple") cout << "Match\n";
    if(s1 != s2) cout << "Different\n";
    if(s1 < s2) cout << "s1 comes before s2\n"; // lexicographic
    
    return 0;
}
```
- Use `==` for comparison, not `=`
- Strings are compared lexicographically (dictionary order)
- `compare()` method returns int: 0 (equal), <0 (less), >0 (greater)

### String Operations
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "Hello World";
    
    // substring: substr(start_index, length)
    string sub = s.substr(0, 5); // "Hello"
    string sub2 = s.substr(6);   // "World" (from index 6 to end)
    
    // find: returns position or string::npos if not found
    size_t pos = s.find("World");
    if(pos != string::npos){
        cout << "Found at position " << pos << "\n"; // 6
    }
    
    // append
    s.append("!");      // "Hello World!"
    s += " Goodbye";    // "Hello World! Goodbye"
    
    // insert at position
    s.insert(5, " there"); // inserts at index 5
    
    // erase: erase(start_index, length)
    s.erase(0, 6);  // removes first 6 characters
    
    // replace: replace(start_index, length, new_string)
    s.replace(0, 5, "Goodbye");
    
    return 0;
}
```

### Iterating Through Strings
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "Hello";
    
    // using index
    for(size_t i = 0; i < s.size(); i++){
        cout << s[i] << " ";
    }
    cout << "\n";
    
    // using ranged for (read-only)
    for(char c : s){
        cout << c << " ";
    }
    cout << "\n";
    
    // using ranged for with reference (can modify)
    for(char& c : s){
        c = toupper(c);  // convert to uppercase
    }
    cout << s << "\n"; // HELLO
    
    return 0;
}
```
- Strings are mutable in C++ (unlike Java)
- Can iterate like vectors

### Character Functions
```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main(){
    char c = 'a';
    
    cout << toupper(c) << "\n";     // A
    cout << tolower('B') << "\n";   // b
    cout << isalpha(c) << "\n";     // 1 (true)
    cout << isdigit('5') << "\n";   // 1 (true)
    cout << isspace(' ') << "\n";   // 1 (true)
    cout << isalnum('a') << "\n";   // 1 (alphanumeric)
    
    return 0;
}
```
- These functions return non-zero (true) or 0 (false)
- Include `<cctype>` header

### C-strings vs std::string
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
    // C-string (character array)
    char cstr[20] = "Hello";
    cout << strlen(cstr) << "\n";  // 5
    strcat(cstr, " World");        // concatenate
    strcpy(cstr, "New text");      // copy
    
    // C++ string (preferred)
    string str = "Hello";
    cout << str.length() << "\n";
    str += " World";  // easier concatenation
    str = "New text";  // easier assignment
    
    // Convert between types
    const char* cstrFromStr = str.c_str();  // string → C-string
    string strFromCstr = string(cstr);      // C-string → string
    
    return 0;
}
```
**Prefer std::string over C-strings:**
- Safer (no buffer overflows)
- Easier to use
- Automatic memory management

## Vector Patterns

## Vector Patterns

### Dynamic Resizing and Memory Management
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    
    // Reserve space to avoid reallocations
    v.reserve(100);  // allocate space for 100 elements
    
    for(int i = 0; i < 100; i++){
        v.push_back(i);  // no reallocation needed
    }
    
    cout << "Size: " << v.size() << "\n";          // 100
    cout << "Capacity: " << v.capacity() << "\n";  // at least 100
    
    // Resize vector
    v.resize(50);  // shrink to 50 elements
    v.resize(100, 0);  // grow to 100, fill new elements with 0
    
    // Shrink capacity to fit size
    v.shrink_to_fit();
    
    return 0;
}
```

### Initialization Patterns
```cpp
#include <vector>
using namespace std;

int main(){
    // Uniform initialization (all same value)
    vector<int> v1(10, 5);  // {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
    
    // Fill initialization
    vector<int> v2(10);  // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    fill(v2.begin(), v2.end(), 3);  // fill all with 3
    
    // Range initialization
    int arr[] = {1, 2, 3, 4, 5};
    vector<int> v3(arr, arr + 5);  // from array
    
    vector<int> v4 = {1, 2, 3, 4, 5};
    vector<int> v5(v4.begin(), v4.begin() + 3);  // {1, 2, 3}
    
    return 0;
}
```

### 2D Vectors for Matrices
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // Create 3x4 matrix
    int rows = 3, cols = 4;
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));
    
    // Fill with values
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = i * cols + j;
        }
    }
    
    // Print matrix
    for(const auto& row : matrix){
        for(int val : row){
            cout << val << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
```

### Vectors (Dynamic Arrays)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // create an empty vector
    vector<int> numbers;
    
    // add elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    
    // access elements
    cout << numbers[0] << "\n";  // 10
    cout << numbers.at(1) << "\n"; // 20 (with bounds checking)
    
    // size
    cout << "Size: " << numbers.size() << "\n"; // 3
    
    // iterate
    for(size_t i = 0; i < numbers.size(); i++){
        cout << numbers[i] << "\n";
    }
    
    return 0;
}
```

### Vector Initialization
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v1;                    // empty vector
    vector<int> v2(5);                 // 5 elements, all 0
    vector<int> v3(5, 10);             // 5 elements, all 10
    vector<int> v4 = {1, 2, 3, 4, 5};  // initialized with values
    vector<string> v5 = {"hello", "world"};
    
    return 0;
}
```

### Vector Operations
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {10, 20, 30, 40, 50};
    
    // add to end
    v.push_back(60);
    
    // remove from end
    v.pop_back();
    
    // insert at position
    v.insert(v.begin() + 2, 25); // insert 25 at index 2
    
    // erase element at position
    v.erase(v.begin() + 1);  // remove element at index 1
    
    // clear all elements
    v.clear();  // size becomes 0
    
    // check if empty
    if(v.empty()){
        cout << "Vector is empty\n";
    }
    
    return 0;
}
```
- **Important**: `clear()` empties the vector (size = 0), doesn't delete the vector
- For size comparisons, use `size_t` because `size()` returns unsigned type

### Vector Operations (Sorting, Reversing, Searching)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {5, 2, 8, 1, 9, 3};
    
    // Sorting
    sort(v.begin(), v.end());  // ascending
    // v: {1, 2, 3, 5, 8, 9}
    
    sort(v.begin(), v.end(), greater<int>());  // descending
    // v: {9, 8, 5, 3, 2, 1}
    
    // Reversing
    reverse(v.begin(), v.end());
    // v: {1, 2, 3, 5, 8, 9}
    
    // Searching
    auto it = find(v.begin(), v.end(), 5);
    if(it != v.end()){
        cout << "Found at index: " << (it - v.begin()) << "\n";
    }
    
    // Binary search (requires sorted vector)
    sort(v.begin(), v.end());
    if(binary_search(v.begin(), v.end(), 5)){
        cout << "5 exists in vector\n";
    }
    
    return 0;
}
```

### Iterating Techniques
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {10, 20, 30, 40, 50};
    
    // 1. Index-based iteration
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
    
    // 2. Iterator-based iteration
    for(auto it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
    
    // 3. Range-based for loop (C++11)
    for(const auto& val : v){
        cout << val << " ";
    }
    cout << "\n";
    
    // 4. Algorithm-based iteration (std::for_each)
    for_each(v.begin(), v.end(), [](int x){ cout << x << " "; });
    cout << "\n";
    
    return 0;
}
```

### Ranged For Loop
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> numbers = {10, 20, 30, 40};
    
    // iterate through vector without indexing (read-only copy)
    for(int num : numbers){
        cout << num << "\n";
    }
    
    // using reference to modify elements
    for(int& num : numbers){
        num *= 2; // doubles each element
    }
    
    // const reference (read-only, no copy)
    for(const int& num : numbers){
        cout << num << " "; // 20 40 60 80
    }
    
    return 0;
}
```
- Ranged for creates a **copy** unless you use `&` reference
- Cannot modify vector size during iteration (no push_back/pop_back)
- Safer than index-based loops, avoids off-by-one errors

### 2D Vectors
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // create a 3x4 2D vector
    vector<vector<int>> matrix(3, vector<int>(4, 0));
    
    // set values
    matrix[0][0] = 1;
    matrix[1][2] = 5;
    
    // iterate through 2D vector
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
```

### Vector of Strings
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    vector<string> words = {"apple", "banana", "cherry"};
    
    words.push_back("date");
    
    for(const string& word : words){
        cout << word << "\n";
    }
    
    return 0;
}
```

## Modern Loop Patterns

### Range-Based For Loops (for-each style)
```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
    // With vectors
    vector<int> v = {1, 2, 3, 4, 5};
    for(int num : v){
        cout << num << " ";
    }
    cout << "\n";
    
    // With const reference (efficient)
    vector<string> names = {"Alice", "Bob", "Charlie"};
    for(const auto& name : names){
        cout << name << "\n";
    }
    
    // Modifying elements
    for(int& num : v){
        num *= 2;
    }
    
    // With maps (C++17 structured bindings)
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    for(const auto& [name, age] : ages){
        cout << name << ": " << age << "\n";
    }
    
    return 0;
}
```

### Iterator-Based Loops
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    // Forward iteration
    for(auto it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
    
    // Reverse iteration
    for(auto it = v.rbegin(); it != v.rend(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
    
    // Const iterator (read-only)
    for(auto it = v.cbegin(); it != v.cend(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
    
    return 0;
}
```

### Algorithm-Based Iteration
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    // std::for_each with lambda
    for_each(v.begin(), v.end(), [](int x){ 
        cout << x * 2 << " "; 
    });
    cout << "\n";
    
    // std::transform (create new vector)
    vector<int> doubled(v.size());
    transform(v.begin(), v.end(), doubled.begin(), [](int x){ 
        return x * 2; 
    });
    
    // std::for_each_n (process n elements)
    for_each_n(v.begin(), 3, [](int x){ 
        cout << x << " "; 
    });
    cout << "\n";
    
    return 0;
}
```

## File I/O

### Reading from a File (Word by Word)
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream inputFile("data.txt");
    
    // check if file opened successfully
    if(!inputFile){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    // read word by word (whitespace delimited)
    string word;
    while(inputFile >> word){
        cout << word << "\n";
    }
    
    inputFile.close();
    
    return 0;
}
```

### Reading from a File (Line by Line)
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream inputFile("data.txt");
    
    if(!inputFile){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    // read line by line
    string line;
    while(getline(inputFile, line)){
        cout << line << "\n";
    }
    
    inputFile.close();  // happens automatically at end of scope
    
    return 0;
}
```
- `>>` reads word by word (stops at whitespace)
- `getline(file, string)` reads entire line including spaces

### Writing to a File
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ofstream outputFile("output.txt");
    
    if(!outputFile){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    outputFile << "Hello World\n";
    outputFile << "Writing to a file\n";
    
    outputFile.close();
    
    return 0;
}
```

### Appending to a File
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream outputFile("output.txt", ios::app);  // append mode
    
    if(!outputFile){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    outputFile << "This line is appended\n";
    
    return 0;
}
```

### File Stream Types
- `ifstream` - input file stream (reading)
- `ofstream` - output file stream (writing)
- `fstream` - file stream (both reading and writing)

### Opening and Closing Files
```cpp
#include <fstream>
using namespace std;

int main(){
    // Open file in constructor
    ifstream inputFile("data.txt");
    
    // Or use open() method
    ofstream outputFile;
    outputFile.open("output.txt");
    
    // Always close files when done
    inputFile.close();
    outputFile.close();
    
    // Files close automatically when out of scope
    {
        ifstream file("temp.txt");
        // file closes automatically here
    }
    
    return 0;
}
```

### Checking File Status
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream file("data.txt");
    
    // Method 1: Check bool conversion
    if(!file){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    // Method 2: Check is_open()
    if(file.is_open()){
        cout << "File opened successfully\n";
    }
    
    // Check for errors during reading
    int value;
    while(file >> value){
        cout << value << "\n";
    }
    
    if(file.eof()){
        cout << "Reached end of file\n";
    } else if(file.fail()){
        cout << "Format error\n";
    } else if(file.bad()){
        cout << "Read/write error\n";
    }
    
    return 0;
}
```

### Reading Patterns
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream file("data.txt");
    
    // Word-by-word (whitespace delimited)
    string word;
    while(file >> word){
        cout << word << "\n";
    }
    
    // Line-by-line
    file.clear();  // clear error flags
    file.seekg(0);  // go back to beginning
    string line;
    while(getline(file, line)){
        cout << line << "\n";
    }
    
    // Character-by-character
    file.clear();
    file.seekg(0);
    char ch;
    while(file.get(ch)){
        cout << ch;
    }
    
    return 0;
}
```

### Writing to Files
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream file("output.txt");
    
    if(!file){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    file << "Hello World\n";
    file << "Writing to a file\n";
    
    // Write numbers
    for(int i = 1; i <= 5; i++){
        file << i << " ";
    }
    file << "\n";
    
    file.close();
    
    return 0;
}
```

### Append Mode vs Overwrite Mode
```cpp
#include <fstream>
using namespace std;

int main(){
    // Overwrite mode (default)
    ofstream file1("output.txt");  // erases existing content
    file1 << "New content\n";
    file1.close();
    
    // Append mode
    ofstream file2("output.txt", ios::app);  // keeps existing content
    file2 << "Appended content\n";
    file2.close();
    
    // Other modes
    ofstream file3("data.txt", ios::out | ios::binary);  // binary mode
    file3.close();
    
    return 0;
}
```

### Binary File I/O Basics
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    // Writing binary data
    ofstream outFile("data.bin", ios::binary);
    int numbers[] = {1, 2, 3, 4, 5};
    outFile.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    outFile.close();
    
    // Reading binary data
    ifstream inFile("data.bin", ios::binary);
    int readNumbers[5];
    inFile.read(reinterpret_cast<char*>(readNumbers), sizeof(readNumbers));
    inFile.close();
    
    for(int num : readNumbers){
        cout << num << " ";
    }
    cout << "\n";
    
    return 0;
}
```
- Binary mode writes raw bytes, not text
- Use `read()` and `write()` for binary I/O
- More efficient than text I/O for large data

## Common Coding Patterns

### Reading Numbers from File into Vector
```cpp
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    ifstream file("numbers.txt");
    vector<int> numbers;
    
    int num;
    while(file >> num){
        numbers.push_back(num);
    }
    
    for(int n : numbers){
        cout << n << " ";
    }
    
    return 0;
}
```

### Counting Words in a String
```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(){
    string text = "Hello world from C++";
    stringstream ss(text);
    
    int count = 0;
    string word;
    while(ss >> word){
        count++;
    }
    
    cout << "Word count: " << count << "\n";
    
    return 0;
}
```

### Reversing a Vector
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    reverse(v.begin(), v.end());
    
    for(int n : v){
        cout << n << " ";  // 5 4 3 2 1
    }
    
    return 0;
}
```

### Sorting a Vector
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {5, 2, 8, 1, 9};
    
    sort(v.begin(), v.end());  // ascending order
    
    for(int n : v){
        cout << n << " ";  // 1 2 5 8 9
    }
    
    return 0;
}
```

### Finding Duplicates
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 2, 4, 3, 5};
    
    // Method 1: Using set
    unordered_set<int> seen;
    vector<int> duplicates;
    
    for(int num : v){
        if(seen.count(num)){
            duplicates.push_back(num);
        }
        seen.insert(num);
    }
    
    // Method 2: Sort and adjacent_find
    sort(v.begin(), v.end());
    auto it = adjacent_find(v.begin(), v.end());
    if(it != v.end()){
        cout << "Found duplicate: " << *it << "\n";
    }
    
    return 0;
}
```

### Two-Pointer Technique
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Find pair that sums to target
pair<int, int> findPairWithSum(vector<int>& v, int target){
    sort(v.begin(), v.end());
    int left = 0, right = v.size() - 1;
    
    while(left < right){
        int sum = v[left] + v[right];
        if(sum == target){
            return {v[left], v[right]};
        } else if(sum < target){
            left++;
        } else {
            right--;
        }
    }
    
    return {-1, -1};  // not found
}

int main(){
    vector<int> v = {2, 7, 11, 15};
    auto [a, b] = findPairWithSum(v, 9);
    cout << a << " + " << b << " = 9\n";  // 2 + 7 = 9
    return 0;
}
```

### Sliding Window Pattern
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Find maximum sum of k consecutive elements
int maxSumSubarray(const vector<int>& v, int k){
    if(v.size() < k) return 0;
    
    // Calculate sum of first window
    int windowSum = 0;
    for(int i = 0; i < k; i++){
        windowSum += v[i];
    }
    
    int maxSum = windowSum;
    
    // Slide the window
    for(int i = k; i < v.size(); i++){
        windowSum = windowSum - v[i - k] + v[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}

int main(){
    vector<int> v = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    cout << "Max sum of 4 consecutive: " << maxSumSubarray(v, 4) << "\n";  // 39
    return 0;
}
```

### Frequency Counting with Maps
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

int main(){
    vector<int> v = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    
    // Count frequencies
    unordered_map<int, int> freq;
    for(int num : v){
        freq[num]++;
    }
    
    // Print frequencies
    for(const auto& [num, count] : freq){
        cout << num << " appears " << count << " times\n";
    }
    
    // Find most frequent element
    int maxFreq = 0, mostFrequent = 0;
    for(const auto& [num, count] : freq){
        if(count > maxFreq){
            maxFreq = count;
            mostFrequent = num;
        }
    }
    
    cout << "Most frequent: " << mostFrequent << " (" << maxFreq << " times)\n";
    
    return 0;
}
```

### String Tokenization (Splitting)
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(const string& str, char delimiter){
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while(getline(ss, token, delimiter)){
        tokens.push_back(token);
    }
    
    return tokens;
}

int main(){
    string text = "apple,banana,orange,grape";
    vector<string> fruits = split(text, ',');
    
    for(const string& fruit : fruits){
        cout << fruit << "\n";
    }
    
    return 0;
}
```

### Remove Duplicates from Sorted Vector
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 1, 2, 2, 3, 4, 4, 5};
    
    // std::unique moves duplicates to end, returns iterator to new end
    auto newEnd = unique(v.begin(), v.end());
    
    // Erase the duplicates
    v.erase(newEnd, v.end());
    
    // v is now {1, 2, 3, 4, 5}
    for(int num : v){
        cout << num << " ";
    }
    cout << "\n";
    
    return 0;
}
```

### Custom Sorting with Comparator
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
    string name;
    int age;
};

int main(){
    vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    // Sort by age (ascending)
    sort(people.begin(), people.end(), [](const Person& a, const Person& b){
        return a.age < b.age;
    });
    
    // Sort by name (alphabetical)
    sort(people.begin(), people.end(), [](const Person& a, const Person& b){
        return a.name < b.name;
    });
    
    for(const auto& p : people){
        cout << p.name << " (" << p.age << ")\n";
    }
    
    return 0;
}
```
