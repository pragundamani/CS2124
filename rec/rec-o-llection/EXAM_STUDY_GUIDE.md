# CS2124 Comprehensive Exam Notes (Lectures + Recitations + HW)

## Source Coverage
- Lecture files used: `/home/paragon/CS2124/notes/lec1.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec2.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/lec13.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/lec4_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec5_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec6_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec7_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec8_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/lec9_breakdown.md`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec4.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec5.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec6.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec7.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec8.cpp`.
- Lecture files used: `/home/paragon/CS2124/notes/source/lec9.cpp`.
- Recitation files used: `rec01.cpp` to `rec07.cpp`.
- Homework files used: `/home/paragon/CS2124/hw/hw05/hw01.cpp` to `hw05.cpp`.
- Formatting constraint honored: flattened bullets only, no tables.

## Core C++ Foundations (lec1)
- Minimal program skeleton:
```cpp
int main() {
    return 0;
}
```
- Every function has an explicit return type.
- `//` is line comment syntax.
- `/* ... */` is block comment syntax.
- Stream output basics:
```cpp
#include <iostream>
std::cout << "CS";
```
- Namespace convenience form:
```cpp
using namespace std;
cout << "CS";
```
- Chaining output uses repeated `<<` operators.
- `\n` inserts newline characters.
- Primitive types to remember: `int`, `long`, `float`, `double`, `char`, `bool`.
- Integer division truncates toward zero.
- Mixed int/double division promotes to floating point.
- Division by zero is undefined behavior for integers.
- Unsigned wraparound is modular arithmetic.
- Logical operators: `&&`, `||`, `!`.
- Comparison operators: `==`, `!=`, `<`, `>`, `<=`, `>=`.
- Arithmetic operators: `+`, `-`, `*`, `/`, `%`.
- Compound assignment operators: `+=`, `-=`, `*=`, `/=`, `%=`.
- Loop forms to know cold: `while`, `for`, `do-while`.
- `break` exits loop immediately.
- `continue` skips to next iteration.
- Vectors are dynamic arrays with runtime size growth.
- Use `size_t` with vector size/index comparisons.
- `vector.clear()` removes elements and sets logical size to zero.
- Range-for by value copies each element.
- Range-for by reference (`T&`) allows in-place mutation.
- Strings are mutable objects in C++.
- String API essentials: `.size()`, `.length()`, `[]`, `substr`, `find`.
- `string::npos` means “not found”.
- File stream categories: `ifstream`, `ofstream`, `fstream`.
- Always check stream open success before reading.

## Initialization, Encapsulation, Methods (lec4)
- Class default access is private.
- Struct default access is public.
- Constructor initialization lists initialize members before constructor body.
- Initialization-list pattern:
```cpp
class Person {
public:
    Person(const string& name) : name(name) {}
private:
    string name;
};
```
- Use `const` member functions for read-only operations.
- Getter pattern with const-correct return reference:
```cpp
const string& getName() const { return name; }
```
- Free helper can use getters instead of breaking encapsulation.
- Friend operator pattern for printable objects:
```cpp
friend ostream& operator<<(ostream& os, const Person& p);
```
- `ostream` is passed by reference.
- `operator<<` returns `ostream&` for chainability.

## Nested Classes, Scope Resolution, Constructors (lec5)
- Nested class can be private or public depending on design intent.
- Private nested class hides helper type from external API.
- Outer class can own nested-class object as a member.
- Nested type usage syntax inside class: `Date bday;`.
- Nested type usage syntax outside class: `Person::Date`.
- Scope resolution operator is `::`.
- Constructor composition pattern:
```cpp
Person(const string& name, int m, int d, int y)
    : name(name), bday(m, d, y) {}
```
- If you define any constructor, default no-arg constructor is not auto-generated.
- Friend overload for nested class typically uses fully-qualified nested type.

## Pointers, Self-Referential Design, nullptr (lec6)
- Class cannot contain direct instance of itself as member.
- Class can contain pointer to same class type.
- Self-referential relation pattern:
```cpp
class Person {
private:
    Person* spouse;
};
```
- Pointer stores address.
- Reference is alias, not reseatable address holder.
- Address-of operator: `&x`.
- Dereference operator: `*p`.
- Arrow operator accesses pointee members: `p->name`.
- Null pointer literal in modern C++ is `nullptr`.
- Initialize pointers to `nullptr` when no valid target exists.
- Marriage pattern from lecture: set both directional links atomically.

## Const Pointers and Pointer Constness (lec7, lec9)
- `const int* p` means pointer to const int.
- `int* const p` means const pointer to int.
- `const int* const p` means const pointer to const int.
- Pointer-constness example:
```cpp
int x = 17;
int y = 42;
const int* p = &x; // cannot modify *p
int* const q = &x; // cannot reseat q
```
- Use const-correct pointer types to express intended mutability.

## Copy Control and Rule of Three (lec8, rec05, rec06)
- Any class owning raw heap memory needs copy control.
- Rule of Three members:
- Destructor.
- Copy constructor.
- Copy assignment operator.
- Destructor responsibility: free owned heap resource.
- Copy constructor responsibility: deep-copy source into new object.
- Copy assignment responsibility: self-assignment guard, release old, deep-copy new, return `*this`.
- Copy constructor template:
```cpp
Thing(const Thing& rhs) {
    p = new int(*rhs.p);
}
```
- Copy assignment template:
```cpp
Thing& operator=(const Thing& rhs) {
    if (this != &rhs) {
        delete p;
        p = new int(*rhs.p);
    }
    return *this;
}
```
- Passing object by value triggers copy constructor.
- Shallow copy of pointer-owning classes causes double-delete risks.
- Deep copy duplicates pointee resources to separate ownership.
- `rec05.cpp` deep-copies `StudentRecord*` vector elements.
- `rec06.cpp` deep-copies dynamic `Entry**` array and owned entries.

## Manual Dynamic Arrays and Vector Internals (lec9, rec06)
- Conceptual vector internals:
- Logical size.
- Allocated capacity.
- Pointer to heap buffer.
- Basic custom-vector fields:
```cpp
size_t theSize;
size_t theCapacity;
int* data;
```
- Reallocation when full:
- Allocate bigger array.
- Copy/move old elements.
- Release old storage.
- Update pointer/capacity.
- `rec06.cpp` demonstrates doubling-capacity growth strategy.
- `new[]` must pair with `delete[]`.
- `new` must pair with `delete`.

## Constructor Conversions and explicit (lec2)
- Single-argument constructors can create implicit conversions.
- `explicit` blocks unwanted implicit conversions.
- Pattern:
```cpp
class Length {
public:
    explicit Length(int meters) : meters(meters) {}
private:
    int meters;
};
```
- Practical exam point: mark single-arg constructors `explicit` unless implicit conversion is intended.

## Lecture 13 Status (lec13)
- `lec13.cpp` currently has empty `main` placeholder.
- No additional concepts were encoded there yet.

## File I/O Patterns (lec1, rec01, rec02, rec03, hw01, hw02, hw03, hw05)
- Open and validate once pattern:
```cpp
ifstream in("input.txt");
if (!in) {
    cerr << "Error opening input.txt" << endl;
    exit(1);
}
```
- Retry-open with user input pattern:
```cpp
ifstream in;
string filename;
cin >> filename;
in.open(filename);
while (!in) {
    in.clear();
    cin >> filename;
    in.open(filename);
}
```
- Word-token loop pattern:
```cpp
string token;
while (in >> token) {
    // process token
}
```
- Full-line loop pattern:
```cpp
string line;
while (getline(in, line)) {
    // process line
}
```
- Structured record parsing pattern:
```cpp
string name;
char c, h;
int a, b;
while (in >> name >> c >> a >> h >> b) {
    // process one record
}
```
- Command-dispatch pattern:
```cpp
string command;
while (in >> command) {
    if (command == "Warrior") { /* parse + handle */ }
    else if (command == "Battle") { /* parse + handle */ }
    else if (command == "Status") { /* handle */ }
}
```

## Operators and Overloading Coverage (lec4-5-8 + rec + hw)
- Stream insertion overload pattern everywhere:
```cpp
ostream& operator<<(ostream& os, const Type& rhs) {
    // print rhs
    return os;
}
```
- Return `ostream&` to allow `cout << a << b` chaining.
- `rec06.cpp` overloads `Directory::operator[]` for name lookup.
- `rec06.cpp` overloads copy assignment for deep-copy ownership.
- `rec07.cpp` overload set includes arithmetic, comparison, increment, decrement, stream, and bool conversion.
- `rec07.cpp` style pattern: implement non-mutating `operator+` using mutating `operator+=`.
- `rec07.cpp` style pattern: define `!=`, `>`, `<=`, `>=` in terms of `==` and `<`.
- `rec07.cpp` prefix/postfix distinction is mandatory exam knowledge.
- `hw03`, `hw04`, `hw05` use `operator<<` for domain-friendly status output.

## Struct-to-Class Design Progression (hw02 -> hw03 -> hw05)
- `hw02.cpp` uses plain `struct Warrior` and free functions.
- `hw03.cpp` moves behavior into classes (`Warrior`, `WarriorCollection`).
- `hw03.cpp` introduces nested private `Weapon` class for stronger encapsulation.
- `hw04.cpp` introduces object graph relation (`Noble` owns army references).
- `hw05.cpp` expands to command engine over heap-managed nobles/warriors.
- Exam narrative: abstraction increases while free-function glue decreases.

## Battle Logic Invariants (hw02, hw03, hw04, hw05, rec03)
- Battle output always announces participants first.
- Dead vs dead check must happen before strength comparisons.
- If both zero-strength, print dual-dead message.
- If one dead, print corresponding already-dead message.
- Equal strengths produce mutual annihilation.
- Unequal strengths reduce winner by loser amount or ratio depending model.
- `hw02/hw03` model uses absolute subtraction.
- `hw04/hw05` model uses army total ratio scaling.
- Invariant: strengths never become negative in correct implementation.
- Invariant: dead combatants remain dead unless explicitly revived logic exists.

## Noble-Warrior Employment Invariants (hw04, hw05)
- Each warrior employed by at most one noble.
- Hire fails if noble dead.
- Hire fails if warrior already employed.
- Fire fails if noble dead or warrior not in noble’s army.
- Fire success must clear warrior employment flag.
- Army order can be preserved by left-shift + pop_back removal.
- Employment query helper pattern:
```cpp
bool employs(const Warrior& w) const {
    return findWarrior(w) != army.size();
}
```

## Searching and Sentinel Patterns (hw02, hw03, hw05, rec02)
- Index sentinel pattern returns `vec.size()` for “not found”.
- Pointer sentinel pattern returns `nullptr` for “not found”.
- Keep sentinel style consistent per subsystem.
- Example index lookup:
```cpp
size_t findItem(const vector<Item>& items, const string& name) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].name == name) return i;
    }
    return items.size();
}
```
- Example pointer lookup:
```cpp
Type* findType(const vector<Type*>& items, const string& name) {
    for (Type* p : items) {
        if (p->getName() == name) return p;
    }
    return nullptr;
}
```

## Memory Ownership Models Across Your Code
- Stack object model example: locals with automatic cleanup at scope end.
- Non-owning pointer model example: vector of addresses to external objects.
- Owning pointer model example: vector of `new`-allocated objects requiring explicit delete.
- `hw04.cpp` army stores pointers to stack warriors owned by `main`.
- `hw05.cpp` vectors own heap nobles/warriors and perform explicit clear/delete cleanup.
- `rec05.cpp` `Section` owns `StudentRecord*` entries and deletes in destructor.
- `rec06.cpp` `Directory` owns entry pointer array and pointed entries.
- One owner rule: decide exactly who deletes each heap object.

## Pointer Safety Checklist (lec6-9, rec04, hw05)
- Initialize pointers before use.
- Set dangling pointers to `nullptr` after delete.
- Never dereference null pointers.
- Never dereference deleted pointers.
- Never `delete` stack addresses.
- Match `new` with `delete`.
- Match `new[]` with `delete[]`.
- Avoid double delete by clear ownership contracts.

## Const-Correctness Patterns (lec4, lec6, lec7, lec9, rec, hw)
- Mark methods `const` when they do not mutate object state.
- Pass large read-only arguments as `const T&`.
- Use `T&` for in-place mutation parameters.
- Return const references from getters to avoid copying and protect state.
- Const correctness improves API safety and compile-time bug detection.

## String and Character Algorithms (hw01)
- Caesar-decrypt uppercase-only transformation:
```cpp
char decryptChar(char c, int key) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' - key + 26) % 26;
    }
    return c;
}
```
- In-place string decryption pattern:
```cpp
void decryptString(string& s, int key) {
    for (char& ch : s) {
        ch = decryptChar(ch, key);
    }
}
```
- Reverse output pattern must avoid unsigned underflow:
```cpp
for (size_t i = vec.size(); i > 0; --i) {
    cout << vec[i - 1] << '\n';
}
```

## Rational Number Patterns (rec07)
- Maintain invariant: denominator positive.
- Maintain invariant: fraction reduced by gcd.
- Normalize after input and arithmetic updates.
- Prefix increment adds denominator to numerator.
- Postfix increment returns prior value copy.
- Explicit bool conversion evaluates rational nonzero state.
- Comparison via cross multiplication avoids floating conversion.

## Dynamic Array and Copy Control Pattern (rec06)
- Class with owned dynamic array members must define full copy control.
- Deep-copy copy constructor allocates new array and clones entries.
- Deep-copy assignment releases old resources before cloning new resources.
- Self-assignment check prevents invalid delete/copy sequence.
- Destructor releases owned objects then pointer array.
- Overloaded index operator provides dictionary-like lookup API.

## Common Exam Gotchas Seen in Your Lecture/Rec/HW Material
- `sizeof(vector)` is not element count.
- Forgetting stream state reset (`clear`) before reopen causes persistent failures.
- `getline` after `>>` may read leftover newline unless handled.
- Unsigned loop underflow can make infinite or wraparound loops.
- Missing self-assignment guard in assignment operator can corrupt memory.
- Shallow-copying raw pointers causes double-free bugs.
- Returning references to local variables creates dangling references.
- Omitting const on read-only methods blocks use on const objects.
- Forgetting to mark single-arg constructors `explicit` allows accidental conversions.
- Not checking lookup sentinel/null before dereference leads to crashes.
- Calling `delete` on non-heap memory is undefined behavior.

## Practical Snippet Bank for Exam
- Friend stream output skeleton:
```cpp
class X {
    friend ostream& operator<<(ostream& os, const X& rhs);
};
ostream& operator<<(ostream& os, const X& rhs) {
    return os;
}
```
- Safe command parser skeleton:
```cpp
void process(istream& in) {
    string cmd;
    while (in >> cmd) {
        if (cmd == "A") {}
        else if (cmd == "B") {}
        else if (cmd == "C") {}
    }
}
```
- Pointer constness skeleton:
```cpp
int x = 1;
const int* p = &x;
int* const q = &x;
const int* const r = &x;
```
- Rule-of-Three class skeleton:
```cpp
class Owner {
public:
    Owner() : p(new int(0)) {}
    ~Owner() { delete p; }
    Owner(const Owner& rhs) : p(new int(*rhs.p)) {}
    Owner& operator=(const Owner& rhs) {
        if (this != &rhs) {
            delete p;
            p = new int(*rhs.p);
        }
        return *this;
    }
private:
    int* p;
};

```

````markdown
## High-Frequency Midterm Traps (CS2124)

- **Copy constructor vs assignment**
  - `Thing y = x;` → copy constructor
  - `Thing y; y = x;` → assignment operator
  - Creation uses constructor; modification uses assignment.

- **Returning reference to local variable**
```cpp
int& foo() {
    int x = 10;
    return x;  // dangling reference
}
````

* Compiles but results in **undefined behavior**.

* **Returning pointer to local variable**

```cpp
int* foo() {
    int x = 10;
    return &x;
}
```

* Stack variable disappears → **dangling pointer**.

* **Initialization order in constructors**

```cpp
class Demo {
    int b;
    int a;
public:
    Demo(int val) : b(a), a(val) {}
};
```

* Members initialize in **declaration order**, not initializer-list order.

* **Dot vs arrow operator precedence**

```cpp
*p.get()
```

* Parsed as:

```cpp
*(p.get())
```

* Not:

```cpp
(*p).get()
```

* **Pointer vs object member access**

```cpp
p->member
```

equals

```cpp
(*p).member
```

* **Const correctness errors**

```cpp
const int i = 7;
int* p = &i;     // illegal
```

* Cannot store address of const object in non-const pointer.

* **Range-for copy vs reference**

```cpp
for(int x : v)   // copy
for(int& x : v)  // reference
```

* Only reference modifies the container.

* **Const range-for**

```cpp
for(const int& x : v)
```

* Read-only iteration.

* **Implicit constructor conversion**

```cpp
class Num {
public:
    Num(int x);
};
show(3);
```

* Works via implicit conversion.
* Prevent with:

```cpp
explicit Num(int x);
```

* **Self-assignment bug**

```cpp
Bag& operator=(const Bag& rhs) {
    delete p;
    p = new int(*rhs.p);
}
```

* `b = b;` deletes data before copying.
* Fix with:

```cpp
if (this != &rhs)
```

* **Shallow copy of pointer member**

```cpp
Wrap(const Wrap& rhs) : p(rhs.p) {}
```

* Two objects share same pointer → **double delete**.

* **new vs new[] pairing**

```cpp
new T      → delete
new T[n]   → delete[]
```

* **Deleting stack memory**

```cpp
int x;
delete &x;  // undefined behavior
```

* **Dereferencing past-the-end pointer**

```cpp
int arr[3];
int* p = arr + 3;
*p;  // undefined behavior
```

* Pointer valid for comparison but **not dereference**.

* **sizeof array decay**

```cpp
void f(int arr[]) {
    sizeof(arr);
}
```

* `arr` becomes pointer → returns pointer size.

* **Vector size vs capacity misunderstanding**

* `vector.size()` → number of elements.

* `sizeof(vector)` → size of container object.

* **Unsigned loop underflow**

```cpp
for(size_t i = v.size()-1; i >= 0; i--)
```

* Infinite loop due to wraparound.

* **Using uninitialized pointers**

```cpp
int* p;
*p = 5;   // undefined behavior
```

* **Dangling pointer after delete**

```cpp
delete p;
*p = 5;   // invalid
```

* **Assignment operator return type**

```cpp
Num& operator=(const Num& rhs);
```

* Must return reference for chaining:

```cpp
a = b = c;
```

* **Incorrect operator<< signature**
  Correct pattern:

```cpp
ostream& operator<<(ostream& os, const T& rhs);
```

* **Range-for requires begin/end**
  Container must provide:

```cpp
begin()
end()
```

* **Vector element modification trap**

```cpp
for(int x : v) { x += 5; }
```

* Vector unchanged.

* **Pointer equality vs value equality**

```cpp
p == q
```

* Compares **addresses**, not contents.

* **Nested class access**

* Outer class **can access private members of nested class**, but external code cannot.

* **Implicit destructor invocation**

* Stack objects destroy automatically at scope exit.

* Heap objects require manual `delete`.

* **Memory ownership confusion**

* Only the **owner deletes heap memory**.

* Multiple owners → double free.

* **Command parsing pitfalls**

* Mixing `getline` after `>>` without clearing newline causes empty reads.

* **Const member function restriction**

```cpp
void set(int n) const { val = n; }
```

* Illegal because const method cannot modify members.

```
```

## One-Pass Final Review Checklist
- I can explain default access differences between struct and class.
- I can write and explain initialization lists.
- I can explain friend function tradeoffs and stream operator signatures.
- I can explain nested class visibility and `Outer::Inner` scope resolution.
- I can explain pointer basics, `nullptr`, and arrow syntax.
- I can distinguish `const int*` from `int* const`.
- I can implement Rule of Three for pointer-owning classes.
- I can reason about deep copy vs shallow copy outcomes.
- I can implement safe command parsing with validation checks.
- I can model ownership for vectors of raw pointers and clean them correctly.
- I can implement battle/state invariants without contradictory states.
- I can identify and prevent unsigned-underflow loop bugs.
- I can explain `explicit` constructors and conversion control.
- I can write safe file parsing loops for words, lines, and structured records.



