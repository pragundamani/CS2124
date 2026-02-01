# C++ Learning Schedule - From Python to C++

**Target Audience:** Intermediate Python developer learning C++  
**Duration:** 12 weeks (3 months)  
**Time Commitment:** 10-15 hours/week  
**Start Date:** January 26, 2026

---

## 🎯 Learning Goals

By the end of this schedule, you will:
- Master C++ fundamentals and syntax
- Understand memory management and pointers
- Write object-oriented C++ programs
- Use STL containers and algorithms effectively
- Apply modern C++ features (C++11/14/17)
- Build real-world C++ projects

---

## 📅 Week-by-Week Breakdown

### **Week 1: C++ Fundamentals & Setup**
**Focus:** Get comfortable with C++ basics and tooling

#### Day 1-2: Environment Setup & First Programs
- [ ] Install C++ compiler (g++ or clang)
- [ ] Set up IDE/editor (VS Code, CLion, or Visual Studio)
- [ ] Read: `basics.md` - Program Structure & Syntax
- [ ] Read: `basics.md` - Data Types & Variables
- [ ] **Practice:**
  - Write "Hello World" program
  - Create a program that takes user input and prints it
  - Make a simple calculator (add, subtract, multiply, divide)

**Python → C++ Differences to Notice:**
```python
# Python: Dynamic typing
x = 5
x = "hello"  # OK

# C++: Static typing
int x = 5;
// x = "hello";  // ERROR!
```

#### Day 3-4: Operators & Control Flow
- [ ] Read: `basics.md` - Operators (all types)
- [ ] Read: `basics.md` - Control Flow
- [ ] **Practice:**
  - FizzBuzz problem
  - Grade calculator (if-else chains)
  - Simple number guessing game

**Key Difference:**
```python
# Python
if x == 5:
    print("Five")

# C++
if(x == 5){
    cout << "Five\n";
}
// Note: Braces are required for multi-line blocks
```

#### Day 5-7: Loops & Input/Output
- [ ] Read: `basics.md` - Loops
- [ ] Read: `basics.md` - Input & Output
- [ ] **Practice:**
  - Sum of numbers from 1 to N
  - Multiplication table generator
  - Read numbers from user until they enter 0, print average
  - Build a menu-driven program (choose operation)

**Week 1 Project:** Command-line Temperature Converter
- Convert between Celsius, Fahrenheit, and Kelvin
- Menu-driven interface
- Input validation
- Loop until user chooses to quit

---

### **Week 2: Functions & Code Organization**
**Focus:** Writing reusable, modular code

#### Day 1-3: Functions
- [ ] Read: `advanced_basics.md` - Functions (all subsections)
- [ ] **Practice:**
  - Write function to check if number is prime
  - Create function to calculate factorial
  - Build a library of math functions (power, abs, max, min)
  - Understand pass-by-value vs pass-by-reference

**Python → C++ Key Difference:**
```python
# Python: Everything is pass-by-reference (to objects)
def modify(lst):
    lst.append(1)  # modifies original

# C++: Must explicitly choose
void modify1(vector<int> v) { }     // pass by value (copy)
void modify2(vector<int>& v) { }    // pass by reference
void modify3(const vector<int>& v) { } // read-only reference
```

#### Day 4-5: Recursion
- [ ] Read: `advanced_basics.md` - Recursion
- [ ] **Practice:**
  - Recursive factorial
  - Fibonacci sequence
  - Sum of array elements (recursive)
  - Tower of Hanoi

#### Day 6-7: Arrays & Vectors Introduction
- [ ] Read: `advanced_basics.md` - Arrays
- [ ] Read: `advanced_basics.md` - Vectors (first half)
- [ ] **Practice:**
  - Find max/min in array
  - Reverse an array
  - Create a simple todo list with vector<string>

**Week 2 Project:** Student Grade Manager
- Store student names and grades
- Calculate class average
- Find highest/lowest grade
- Use functions for each operation
- Use vectors for storage

---

### **Week 3: STL Containers & Strings**
**Focus:** Master C++ Standard Template Library basics

#### Day 1-3: Vectors Deep Dive
- [ ] Read: `advanced_basics.md` - Vectors (complete)
- [ ] Read: `common_patterns.md` - Vector Patterns
- [ ] **Practice:**
  - 2D vector (matrix operations)
  - Remove duplicates from vector
  - Sort and search in vectors

#### Day 4-5: Strings
- [ ] Read: `common_patterns.md` - String Operations
- [ ] **Practice:**
  - String reversal
  - Check if string is palindrome
  - Count vowels and consonants
  - String tokenization (split by delimiter)

**Python → C++ String Differences:**
```python
# Python: strings are immutable
s = "hello"
s = s + " world"  # creates new string

# C++: strings are mutable
string s = "hello";
s += " world";  // modifies in place
s[0] = 'H';     // can modify characters
```

#### Day 6-7: File I/O
- [ ] Read: `common_patterns.md` - File I/O
- [ ] **Practice:**
  - Read text file and count words
  - Write program data to file
  - CSV file reader

**Week 3 Project:** Text File Analyzer
- Read a text file
- Count lines, words, characters
- Find most common word
- Generate statistics report
- Save report to output file

---

### **Week 4: Pointers & Memory - The Big Difference!**
**Focus:** Master what makes C++ unique - manual memory management

#### Day 1-2: Pointer Basics
- [ ] Read: `intermediate.md` - Pointer Basics
- [ ] Read: `intermediate.md` - Pointer Arithmetic
- [ ] **Practice:**
  - Swap two numbers using pointers
  - Array traversal with pointers
  - Understand pointer and reference differences

**This is NEW for Python developers:**
```cpp
int x = 5;
int* ptr = &x;  // ptr holds address of x
*ptr = 10;      // changes x to 10

// Python has no direct equivalent - 
// everything is already a reference!
```

#### Day 3-4: Dynamic Memory
- [ ] Read: `intermediate.md` - Dynamic Memory Allocation
- [ ] Read: `intermediate.md` - Memory Leaks and Prevention
- [ ] **Practice:**
  - Allocate array dynamically
  - Create linked list node with new/delete
  - Practice proper cleanup

**Critical for C++:**
```cpp
int* ptr = new int(42);  // allocate
// ... use ptr ...
delete ptr;  // MUST free memory!

// Python: garbage collector does this automatically
```

#### Day 5-7: Smart Pointers (Modern C++)
- [ ] Read: `intermediate.md` - Smart Pointers Introduction
- [ ] **Practice:**
  - Convert raw pointers to unique_ptr
  - Use shared_ptr for shared ownership
  - Understand when to use each type

**Week 4 Project:** Dynamic Array Class
- Create your own dynamic array class
- Implement push_back, pop_back, resize
- Proper memory management
- Then compare with std::vector

---

### **Week 5: Object-Oriented Programming**
**Focus:** Classes and encapsulation

#### Day 1-3: Classes & Objects
- [ ] Read: `intermediate.md` - OOP Basics (first half)
- [ ] **Practice:**
  - Create a `Person` class (name, age, methods)
  - Build a `BankAccount` class (balance, deposit, withdraw)
  - Make a `Rectangle` class (width, height, area, perimeter)

**Python → C++ OOP Differences:**
```python
# Python
class Person:
    def __init__(self, name):
        self.name = name  # public by default

# C++
class Person {
private:
    string name;  // private by default
public:
    Person(string n) : name(n) {}  // constructor
    string getName() const { return name; }
};
```

#### Day 4-5: Constructors & Destructors
- [ ] Read: `intermediate.md` - Constructors
- [ ] Read: `intermediate.md` - Destructors
- [ ] **Practice:**
  - Default, parameterized, copy constructors
  - Destructor for resource cleanup
  - Constructor initializer lists

#### Day 6-7: Class Design
- [ ] Read: `intermediate.md` - this Pointer
- [ ] Read: `intermediate.md` - Const Member Functions
- [ ] Read: `intermediate.md` - Static Members
- [ ] **Practice:**
  - Design a `Date` class
  - Create a `Counter` class with static count
  - Implement method chaining

**Week 5 Project:** Library Management System
- Book class (title, author, ISBN)
- Library class (collection of books)
- Add, remove, search books
- Borrow/return functionality
- Proper encapsulation

---

### **Week 6: STL Containers Deep Dive**
**Focus:** Master standard containers

#### Day 1-2: Sequence Containers
- [ ] Read: `intermediate.md` - Standard Library Containers
- [ ] **Practice:**
  - Use deque for queue operations
  - Implement stack using vector
  - Compare vector vs list performance

#### Day 3-4: Associative Containers
- [ ] Read: `intermediate.md` - Associative Containers
- [ ] **Practice:**
  - Word frequency counter (map)
  - Remove duplicates (set)
  - Phone book (unordered_map)

**Python dict → C++ map:**
```python
# Python
ages = {"Alice": 25, "Bob": 30}
ages["Charlie"] = 28

# C++
map<string, int> ages;
ages["Alice"] = 25;
ages["Bob"] = 30;
ages["Charlie"] = 28;

// Or unordered_map for hash table (like Python dict)
```

#### Day 5-7: STL Algorithms
- [ ] Read: `advanced_basics.md` - Standard Library Algorithms
- [ ] Read: `common_patterns.md` - Common Coding Patterns
- [ ] **Practice:**
  - Sort with custom comparator
  - Transform and filter operations
  - Find, count, accumulate

**Week 6 Project:** Contact Manager
- Store contacts (name, phone, email)
- Search by name
- Sort by different fields
- Export/import from file
- Use appropriate containers (map, vector)

---

### **Week 7: Templates & Generic Programming**
**Focus:** Write reusable, type-independent code

#### Day 1-3: Function Templates
- [ ] Read: `intermediate.md` - Templates Basics - Function Templates
- [ ] **Practice:**
  - Generic swap function
  - Generic max/min function
  - Template for array printing

**Similar to Python's duck typing, but compile-time:**
```python
# Python: works with any type that supports +
def add(a, b):
    return a + b

# C++: explicit template
template<typename T>
T add(T a, T b) {
    return a + b;
}
```

#### Day 4-5: Class Templates
- [ ] Read: `intermediate.md` - Templates Basics - Class Templates
- [ ] **Practice:**
  - Generic Pair class
  - Stack template class
  - Array wrapper template

#### Day 6-7: STL with Templates
- [ ] Practice using templates with STL
- [ ] Review common_patterns.md examples
- [ ] **Practice:**
  - Create generic container wrapper
  - Use templates with custom classes

**Week 7 Project:** Generic Data Structure Library
- Implement templated Stack
- Implement templated Queue
- Implement templated LinkedList
- Write test cases for different types

---

### **Week 8: Exception Handling & Error Management**
**Focus:** Robust error handling

#### Day 1-3: Exception Basics
- [ ] Read: `intermediate.md` - Exception Handling
- [ ] **Practice:**
  - Try-catch blocks
  - Throwing exceptions
  - Multiple catch blocks

**Python → C++ Exceptions:**
```python
# Python
try:
    result = 10 / 0
except ZeroDivisionError as e:
    print(f"Error: {e}")

# C++
try {
    if(b == 0) throw runtime_error("Division by zero");
    result = a / b;
} catch(const runtime_error& e) {
    cerr << "Error: " << e.what() << "\n";
}
```

#### Day 4-7: Error Handling Strategies
- [ ] Read about exception safety
- [ ] Learn RAII principle
- [ ] **Practice:**
  - File operations with error handling
  - Input validation with exceptions
  - Custom exception classes

**Week 8 Project:** Robust Calculator
- Parse mathematical expressions
- Handle all errors gracefully
- Division by zero
- Invalid input
- File I/O errors
- Provide helpful error messages

---

### **Week 9: Advanced OOP**
**Focus:** Inheritance and polymorphism

#### Day 1-3: Inheritance
- [ ] Read: `advanced.md` - Inheritance
- [ ] **Practice:**
  - Base class Animal, derived Dog/Cat
  - Shape hierarchy (Circle, Rectangle, Triangle)
  - Employee hierarchy (Manager, Developer)

**Python → C++ Inheritance:**
```python
# Python
class Animal:
    def speak(self):
        pass

class Dog(Animal):
    def speak(self):
        return "Woof"

# C++
class Animal {
public:
    virtual void speak() = 0;  // pure virtual
    virtual ~Animal() {}       // virtual destructor!
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof\n"; }
};
```

#### Day 4-5: Polymorphism & Virtual Functions
- [ ] Read: `advanced.md` - Virtual Functions and Polymorphism
- [ ] Read: `advanced.md` - Abstract Classes
- [ ] **Practice:**
  - Virtual function examples
  - Abstract base classes
  - Polymorphic collections

#### Day 6-7: Advanced OOP Concepts
- [ ] Read: `advanced.md` - Virtual Destructors
- [ ] Read: `advanced.md` - Composition vs Inheritance
- [ ] **Practice:**
  - When to use composition
  - Interface design patterns

**Week 9 Project:** Shape Drawing System
- Abstract Shape base class
- Concrete shapes (Circle, Rectangle, Triangle, etc.)
- Calculate area and perimeter
- Draw method (console output)
- Collection of mixed shapes
- Demonstrate polymorphism

---

### **Week 10: Modern C++ Features**
**Focus:** C++11/14/17 features

#### Day 1-2: Auto, Range-based Loops, Lambda
- [ ] Read: `expert.md` - Auto and Decltype
- [ ] Read: `expert.md` - Range-Based For Loops
- [ ] Read: `advanced.md` - Lambda Expressions
- [ ] **Practice:**
  - Use auto for type deduction
  - Range-based loops everywhere
  - Lambda for sorting, filtering

**Lambdas (similar to Python):**
```python
# Python
numbers = [1, 2, 3, 4, 5]
evens = list(filter(lambda x: x % 2 == 0, numbers))

# C++
vector<int> numbers = {1, 2, 3, 4, 5};
auto isEven = [](int x) { return x % 2 == 0; };
// Use with algorithms
```

#### Day 3-4: Smart Pointers & Move Semantics
- [ ] Read: `advanced.md` - Move Semantics & Rvalue References
- [ ] Read: `expert.md` - Modern C++ smart pointers section
- [ ] **Practice:**
  - Use unique_ptr everywhere
  - Understand move semantics
  - std::move practice

#### Day 5-7: Modern STL Features
- [ ] Read: `expert.md` - std::optional, std::variant
- [ ] **Practice:**
  - Use std::optional for "maybe" values
  - Structured bindings
  - Modern algorithms

**Week 10 Project:** Modern C++ Task Manager
- Use smart pointers exclusively
- Lambda functions for filtering
- Modern STL containers
- std::optional for return values
- Move semantics for efficiency

---

### **Week 11: Real-World Patterns & Best Practices**
**Focus:** Professional C++ development

#### Day 1-2: Common Patterns
- [ ] Read: `common_patterns.md` - All advanced patterns
- [ ] **Practice:**
  - Two-pointer technique
  - Sliding window
  - Frequency counting
  - Custom sorting

#### Day 3-4: Design Patterns
- [ ] Read: `expert.md` - Design Patterns (Factory, Singleton)
- [ ] **Practice:**
  - Implement Factory pattern
  - Understand when to use Singleton
  - Observer pattern basics

#### Day 5-7: Code Quality
- [ ] Read: `expert.md` - SOLID Principles
- [ ] Read: `advanced_basics.md` - Best Practices
- [ ] **Practice:**
  - Refactor old code
  - Apply naming conventions
  - Code review your projects

**Week 11 Project:** Mini Game Engine Framework
- Entity-component system
- Factory pattern for entity creation
- Observer pattern for events
- Smart pointers for memory
- Modern C++ throughout

---

### **Week 12: Final Project & Review**
**Focus:** Build something real and comprehensive

#### Day 1-2: Planning
- [ ] Choose final project (see suggestions below)
- [ ] Design class hierarchy
- [ ] Plan data structures
- [ ] Write pseudocode

#### Day 3-6: Implementation
- [ ] Code your project
- [ ] Apply everything learned
- [ ] Use modern C++ features
- [ ] Proper error handling
- [ ] Memory management

#### Day 7: Review & Polish
- [ ] Code review
- [ ] Add comments
- [ ] Test thoroughly
- [ ] Create README

### **Final Project Options:**

1. **Text-Based RPG Game**
   - Character classes (inheritance)
   - Inventory system (containers)
   - Battle system
   - Save/Load (file I/O)
   - Smart pointers for game objects

2. **Data Structure Visualizer**
   - Implement various data structures
   - Templated implementations
   - Visualize operations (console)
   - Performance comparisons
   - Exception handling

3. **File Compression Tool**
   - Read/write binary files
   - Huffman encoding implementation
   - Memory efficient design
   - Progress reporting
   - Error handling

4. **Personal Finance Manager**
   - Track income/expenses
   - Categories and budgets
   - Reports and statistics
   - Data persistence
   - Modern STL usage

5. **Command-Line Chat Server**
   - Client-server architecture
   - Socket programming
   - Multi-threading
   - User management
   - Protocol design

---

## 📚 Daily Routine Recommendation

### Weekday Schedule (2 hours/day)
- **15 min:** Review previous concepts
- **45 min:** Read new material and take notes
- **45 min:** Hands-on coding practice
- **15 min:** Document what you learned

### Weekend Schedule (3-4 hours/day)
- **1 hour:** Deep dive into new concepts
- **2-3 hours:** Project work and practice
- **30 min:** Review and consolidate learning

---

## 🎯 Key Success Strategies

### 1. **Come from Python Mindset:**
- Accept that C++ is lower-level
- Embrace explicit memory management
- Types matter - use them wisely
- Compilation errors are your friend

### 2. **Practice Daily:**
- Code every single day
- Type out examples, don't copy-paste
- Break things intentionally to learn
- Debug your own errors

### 3. **Leverage Python Knowledge:**
```
Python List      → C++ std::vector
Python Dict      → C++ std::map or std::unordered_map
Python Set       → C++ std::set or std::unordered_set
Python Tuple     → C++ std::tuple or std::pair
Python generator → C++ iterator or range-based for
```

### 4. **Use Compiler Warnings:**
```bash
# Always compile with warnings
g++ -Wall -Wextra -std=c++17 program.cpp -o program

# Add these flags:
# -Wall: enable common warnings
# -Wextra: extra warnings
# -Wpedantic: strict standard compliance
# -std=c++17: use C++17 standard
```

### 5. **Build Projects:**
- Don't just do exercises
- Build real things you care about
- Refactor as you learn new concepts
- Keep a portfolio

### 6. **Read Others' Code:**
- Browse GitHub C++ projects
- Study STL implementation
- Read cppreference.com
- Learn from best practices

---

## 📖 Comparison Guide: Python vs C++

### Quick Reference for Python Developers:

| Concept | Python | C++ |
|---------|--------|-----|
| **Variables** | `x = 5` | `int x = 5;` |
| **Lists** | `lst = [1,2,3]` | `vector<int> vec = {1,2,3};` |
| **Dictionaries** | `d = {'a': 1}` | `map<string, int> m = {{"a", 1}};` |
| **Functions** | `def func(x):` | `void func(int x) {` |
| **Classes** | `class C:` | `class C {` |
| **Printing** | `print(x)` | `cout << x << "\n";` |
| **Input** | `x = input()` | `cin >> x;` |
| **String concat** | `s1 + s2` | `s1 + s2` (same!) |
| **List append** | `lst.append(x)` | `vec.push_back(x);` |
| **Length** | `len(lst)` | `vec.size()` |
| **Range loop** | `for x in lst:` | `for(auto x : vec) {` |
| **Index loop** | `for i in range(n):` | `for(int i=0; i<n; ++i) {` |
| **Exceptions** | `try:/except:` | `try {} catch() {}` |
| **None** | `None` | `nullptr` |
| **True/False** | `True/False` | `true/false` |

### Memory Management Mindset Shift:

**Python:**
- Everything is automatic
- Garbage collector handles cleanup
- References everywhere

**C++:**
- You control memory
- Must delete what you new
- Choose value vs reference vs pointer
- Modern C++: use smart pointers!

---

## ✅ Weekly Checkpoints

### End of Week 1:
- [ ] Can write basic C++ programs
- [ ] Understand compilation process
- [ ] Comfortable with loops and conditionals

### End of Week 2:
- [ ] Write modular code with functions
- [ ] Understand pass-by-value vs reference
- [ ] Use vectors for dynamic arrays

### End of Week 3:
- [ ] Master STL containers basics
- [ ] Handle files confidently
- [ ] String manipulation skills

### End of Week 4:
- [ ] Understand pointers and memory
- [ ] Use smart pointers
- [ ] Grasp the difference from Python

### End of Week 5:
- [ ] Write classes with proper encapsulation
- [ ] Understand constructors/destructors
- [ ] Design object-oriented systems

### End of Week 6:
- [ ] Use all major STL containers
- [ ] Apply STL algorithms
- [ ] Choose right container for task

### End of Week 7:
- [ ] Write template functions
- [ ] Create generic classes
- [ ] Understand type parameters

### End of Week 8:
- [ ] Handle errors properly
- [ ] Write exception-safe code
- [ ] Input validation mastery

### End of Week 9:
- [ ] Use inheritance effectively
- [ ] Implement polymorphism
- [ ] Design class hierarchies

### End of Week 10:
- [ ] Use modern C++ features
- [ ] Write idiomatic C++17 code
- [ ] Leverage standard library

### End of Week 11:
- [ ] Apply design patterns
- [ ] Write professional code
- [ ] Follow best practices

### End of Week 12:
- [ ] Complete working project
- [ ] Portfolio-ready code
- [ ] Confident C++ developer!

---

## 🚀 After 12 Weeks - Next Steps

### Continue Learning:
1. **Concurrency & Multithreading**
   - Threading library deep dive
   - Lock-free programming
   - Parallel algorithms

2. **Advanced C++**
   - Metaprogramming
   - Perfect forwarding
   - SFINAE and concepts

3. **Specialized Domains**
   - Game development (Unreal Engine)
   - Systems programming
   - Embedded C++
   - High-performance computing

4. **Professional Skills**
   - CMake mastery
   - Testing frameworks
   - Continuous integration
   - Code review practices

### Keep Practicing:
- **LeetCode/HackerRank** in C++
- **Project Euler** problems
- **Advent of Code** challenges
- Contribute to open source C++ projects

### Resources:
- **cppreference.com** - Best C++ reference
- **learncpp.com** - Comprehensive tutorials
- **C++ Weekly** (YouTube) - Jason Turner
- **CppCon** talks on YouTube

---

## 💡 Tips for Success

### Do's:
✅ Compile and run every example  
✅ Make mistakes and learn from them  
✅ Ask "why" not just "how"  
✅ Build projects, not just exercises  
✅ Use modern C++ features  
✅ Read compiler errors carefully  
✅ Refactor code as you learn  

### Don'ts:
❌ Skip the basics (pointers, memory)  
❌ Just read without coding  
❌ Give up on compiler errors  
❌ Use C-style code in C++  
❌ Ignore memory leaks  
❌ Compare C++ to Python negatively  
❌ Try to learn everything at once  

---

## 🎓 Graduation Criteria

You're ready to move to advanced topics when you can:
- [ ] Write a multi-class program from scratch
- [ ] Use pointers and references correctly
- [ ] Choose appropriate STL containers
- [ ] Handle errors gracefully
- [ ] Implement inheritance hierarchies
- [ ] Use templates effectively
- [ ] Apply modern C++ features
- [ ] Debug your own code efficiently
- [ ] Complete projects without external help
- [ ] Read and understand others' C++ code

---

**Remember:** Coming from Python, C++ will feel more verbose and "manual" at first. That's normal! The control you gain over memory and performance is worth the learning curve. Stick with it, and you'll appreciate both languages for their strengths.

**Good luck on your C++ journey! 🚀**

*Start Date: January 26, 2026*  
*Expected Completion: April 19, 2026*  
*You've got this! 💪*
