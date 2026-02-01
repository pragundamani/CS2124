# C++ Advanced Basics

## Functions

### Function Declaration and Definition
```cpp
#include <iostream>
using namespace std;

// function declaration (prototype)
int add(int a, int b);

int main(){
    int result = add(5, 3);
    cout << result << "\n"; // 8
    return 0;
}

// function definition
int add(int a, int b){
    return a + b;
}
```
- Declaration tells compiler function exists
- Definition provides the implementation

### Void Functions
```cpp
#include <iostream>
using namespace std;

void greet( name){
    cout << "Hello, " << name << "!\n";
}

int main(){
    greet("Alice");
    greet("Bob");
    return 0;
}
```

### Function Prototypes and Forward Declarations
```cpp
#include <iostream>
using namespace std;

// function prototypes (declaration)
int multiply(int a, int b);
void displayResult(int result);

int main(){
    int result = multiply(4, 5);
    displayResult(result);
    return 0;
}

// function definitions
int multiply(int a, int b){
    return a * b;
}

void displayResult(int result){
    cout << "Result: " << result << "\n";
}
```
- Prototypes allow you to define functions after main()
- Must match the actual function signature

### Return Types
```cpp
// Value return
int getValue(){
    return 42;
}

// Reference return (advanced - be careful!)
int& getReference(int& x){
    return x;  // returns reference to x
}

// Void return (no return value)
void printMessage(){
    cout << "Hello\n";
    return;  // optional for void functions
}

int main(){
    int val = getValue();  // 42
    
    int num = 10;
    getReference(num) = 20;  // modifies num through reference
    cout << num << "\n";  // 20
    
    return 0;
}
```

### Pass by Value
```cpp
#include <iostream>
using namespace std;

void increment(int x){
    x++;  // only changes local copy
}

int main(){
    int num = 5;
    increment(num);
    cout << num << "\n"; // 5 (unchanged)
    return 0;
}
```

### Pass by Reference
```cpp
#include <iostream>
using namespace std;

void increment(int& x){
    x++;  // changes the original variable
}

int main(){
    int num = 5;
    increment(num);
    cout << num << "\n"; // 6 (changed)
    return 0;
}
```
- Use `&` to pass by reference
- Avoids copying large objects (vectors, strings)
- Use `const&` for read-only references

### Const Reference Parameters
```cpp
#include <iostream>
#include <vector>
using namespace std;

void printVector(const vector<int>& v){
    for(int num : v){
        cout << num << " ";
    }
    cout << "\n";
}

int main(){
    vector<int> numbers = {1, 2, 3, 4, 5};
    printVector(numbers);  // efficient, no copy made
    return 0;
}
```

### Default Parameters
```cpp
#include <iostream>
using namespace std;

void greet(string name = "Guest", string greeting = "Hello"){
    cout << greeting << ", " << name << "!\n";
}

int main(){
    greet();                    // Hello, Guest!
    greet("Alice");             // Hello, Alice!
    greet("Bob", "Hi");         // Hi, Bob!
    return 0;
}
```

### Function Overloading
```cpp
#include <iostream>
using namespace std;

int add(int a, int b){
    return a + b;
}

double add(double a, double b){
    return a + b;
}

int add(int a, int b, int c){
    return a + b + c;
}

int main(){
    cout << add(5, 3) << "\n";        // 8
    cout << add(2.5, 3.7) << "\n";    // 6.2
    cout << add(1, 2, 3) << "\n";     // 6
    return 0;
}
```
- Functions with same name but different parameters
- Compiler selects correct version based on arguments

### Inline Functions
```cpp
inline int square(int x){
    return x * x;
}

int main(){
    int result = square(5);  // compiler may inline this call
    return 0;
}
```
- Hint to compiler to insert function code directly (avoid call overhead)
- Use for small, frequently called functions
- Compiler may ignore inline suggestion

### Function Signatures and Name Mangling
```cpp
// These are different signatures (can coexist)
void func(int x);
void func(double x);
void func(int x, int y);

// These are NOT different signatures (cannot coexist)
int func(int x);    // only return type differs
void func(int x);   // ERROR: conflicts with above
```
- Signature = function name + parameter types (not return type)
- C++ uses name mangling to encode signatures in compiled code

## Recursion

### Basic Recursion Example
```cpp
#include <iostream>
using namespace std;

void countdown(int n){
    if(n <= 0){
        cout << "Blastoff!\n";
        return;
    }
    cout << n << "\n";
    countdown(n - 1);
}

int main(){
    countdown(5);
    return 0;
}
```

### Factorial
```cpp
#include <iostream>
using namespace std;

int factorial(int n){
    if(n <= 1){
        return 1;  // base case
    }
    return n * factorial(n - 1);  // recursive case
}

int main(){
    cout << factorial(5) << "\n";  // 120
    cout << factorial(0) << "\n";  // 1
    return 0;
}
```
- Base case: condition that stops recursion
- Recursive case: function calls itself

### Recursion vs Iteration Trade-offs
```cpp
// Recursive Fibonacci (simple but slow - O(2^n))
int fibRecursive(int n){
    if(n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative Fibonacci (faster - O(n))
int fibIterative(int n){
    if(n <= 1) return n;
    int prev = 0, curr = 1;
    for(int i = 2; i <= n; i++){
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```
**Recursion Pros:**
- More elegant for tree/graph problems
- Natural for divide-and-conquer algorithms
- Easier to understand for some problems

**Recursion Cons:**
- Stack overhead (function calls)
- Risk of stack overflow
- Can be slower than iteration

### Stack Overflow Prevention
```cpp
#include <iostream>
using namespace std;

// Bad: no base case or wrong base case
void infiniteRecursion(int n){
    cout << n << "\n";
    infiniteRecursion(n + 1);  // never stops!
}

// Good: proper base case
void safeRecursion(int n){
    if(n <= 0) return;  // base case
    cout << n << "\n";
    safeRecursion(n - 1);
}
```

### Tail Recursion Optimization
```cpp
// Not tail recursive (operation after recursive call)
int factorial(int n){
    if(n <= 1) return 1;
    return n * factorial(n - 1);  // multiplication happens AFTER call
}

// Tail recursive (no operation after recursive call)
int factorialTail(int n, int accumulator = 1){
    if(n <= 1) return accumulator;
    return factorialTail(n - 1, n * accumulator);  // call is last operation
}
```
- Tail recursive functions can be optimized by compiler to iteration
- Reduces stack space usage

### Fibonacci Sequence
```cpp
#include <iostream>
using namespace std;

int fibonacci(int n){
    if(n <= 1){
        return n;  // base cases: fib(0)=0, fib(1)=1
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(){
    for(int i = 0; i < 10; i++){
        cout << fibonacci(i) << " ";
    }
    // Output: 0 1 1 2 3 5 8 13 21 34
    return 0;
}
```

### Sum of Array Elements (Recursion)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int sum(const vector<int>& v, size_t index = 0){
    if(index >= v.size()){
        return 0;  // base case
    }
    return v[index] + sum(v, index + 1);
}

int main(){
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << sum(numbers) << "\n";  // 15
    return 0;
}
```

### Binary Search (Recursion)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& v, int target, int left, int right){
    if(left > right){
        return -1;  // not found
    }
    
    int mid = left + (right - left) / 2;
    
    if(v[mid] == target){
        return mid;
    }
    else if(v[mid] > target){
        return binarySearch(v, target, left, mid - 1);
    }
    else{
        return binarySearch(v, target, mid + 1, right);
    }
}

int main(){
    vector<int> sorted = {1, 3, 5, 7, 9, 11, 13};
    int index = binarySearch(sorted, 7, 0, sorted.size() - 1);
    cout << "Found at index: " << index << "\n";  // 3
    return 0;
}
```

### Tower of Hanoi (Advanced Recursion)
```cpp
#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from, char to, char aux){
    if(n == 1){
        cout << "Move disk 1 from " << from << " to " << to << "\n";
        return;
    }
    towerOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    towerOfHanoi(n - 1, aux, to, from);
}

int main(){
    towerOfHanoi(3, 'A', 'C', 'B');
    return 0;
}
```

## Arrays

### Static Array Declaration and Initialization
```cpp
#include <iostream>
using namespace std;

int main(){
    // Declaration
    int arr[5];  // uninitialized array of 5 integers
    
    // Initialization
    int numbers[5] = {1, 2, 3, 4, 5};
    int partial[5] = {1, 2};  // {1, 2, 0, 0, 0} - rest are zero
    int sized[] = {1, 2, 3};  // size determined automatically (3)
    
    // Accessing elements
    cout << numbers[0] << "\n";  // 1
    cout << numbers[4] << "\n";  // 5
    
    // Modifying elements
    numbers[2] = 10;
    
    return 0;
}
```

### Array Indexing and Bounds
```cpp
#include <iostream>
using namespace std;

int main(){
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Valid indices: 0 to 4
    for(int i = 0; i < 5; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
    
    // WARNING: No bounds checking!
    // arr[5] = 60;  // Undefined behavior - array overflow
    // arr[-1] = 5;  // Undefined behavior - negative index
    
    return 0;
}
```
- Arrays use zero-based indexing
- C++ does NOT check bounds automatically
- Accessing out-of-bounds = undefined behavior (crash or corruption)

### Multidimensional Arrays (2D, 3D)
```cpp
#include <iostream>
using namespace std;

int main(){
    // 2D array (matrix)
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Access elements
    cout << matrix[0][0] << "\n";  // 1
    cout << matrix[2][3] << "\n";  // 12
    
    // Iterate through 2D array
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 3D array
    int cube[2][3][4];  // 2 layers, 3 rows, 4 columns
    
    return 0;
}
```

### Array Decay to Pointers
```cpp
#include <iostream>
using namespace std;

void printArray(int* arr, int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main(){
    int numbers[] = {1, 2, 3, 4, 5};
    
    // Array name decays to pointer to first element
    int* ptr = numbers;  // equivalent to &numbers[0]
    
    cout << numbers[0] << "\n";  // 1
    cout << *ptr << "\n";        // 1 (same)
    
    printArray(numbers, 5);  // pass array as pointer
    
    return 0;
}
```

### Passing Arrays to Functions
```cpp
#include <iostream>
using namespace std;

// Method 1: Array notation (decays to pointer)
void modifyArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        arr[i] *= 2;
    }
}

// Method 2: Pointer notation (same as above)
void printArray(int* arr, int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// Method 3: Reference to array (preserves size)
void printArrayRef(int (&arr)[5]){
    for(int i = 0; i < 5; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main(){
    int numbers[5] = {1, 2, 3, 4, 5};
    
    modifyArray(numbers, 5);
    printArray(numbers, 5);      // 2 4 6 8 10
    printArrayRef(numbers);      // 2 4 6 8 10
    
    return 0;
}
```

### Array Limitations
```cpp
// Problems with C-style arrays:

// 1. No size information
int arr[5];
// sizeof(arr) / sizeof(arr[0]) works only in same scope
// When passed to function, size is lost

// 2. No bounds checking
arr[100] = 5;  // Compiles but undefined behavior

// 3. Cannot be copied or assigned
int arr1[5] = {1, 2, 3, 4, 5};
// int arr2[5] = arr1;  // ERROR: cannot copy arrays

// 4. Cannot be returned from functions
// int[] getArray(){ return arr; }  // ERROR

// 5. Cannot be resized
// Once size is set, it's fixed

// Solution: Use std::vector or std::array instead!
```

## Vectors (std::vector)

### Dynamic Array Concept
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v;  // empty vector
    
    // Vectors can grow dynamically
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    cout << "Size: " << v.size() << "\n";  // 3
    
    // Vectors handle memory automatically
    // No need to worry about size limits
    
    return 0;
}
```

### Initialization Methods
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // Method 1: Empty vector
    vector<int> v1;
    
    // Method 2: With size (all zeros)
    vector<int> v2(5);  // {0, 0, 0, 0, 0}
    
    // Method 3: With size and default value
    vector<int> v3(5, 10);  // {10, 10, 10, 10, 10}
    
    // Method 4: Initializer list
    vector<int> v4 = {1, 2, 3, 4, 5};
    vector<int> v5{1, 2, 3, 4, 5};  // C++11 style
    
    // Method 5: From another vector
    vector<int> v6 = v4;  // copy
    vector<int> v7(v4.begin(), v4.begin() + 3);  // {1, 2, 3}
    
    return 0;
}
```

### Common Operations
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {10, 20, 30, 40, 50};
    
    // Add to end
    v.push_back(60);  // {10, 20, 30, 40, 50, 60}
    
    // Remove from end
    v.pop_back();  // {10, 20, 30, 40, 50}
    
    // Insert at position
    v.insert(v.begin() + 2, 25);  // {10, 20, 25, 30, 40, 50}
    
    // Erase element at position
    v.erase(v.begin() + 1);  // {10, 25, 30, 40, 50}
    
    // Erase range
    v.erase(v.begin(), v.begin() + 2);  // {30, 40, 50}
    
    // Clear all elements
    v.clear();  // size becomes 0
    
    // Check if empty
    if(v.empty()){
        cout << "Vector is empty\n";
    }
    
    return 0;
}
```

### Accessing Elements
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {10, 20, 30, 40, 50};
    
    // Using [] operator (no bounds checking)
    cout << v[0] << "\n";  // 10
    cout << v[4] << "\n";  // 50
    
    // Using at() (with bounds checking)
    cout << v.at(0) << "\n";  // 10
    try {
        cout << v.at(10) << "\n";  // throws exception
    } catch (const out_of_range& e) {
        cout << "Out of range!\n";
    }
    
    // Front and back
    cout << v.front() << "\n";  // 10 (first element)
    cout << v.back() << "\n";   // 50 (last element)
    
    return 0;
}
```

### Size vs Capacity
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    
    cout << "Size: " << v.size() << "\n";          // 0
    cout << "Capacity: " << v.capacity() << "\n";  // 0
    
    v.push_back(1);
    cout << "Size: " << v.size() << "\n";          // 1
    cout << "Capacity: " << v.capacity() << "\n";  // 1 (or more)
    
    v.push_back(2);
    cout << "Size: " << v.size() << "\n";          // 2
    cout << "Capacity: " << v.capacity() << "\n";  // 2 (or more)
    
    // Reserve capacity (optimization)
    v.reserve(100);  // allocate space for 100 elements
    cout << "Capacity: " << v.capacity() << "\n";  // 100
    
    // Shrink capacity to fit size
    v.shrink_to_fit();
    
    return 0;
}
```
- **Size**: number of elements currently in vector
- **Capacity**: allocated space (may be larger than size)
- Vector automatically increases capacity when needed

### Iterating Through Vectors
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {10, 20, 30, 40, 50};
    
    // Method 1: Index-based
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
    
    // Method 2: Range-based for (read-only)
    for(int num : v){
        cout << num << " ";
    }
    cout << "\n";
    
    // Method 3: Range-based for (modifiable)
    for(int& num : v){
        num *= 2;
    }
    
    // Method 4: Iterator-based
    for(auto it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
    
    return 0;
}
```

### Vectors of Vectors (2D Vectors)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // Create 2D vector (3x4 matrix)
    vector<vector<int>> matrix(3, vector<int>(4, 0));
    
    // Initialize with values
    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Access elements
    cout << grid[0][0] << "\n";  // 1
    cout << grid[2][2] << "\n";  // 9
    
    // Iterate
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    
    // Jagged array (variable row sizes)
    vector<vector<int>> jagged = {
        {1, 2},
        {3, 4, 5, 6},
        {7}
    };
    
    return 0;
}
```

## Pointers (Introduction)

### Pointer Basics
```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 10;
    int* ptr = &x;  // ptr stores the address of x
    
    cout << "Value of x: " << x << "\n";           // 10
    cout << "Address of x: " << &x << "\n";        // memory address
    cout << "Value of ptr: " << ptr << "\n";       // memory address
    cout << "Value at ptr: " << *ptr << "\n";      // 10
    
    *ptr = 20;  // changes x through pointer
    cout << "New value of x: " << x << "\n";       // 20
    
    return 0;
}
```
- `&` - address-of operator
- `*` - dereference operator (access value at address)

### Null Pointers
```cpp
#include <iostream>
using namespace std;

int main(){
    int* ptr = nullptr;  // or NULL
    
    if(ptr == nullptr){
        cout << "Pointer is null\n";
    }
    
    return 0;
}
```

## Structures (Structs)

### Struct Definition and Syntax
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student{
    string name;
    int age;
    double gpa;
};

int main(){
    Student s1;
    s1.name = "Alice";
    s1.age = 20;
    s1.gpa = 3.8;
    
    cout << s1.name << " is " << s1.age << " years old\n";
    cout << "GPA: " << s1.gpa << "\n";
    
    return 0;
}
```

### Member Variables and Initialization
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Point{
    int x;
    int y;
};

int main(){
    Point p1 = {10, 20};
    Point p2{5, 15};  // C++11 style
    
    cout << "p1: (" << p1.x << ", " << p1.y << ")\n";
    cout << "p2: (" << p2.x << ", " << p2.y << ")\n";
    
    return 0;
}
```

### Accessing Struct Members
```cpp
struct Point{
    int x;
    int y;
};

int main(){
    Point p;
    
    // Dot operator for direct access
    p.x = 10;
    p.y = 20;
    
    // Arrow operator for pointer access
    Point* ptr = &p;
    ptr->x = 30;  // equivalent to (*ptr).x = 30
    ptr->y = 40;
    
    return 0;
}
```

### Vector of Structs
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book{
    string title;
    string author;
    int year;
};

int main(){
    vector<Book> library;
    
    library.push_back({"1984", "George Orwell", 1949});
    library.push_back({"Brave New World", "Aldous Huxley", 1932});
    
    for(const Book& book : library){
        cout << book.title << " by " << book.author;
        cout << " (" << book.year << ")\n";
    }
    
    return 0;
}
```

### Functions with Structs
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Rectangle{
    double width;
    double height;
};

double area(const Rectangle& r){
    return r.width * r.height;
}

void printRectangle(const Rectangle& r){
    cout << "Width: " << r.width << ", Height: " << r.height << "\n";
    cout << "Area: " << area(r) << "\n";
}

int main(){
    Rectangle rect = {5.0, 3.0};
    printRectangle(rect);
    return 0;
}
```

### Structs vs Classes (Basic Differences)
```cpp
// Struct: members are public by default
struct MyStruct {
    int x;  // public
private:
    int y;  // explicitly private
};

// Class: members are private by default
class MyClass {
    int x;  // private
public:
    int y;  // explicitly public
};
```
- In C++, structs and classes are nearly identical
- Main difference: default access level
- Convention: use struct for simple data containers, class for objects with behavior

### Nested Structs
```cpp
struct Address {
    string street;
    string city;
    string zipCode;
};

struct Person {
    string name;
    int age;
    Address address;  // nested struct
};

int main(){
    Person p;
    p.name = "Bob";
    p.age = 30;
    p.address.street = "123 Main St";
    p.address.city = "New York";
    p.address.zipCode = "10001";
    
    cout << p.name << " lives at " << p.address.street << "\n";
    
    return 0;
}
```

## Enumerations

### Basic Enum
```cpp
#include <iostream>
using namespace std;

enum Color{
    RED,
    GREEN,
    BLUE
};

int main(){
    Color myColor = RED;
    
    if(myColor == RED){
        cout << "Color is red\n";
    }
    
    return 0;
}
```

### Enum Class (Scoped Enums)
```cpp
#include <iostream>
using namespace std;

enum class Direction{
    North,
    South,
    East,
    West
};

int main(){
    Direction dir = Direction::North;
    
    if(dir == Direction::North){
        cout << "Going north\n";
    }
    
    return 0;
}
```
- Preferred over basic enum (no namespace pollution)
- Must use scope resolution: `Direction::North`

### Underlying Types
```cpp
// Specify underlying type
enum class Status : char {
    Active = 'A',
    Inactive = 'I',
    Pending = 'P'
};

// Default underlying type for basic enum is int
enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

int main(){
    Status s = Status::Active;
    
    // Cast to underlying type
    char c = static_cast<char>(s);  // 'A'
    
    return 0;
}
```

### Enum in Switch Statements
```cpp
enum class TrafficLight {
    Red,
    Yellow,
    Green
};

void handleLight(TrafficLight light){
    switch(light){
        case TrafficLight::Red:
            cout << "Stop!\n";
            break;
        case TrafficLight::Yellow:
            cout << "Slow down!\n";
            break;
        case TrafficLight::Green:
            cout << "Go!\n";
            break;
    }
}
```

## Standard Library Algorithms

### Sorting
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {5, 2, 8, 1, 9};
    
    // std::sort (ascending order)
    sort(v.begin(), v.end());
    // v is now {1, 2, 5, 8, 9}
    
    // Descending order
    sort(v.begin(), v.end(), greater<int>());
    // v is now {9, 8, 5, 2, 1}
    
    // std::stable_sort (maintains relative order of equal elements)
    stable_sort(v.begin(), v.end());
    
    return 0;
}
```

### Searching
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 3, 5, 7, 9, 11};
    
    // std::find (linear search)
    auto it = find(v.begin(), v.end(), 5);
    if(it != v.end()){
        cout << "Found at index: " << (it - v.begin()) << "\n";
    }
    
    // std::binary_search (requires sorted vector)
    if(binary_search(v.begin(), v.end(), 7)){
        cout << "Found 7\n";
    }
    
    // std::lower_bound (first element >= value)
    auto lb = lower_bound(v.begin(), v.end(), 5);
    cout << "Lower bound: " << *lb << "\n";  // 5
    
    // std::upper_bound (first element > value)
    auto ub = upper_bound(v.begin(), v.end(), 5);
    cout << "Upper bound: " << *ub << "\n";  // 7
    
    return 0;
}
```

### Min/Max
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // std::min and std::max for two values
    cout << min(5, 10) << "\n";  // 5
    cout << max(5, 10) << "\n";  // 10
    
    // std::min_element and std::max_element for containers
    vector<int> v = {5, 2, 8, 1, 9};
    
    auto minIt = min_element(v.begin(), v.end());
    auto maxIt = max_element(v.begin(), v.end());
    
    cout << "Min: " << *minIt << "\n";  // 1
    cout << "Max: " << *maxIt << "\n";  // 9
    
    // std::minmax_element (returns both)
    auto [min, max] = minmax_element(v.begin(), v.end());
    cout << "Min: " << *min << ", Max: " << *max << "\n";
    
    return 0;
}
```

### Counting
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 2, 4, 2, 5};
    
    // std::count
    int count = count(v.begin(), v.end(), 2);
    cout << "Count of 2: " << count << "\n";  // 3
    
    // std::count_if (with predicate)
    int evenCount = count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    cout << "Even count: " << evenCount << "\n";  // 4
    
    return 0;
}
```

### Accumulation
```cpp
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    // std::accumulate (sum)
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "Sum: " << sum << "\n";  // 15
    
    // With custom operation (product)
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "Product: " << product << "\n";  // 120
    
    return 0;
}
```

### Reversing
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    // std::reverse (modifies in place)
    reverse(v.begin(), v.end());
    // v is now {5, 4, 3, 2, 1}
    
    for(int n : v) cout << n << " ";
    cout << "\n";
    
    return 0;
}
```

### Filling
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v(10);
    
    // std::fill (fill with value)
    fill(v.begin(), v.end(), 5);
    // v is now {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
    
    // std::fill_n (fill n elements)
    fill_n(v.begin(), 5, 10);
    // v is now {10, 10, 10, 10, 10, 5, 5, 5, 5, 5}
    
    return 0;
}
```

## Additional Algorithms

### Finding Maximum/Minimum
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> numbers = {5, 2, 8, 1, 9};
    
    int maxVal = *max_element(numbers.begin(), numbers.end());
    int minVal = *min_element(numbers.begin(), numbers.end());
    
    cout << "Max: " << maxVal << "\n";  // 9
    cout << "Min: " << minVal << "\n";  // 1
    
    return 0;
}
```

### Counting Occurrences
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};
    
    int count = count(numbers.begin(), numbers.end(), 2);
    cout << "Number of 2s: " << count << "\n";  // 3
    
    return 0;
}
```

### Checking for Element
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    if(find(numbers.begin(), numbers.end(), 3) != numbers.end()){
        cout << "Found 3\n";
    }
    
    return 0;
}
```

## Best Practices

### Magic Numbers
```cpp
// Bad
for(int i = 0; i < 100; i++){
    // what does 100 mean?
}

// Good
const int MAX_STUDENTS = 100;
for(int i = 0; i < MAX_STUDENTS; i++){
    // clear meaning
}
```

### Meaningful Variable Names
```cpp
// Bad
int d;  // what is d?
double calc(int x, int y);  // what does calc do?

// Good
int daysUntilDeadline;
double calculateArea(int width, int height);
```

### Function Design
```cpp
// Keep functions short and focused
// Each function should do ONE thing
// Use descriptive names

bool isEven(int num){
    return num % 2 == 0;
}

bool isPrime(int num){
    if(num < 2) return false;
    for(int i = 2; i * i <= num; i++){
        if(num % i == 0) return false;
    }
    return true;
}
```

### Error Handling
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream file("data.txt");
    
    if(!file){
        cerr << "Error: Could not open file\n";
        return 1;  // return error code
    }
    
    // process file...
    
    return 0;  // return success
}
```
- Use `cerr` for error messages
- Return non-zero from main() to indicate errors
- Check file operations before using them

### Code Organization and Readability
```cpp
// Bad: Everything in one function
void processData(){
    // 200 lines of mixed logic...
}

// Good: Separate concerns
void readData(){ /* ... */ }
void validateData(){ /* ... */ }
void processData(){ /* ... */ }
void displayResults(){ /* ... */ }
```

### DRY Principle (Don't Repeat Yourself)
```cpp
// Bad: Repeated code
cout << "Student 1: " << name1 << ", Grade: " << grade1 << "\n";
cout << "Student 2: " << name2 << ", Grade: " << grade2 << "\n";
cout << "Student 3: " << name3 << ", Grade: " << grade3 << "\n";

// Good: Function for repeated logic
void printStudent(const string& name, double grade){
    cout << "Student: " << name << ", Grade: " << grade << "\n";
}

printStudent(name1, grade1);
printStudent(name2, grade2);
printStudent(name3, grade3);
```

### Input Validation
```cpp
#include <iostream>
#include <limits>
using namespace std;

int getValidInteger(){
    int value;
    while(true){
        cout << "Enter an integer: ";
        if(cin >> value){
            return value;  // valid input
        } else {
            cout << "Invalid input. Try again.\n";
            cin.clear();  // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main(){
    int num = getValidInteger();
    cout << "You entered: " << num << "\n";
    return 0;
}
```
