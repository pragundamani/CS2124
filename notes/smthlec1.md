## Basics
### program skeleton:

```cpp
int main(){
    return 0;
    }
```
- Every function needs return/void
- Comments // for line and /* */ for block comments

### print
```cpp
#include <iostream> //output library

int main(){
    std::cout << "CS";
    return 0;
    }
```

for not using std:: every time:
```cpp
#include <iostream>
using namespace std;
int main(){
    cout << "CS";
    return 0;
    }
```

also output chaining with << and new line with \n
```"CS" << " OOP\n"```

### variables have strict types
```cpp
#include <iostream>
using namespace std;

int main(){
    int a = 5;          // integer
    double b = 3.14;   // floating point number
    char c = 'A';      // single character
    string s = "CS";   // string of characters
    bool flag = true;  // boolean value

    cout << a << "\n";
    cout << b << "\n";
    cout << c << "\n";
    cout << s << "\n";
    cout << flag << "\n";

    return 0;
    }
```

### primitives
Fundamental data types:
- int, unsigned int: 4 bytes on most architectures
- long, unsigned long: at least 4 bytes, often 8 bytes
- float: 4 bytes, single precision floating point
- double: 8 bytes, double precision floating point
- char: 1 byte, represents a single character
- bool: 1 byte, represents true or false

### Int arithemtic
```math
5/2 = 2
5.0/2 = 5/2.0 = 2.5
5/0 = undefined (runtime error) #not always
5.0/0 = inf
0U - 1 = 4294967295 (unsigned wrap around) 2^32 - 1
```

### Operations
#### logical
```operations
and: &&
or: ||
not: !
```
*DO NOT use the words for logical operators*
#### others
```operations
loop through: ++, --
math: +, -, *, /, %
compare: ==, !=, <, >, <=, >=
assign: =
compound assign: +=, -=, *=, /=, %=
```

### loops
#### While loop
```cpp
#include <iostream>
using namespace std;

int main(){
    int i = 0;
    while(i < 5){
	cout << i << "\n";
	i++;
	}
    return 0;
    }
```

#### For loop
```cpp
#include <iostream>
using namespace std;

int main(){
    for(int i = 0; i > 5; i++){
	if (x==3) continue; //Using break is not illegal
	cout << i << "\n";
	}
	cout << "Done\n";
    return 0;
    }
```

#### do while loop
```cpp
#include <iostream>
using namespace std;

int main(){
    int i = 0;
    do {
	cout << i << "\n";
	i++;
	} while(i < 5);
    return 0;
    }
```

### Collections 
#### Vectors (dynamic arrays)

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> numbers; // create an empty vector of integers
    // add elements to the vector
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    // access elements in the vector
    for(size_t i = 0; i < numbers.size(); i++){
	cout << numbers[i] << "\n";
    }
    return 0;
    }
```

- *For Vectors(arrays) any operations that use size comparisons need to use `size_t`*
- `$vector.size()` returns `size_t` which is unsigned
- `$vector.clear()` empties the size to 0 not the vector

> Local Arrays exist, but are limited to fixed sizes from compile time.

### Ranged for
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> numbers = {10, 20, 30, 40};
    // iterate through vector without indexing
    for(int num : numbers){
        cout << num << "\n";
    }
    // using reference to modify elements
    for(int& num : numbers){
        num *= 2; // doubles each element
    }
    return 0;
    }
```

- Ranged for creates a copy of each element unless you use `&` reference
- Cannot modify vector size during iteration (push_back/pop_back)
- Safer than index-based loops, avoids off-by-one errors

### Strings
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1 = "Hello";
    string s2 = "World";
    
    // concatenation
    string s3 = s1 + " " + s2;
    cout << s3 << "\n"; // Hello World
    
    // length
    cout << s1.size() << "\n"; // 5
    cout << s1.length() << "\n"; // 5 (same as size)
    
    // access characters
    cout << s1[0] << "\n"; // H
    
    // comparison
    if(s1 == "Hello") cout << "Match\n";
    if(s1 < s2) cout << "s1 comes before s2\n"; // lexicographic
    
    // substring
    string sub = s3.substr(0, 5); // "Hello"
    
    // find
    size_t pos = s3.find("World");
    if(pos != string::npos) cout << "Found at " << pos << "\n";
    
    return 0;
    }
```

- Strings are mutable in C++ (unlike Java)
- Use `==` for comparison, not `=`
- `string::npos` is returned when find() doesn't find the substring
- Can iterate through strings like vectors

### File reading
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    // reading from a file
    ifstream inputFile("data.txt");
    
    // check if file opened successfully
    if(!inputFile){
        cerr << "Failed to open file\n";
        return 1;
    }
    
    // read word by word
    string word;
    while(inputFile >> word){
        cout << word << "\n";
    }
    
    // close file (happens automatically at end of scope)
    inputFile.close();
    
    // reading line by line
    ifstream inputFile2("data.txt");
    string line;
    while(getline(inputFile2, line)){
        cout << line << "\n";
    }
    
    return 0;
    }
```

- `ifstream` for input, `ofstream` for output, `fstream` for both
- Always check if file opened with `if(!file)` or `if(file.is_open())`
- `>>` reads word by word (whitespace delimited)
- `getline(file, string)` reads entire line including spaces
- File closes automatically when ifstream goes out of scope
- Can use `file.clear()` to reset error flags and `file.seekg(0)` to go back to beginning
