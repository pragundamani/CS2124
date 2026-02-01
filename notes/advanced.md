# C++ Advanced Concepts

## Advanced Object-Oriented Programming

### Inheritance (Single, Multiple)
```cpp
#include <iostream>
using namespace std;

// Base class
class Animal {
protected:
    string name;
public:
    Animal(string n) : name(n) {}
    void eat() { cout << name << " is eating\n"; }
};

// Single inheritance
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    void bark() { cout << name << " is barking\n"; }
};

// Multiple inheritance
class Flyable {
public:
    void fly() { cout << "Flying\n"; }
};

class Swimmable {
public:
    void swim() { cout << "Swimming\n"; }
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(string n) : Animal(n) {}
};

int main(){
    Dog dog("Buddy");
    dog.eat();
    dog.bark();
    
    Duck duck("Donald");
    duck.eat();
    duck.fly();
    duck.swim();
    
    return 0;
}
```

### Virtual Functions and Polymorphism
```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;  // pure virtual
    virtual void display() const {
        cout << "This is a shape\n";
    }
    virtual ~Shape() {}  // virtual destructor
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    void display() const override {
        cout << "Circle with radius " << radius << "\n";
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    void display() const override {
        cout << "Rectangle " << width << "x" << height << "\n";
    }
};

void printShapeInfo(const Shape& shape){
    shape.display();
    cout << "Area: " << shape.area() << "\n";
}

int main(){
    Circle c(5.0);
    Rectangle r(4.0, 6.0);
    
    printShapeInfo(c);  // polymorphism in action
    printShapeInfo(r);
    
    return 0;
}
```

### Abstract Classes and Pure Virtual Functions
```cpp
// Abstract class (has at least one pure virtual function)
class AbstractDatabase {
public:
    virtual void connect() = 0;  // pure virtual
    virtual void disconnect() = 0;
    virtual void query(const string& sql) = 0;
    virtual ~AbstractDatabase() {}
};

class MySQLDatabase : public AbstractDatabase {
public:
    void connect() override {
        cout << "Connecting to MySQL\n";
    }
    
    void disconnect() override {
        cout << "Disconnecting from MySQL\n";
    }
    
    void query(const string& sql) override {
        cout << "Executing MySQL query: " << sql << "\n";
    }
};

// Cannot instantiate abstract class
// AbstractDatabase db;  // ERROR

// Can use pointers/references to abstract class
void useDatabase(AbstractDatabase& db){
    db.connect();
    db.query("SELECT * FROM users");
    db.disconnect();
}
```

### Virtual Destructors
```cpp
class Base {
public:
    virtual ~Base() {  // virtual destructor
        cout << "Base destructor\n";
    }
};

class Derived : public Base {
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() override {
        delete[] data;
        cout << "Derived destructor\n";
    }
};

int main(){
    Base* ptr = new Derived();
    delete ptr;  // calls both destructors correctly
    // Without virtual destructor, only Base destructor called = memory leak!
    
    return 0;
}
```
- **Always make base class destructors virtual** when using polymorphism

### Function Overriding vs Overloading
```cpp
class Base {
public:
    void func(int x) { cout << "Base::func(int)\n"; }
    virtual void process() { cout << "Base::process()\n"; }
};

class Derived : public Base {
public:
    // Overriding (replaces base class function)
    void process() override { cout << "Derived::process()\n"; }
    
    // Overloading (different signature)
    void func(double x) { cout << "Derived::func(double)\n"; }
    
    // Hiding (same signature, not virtual)
    void func(int x) { cout << "Derived::func(int)\n"; }
};
```
- **Overriding**: virtual function in derived class replaces base version
- **Overloading**: functions with different signatures
- **Hiding**: non-virtual function in derived hides base version

### Diamond Problem and Virtual Inheritance
```cpp
class Animal {
public:
    string name;
    Animal(string n) : name(n) {}
};

class Mammal : virtual public Animal {  // virtual inheritance
public:
    Mammal(string n) : Animal(n) {}
};

class WingedAnimal : virtual public Animal {
public:
    WingedAnimal(string n) : Animal(n) {}
};

class Bat : public Mammal, public WingedAnimal {
public:
    Bat(string n) : Animal(n), Mammal(n), WingedAnimal(n) {}
};

int main(){
    Bat bat("Batty");
    // Without virtual inheritance, bat would have two copies of Animal
    // With virtual inheritance, only one copy
    cout << bat.name << "\n";  // OK
    
    return 0;
}
```

### Composition vs Inheritance
```cpp
// Inheritance (IS-A relationship)
class Animal {
public:
    void breathe() { cout << "Breathing\n"; }
};

class Dog : public Animal {  // Dog IS-A Animal
public:
    void bark() { cout << "Barking\n"; }
};

// Composition (HAS-A relationship)
class Engine {
public:
    void start() { cout << "Engine started\n"; }
};

class Car {
    Engine engine;  // Car HAS-A Engine
public:
    void drive() {
        engine.start();
        cout << "Car is driving\n";
    }
};
```
**Prefer composition over inheritance when:**
- Relationship is HAS-A, not IS-A
- Need more flexibility
- Want to avoid deep inheritance hierarchies

## Operator Overloading

### Overloadable Operators
```cpp
// Almost all operators can be overloaded:
+  -  *  /  %  ^  &  |  ~
!  =  <  >  +=  -=  *=  /=  %=
^=  &=  |=  <<  >>  >>=  <<=  ==  !=
<=  >=  &&  ||  ++  --  ,  ->*  ->
()  []  new  delete  new[]  delete[]

// Cannot overload:
::  .*  .  ?:  sizeof  typeid
```

### Member vs Non-Member Operator Functions
```cpp
class Complex {
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Member operator (implicit first parameter is this)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // Friend non-member operator (access to private members)
    friend ostream& operator<<(ostream& os, const Complex& c);
};

// Non-member operator
ostream& operator<<(ostream& os, const Complex& c){
    os << c.real << " + " << c.imag << "i";
    return os;
}

// Use non-member when:
// - Left operand is not your class (e.g., <<, >>)
// - Want symmetry (e.g., a + b and b + a)
```

### Assignment Operator (Copy and Move)
```cpp
class String {
    char* data;
    size_t length;
    
public:
    // Copy assignment operator
    String& operator=(const String& other){
        if(this == &other) return *this;  // self-assignment check
        
        delete[] data;  // clean up old data
        
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        
        return *this;
    }
    
    // Move assignment operator
    String& operator=(String&& other) noexcept {
        if(this == &other) return *this;
        
        delete[] data;
        
        data = other.data;
        length = other.length;
        
        other.data = nullptr;  // leave other in valid state
        other.length = 0;
        
        return *this;
    }
};
```

### Arithmetic Operators
```cpp
class Vector2D {
    double x, y;
public:
    Vector2D(double x, double y) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    Vector2D& operator+=(const Vector2D& other){
        x += other.x;
        y += other.y;
        return *this;
    }
    
    friend Vector2D operator*(double scalar, const Vector2D& v){
        return v * scalar;  // enable scalar * vector
    }
};
```

### Comparison Operators
```cpp
class Person {
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    
    bool operator==(const Person& other) const {
        return age == other.age && name == other.name;
    }
    
    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Person& other) const {
        return age < other.age;
    }
    
    bool operator>(const Person& other) const {
        return other < *this;
    }
    
    bool operator<=(const Person& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Person& other) const {
        return !(*this < other);
    }
};
```

### Stream Operators (<<, >>)
```cpp
class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}
    
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
};

ostream& operator<<(ostream& os, const Point& p){
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

istream& operator>>(istream& is, Point& p){
    char paren, comma;
    is >> paren >> p.x >> comma >> p.y >> paren;
    return is;
}

int main(){
    Point p(3, 4);
    cout << p << "\n";  // (3, 4)
    
    Point p2(0, 0);
    cin >> p2;  // input: (5,6)
    cout << p2 << "\n";  // (5, 6)
    
    return 0;
}
```

### Subscript Operator []
```cpp
class Array {
    int* data;
    size_t size;
public:
    Array(size_t s) : size(s) {
        data = new int[size];
    }
    
    ~Array() { delete[] data; }
    
    int& operator[](size_t index){
        return data[index];
    }
    
    const int& operator[](size_t index) const {
        return data[index];
    }
};

int main(){
    Array arr(5);
    arr[0] = 10;
    arr[1] = 20;
    cout << arr[0] << "\n";
    
    return 0;
}
```

### Function Call Operator ()
```cpp
class Adder {
    int base;
public:
    Adder(int b) : base(b) {}
    
    int operator()(int x) const {
        return base + x;
    }
};

int main(){
    Adder add10(10);
    cout << add10(5) << "\n";   // 15
    cout << add10(20) << "\n";  // 30
    
    return 0;
}
```
- Objects with operator() are called "functors" or "function objects"


## Move Semantics & Rvalue References

### Lvalues vs Rvalues
```cpp
int x = 5;       // x is lvalue (has address)
int y = x + 2;   // x is lvalue, (x + 2) is rvalue (temporary)

int* ptr = &x;   // OK: x is lvalue
// int* ptr2 = &(x + 2);  // ERROR: can't take address of rvalue

// Lvalue: has identity, persists beyond expression
// Rvalue: temporary, doesn't persist

string getName() { return "John"; }
string name = getName();  // getName() returns rvalue
```

### Rvalue References (&&)
```cpp
void func(int& x) { cout << "Lvalue reference\n"; }
void func(int&& x) { cout << "Rvalue reference\n"; }

int main(){
    int a = 5;
    func(a);      // calls lvalue version
    func(10);     // calls rvalue version
    func(a + 2);  // calls rvalue version
    
    int&& r = 10;  // rvalue reference
    // r is itself an lvalue (has name and address)
    
    return 0;
}
```

### Move Constructors
```cpp
class String {
    char* data;
    size_t length;
public:
    // Copy constructor (expensive for large data)
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "Copy constructor\n";
    }
    
    // Move constructor (cheap, steals resources)
    String(String&& other) noexcept {
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
        cout << "Move constructor\n";
    }
    
    ~String() { delete[] data; }
};

String makeString() {
    String s("Hello");
    return s;  // moves, not copies
}

int main(){
    String s1 = makeString();  // move constructor called
    String s2 = s1;            // copy constructor called
    
    return 0;
}
```

### Move Assignment Operators
```cpp
class Buffer {
    int* data;
    size_t size;
public:
    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if(this == &other) return *this;
        
        delete[] data;  // cleanup current resources
        
        data = other.data;
        size = other.size;
        
        other.data = nullptr;
        other.size = 0;
        
        return *this;
    }
};
```

### std::move
```cpp
#include <utility>
#include <vector>
using namespace std;

int main(){
    vector<int> v1 = {1, 2, 3, 4, 5};
    
    // Copy (expensive)
    vector<int> v2 = v1;
    
    // Move (cheap) - v1 becomes empty
    vector<int> v3 = move(v1);
    
    cout << "v1 size: " << v1.size() << "\n";  // 0
    cout << "v3 size: " << v3.size() << "\n";  // 5
    
    return 0;
}
```
- `std::move` doesn't move anything, it just casts to rvalue reference
- Actual move happens in move constructor/assignment

### Perfect Forwarding
```cpp
#include <utility>
using namespace std;

template<typename T>
void wrapper(T&& arg) {
    // Forward arg preserving its value category
    process(forward<T>(arg));
}

void process(int& x) { cout << "Lvalue\n"; }
void process(int&& x) { cout << "Rvalue\n"; }

int main(){
    int a = 5;
    wrapper(a);      // forwards as lvalue
    wrapper(10);     // forwards as rvalue
    
    return 0;
}
```

### Copy Elision and RVO
```cpp
class Object {
public:
    Object() { cout << "Constructor\n"; }
    Object(const Object&) { cout << "Copy\n"; }
    Object(Object&&) noexcept { cout << "Move\n"; }
};

Object createObject() {
    return Object();  // RVO: no copy or move
}

int main(){
    Object obj = createObject();  // typically just "Constructor"
    // Compiler elides copy/move (Return Value Optimization)
    
    return 0;
}
```
- RVO = Return Value Optimization
- Compiler can elide copies/moves even if they have side effects
- Guaranteed in C++17 for temporaries

## Advanced Templates

### Template Specialization (Full and Partial)
```cpp
// Primary template
template<typename T>
class Container {
public:
    void info() { cout << "Generic container\n"; }
};

// Full specialization for bool
template<>
class Container<bool> {
public:
    void info() { cout << "Bool container\n"; }
};

// Partial specialization for pointers
template<typename T>
class Container<T*> {
public:
    void info() { cout << "Pointer container\n"; }
};

int main(){
    Container<int> c1;
    c1.info();  // Generic container
    
    Container<bool> c2;
    c2.info();  // Bool container
    
    Container<int*> c3;
    c3.info();  // Pointer container
    
    return 0;
}
```

### Variadic Templates
```cpp
#include <iostream>
using namespace std;

// Base case: no arguments
void print() {
    cout << "\n";
}

// Recursive case: at least one argument
template<typename T, typename... Args>
void print(T first, Args... args) {
    cout << first << " ";
    print(args...);  // recursive call with remaining args
}

// Fold expressions (C++17)
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // fold with +
}

int main(){
    print(1, 2.5, "hello", 'c');  // 1 2.5 hello c
    
    cout << sum(1, 2, 3, 4, 5) << "\n";  // 15
    
    return 0;
}
```

### Template Template Parameters
```cpp
template<typename T, template<typename> class Container>
class Stack {
    Container<T> data;
public:
    void push(const T& item) { data.push_back(item); }
    // ...
};

// Usage:
Stack<int, vector> intStack;
Stack<string, list> strStack;
```

### SFINAE (Substitution Failure Is Not An Error)
```cpp
#include <type_traits>
using namespace std;

// Only enabled for integral types
template<typename T>
typename enable_if<is_integral<T>::value, T>::type
double_value(T x) {
    return x * 2;
}

// Only enabled for floating point types
template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type
double_value(T x) {
    return x * 2.0;
}

int main(){
    cout << double_value(5) << "\n";      // uses integral version
    cout << double_value(3.14) << "\n";   // uses floating point version
    
    return 0;
}
```

### Concepts (C++20)
```cpp
#include <concepts>
using namespace std;

// Define concept
template<typename T>
concept Numeric = is_arithmetic_v<T>;

// Use concept
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Concept with requires clause
template<typename T>
concept HasPrint = requires(T t) {
    { t.print() } -> same_as<void>;
};

template<HasPrint T>
void callPrint(T obj) {
    obj.print();
}
```

### Type Traits
```cpp
#include <type_traits>
#include <iostream>
using namespace std;

template<typename T>
void checkType() {
    if constexpr (is_integral_v<T>) {
        cout << "Integral type\n";
    } else if constexpr (is_floating_point_v<T>) {
        cout << "Floating point type\n";
    } else if constexpr (is_pointer_v<T>) {
        cout << "Pointer type\n";
    } else {
        cout << "Other type\n";
    }
}

int main(){
    checkType<int>();      // Integral type
    checkType<double>();   // Floating point type
    checkType<int*>();     // Pointer type
    checkType<string>();   // Other type
    
    return 0;
}
```

## Lambda Expressions

### Lambda Syntax and Captures
```cpp
// Basic lambda
auto lambda = []() { cout << "Hello\n"; };
lambda();

// Lambda with parameters and return type
auto add = [](int a, int b) -> int { return a + b; };
cout << add(3, 5) << "\n";  // 8

// Capture by value [=]
int x = 10;
auto byValue = [=]() { cout << x << "\n"; };  // captures copy of x

// Capture by reference [&]
auto byRef = [&]() { x = 20; };  // can modify x
byRef();
cout << x << "\n";  // 20

// Mixed captures
int a = 1, b = 2;
auto mixed = [a, &b]() { cout << a << " " << b << "\n"; };

// Capture all by value, specific by reference
auto specific = [=, &b]() { cout << a << " " << b << "\n"; };
```

### Capture Modes
```cpp
int x = 10, y = 20;

[=]()  { }     // capture all by value
[&]()  { }     // capture all by reference
[x]()  { }     // capture x by value
[&x]() { }     // capture x by reference
[x, &y]() { }  // capture x by value, y by reference
[=, &y]() { }  // capture all by value except y (by reference)
[&, x]() { }   // capture all by reference except x (by value)

// Capture this pointer (for member functions)
[this]() { memberVar = 10; }

// Capture by copy of this (C++17)
[*this]() { /* ... */ }
```

### Mutable Lambdas
```cpp
int x = 10;

// Normal lambda: can't modify captured values
auto lambda1 = [x]() { 
    // x = 20;  // ERROR
    cout << x << "\n";
};

// Mutable lambda: can modify captured values
auto lambda2 = [x]() mutable {
    x = 20;  // OK (modifies copy, not original)
    cout << x << "\n";
};

lambda2();  // 20
cout << x << "\n";  // still 10 (original unchanged)
```

### Lambda with Parameters and Return Types
```cpp
// Inferred return type
auto multiply = [](int a, int b) { return a * b; };

// Explicit return type
auto divide = [](double a, double b) -> double {
    return b != 0 ? a / b : 0;
};

// Multiple statements
auto process = [](int x) -> int {
    if (x < 0) return 0;
    if (x > 100) return 100;
    return x;
};
```

### Generic Lambdas (C++14)
```cpp
// Auto parameters (generic lambda)
auto print = [](auto x) { cout << x << "\n"; };

print(42);
print(3.14);
print("hello");

// Generic lambda with operators
auto add = [](auto a, auto b) { return a + b; };

cout << add(1, 2) << "\n";         // 3
cout << add(1.5, 2.5) << "\n";     // 4.0
cout << add(string("Hello"), string(" World")) << "\n";  // Hello World
```

### Lambda Best Practices
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Use with STL algorithms
    auto isEven = [](int x) { return x % 2 == 0; };
    int evenCount = count_if(numbers.begin(), numbers.end(), isEven);
    
    // Immediately invoked lambda expression (IILE)
    int result = [](int x, int y) { return x + y; }(10, 20);
    
    // Lambda for callbacks
    auto button_click = [](string msg) {
        cout << "Button clicked: " << msg << "\n";
    };
    
    button_click("Submit");
    
    return 0;
}
```


## STL Algorithms Advanced

### Transform Operations
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> result(v.size());
    
    // Transform each element
    transform(v.begin(), v.end(), result.begin(), 
              [](int x) { return x * 2; });
    // result: {2, 4, 6, 8, 10}
    
    // Transform two ranges
    vector<int> v2 = {1, 1, 1, 1, 1};
    transform(v.begin(), v.end(), v2.begin(), result.begin(),
              [](int a, int b) { return a + b; });
    // result: {2, 3, 4, 5, 6}
    
    return 0;
}
```

### Partitioning
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 5, 3, 8, 2, 9, 4};
    
    // Partition: evens before odds
    partition(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    // v: {4, 2, 8, 5, 3, 9, 1} (order within partitions not guaranteed)
    
    // Stable partition: maintains relative order
    stable_partition(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    
    // Partition point
    auto it = partition_point(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    cout << "First odd: " << *it << "\n";
    
    return 0;
}
```

### Removing Elements
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 2, 4, 2, 5};
    
    // remove: moves elements to end, returns iterator to new end
    auto newEnd = remove(v.begin(), v.end(), 2);
    v.erase(newEnd, v.end());  // actually remove
    // v: {1, 3, 4, 5}
    
    // remove_if: with predicate
    vector<int> v2 = {1, 2, 3, 4, 5, 6};
    auto newEnd2 = remove_if(v2.begin(), v2.end(), 
                             [](int x) { return x % 2 == 0; });
    v2.erase(newEnd2, v2.end());
    // v2: {1, 3, 5}
    
    return 0;
}
```

### Unique Operations
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 1, 2, 2, 3, 3, 4};
    
    // Remove consecutive duplicates
    auto newEnd = unique(v.begin(), v.end());
    v.erase(newEnd, v.end());
    // v: {1, 2, 3, 4}
    
    // With custom comparator
    vector<int> v2 = {1, 2, 3, 4, 5, 6};
    auto newEnd2 = unique(v2.begin(), v2.end(),
                          [](int a, int b) { return (a % 2) == (b % 2); });
    v2.erase(newEnd2, v2.end());
    // v2: {1, 2} (one odd, one even)
    
    return 0;
}
```

### Set Operations
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {3, 4, 5, 6, 7};
    vector<int> result;
    
    // Union
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(),
              back_inserter(result));
    // result: {1, 2, 3, 4, 5, 6, 7}
    
    result.clear();
    // Intersection
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                     back_inserter(result));
    // result: {3, 4, 5}
    
    result.clear();
    // Difference (in v1 but not in v2)
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                   back_inserter(result));
    // result: {1, 2}
    
    return 0;
}
```

### Heap Operations
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {3, 1, 4, 1, 5, 9};
    
    // Make heap (max heap by default)
    make_heap(v.begin(), v.end());
    // v is now a heap: largest element at front
    
    cout << "Max: " << v.front() << "\n";  // 9
    
    // Add element to heap
    v.push_back(10);
    push_heap(v.begin(), v.end());
    
    // Remove max element
    pop_heap(v.begin(), v.end());  // moves max to end
    v.pop_back();  // actually remove
    
    // Sort heap
    sort_heap(v.begin(), v.end());
    // v is now sorted
    
    return 0;
}
```

### Permutations
```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3};
    
    // Generate all permutations
    do {
        for(int x : v) cout << x << " ";
        cout << "\n";
    } while(next_permutation(v.begin(), v.end()));
    
    // Output:
    // 1 2 3
    // 1 3 2
    // 2 1 3
    // 2 3 1
    // 3 1 2
    // 3 2 1
    
    // prev_permutation: generates in reverse order
    
    return 0;
}
```

### Custom Comparators and Predicates
```cpp
#include <algorithm>
#include <vector>
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
    
    // Sort by age
    sort(people.begin(), people.end(),
         [](const Person& a, const Person& b) {
             return a.age < b.age;
         });
    
    // Find first person over 30
    auto it = find_if(people.begin(), people.end(),
                      [](const Person& p) { return p.age > 30; });
    
    // Count people under 30
    int count = count_if(people.begin(), people.end(),
                         [](const Person& p) { return p.age < 30; });
    
    return 0;
}
```

## Iterators

### Iterator Categories
```cpp
// 1. Input Iterator (read once, forward only)
//    - istream_iterator

// 2. Output Iterator (write once, forward only)
//    - ostream_iterator, back_inserter

// 3. Forward Iterator (read/write, forward only)
//    - forward_list iterators

// 4. Bidirectional Iterator (read/write, forward and backward)
//    - list, set, map iterators

// 5. Random Access Iterator (read/write, arbitrary jumps)
//    - vector, deque, array iterators

// Each category supports operations of previous categories plus more
```

### Iterator Operations
```cpp
#include <vector>
#include <iterator>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin();
    
    // All iterators
    ++it;           // advance
    *it;            // dereference
    it == v.end();  // compare
    
    // Bidirectional iterators (also)
    --it;           // move backward
    
    // Random access iterators (also)
    it += 3;        // jump forward
    it -= 2;        // jump backward
    it[2];          // subscript
    it < v.end();   // relational comparison
    
    // Iterator functions
    advance(it, 2);                    // move iterator
    auto dist = distance(it, v.end()); // distance between iterators
    auto next_it = next(it);           // next iterator
    auto prev_it = prev(it);           // previous iterator
    
    return 0;
}
```

### Reverse Iterators
```cpp
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    // Iterate in reverse
    for(auto it = v.rbegin(); it != v.rend(); ++it){
        cout << *it << " ";  // 5 4 3 2 1
    }
    cout << "\n";
    
    // Convert between normal and reverse iterators
    auto rit = v.rbegin();
    auto it = rit.base();  // corresponding forward iterator
    
    return 0;
}
```

### Insert Iterators
```cpp
#include <iterator>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    
    // back_inserter: inserts at end
    auto back_it = back_inserter(v);
    *back_it = 1;
    *back_it = 2;
    // v: {1, 2}
    
    // front_inserter: inserts at front (for deque, list)
    deque<int> d;
    auto front_it = front_inserter(d);
    *front_it = 1;
    *front_it = 2;
    // d: {2, 1}
    
    // inserter: inserts at specified position
    auto insert_it = inserter(v, v.begin());
    *insert_it = 0;
    // v: {0, 1, 2}
    
    return 0;
}
```

### Stream Iterators
```cpp
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    // istream_iterator: read from stream
    ifstream file("numbers.txt");
    istream_iterator<int> in_it(file);
    istream_iterator<int> eof;
    
    vector<int> numbers(in_it, eof);
    
    // ostream_iterator: write to stream
    ostream_iterator<int> out_it(cout, " ");
    copy(numbers.begin(), numbers.end(), out_it);
    
    return 0;
}
```

### Custom Iterators
```cpp
class Range {
    int current, end;
public:
    class Iterator {
        int value;
    public:
        Iterator(int v) : value(v) {}
        int operator*() const { return value; }
        Iterator& operator++() { ++value; return *this; }
        bool operator!=(const Iterator& other) const {
            return value != other.value;
        }
    };
    
    Range(int start, int end) : current(start), end(end) {}
    Iterator begin() const { return Iterator(current); }
    Iterator end() const { return Iterator(end); }
};

int main(){
    for(int i : Range(1, 10)){
        cout << i << " ";  // 1 2 3 4 5 6 7 8 9
    }
    
    return 0;
}
```

## Multithreading Basics

### std::thread
```cpp
#include <iostream>
#include <thread>
using namespace std;

void printMessage(string msg){
    cout << msg << "\n";
}

int main(){
    // Create thread
    thread t1(printMessage, "Hello from thread 1");
    thread t2(printMessage, "Hello from thread 2");
    
    // Wait for threads to finish
    t1.join();
    t2.join();
    
    cout << "Main thread done\n";
    
    return 0;
}
```

### Thread Synchronization
```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
int counter = 0;

void increment(){
    for(int i = 0; i < 1000; ++i){
        mtx.lock();
        ++counter;
        mtx.unlock();
    }
}

int main(){
    thread t1(increment);
    thread t2(increment);
    
    t1.join();
    t2.join();
    
    cout << "Counter: " << counter << "\n";  // 2000
    
    return 0;
}
```

### lock_guard and unique_lock
```cpp
#include <mutex>
using namespace std;

mutex mtx;

void safeIncrement(int& counter){
    // lock_guard: automatic lock/unlock
    lock_guard<mutex> lock(mtx);
    ++counter;
}  // automatically unlocks

void flexibleIncrement(int& counter){
    // unique_lock: more flexible
    unique_lock<mutex> lock(mtx);
    ++counter;
    lock.unlock();  // can manually unlock
    // do other work
    lock.lock();    // can relock
    ++counter;
}
```

### Condition Variables
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

mutex mtx;
condition_variable cv;
queue<int> dataQueue;

void producer(){
    for(int i = 1; i <= 5; ++i){
        {
            lock_guard<mutex> lock(mtx);
            dataQueue.push(i);
            cout << "Produced: " << i << "\n";
        }
        cv.notify_one();  // wake up consumer
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(){
    for(int i = 0; i < 5; ++i){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return !dataQueue.empty(); });
        
        int data = dataQueue.front();
        dataQueue.pop();
        cout << "Consumed: " << data << "\n";
    }
}

int main(){
    thread t1(producer);
    thread t2(consumer);
    
    t1.join();
    t2.join();
    
    return 0;
}
```

### Atomic Operations
```cpp
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> counter(0);

void increment(){
    for(int i = 0; i < 1000; ++i){
        ++counter;  // atomic operation, no mutex needed
    }
}

int main(){
    thread t1(increment);
    thread t2(increment);
    
    t1.join();
    t2.join();
    
    cout << "Counter: " << counter << "\n";  // 2000
    
    return 0;
}
```

### Thread-Safe Data Structures
```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

template<typename T>
class ThreadSafeQueue {
    queue<T> data;
    mutable mutex mtx;
    condition_variable cv;
    
public:
    void push(T value){
        lock_guard<mutex> lock(mtx);
        data.push(move(value));
        cv.notify_one();
    }
    
    T pop(){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]{ return !data.empty(); });
        T value = move(data.front());
        data.pop();
        return value;
    }
    
    bool empty() const {
        lock_guard<mutex> lock(mtx);
        return data.empty();
    }
};
```

### Race Conditions and Deadlocks
```cpp
// Race condition: multiple threads access shared data
int counter = 0;  // shared
void badIncrement(){
    ++counter;  // NOT atomic: read, increment, write
    // Two threads can read same value, both increment, write same result
}

// Deadlock: threads wait for each other
mutex m1, m2;

void thread1(){
    lock_guard<mutex> lock1(m1);
    lock_guard<mutex> lock2(m2);  // waits for m2
}

void thread2(){
    lock_guard<mutex> lock2(m2);
    lock_guard<mutex> lock1(m1);  // waits for m1 - DEADLOCK!
}

// Solution: always acquire locks in same order
// Or use std::scoped_lock (C++17) for multiple mutexes
void safe_thread(){
    scoped_lock lock(m1, m2);  // acquires both atomically
}
```

### std::async and Futures
```cpp
#include <future>
#include <iostream>
using namespace std;

int calculate(){
    this_thread::sleep_for(chrono::seconds(1));
    return 42;
}

int main(){
    // Launch async task
    future<int> result = async(launch::async, calculate);
    
    cout << "Doing other work...\n";
    
    // Get result (blocks until ready)
    int value = result.get();
    cout << "Result: " << value << "\n";
    
    return 0;
}
```

