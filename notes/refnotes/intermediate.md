# C++ Intermediate Concepts

## Pointers & Memory

### Pointer Basics
```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 10;
    int* ptr = &x;  // ptr stores the address of x
    
    cout << "Value of x: " << x << "\n";           // 10
    cout << "Address of x: " << &x << "\n";        // memory address (e.g., 0x7ffd...)
    cout << "Value of ptr: " << ptr << "\n";       // same address
    cout << "Value at ptr: " << *ptr << "\n";      // 10 (dereference)
    
    // Modify through pointer
    *ptr = 20;
    cout << "New value of x: " << x << "\n";       // 20
    
    return 0;
}
```
- `&` = address-of operator (gets memory address)
- `*` = dereference operator (accesses value at address)
- `int*` = pointer to int type

### Declaration and Dereferencing
```cpp
int x = 5;
int* p = &x;   // p points to x
int** pp = &p; // pp points to p (pointer to pointer)

cout << x << "\n";    // 5
cout << *p << "\n";   // 5 (dereference once)
cout << **pp << "\n"; // 5 (dereference twice)
```

### Address-of Operator
```cpp
int a = 42;
int* ptr = &a;  // & gets the address of a

cout << "Address of a: " << &a << "\n";
cout << "ptr holds: " << ptr << "\n";  // same address

// Can't get address of temporary
// int* bad = &(5 + 3);  // ERROR: can't take address of rvalue
```

### Pointer Arithmetic
```cpp
#include <iostream>
using namespace std;

int main(){
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // points to first element
    
    cout << *ptr << "\n";       // 10
    cout << *(ptr + 1) << "\n"; // 20
    cout << *(ptr + 2) << "\n"; // 30
    
    ptr++;  // move to next element
    cout << *ptr << "\n";  // 20
    
    ptr += 2;  // move 2 elements forward
    cout << *ptr << "\n";  // 40
    
    return 0;
}
```
- Pointer arithmetic accounts for type size
- `ptr + 1` moves by `sizeof(type)` bytes

### Null Pointers
```cpp
#include <iostream>
using namespace std;

int main(){
    // C++11: use nullptr
    int* ptr1 = nullptr;
    
    // Old C style: NULL
    int* ptr2 = NULL;
    
    // Check before dereferencing
    if(ptr1 == nullptr){
        cout << "ptr1 is null, cannot dereference\n";
    }
    
    // Always initialize pointers
    int* ptr3 = nullptr;  // good
    // int* ptr4;  // bad: uninitialized (dangling pointer)
    
    return 0;
}
```
- Always check pointers before dereferencing
- Prefer `nullptr` over `NULL` in modern C++
- Dereferencing null pointer = undefined behavior (usually crash)

### Pointers vs References
```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 10;
    
    // Reference (alias)
    int& ref = x;  // must be initialized
    ref = 20;      // changes x
    // int& ref2;  // ERROR: must initialize
    
    // Pointer
    int* ptr = &x;  // can be uninitialized (nullptr)
    *ptr = 30;      // changes x
    ptr = nullptr;  // can be reassigned
    
    cout << x << "\n";  // 30
    
    return 0;
}
```
**References:**
- Must be initialized
- Cannot be null
- Cannot be reassigned
- Syntactically cleaner

**Pointers:**
- Can be null
- Can be reassigned
- More flexible
- Require explicit dereferencing

### Dynamic Memory Allocation
```cpp
#include <iostream>
using namespace std;

int main(){
    // Allocate single int
    int* ptr = new int;
    *ptr = 42;
    cout << *ptr << "\n";
    delete ptr;  // must free memory
    
    // Allocate and initialize
    int* ptr2 = new int(100);
    cout << *ptr2 << "\n";
    delete ptr2;
    
    // Allocate array
    int* arr = new int[5];
    for(int i = 0; i < 5; i++){
        arr[i] = i * 10;
    }
    delete[] arr;  // use delete[] for arrays
    
    return 0;
}
```
- `new` allocates on heap
- Must `delete` to avoid memory leaks
- Use `delete[]` for arrays

### Memory Leaks and Prevention
```cpp
void badFunction(){
    int* ptr = new int(42);
    // forgot to delete - MEMORY LEAK
}

void goodFunction(){
    int* ptr = new int(42);
    // ... use ptr ...
    delete ptr;  // cleanup
}

void exceptionSafe(){
    int* ptr = new int(42);
    try {
        // risky code
    } catch(...) {
        delete ptr;  // cleanup even on exception
        throw;
    }
    delete ptr;
}

// Better: use smart pointers (see below)
#include <memory>
void bestFunction(){
    unique_ptr<int> ptr = make_unique<int>(42);
    // automatic cleanup, even with exceptions
}
```

### Arrays and Pointers Relationship
```cpp
#include <iostream>
using namespace std;

int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Array name decays to pointer
    int* ptr = arr;  // equivalent to &arr[0]
    
    // These are equivalent
    cout << arr[2] << "\n";    // 3
    cout << *(arr + 2) << "\n";  // 3
    cout << ptr[2] << "\n";    // 3
    cout << *(ptr + 2) << "\n";  // 3
    
    // Pointer arithmetic
    for(int i = 0; i < 5; i++){
        cout << *(ptr + i) << " ";
    }
    
    return 0;
}
```

### Pointers to Functions
```cpp
#include <iostream>
using namespace std;

int add(int a, int b){
    return a + b;
}

int multiply(int a, int b){
    return a * b;
}

int main(){
    // Declare function pointer
    int (*operation)(int, int);
    
    // Point to add function
    operation = add;
    cout << operation(5, 3) << "\n";  // 8
    
    // Point to multiply function
    operation = multiply;
    cout << operation(5, 3) << "\n";  // 15
    
    // Use with typedef for clarity
    typedef int (*BinaryOp)(int, int);
    BinaryOp op = add;
    cout << op(10, 20) << "\n";  // 30
    
    return 0;
}
```

## Dynamic Memory Management

### Heap vs Stack Memory
```cpp
// Stack allocation (automatic)
void stackExample(){
    int x = 10;  // on stack
    int arr[100];  // on stack
    // automatically destroyed when function returns
}

// Heap allocation (dynamic)
void heapExample(){
    int* ptr = new int(10);  // on heap
    int* arr = new int[100];  // on heap
    // must manually delete
    delete ptr;
    delete[] arr;
}
```

**Stack:**
- Fast allocation/deallocation
- Limited size (~1-8MB)
- Automatic cleanup
- LIFO order

**Heap:**
- Slower allocation/deallocation
- Large size (limited by RAM)
- Manual cleanup required
- Flexible lifetime

### new and delete Operators
```cpp
#include <iostream>
using namespace std;

int main(){
    // Single object
    int* p1 = new int;        // uninitialized
    int* p2 = new int(42);    // initialized
    int* p3 = new int{42};    // C++11 uniform initialization
    
    delete p1;
    delete p2;
    delete p3;
    
    // Array of objects
    int* arr = new int[10];   // uninitialized
    int* arr2 = new int[10]();  // zero-initialized
    int* arr3 = new int[5]{1, 2, 3, 4, 5};  // initialized
    
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    
    return 0;
}
```
- `new` can throw `std::bad_alloc` on failure
- `new(nothrow)` returns `nullptr` on failure
- Always match `new` with `delete`, `new[]` with `delete[]`

### new[] and delete[] for Arrays
```cpp
#include <iostream>
using namespace std;

int main(){
    int size = 5;
    int* dynamicArray = new int[size];
    
    // Use like regular array
    for(int i = 0; i < size; i++){
        dynamicArray[i] = i * 2;
    }
    
    for(int i = 0; i < size; i++){
        cout << dynamicArray[i] << " ";
    }
    cout << "\n";
    
    // MUST use delete[] for arrays
    delete[] dynamicArray;  // correct
    // delete dynamicArray;  // WRONG: undefined behavior
    
    return 0;
}
```

### Memory Leak Detection
```cpp
// Tools for detecting memory leaks:
// 1. Valgrind (Linux/Mac)
//    valgrind --leak-check=full ./program
//
// 2. AddressSanitizer (Clang/GCC)
//    compile with: g++ -fsanitize=address -g program.cpp
//
// 3. Visual Studio Memory Profiler (Windows)

// Common leak patterns:
void leak1(){
    int* ptr = new int(42);
    // forgot delete
}

void leak2(){
    int* ptr = new int(42);
    ptr = new int(100);  // lost reference to first allocation
    delete ptr;  // only deletes second
}

void leak3(){
    int* ptr = new int(42);
    if(someCondition){
        return;  // forgot to delete before return
    }
    delete ptr;
}
```

### RAII Principle
**Resource Acquisition Is Initialization**
```cpp
#include <iostream>
#include <fstream>
using namespace std;

// Bad: Manual resource management
void badExample(){
    int* ptr = new int(42);
    ifstream file("data.txt");
    
    // ... code that might throw exception ...
    
    delete ptr;
    file.close();  // might not execute if exception thrown
}

// Good: RAII with automatic cleanup
class IntWrapper {
    int* ptr;
public:
    IntWrapper(int val) : ptr(new int(val)) {}
    ~IntWrapper() { delete ptr; }  // automatic cleanup
    int get() { return *ptr; }
};

void goodExample(){
    IntWrapper wrapper(42);
    ifstream file("data.txt");
    // resources automatically cleaned up when leaving scope
    // even if exception is thrown
}
```

### Smart Pointers Introduction

#### unique_ptr
```cpp
#include <iostream>
#include <memory>
using namespace std;

int main(){
    // Create unique_ptr
    unique_ptr<int> ptr1 = make_unique<int>(42);
    cout << *ptr1 << "\n";  // 42
    
    // Cannot copy (exclusive ownership)
    // unique_ptr<int> ptr2 = ptr1;  // ERROR
    
    // Can move
    unique_ptr<int> ptr2 = move(ptr1);
    // ptr1 is now null, ptr2 owns the resource
    
    if(ptr1 == nullptr){
        cout << "ptr1 is null\n";
    }
    cout << *ptr2 << "\n";  // 42
    
    // Automatic cleanup (no delete needed)
    return 0;
}
```
- Exclusive ownership
- Cannot be copied, only moved
- Zero overhead compared to raw pointer
- Automatic cleanup

#### shared_ptr
```cpp
#include <iostream>
#include <memory>
using namespace std;

int main(){
    // Create shared_ptr
    shared_ptr<int> ptr1 = make_shared<int>(42);
    cout << "Use count: " << ptr1.use_count() << "\n";  // 1
    
    // Can copy (shared ownership)
    shared_ptr<int> ptr2 = ptr1;
    cout << "Use count: " << ptr1.use_count() << "\n";  // 2
    
    {
        shared_ptr<int> ptr3 = ptr1;
        cout << "Use count: " << ptr1.use_count() << "\n";  // 3
    }  // ptr3 destroyed
    
    cout << "Use count: " << ptr1.use_count() << "\n";  // 2
    
    // Resource deleted when last shared_ptr is destroyed
    return 0;
}
```
- Shared ownership
- Reference counting
- Slightly more overhead than unique_ptr
- Automatic cleanup when count reaches 0

#### weak_ptr
```cpp
#include <iostream>
#include <memory>
using namespace std;

int main(){
    shared_ptr<int> shared = make_shared<int>(42);
    weak_ptr<int> weak = shared;  // doesn't increase ref count
    
    cout << "Use count: " << shared.use_count() << "\n";  // 1
    
    // Check if resource still exists
    if(auto locked = weak.lock()){
        cout << "Value: " << *locked << "\n";  // 42
    }
    
    shared.reset();  // destroys resource
    
    if(weak.expired()){
        cout << "Resource no longer exists\n";
    }
    
    return 0;
}
```
- Doesn't affect reference count
- Used to break circular dependencies
- Must convert to shared_ptr to access resource


## Object-Oriented Programming Basics

### Classes vs Structs
```cpp
// Struct: public by default
struct Point {
    int x, y;  // public
    void print(){ cout << x << ", " << y << "\n"; }
};

// Class: private by default
class Rectangle {
    int width, height;  // private
public:
    void setDimensions(int w, int h){
        width = w;
        height = h;
    }
};
```
- Use struct for simple data containers (POD)
- Use class for objects with behavior and encapsulation

### Access Specifiers
```cpp
class MyClass {
private:
    int privateData;  // accessible only within class
    
protected:
    int protectedData;  // accessible in class and derived classes
    
public:
    int publicData;  // accessible everywhere
    
    void publicMethod(){
        privateData = 10;  // OK
        protectedData = 20;  // OK
    }
};

int main(){
    MyClass obj;
    // obj.privateData = 5;  // ERROR
    // obj.protectedData = 5;  // ERROR
    obj.publicData = 5;  // OK
    return 0;
}
```

### Member Functions (Methods)
```cpp
class Counter {
private:
    int count;
    
public:
    // Constructor
    Counter() : count(0) {}
    
    // Member functions
    void increment(){
        count++;
    }
    
    void decrement(){
        count--;
    }
    
    int getValue() const {  // const member function
        return count;
    }
    
    void setValue(int val){
        count = val;
    }
};

int main(){
    Counter c;
    c.increment();
    c.increment();
    cout << c.getValue() << "\n";  // 2
    return 0;
}
```

### Constructors
```cpp
class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    // Default constructor
    Student(){
        name = "Unknown";
        age = 0;
        gpa = 0.0;
    }
    
    // Parameterized constructor
    Student(string n, int a, double g){
        name = n;
        age = a;
        gpa = g;
    }
    
    // Constructor with initializer list (preferred)
    Student(string n, int a) : name(n), age(a), gpa(0.0) {}
    
    // Copy constructor
    Student(const Student& other)
        : name(other.name), age(other.age), gpa(other.gpa) {}
    
    // Move constructor (C++11)
    Student(Student&& other) noexcept
        : name(move(other.name)), age(other.age), gpa(other.gpa) {}
    
    void display(){
        cout << name << ", " << age << ", GPA: " << gpa << "\n";
    }
};

int main(){
    Student s1;  // default constructor
    Student s2("Alice", 20, 3.8);  // parameterized
    Student s3(s2);  // copy constructor
    Student s4 = move(s3);  // move constructor
    
    s1.display();
    s2.display();
    s4.display();
    
    return 0;
}
```

### Destructors
```cpp
class ResourceManager {
private:
    int* data;
    int size;
    
public:
    ResourceManager(int s) : size(s) {
        data = new int[size];
        cout << "Constructor: allocated " << size << " ints\n";
    }
    
    // Destructor: cleanup resources
    ~ResourceManager(){
        delete[] data;
        cout << "Destructor: freed memory\n";
    }
    
    void setValue(int index, int value){
        if(index >= 0 && index < size){
            data[index] = value;
        }
    }
};

int main(){
    {
        ResourceManager rm(10);
        rm.setValue(0, 42);
    }  // destructor automatically called here
    
    cout << "After scope\n";
    return 0;
}
```
- Destructor is called automatically when object goes out of scope
- Should free any resources (memory, files, etc.)
- Name is `~ClassName()`

### this Pointer
```cpp
class Box {
private:
    int width, height;
    
public:
    Box(int width, int height){
        this->width = width;  // differentiate from parameter
        this->height = height;
    }
    
    Box& setWidth(int width){
        this->width = width;
        return *this;  // enable method chaining
    }
    
    Box& setHeight(int height){
        this->height = height;
        return *this;
    }
    
    void display(){
        cout << "Box: " << width << "x" << height << "\n";
    }
};

int main(){
    Box box(10, 20);
    box.setWidth(15).setHeight(25).display();  // method chaining
    return 0;
}
```

### Const Member Functions
```cpp
class Point {
private:
    int x, y;
    
public:
    Point(int x, int y) : x(x), y(y) {}
    
    // Const member function: promises not to modify object
    int getX() const { return x; }
    int getY() const { return y; }
    
    // Non-const: can modify
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    
    void display() const {
        cout << "(" << x << ", " << y << ")\n";
        // x = 10;  // ERROR: can't modify in const function
    }
};

void printPoint(const Point& p){
    // Can only call const member functions on const object
    cout << p.getX() << ", " << p.getY() << "\n";
    // p.setX(5);  // ERROR: setX is not const
}
```

### Static Members
```cpp
class Counter {
private:
    static int objectCount;  // shared by all instances
    int id;
    
public:
    Counter(){
        objectCount++;
        id = objectCount;
    }
    
    ~Counter(){
        objectCount--;
    }
    
    int getId() const { return id; }
    
    // Static member function
    static int getObjectCount(){
        return objectCount;
        // Cannot access non-static members here
    }
};

// Must define static member outside class
int Counter::objectCount = 0;

int main(){
    cout << "Count: " << Counter::getObjectCount() << "\n";  // 0
    
    Counter c1, c2, c3;
    cout << "Count: " << Counter::getObjectCount() << "\n";  // 3
    
    {
        Counter c4;
        cout << "Count: " << Counter::getObjectCount() << "\n";  // 4
    }
    
    cout << "Count: " << Counter::getObjectCount() << "\n";  // 3
    
    return 0;
}
```

## Standard Library Containers

### std::array (Fixed-Size Arrays)
```cpp
#include <iostream>
#include <array>
using namespace std;

int main(){
    // Fixed size, stack allocated
    array<int, 5> arr = {1, 2, 3, 4, 5};
    
    cout << "Size: " << arr.size() << "\n";  // 5
    cout << "First: " << arr.front() << "\n";  // 1
    cout << "Last: " << arr.back() << "\n";  // 5
    
    // Bounds-checked access
    cout << arr.at(2) << "\n";  // 3
    // arr.at(10);  // throws out_of_range
    
    // Fill with value
    arr.fill(0);
    
    // Can be passed/returned from functions
    return 0;
}
```
- Size must be known at compile time
- No overhead compared to C array
- STL algorithms compatible

### std::deque (Double-Ended Queue)
```cpp
#include <iostream>
#include <deque>
using namespace std;

int main(){
    deque<int> dq;
    
    // Add at both ends
    dq.push_back(1);
    dq.push_front(0);
    dq.push_back(2);
    // dq: {0, 1, 2}
    
    // Remove from both ends
    dq.pop_front();  // removes 0
    dq.pop_back();   // removes 2
    
    // Random access like vector
    dq[0] = 10;
    
    return 0;
}
```
- Fast insertion/deletion at both ends
- Slightly slower random access than vector
- No contiguous memory guarantee

### std::list (Doubly-Linked List)
```cpp
#include <iostream>
#include <list>
using namespace std;

int main(){
    list<int> lst = {1, 2, 3, 4, 5};
    
    // Fast insertion/deletion anywhere
    auto it = lst.begin();
    advance(it, 2);  // move to 3rd element
    lst.insert(it, 99);  // insert before 3rd
    
    // Remove elements
    lst.remove(2);  // remove all 2s
    
    // No random access (no [] operator)
    // Must use iterators
    for(auto val : lst){
        cout << val << " ";
    }
    
    return 0;
}
```

### std::forward_list (Singly-Linked List)
```cpp
#include <forward_list>
using namespace std;

int main(){
    forward_list<int> flist = {1, 2, 3, 4, 5};
    
    // Only forward iteration
    for(int val : flist){
        cout << val << " ";
    }
    
    // Insert after position
    auto it = flist.before_begin();
    flist.insert_after(it, 0);  // insert at front
    
    // More memory efficient than list
    return 0;
}
```

### Container Selection Criteria
```cpp
// Use vector when:
// - Need random access
// - Mostly append at end
// - Want cache-friendly memory layout

// Use deque when:
// - Need fast insertion/removal at both ends
// - Need random access

// Use list when:
// - Frequent insertion/deletion in middle
// - Don't need random access
// - Iterator stability important

// Use array when:
// - Fixed size known at compile time
// - Want stack allocation

// Use forward_list when:
// - Only need forward iteration
// - Want minimal memory overhead
```

## Associative Containers

### std::map (Ordered Key-Value Pairs)
```cpp
#include <iostream>
#include <map>
using namespace std;

int main(){
    map<string, int> ages;
    
    // Insert elements
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 28;
    ages.insert({"David", 35});
    ages.insert(make_pair("Eve", 22));
    
    // Access elements
    cout << "Alice's age: " << ages["Alice"] << "\n";
    
    // Check if key exists
    if(ages.find("Bob") != ages.end()){
        cout << "Bob found\n";
    }
    
    if(ages.count("Frank") == 0){
        cout << "Frank not found\n";
    }
    
    // Iterate (sorted by key)
    for(const auto& [name, age] : ages){
        cout << name << ": " << age << "\n";
    }
    
    // Remove element
    ages.erase("Bob");
    
    return 0;
}
```

### std::set (Ordered Unique Elements)
```cpp
#include <iostream>
#include <set>
using namespace std;

int main(){
    set<int> numbers;
    
    // Insert elements (automatically sorted, duplicates ignored)
    numbers.insert(5);
    numbers.insert(2);
    numbers.insert(8);
    numbers.insert(2);  // ignored
    
    // Check if element exists
    if(numbers.count(5)){
        cout << "5 is in set\n";
    }
    
    // Iterate (sorted order)
    for(int num : numbers){
        cout << num << " ";  // 2 5 8
    }
    cout << "\n";
    
    // Remove element
    numbers.erase(5);
    
    return 0;
}
```

### std::unordered_map (Hash Table)
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    unordered_map<string, int> scores;
    
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    
    // O(1) average access time
    cout << scores["Alice"] << "\n";
    
    // Iterate (unordered)
    for(const auto& [name, score] : scores){
        cout << name << ": " << score << "\n";
    }
    
    return 0;
}
```
- Faster than map (O(1) vs O(log n))
- Unordered iteration
- Requires hash function for key type

### std::unordered_set (Hash Set)
```cpp
#include <unordered_set>
using namespace std;

int main(){
    unordered_set<int> nums = {1, 2, 3, 4, 5};
    
    // O(1) insertion and lookup
    nums.insert(6);
    
    if(nums.count(3)){
        cout << "Found 3\n";
    }
    
    return 0;
}
```

### std::multimap and std::multiset
```cpp
#include <map>
#include <set>
using namespace std;

int main(){
    // multimap: allows duplicate keys
    multimap<string, int> scores;
    scores.insert({"Alice", 90});
    scores.insert({"Alice", 95});  // allowed
    scores.insert({"Bob", 87});
    
    // multiset: allows duplicate values
    multiset<int> numbers = {1, 2, 2, 3, 3, 3};
    
    cout << "Count of 3: " << numbers.count(3) << "\n";  // 3
    
    return 0;
}
```


### Common Container Operations
```cpp
// All containers support:
container.size()      // number of elements
container.empty()     // check if empty
container.clear()     // remove all elements

// Most containers support:
container.insert(value)     // add element
container.erase(iterator)   // remove element
container.find(value)       // search for element
container.count(value)      // count occurrences

// Sequence containers (vector, deque, list):
container.push_back(value)
container.pop_back()
container.front()
container.back()

// Associative containers (map, set):
container[key]          // map only
container.insert(value)
container.erase(key)
```

## Exception Handling

### try-catch Blocks
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int divide(int a, int b){
    if(b == 0){
        throw runtime_error("Division by zero!");
    }
    return a / b;
}

int main(){
    try {
        int result = divide(10, 0);
        cout << result << "\n";
    }
    catch(const runtime_error& e){
        cerr << "Error: " << e.what() << "\n";
    }
    
    cout << "Program continues\n";
    return 0;
}
```

### Throw Statements
```cpp
#include <stdexcept>
using namespace std;

void validateAge(int age){
    if(age < 0){
        throw invalid_argument("Age cannot be negative");
    }
    if(age > 150){
        throw out_of_range("Age too large");
    }
}

int main(){
    try {
        validateAge(-5);
    }
    catch(const invalid_argument& e){
        cerr << "Invalid argument: " << e.what() << "\n";
    }
    catch(const out_of_range& e){
        cerr << "Out of range: " << e.what() << "\n";
    }
    
    return 0;
}
```

### Standard Exceptions
```cpp
#include <exception>
#include <stdexcept>
#include <iostream>
using namespace std;

// std::exception hierarchy:
//   exception
//   ├── logic_error
//   │   ├── invalid_argument
//   │   ├── domain_error
//   │   ├── length_error
//   │   └── out_of_range
//   └── runtime_error
//       ├── range_error
//       ├── overflow_error
//       └── underflow_error

void testExceptions(){
    try {
        // Your code here
        throw runtime_error("Something went wrong");
    }
    catch(const invalid_argument& e){
        cerr << "Invalid argument\n";
    }
    catch(const out_of_range& e){
        cerr << "Out of range\n";
    }
    catch(const runtime_error& e){
        cerr << "Runtime error: " << e.what() << "\n";
    }
    catch(const exception& e){  // catch-all for std exceptions
        cerr << "Unknown exception: " << e.what() << "\n";
    }
    catch(...){  // catch absolutely everything
        cerr << "Unknown error\n";
    }
}
```

### Custom Exceptions
```cpp
#include <exception>
#include <string>
using namespace std;

class MyException : public exception {
private:
    string message;
    
public:
    MyException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

void riskyFunction(){
    throw MyException("Custom error occurred");
}

int main(){
    try {
        riskyFunction();
    }
    catch(const MyException& e){
        cerr << "Caught: " << e.what() << "\n";
    }
    
    return 0;
}
```

### Exception Safety Guarantees
```cpp
// 1. No-throw guarantee: never throws exceptions
void noThrow() noexcept {
    // guaranteed not to throw
}

// 2. Strong guarantee: if exception thrown, state unchanged
void strongGuarantee(vector<int>& vec){
    vector<int> temp = vec;  // make copy
    temp.push_back(42);      // might throw
    vec = move(temp);        // no-throw swap
}

// 3. Basic guarantee: if exception thrown, no resource leaks
class BasicGuarantee {
    int* data;
public:
    void allocate(int size){
        int* temp = new int[size];  // might throw
        delete[] data;              // cleanup old
        data = temp;                // commit
    }
};

// 4. No guarantee: might leak or corrupt (avoid this!)
```

### RAII and Exception Safety
```cpp
#include <fstream>
#include <mutex>
#include <memory>
using namespace std;

// Bad: manual resource management
void badFunction(){
    int* ptr = new int(42);
    ifstream file("data.txt");
    
    // if exception here, memory leaked and file not closed
    processData();
    
    delete ptr;
    file.close();
}

// Good: RAII - resources cleaned up automatically
void goodFunction(){
    unique_ptr<int> ptr = make_unique<int>(42);
    ifstream file("data.txt");
    lock_guard<mutex> lock(myMutex);
    
    // even if exception, everything cleaned up automatically
    processData();
}
```

## Templates Basics

### Function Templates
```cpp
#include <iostream>
using namespace std;

// Template function for any type
template<typename T>
T max(T a, T b){
    return (a > b) ? a : b;
}

// Template with multiple type parameters
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main(){
    cout << max(10, 20) << "\n";         // int version
    cout << max(3.14, 2.71) << "\n";     // double version
    cout << max('a', 'z') << "\n";       // char version
    
    cout << add(5, 3.14) << "\n";        // mixed types
    
    return 0;
}
```

### Class Templates
```cpp
#include <iostream>
using namespace std;

template<typename T>
class Box {
private:
    T value;
    
public:
    Box(T val) : value(val) {}
    
    T getValue() const { return value; }
    void setValue(T val) { value = val; }
    
    void display() const {
        cout << "Box contains: " << value << "\n";
    }
};

int main(){
    Box<int> intBox(42);
    Box<string> strBox("Hello");
    Box<double> dblBox(3.14);
    
    intBox.display();
    strBox.display();
    dblBox.display();
    
    return 0;
}
```

### Template Parameters
```cpp
// Type parameter
template<typename T>
class Container {
    T value;
};

// Non-type parameter (compile-time constant)
template<typename T, int Size>
class Array {
    T data[Size];
public:
    int size() const { return Size; }
};

// Default template parameter
template<typename T = int>
class DefaultBox {
    T value;
};

int main(){
    Array<int, 10> arr;
    cout << arr.size() << "\n";  // 10
    
    DefaultBox<> box;  // uses int as default
    
    return 0;
}
```

### Template Specialization (Basic)
```cpp
#include <iostream>
using namespace std;

// Generic template
template<typename T>
class Printer {
public:
    void print(T value){
        cout << "Generic: " << value << "\n";
    }
};

// Full specialization for bool
template<>
class Printer<bool> {
public:
    void print(bool value){
        cout << "Bool: " << (value ? "true" : "false") << "\n";
    }
};

int main(){
    Printer<int> intPrinter;
    intPrinter.print(42);  // Generic: 42
    
    Printer<bool> boolPrinter;
    boolPrinter.print(true);  // Bool: true
    
    return 0;
}
```

### Common Use Cases
```cpp
// 1. Generic containers
template<typename T>
class Stack {
    vector<T> data;
public:
    void push(const T& item) { data.push_back(item); }
    T pop() { T item = data.back(); data.pop_back(); return item; }
};

// 2. Generic algorithms
template<typename T>
T sum(const vector<T>& vec){
    T total = T();
    for(const T& val : vec){
        total += val;
    }
    return total;
}

// 3. Type-safe wrappers
template<typename T>
class SmartPointer {
    T* ptr;
public:
    SmartPointer(T* p) : ptr(p) {}
    ~SmartPointer() { delete ptr; }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};

int main(){
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << sum(numbers) << "\n";  // 15
    
    SmartPointer<int> ptr(new int(42));
    cout << *ptr << "\n";
    
    return 0;
}
```
