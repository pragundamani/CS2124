# C++ Expert Level - Modern Features & Advanced Topics

## Modern C++ Features (C++11/14/17/20)

### Auto and Decltype
```cpp
// auto: type deduction
auto x = 42;              // int
auto y = 3.14;            // double
auto z = "hello";         // const char*
auto str = string("hi");  // string

// decltype: query type of expression
int a = 5;
decltype(a) b = 10;       // b is int

decltype(a + b) c = 15;   // c is int (type of a + b)

// decltype(auto): perfect forwarding return type
template<typename Func, typename... Args>
decltype(auto) call(Func f, Args&&... args) {
    return f(forward<Args>(args)...);
}
```

### Uniform Initialization
```cpp
// C++11: uniform initialization with braces
int x{42};
double y{3.14};
string s{"hello"};

vector<int> v{1, 2, 3, 4, 5};
map<string, int> m{{"one", 1}, {"two", 2}};

// Prevents narrowing conversions
int a = 3.14;   // OK but loses precision
// int b{3.14};   // ERROR: narrowing conversion

// Initializer lists
class Point {
    int x, y;
public:
    Point(initializer_list<int> list) {
        auto it = list.begin();
        x = *it++;
        y = *it;
    }
};

Point p{3, 4};
```

### Range-Based For Loops
```cpp
vector<int> v = {1, 2, 3, 4, 5};

// C++11
for(int x : v) {
    cout << x << " ";
}

// C++11 with reference
for(int& x : v) {
    x *= 2;
}

// C++17 with structured bindings
map<string, int> m{{"a", 1}, {"b", 2}};
for(const auto& [key, value] : m) {
    cout << key << ": " << value << "\n";
}
```

### nullptr
```cpp
// C++11: nullptr instead of NULL
void func(int x) { cout << "int\n"; }
void func(int* ptr) { cout << "pointer\n"; }

int main(){
    func(0);        // calls func(int)
    func(NULL);     // ambiguous in some contexts
    func(nullptr);  // calls func(int*)
    
    int* ptr = nullptr;  // preferred over NULL or 0
    
    return 0;
}
```

### Constexpr Functions
```cpp
// C++11: compile-time constant expressions
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main(){
    constexpr int result = factorial(5);  // computed at compile time
    int arr[factorial(4)];  // OK: constexpr can be used for array size
    
    return 0;
}

// C++14: relaxed constexpr (loops, local variables)
constexpr int sum(int n) {
    int total = 0;
    for(int i = 1; i <= n; ++i) {
        total += i;
    }
    return total;
}
```

### Static Assertions
```cpp
// Compile-time assertions
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(void*) == 8, "64-bit pointers required");

template<typename T>
class Container {
    static_assert(is_copy_constructible_v<T>, 
                  "T must be copy constructible");
    // ...
};
```

### Structured Bindings (C++17)
```cpp
#include <tuple>
#include <map>
using namespace std;

// Unpack tuple/pair
pair<int, string> getPerson() {
    return {25, "Alice"};
}

auto [age, name] = getPerson();  // C++17
cout << name << " is " << age << "\n";

// Unpack array
int arr[] = {1, 2, 3};
auto [a, b, c] = arr;

// Unpack struct
struct Point { int x, y; };
Point p{3, 4};
auto [x, y] = p;

// Unpack map elements
map<string, int> m{{"a", 1}, {"b", 2}};
for(const auto& [key, value] : m) {
    cout << key << ": " << value << "\n";
}
```

### if/switch with Initializers (C++17)
```cpp
// if with initializer
if(auto it = myMap.find(key); it != myMap.end()) {
    // use it
    cout << it->second << "\n";
}
// it goes out of scope

// switch with initializer
switch(auto result = compute(); result) {
    case 0: break;
    case 1: break;
    default: break;
}
```

### std::optional (C++17)
```cpp
#include <optional>
using namespace std;

optional<int> findValue(const vector<int>& v, int target) {
    auto it = find(v.begin(), v.end(), target);
    if(it != v.end()) {
        return *it;
    }
    return nullopt;  // represents absence of value
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    
    if(auto result = findValue(v, 3); result) {
        cout << "Found: " << *result << "\n";
    } else {
        cout << "Not found\n";
    }
    
    // has_value() and value()
    if(result.has_value()) {
        cout << result.value() << "\n";
    }
    
    // value_or() provides default
    cout << findValue(v, 10).value_or(-1) << "\n";  // -1
    
    return 0;
}
```

### std::variant (C++17)
```cpp
#include <variant>
#include <string>
using namespace std;

int main(){
    // Can hold int OR string OR double
    variant<int, string, double> var;
    
    var = 42;                    // holds int
    var = "hello";               // now holds string
    var = 3.14;                  // now holds double
    
    // Access value
    cout << get<double>(var) << "\n";  // 3.14
    // cout << get<int>(var);  // throws bad_variant_access
    
    // Check which type
    if(holds_alternative<double>(var)) {
        cout << "Holds double\n";
    }
    
    // Visit pattern
    visit([](auto&& arg) {
        cout << arg << "\n";
    }, var);
    
    return 0;
}
```

### std::any (C++17)
```cpp
#include <any>
#include <iostream>
using namespace std;

int main(){
    any a = 42;
    a = 3.14;
    a = string("hello");
    
    // Type checking and casting
    if(a.type() == typeid(string)) {
        cout << any_cast<string>(a) << "\n";
    }
    
    // Throws bad_any_cast if wrong type
    try {
        cout << any_cast<int>(a) << "\n";
    } catch(const bad_any_cast& e) {
        cout << "Wrong type\n";
    }
    
    return 0;
}
```

### Modules (C++20)
```cpp
// mymodule.cpp
export module mymodule;

export int add(int a, int b) {
    return a + b;
}

// main.cpp
import mymodule;

int main(){
    cout << add(3, 5) << "\n";
    return 0;
}
```
- Faster compilation than headers
- Better encapsulation
- No header guards needed

### Ranges Library (C++20)
```cpp
#include <ranges>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Filter and transform
    auto result = v 
        | views::filter([](int x) { return x % 2 == 0; })
        | views::transform([](int x) { return x * 2; });
    
    for(int x : result) {
        cout << x << " ";  // 4 8 12 16 20
    }
    
    return 0;
}
```

### Coroutines (C++20)
```cpp
#include <coroutine>
#include <iostream>
using namespace std;

// Generator using coroutines
generator<int> fibonacci() {
    int a = 0, b = 1;
    while(true) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

int main(){
    auto fib = fibonacci();
    for(int i = 0; i < 10; ++i) {
        cout << fib() << " ";
    }
    // 0 1 1 2 3 5 8 13 21 34
    
    return 0;
}
```

## Advanced Memory Management

### Custom Allocators
```cpp
#include <memory>
using namespace std;

template<typename T>
class PoolAllocator {
    // Memory pool implementation
    T* pool;
    size_t poolSize;
    
public:
    using value_type = T;
    
    PoolAllocator(size_t size) : poolSize(size) {
        pool = static_cast<T*>(::operator new(sizeof(T) * size));
    }
    
    T* allocate(size_t n) {
        // Allocate from pool
        return pool;  // simplified
    }
    
    void deallocate(T* ptr, size_t n) {
        // Return to pool
    }
};

// Use with containers
vector<int, PoolAllocator<int>> v(PoolAllocator<int>(100));
```

### Memory Pools
```cpp
class MemoryPool {
    struct Block {
        Block* next;
    };
    
    Block* freeList;
    size_t blockSize;
    
public:
    MemoryPool(size_t size) : blockSize(size), freeList(nullptr) {}
    
    void* allocate() {
        if(!freeList) {
            // Allocate new chunk
            size_t chunkSize = 1024;
            char* chunk = new char[chunkSize];
            
            // Divide into blocks
            for(size_t i = 0; i < chunkSize; i += blockSize) {
                auto block = reinterpret_cast<Block*>(chunk + i);
                block->next = freeList;
                freeList = block;
            }
        }
        
        Block* block = freeList;
        freeList = freeList->next;
        return block;
    }
    
    void deallocate(void* ptr) {
        auto block = static_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }
};
```

### Placement New
```cpp
#include <new>

int main(){
    // Allocate raw memory
    char buffer[sizeof(int)];
    
    // Construct object in buffer
    int* ptr = new(buffer) int(42);  // placement new
    
    cout << *ptr << "\n";  // 42
    
    // Must manually call destructor
    ptr->~int();
    
    // No delete (memory not from heap)
    
    return 0;
}
```

### Memory Alignment
```cpp
#include <cstddef>
using namespace std;

// Specify alignment
struct alignas(16) AlignedData {
    int x, y, z, w;
};

// Check alignment
static_assert(alignof(AlignedData) == 16);

// Aligned allocation
void* ptr = aligned_alloc(16, 64);  // 64 bytes, 16-byte aligned
free(ptr);

// C++17: aligned new
struct OverAligned {
    alignas(32) char data[32];
};

auto ptr2 = new OverAligned;  // automatically uses aligned allocation
delete ptr2;
```

### Cache-Friendly Data Structures
```cpp
// Bad: pointer chasing (cache misses)
struct Node {
    int data;
    Node* next;
};

// Good: contiguous memory (cache friendly)
vector<int> data;  // all elements in contiguous memory

// Structure of Arrays (SoA) vs Array of Structures (AoS)

// AoS: objects store all fields together
struct Particle {
    float x, y, z;
    float vx, vy, vz;
};
vector<Particle> particles;  // XYZV XYZV XYZV ...

// SoA: separate arrays for each field
struct ParticleSystem {
    vector<float> x, y, z;
    vector<float> vx, vy, vz;
};
// XXX... YYY... ZZZ... VVV...
// Better for SIMD operations
```

### Smart Pointer Implementation Details
```cpp
// Simplified shared_ptr implementation
template<typename T>
class SharedPtr {
    T* ptr;
    size_t* refCount;
    
public:
    SharedPtr(T* p) : ptr(p), refCount(new size_t(1)) {}
    
    SharedPtr(const SharedPtr& other) 
        : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount);
    }
    
    ~SharedPtr() {
        if(--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }
    
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};
```


## Metaprogramming

### Template Metaprogramming (TMP)
```cpp
// Compile-time factorial
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main(){
    constexpr int result = Factorial<5>::value;  // computed at compile time
    int arr[Factorial<4>::value];  // array size known at compile time
    
    return 0;
}
```

### Compile-Time Computation
```cpp
// C++11 constexpr
constexpr int pow(int base, int exp) {
    return exp == 0 ? 1 : base * pow(base, exp - 1);
}

// C++14: more flexible constexpr
constexpr int fibonacci(int n) {
    if(n <= 1) return n;
    
    int a = 0, b = 1;
    for(int i = 2; i <= n; ++i) {
        int next = a + b;
        a = b;
        b = next;
    }
    return b;
}

// C++20: constexpr vectors and strings
constexpr vector<int> makeVector() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    return v;
}
```

### Type Manipulation at Compile Time
```cpp
#include <type_traits>
using namespace std;

// Remove const
template<typename T>
using remove_const_t = typename remove_const<T>::type;

// Add pointer
template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

// Conditional type
template<bool Cond, typename T, typename F>
using conditional_t = typename conditional<Cond, T, F>::type;

// Example: choose type based on size
template<size_t Size>
using int_type = conditional_t<Size <= 2, int16_t,
                 conditional_t<Size <= 4, int32_t, int64_t>>;
```

### SFINAE Techniques
```cpp
#include <type_traits>
using namespace std;

// Enable if has begin() method
template<typename T>
auto process(T& container) 
    -> decltype(container.begin(), void()) {
    // This overload only enabled if T has begin()
    for(auto& item : container) {
        // ...
    }
}

// Enable for arithmetic types
template<typename T>
enable_if_t<is_arithmetic_v<T>, T>
square(T value) {
    return value * value;
}

// Detect member function
template<typename T>
class has_print {
    template<typename U>
    static auto test(int) -> decltype(declval<U>().print(), true_type{});
    
    template<typename>
    static false_type test(...);
    
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};
```

### Tag Dispatching
```cpp
// Define tags
struct iterator_tag {};
struct random_access_iterator_tag : iterator_tag {};

// Implementation functions
template<typename Iter>
void advance_impl(Iter& it, int n, iterator_tag) {
    while(n--) ++it;  // slow for non-random-access
}

template<typename Iter>
void advance_impl(Iter& it, int n, random_access_iterator_tag) {
    it += n;  // fast for random-access
}

// Dispatch based on iterator type
template<typename Iter>
void advance(Iter& it, int n) {
    advance_impl(it, n, typename iterator_traits<Iter>::iterator_category{});
}
```

### Policy-Based Design
```cpp
// Policy classes
template<typename T>
struct NoChecking {
    static void check(const T*, size_t) {}
};

template<typename T>
struct BoundsChecking {
    static void check(const T* ptr, size_t index) {
        if(ptr == nullptr) throw runtime_error("Null pointer");
        // additional bounds checking
    }
};

// Class using policy
template<typename T, typename CheckingPolicy = NoChecking<T>>
class SmartArray {
    T* data;
    size_t size;
    
public:
    T& operator[](size_t index) {
        CheckingPolicy::check(data, index);
        return data[index];
    }
};

// Usage
SmartArray<int, NoChecking<int>> fast_array;
SmartArray<int, BoundsChecking<int>> safe_array;
```

## Design Patterns

### Creational Patterns

#### Factory Pattern
```cpp
class Animal {
public:
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Meow!\n"; }
};

// Factory
class AnimalFactory {
public:
    static unique_ptr<Animal> create(const string& type) {
        if(type == "dog") return make_unique<Dog>();
        if(type == "cat") return make_unique<Cat>();
        return nullptr;
    }
};

int main(){
    auto animal = AnimalFactory::create("dog");
    animal->speak();  // Woof!
    
    return 0;
}
```

#### Singleton Pattern
```cpp
class Singleton {
private:
    Singleton() {}  // private constructor
    
public:
    // Delete copy and move
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton& getInstance() {
        static Singleton instance;  // thread-safe in C++11
        return instance;
    }
    
    void doSomething() {
        cout << "Singleton method\n";
    }
};

int main(){
    Singleton::getInstance().doSomething();
    return 0;
}
```

#### Builder Pattern
```cpp
class Pizza {
    string dough;
    string sauce;
    string topping;
    
public:
    class Builder {
        Pizza pizza;
    public:
        Builder& setDough(const string& d) { 
            pizza.dough = d; 
            return *this; 
        }
        Builder& setSauce(const string& s) { 
            pizza.sauce = s; 
            return *this; 
        }
        Builder& setTopping(const string& t) { 
            pizza.topping = t; 
            return *this; 
        }
        Pizza build() { return move(pizza); }
    };
};

int main(){
    Pizza pizza = Pizza::Builder()
        .setDough("thin")
        .setSauce("tomato")
        .setTopping("cheese")
        .build();
    
    return 0;
}
```

#### Prototype Pattern
```cpp
class Prototype {
public:
    virtual unique_ptr<Prototype> clone() const = 0;
    virtual ~Prototype() = default;
};

class ConcretePrototype : public Prototype {
    int data;
public:
    ConcretePrototype(int d) : data(d) {}
    
    unique_ptr<Prototype> clone() const override {
        return make_unique<ConcretePrototype>(*this);
    }
};
```

### Structural Patterns

#### Adapter Pattern
```cpp
// Existing interface
class LegacyRectangle {
public:
    void draw(int x1, int y1, int x2, int y2) {
        cout << "Rectangle from (" << x1 << "," << y1 
             << ") to (" << x2 << "," << y2 << ")\n";
    }
};

// New interface
class Shape {
public:
    virtual void draw(int x, int y, int width, int height) = 0;
    virtual ~Shape() = default;
};

// Adapter
class RectangleAdapter : public Shape {
    LegacyRectangle rectangle;
public:
    void draw(int x, int y, int width, int height) override {
        rectangle.draw(x, y, x + width, y + height);
    }
};
```

#### Decorator Pattern
```cpp
class Coffee {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};

class SimpleCoffee : public Coffee {
public:
    string getDescription() const override { return "Coffee"; }
    double cost() const override { return 2.0; }
};

class CoffeeDecorator : public Coffee {
protected:
    unique_ptr<Coffee> coffee;
public:
    CoffeeDecorator(unique_ptr<Coffee> c) : coffee(move(c)) {}
};

class Milk : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;
    
    string getDescription() const override {
        return coffee->getDescription() + " + Milk";
    }
    
    double cost() const override {
        return coffee->cost() + 0.5;
    }
};

int main(){
    unique_ptr<Coffee> coffee = make_unique<SimpleCoffee>();
    coffee = make_unique<Milk>(move(coffee));
    
    cout << coffee->getDescription() << ": $" << coffee->cost() << "\n";
    // Coffee + Milk: $2.5
    
    return 0;
}
```

#### Facade Pattern
```cpp
// Complex subsystems
class CPU {
public:
    void freeze() { cout << "CPU freeze\n"; }
    void execute() { cout << "CPU execute\n"; }
};

class Memory {
public:
    void load() { cout << "Memory load\n"; }
};

class HardDrive {
public:
    void read() { cout << "HardDrive read\n"; }
};

// Facade
class ComputerFacade {
    CPU cpu;
    Memory memory;
    HardDrive hd;
    
public:
    void start() {
        cpu.freeze();
        memory.load();
        hd.read();
        cpu.execute();
    }
};

int main(){
    ComputerFacade computer;
    computer.start();  // simple interface to complex system
    
    return 0;
}
```

### Behavioral Patterns

#### Observer Pattern
```cpp
class Observer {
public:
    virtual void update(int state) = 0;
    virtual ~Observer() = default;
};

class Subject {
    vector<Observer*> observers;
    int state;
    
public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }
    
    void setState(int s) {
        state = s;
        notify();
    }
    
    void notify() {
        for(auto obs : observers) {
            obs->update(state);
        }
    }
};

class ConcreteObserver : public Observer {
    string name;
public:
    ConcreteObserver(const string& n) : name(n) {}
    
    void update(int state) override {
        cout << name << " received: " << state << "\n";
    }
};

int main(){
    Subject subject;
    ConcreteObserver obs1("Observer1"), obs2("Observer2");
    
    subject.attach(&obs1);
    subject.attach(&obs2);
    
    subject.setState(42);
    // Observer1 received: 42
    // Observer2 received: 42
    
    return 0;
}
```

#### Strategy Pattern
```cpp
class SortStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

class QuickSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end());  // quick sort implementation
        cout << "QuickSort\n";
    }
};

class MergeSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        stable_sort(data.begin(), data.end());  // merge sort implementation
        cout << "MergeSort\n";
    }
};

class Sorter {
    unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(unique_ptr<SortStrategy> s) {
        strategy = move(s);
    }
    
    void sort(vector<int>& data) {
        strategy->sort(data);
    }
};

int main(){
    Sorter sorter;
    vector<int> data = {5, 2, 8, 1, 9};
    
    sorter.setStrategy(make_unique<QuickSort>());
    sorter.sort(data);
    
    sorter.setStrategy(make_unique<MergeSort>());
    sorter.sort(data);
    
    return 0;
}
```

### SOLID Principles

```cpp
// S - Single Responsibility Principle
// Each class should have one reason to change

// O - Open/Closed Principle
// Open for extension, closed for modification

// L - Liskov Substitution Principle
// Derived classes should be substitutable for base classes

// I - Interface Segregation Principle
// Many specific interfaces better than one general interface

// D - Dependency Inversion Principle
// Depend on abstractions, not concretions
```


## Performance Optimization

### Profiling Tools
```bash
# gprof (GNU Profiler)
g++ -pg program.cpp -o program
./program
gprof program gmon.out > analysis.txt

# Valgrind (memory profiler, leak detector)
valgrind --tool=callgrind ./program
valgrind --leak-check=full ./program

# perf (Linux performance analyzer)
perf record ./program
perf report

# Google Performance Tools
g++ -lprofiler program.cpp
CPUPROFILE=prof.out ./program
google-pprof --text ./program prof.out
```

### Time Complexity Analysis
```cpp
// O(1) - Constant
int getFirst(const vector<int>& v) {
    return v[0];
}

// O(log n) - Logarithmic
int binarySearch(const vector<int>& v, int target) {
    int left = 0, right = v.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(v[mid] == target) return mid;
        if(v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// O(n) - Linear
int findMax(const vector<int>& v) {
    int max = v[0];
    for(int x : v) {
        if(x > max) max = x;
    }
    return max;
}

// O(n log n) - Linearithmic
void sortVector(vector<int>& v) {
    sort(v.begin(), v.end());
}

// O(n²) - Quadratic
vector<int> findDuplicates(const vector<int>& v) {
    vector<int> duplicates;
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = i + 1; j < v.size(); ++j) {
            if(v[i] == v[j]) {
                duplicates.push_back(v[i]);
            }
        }
    }
    return duplicates;
}
```

### Space Complexity Analysis
```cpp
// O(1) - Constant space
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// O(n) - Linear space
vector<int> createCopy(const vector<int>& v) {
    return v;  // creates copy
}

// O(n²) - Quadratic space
vector<vector<int>> createMatrix(int n) {
    return vector<vector<int>>(n, vector<int>(n));
}
```

### Cache Optimization
```cpp
// Bad: column-major access (cache misses)
void sumColumnsNaive(int matrix[1000][1000]) {
    for(int col = 0; col < 1000; ++col) {
        int sum = 0;
        for(int row = 0; row < 1000; ++row) {
            sum += matrix[row][col];  // non-contiguous access
        }
    }
}

// Good: row-major access (cache friendly)
void sumRowsOptimized(int matrix[1000][1000]) {
    for(int row = 0; row < 1000; ++row) {
        int sum = 0;
        for(int col = 0; col < 1000; ++col) {
            sum += matrix[row][col];  // contiguous access
        }
    }
}

// Cache line size is typically 64 bytes
// Accessing contiguous memory utilizes cache lines efficiently
```

### Branch Prediction
```cpp
// Bad: unpredictable branches
int countPositive(const vector<int>& v) {
    int count = 0;
    for(int x : v) {
        if(x > 0) {  // branch might be unpredictable
            ++count;
        }
    }
    return count;
}

// Better: branchless (for sorted data)
int countPositiveBranchless(const vector<int>& v) {
    int count = 0;
    for(int x : v) {
        count += (x > 0);  // no branch
    }
    return count;
}

// Sort data if possible to make branches predictable
sort(v.begin(), v.end());
// Now branches are predictable
```

### Inline Optimization
```cpp
// Inline function: hint to compiler
inline int add(int a, int b) {
    return a + b;
}

// Force inline (use sparingly)
[[gnu::always_inline]]
inline int forceInline(int x) {
    return x * 2;
}

// Prevent inlining
[[gnu::noinline]]
int preventInline(int x) {
    return x * 2;
}
```

### Compiler Optimizations
```bash
# No optimization
g++ program.cpp -o program

# Basic optimization (-O1)
g++ -O1 program.cpp -o program

# Moderate optimization (-O2) - recommended for most cases
g++ -O2 program.cpp -o program

# Aggressive optimization (-O3)
g++ -O3 program.cpp -o program

# Optimize for size
g++ -Os program.cpp -o program

# Fast math (breaks IEEE compliance)
g++ -O3 -ffast-math program.cpp -o program

# Enable all warnings
g++ -Wall -Wextra -Wpedantic program.cpp -o program

# Link-time optimization
g++ -O3 -flto program.cpp -o program
```

### Loop Unrolling
```cpp
// Manual loop unrolling
void sumArrayUnrolled(const int* arr, int size, int& sum) {
    int i = 0;
    // Process 4 elements at a time
    for(; i <= size - 4; i += 4) {
        sum += arr[i];
        sum += arr[i + 1];
        sum += arr[i + 2];
        sum += arr[i + 3];
    }
    // Handle remaining elements
    for(; i < size; ++i) {
        sum += arr[i];
    }
}

// Compiler can auto-unroll with optimization flags
```

### SIMD Basics
```cpp
#include <immintrin.h>  // AVX/SSE intrinsics

// SIMD addition (process 8 floats at once)
void addArraysSIMD(const float* a, const float* b, float* c, int size) {
    int i = 0;
    // Process 8 floats at a time using AVX
    for(; i <= size - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&c[i], vc);
    }
    // Handle remaining elements
    for(; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
}
```

## Build Systems & Tools

### Makefiles
```makefile
# Simple Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = program
SRCS = main.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
rm -f $(OBJS) $(TARGET)

.PHONY: clean
```

### CMake Basics
```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(program main.cpp utils.cpp)

# Add library
add_library(mylib STATIC lib.cpp)

# Link library to executable
target_link_libraries(program mylib)

# Include directories
target_include_directories(program PUBLIC include)

# Find and use external libraries
find_package(Threads REQUIRED)
target_link_libraries(program Threads::Threads)

# Build:
# mkdir build && cd build
# cmake ..
# make
```

### Version Control (Git)
```bash
# Initialize repository
git init
git add .
git commit -m "Initial commit"

# Branching
git branch feature-branch
git checkout feature-branch
git checkout -b new-branch  # create and checkout

# Merging
git checkout main
git merge feature-branch

# Remote repositories
git remote add origin <url>
git push -u origin main
git pull origin main

# Viewing history
git log
git log --oneline --graph --all

# Stashing changes
git stash
git stash pop
```

### Static Analysis Tools
```bash
# Clang-Tidy (linter and static analyzer)
clang-tidy program.cpp -- -std=c++17

# Cppcheck (static analyzer)
cppcheck --enable=all --std=c++17 program.cpp

# Include-what-you-use
include-what-you-use program.cpp

# Clang Static Analyzer
scan-build make
```

### Debugging Tools
```bash
# GDB (GNU Debugger)
g++ -g program.cpp -o program  # compile with debug info
gdb program

# GDB commands:
# break main          - set breakpoint
# run                 - start program
# next                - next line
# step                - step into function
# print var           - print variable
# backtrace           - show call stack
# continue            - continue execution

# LLDB (LLVM Debugger)
lldb program
# Similar commands to GDB
```

### Sanitizers
```bash
# AddressSanitizer (memory errors)
g++ -fsanitize=address -g program.cpp -o program
./program

# UndefinedBehaviorSanitizer
g++ -fsanitize=undefined -g program.cpp -o program

# ThreadSanitizer (data races)
g++ -fsanitize=thread -g program.cpp -o program

# MemorySanitizer (uninitialized memory)
g++ -fsanitize=memory -g program.cpp -o program
```

## Testing & Quality Assurance

### Unit Testing with Google Test
```cpp
#include <gtest/gtest.h>

// Function to test
int add(int a, int b) {
    return a + b;
}

// Test cases
TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(10, 20), 30);
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(add(-2, -3), -5);
    EXPECT_EQ(add(-10, 10), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Compile and link with gtest:
// g++ test.cpp -lgtest -lgtest_main -pthread
```

### Unit Testing with Catch2
```cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

TEST_CASE("Factorial is computed", "[factorial]") {
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(5) == 120);
    
    SECTION("negative numbers") {
        REQUIRE(factorial(-1) == 1);
    }
}

TEST_CASE("Vector operations", "[vector]") {
    std::vector<int> v{1, 2, 3};
    
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    
    v.push_back(4);
    REQUIRE(v.back() == 4);
}
```

### Test-Driven Development (TDD)
```cpp
// 1. Write test first (it fails)
TEST(CalculatorTest, Multiply) {
    Calculator calc;
    EXPECT_EQ(calc.multiply(3, 4), 12);
}

// 2. Write minimal code to pass test
class Calculator {
public:
    int multiply(int a, int b) {
        return a * b;
    }
};

// 3. Refactor while keeping tests passing
```

### Code Coverage
```bash
# Using gcov with g++
g++ --coverage program.cpp -o program
./program
gcov program.cpp

# Generate HTML report with lcov
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
```

## Low-Level Programming

### Bitwise Manipulation Techniques
```cpp
// Check if power of 2
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Count set bits (Hamming weight)
int countSetBits(int n) {
    int count = 0;
    while(n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Swap without temp variable
void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

// Set, clear, toggle bit
void setBit(int& n, int pos) { n |= (1 << pos); }
void clearBit(int& n, int pos) { n &= ~(1 << pos); }
void toggleBit(int& n, int pos) { n ^= (1 << pos); }

// Check if bit is set
bool isBitSet(int n, int pos) {
    return (n & (1 << pos)) != 0;
}
```

### Endianness
```cpp
#include <iostream>
using namespace std;

bool isLittleEndian() {
    uint16_t num = 1;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&num);
    return ptr[0] == 1;  // if first byte is 1, little endian
}

// Swap endianness
uint32_t swapEndian32(uint32_t value) {
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x000000FF) << 24);
}
```

### System Calls
```cpp
#include <unistd.h>
#include <fcntl.h>

// Open file
int fd = open("file.txt", O_RDONLY);

// Read from file
char buffer[100];
ssize_t bytes_read = read(fd, buffer, sizeof(buffer));

// Write to file
int fd_write = open("output.txt", O_WRONLY | O_CREAT, 0644);
write(fd_write, buffer, bytes_read);

// Close files
close(fd);
close(fd_write);
```

### Interfacing with C Code
```cpp
// C++ code calling C
extern "C" {
    #include "c_library.h"
}

// C header for C++ code
#ifdef __cplusplus
extern "C" {
#endif

void my_function(int x);

#ifdef __cplusplus
}
#endif
```

### Inline Assembly
```cpp
// GCC/Clang inline assembly
int add_asm(int a, int b) {
    int result;
    asm("addl %1, %2\n\t"
        "movl %2, %0"
        : "=r"(result)
        : "r"(a), "r"(b));
    return result;
}

// x86-64 CPUID instruction
void cpuid(int info[4], int type) {
    asm volatile("cpuid"
                 : "=a"(info[0]), "=b"(info[1]), 
                   "=c"(info[2]), "=d"(info[3])
                 : "a"(type));
}
```

---

## Summary

This expert-level guide covers:
- Modern C++ features (C++11 through C++20)
- Advanced memory management techniques
- Template metaprogramming and compile-time computation
- Design patterns and SOLID principles
- Performance optimization strategies
- Professional development tools
- Testing and quality assurance
- Low-level programming techniques

Continue practicing these advanced concepts and exploring the latest C++ standards to master the language at an expert level.

