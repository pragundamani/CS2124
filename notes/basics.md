# C++ Basics - Fundamentals

## Program Structure & Syntax

### Compilation Process
```
Source Code (.cpp) → Preprocessor → Compiler → Assembler → Linker → Executable
```
- Preprocessor handles directives (#include, #define)
- Compiler translates to assembly/object code
- Linker combines object files and libraries

### Basic Program Skeleton
```cpp
int main(){
    return 0;
}
```
- Every function needs `return` or `void`
- `main()` returns int (0 = success, non-zero = error)
- Comments: `//` for line, `/* */` for block comments

### Documentation Comments
```cpp
/**
 * Calculates the area of a rectangle
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 * @return The area as a double
 */
double calculateArea(double width, double height){
    return width * height;
}
```

### Preprocessor Directives
```cpp
#include <iostream>  // include standard library
#include "myfile.h"  // include user-defined header

#define PI 3.14159   // define constant (prefer const over #define)
#define MAX(a,b) ((a) > (b) ? (a) : (b))  // macro function

// Header guards (prevent multiple inclusion)
#ifndef MYHEADER_H
#define MYHEADER_H
// header content here
#endif
```

### Hello World
```cpp
#include <iostream>

int main(){
    std::cout << "Hello World";
    return 0;
}
```

### Namespaces
```cpp
#include <iostream>
using namespace std;

int main(){
    cout << "CS";
    return 0;
}
```
- Using `using namespace std;` allows you to skip `std::` prefix
- Output chaining: `cout << "CS" << " OOP\n";`
- New line: `\n` or `endl`

#### Custom Namespaces
```cpp
namespace MyNamespace {
    int value = 42;
    void myFunction(){
        std::cout << "Hello from namespace\n";
    }
}

int main(){
    std::cout << MyNamespace::value << "\n";
    MyNamespace::myFunction();
    
    // Using declaration (specific)
    using MyNamespace::value;
    std::cout << value << "\n";
    
    // Using directive (entire namespace)
    using namespace MyNamespace;
    myFunction();
    
    return 0;
}
```
- Avoid `using namespace std;` in header files
- Prefer specific `using` declarations over entire namespaces

## Data Types & Variables

### Variable Declaration
```cpp
#include <iostream>
using namespace std;

int main(){
    int a = 5;          // integer
    double b = 3.14;    // floating point number
    char c = 'A';       // single character
    string s = "CS";    // string of characters
    bool flag = true;   // boolean value

    cout << a << "\n";
    cout << b << "\n";
    cout << c << "\n";
    cout << s << "\n";
    cout << flag << "\n"; // prints 1 for true, 0 for false

    return 0;
}
```

### Primitive Data Types
Fundamental data types in C++:
- `int`, `unsigned int`: 4 bytes on most architectures
- `long`, `unsigned long`: at least 4 bytes, often 8 bytes
- `float`: 4 bytes, single precision floating point
- `double`: 8 bytes, double precision floating point
- `char`: 1 byte, represents a single character
- `bool`: 1 byte, represents true or false

### Type Sizes
```cpp
#include <iostream>
using namespace std;

int main(){
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Size of double: " << sizeof(double) << " bytes\n";
    cout << "Size of char: " << sizeof(char) << " bytes\n";
    cout << "Size of bool: " << sizeof(bool) << " bytes\n";
    return 0;
}
```

### Type Modifiers
```cpp
// Signed vs Unsigned
int signedInt = -42;        // can be negative
unsigned int unsignedInt = 42;  // only positive (0 to 4,294,967,295)

// Size modifiers
short int shortNum = 100;        // at least 2 bytes
int normalNum = 100000;          // typically 4 bytes
long int longNum = 100000000L;   // at least 4 bytes
long long bigNum = 10000000000LL; // at least 8 bytes

// Combined modifiers
unsigned long long hugeNum = 18446744073709551615ULL;
```

### String Types
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
    // C-style strings (character arrays)
    char cstr[] = "Hello";
    char cstr2[20] = "World";
    
    cout << strlen(cstr) << "\n";  // 5
    strcpy(cstr2, cstr);            // copy
    strcat(cstr2, " World");        // concatenate
    
    // C++ std::string (preferred)
    string str = "Hello";
    str += " World";                // easy concatenation
    cout << str.length() << "\n";   // 11
    
    return 0;
}
```
- Prefer `std::string` over C-strings for safety and convenience

### Type Inference (auto keyword)
```cpp
auto x = 5;           // int
auto y = 3.14;        // double
auto z = 'A';         // char
auto s = "Hello";     // const char*
auto str = string("Hello");  // string

// Useful with complex types
auto it = myVector.begin();  // instead of vector<int>::iterator it
```

### Constants
```cpp
// const keyword
const int MAX_SIZE = 100;
const double PI = 3.14159;
// MAX_SIZE = 200;  // ERROR: cannot modify const

// constexpr (compile-time constant)
constexpr int ARRAY_SIZE = 50;
constexpr double calc(double x){ return x * 2; }
int arr[ARRAY_SIZE];  // OK: constexpr can be used for array size

// const vs constexpr
const int runtime_const = someFunction();      // evaluated at runtime
constexpr int compile_const = 5 * 10;          // evaluated at compile-time
```

### Type Casting
```cpp
// Implicit casting (automatic)
int a = 5;
double b = a;  // int → double (safe)

// Explicit casting (manual)
double x = 3.14;
int y = (int)x;  // C-style cast: 3

// C++ style casts (preferred)
int i = static_cast<int>(x);  // explicit conversion
double d = static_cast<double>(10) / 3;  // 3.333...

// Other cast types (advanced)
// const_cast - remove const qualifier
// dynamic_cast - safe downcasting with polymorphism
// reinterpret_cast - low-level reinterpretation
```

## Operators

### Arithmetic Operators
```cpp
int a = 10, b = 3;
cout << a + b;  // 13 - addition
cout << a - b;  // 7  - subtraction
cout << a * b;  // 30 - multiplication
cout << a / b;  // 3  - division (integer division)
cout << a % b;  // 1  - modulus (remainder)
```

### Integer Arithmetic Gotchas
```
5/2 = 2              // integer division
5.0/2 = 5/2.0 = 2.5  // floating point division
5/0 = undefined      // runtime error (not always caught)
5.0/0 = inf          // floating point infinity
0U - 1 = 4294967295  // unsigned wrap around (2^32 - 1)
```

### Comparison Operators
```cpp
==  // equal to
!=  // not equal to
<   // less than
>   // greater than
<=  // less than or equal to
>=  // greater than or equal to
```

### Logical Operators
```cpp
&&  // and
||  // or
!   // not
```
**DO NOT use the words (and, or, not) as logical operators**

### Assignment Operators
```cpp
=   // assign
+=  // add and assign (a += b is same as a = a + b)
-=  // subtract and assign
*=  // multiply and assign
/=  // divide and assign
%=  // modulus and assign
```

### Increment/Decrement
```cpp
int i = 5;
i++;    // post-increment (i becomes 6)
++i;    // pre-increment (i becomes 7)
i--;    // post-decrement (i becomes 6)
--i;    // pre-decrement (i becomes 5)

// Difference between pre and post
int a = 5;
int b = a++;  // b = 5, a = 6 (use then increment)
int c = ++a;  // c = 7, a = 7 (increment then use)
```

### Bitwise Operators
```cpp
int a = 5;   // 0101 in binary
int b = 3;   // 0011 in binary

cout << (a & b) << "\n";   // 1  (0001) - AND
cout << (a | b) << "\n";   // 7  (0111) - OR
cout << (a ^ b) << "\n";   // 6  (0110) - XOR
cout << (~a) << "\n";      // -6 (1010 in two's complement) - NOT
cout << (a << 1) << "\n";  // 10 (1010) - left shift
cout << (a >> 1) << "\n";  // 2  (0010) - right shift
```
- Used for low-level operations, flags, bit manipulation
- Left shift by n = multiply by 2^n
- Right shift by n = divide by 2^n

### Operator Precedence and Associativity
```cpp
// Precedence (highest to lowest)
// 1. () [] -> .
// 2. ! ~ ++ -- + - (unary)
// 3. * / %
// 4. + -
// 5. << >>
// 6. < <= > >=
// 7. == !=
// 8. &
// 9. ^
// 10. |
// 11. &&
// 12. ||
// 13. ? :
// 14. = += -= *= /= %=

int result = 5 + 3 * 2;  // 11 (not 16) - multiplication first
int result2 = (5 + 3) * 2;  // 16 - parentheses override precedence
```

## Control Flow

### If Statement
```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 10;
    
    if(x > 5){
        cout << "x is greater than 5\n";
    }
    
    return 0;
}
```

### If-Else Statement
```cpp
#include <iostream>
using namespace std;

int main(){
    int x = 3;
    
    if(x > 5){
        cout << "x is greater than 5\n";
    }
    else{
        cout << "x is not greater than 5\n";
    }
    
    return 0;
}
```

### If-Else If-Else Statement
```cpp
#include <iostream>
using namespace std;

int main(){
    int score = 75;
    
    if(score >= 90){
        cout << "Grade: A\n";
    }
    else if(score >= 80){
        cout << "Grade: B\n";
    }
    else if(score >= 70){
        cout << "Grade: C\n";
    }
    else if(score >= 60){
        cout << "Grade: D\n";
    }
    else{
        cout << "Grade: F\n";
    }
    
    return 0;
}
```

### Scope and Block Statements
```cpp
int main(){
    int x = 10;  // scope: entire main function
    
    {
        int y = 20;  // scope: only this block
        cout << x << "\n";  // OK: x is accessible
        cout << y << "\n";  // OK: y is accessible
    }
    
    // cout << y << "\n";  // ERROR: y out of scope
    
    if(x > 5){
        int z = 30;  // scope: only this if block
    }
    // cout << z << "\n";  // ERROR: z out of scope
    
    return 0;
}
```

### Switch Statement
```cpp
#include <iostream>
using namespace std;

int main(){
    int day = 3;
    
    switch(day){
        case 1:
            cout << "Monday\n";
            break;
        case 2:
            cout << "Tuesday\n";
            break;
        case 3:
            cout << "Wednesday\n";
            break;
        case 4:
            cout << "Thursday\n";
            break;
        case 5:
            cout << "Friday\n";
            break;
        default:
            cout << "Weekend\n";
    }
    
    return 0;
}
```
- `break` prevents fall-through to next case
- Without `break`, execution continues to next case

### Fall-through Behavior
```cpp
int day = 2;

switch(day){
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        cout << "Weekday\n";
        break;
    case 6:
    case 7:
        cout << "Weekend\n";
        break;
    default:
        cout << "Invalid day\n";
}
```
- Intentional fall-through groups multiple cases together

### Ternary Operator
```cpp
int a = 10, b = 20;
int max = (a > b) ? a : b;  // max will be 20
cout << max << "\n";
```

## Loops

### While Loop
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
Output: 0 1 2 3 4

### Do-While Loop
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
- Executes at least once, even if condition is false

### Range-Based For Loop (C++11)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Read-only iteration
    for(int num : numbers){
        cout << num << " ";
    }
    cout << "\n";
    
    // Modifying elements (use reference)
    for(int& num : numbers){
        num *= 2;
    }
    
    // Const reference (efficient for large objects)
    for(const auto& num : numbers){
        cout << num << " ";
    }
    
    return 0;
}
```

### For Loop
```cpp
#include <iostream>
using namespace std;

int main(){
    for(int i = 0; i < 5; i++){
        cout << i << "\n";
    }
    cout << "Done\n";
    return 0;
}
```

### Infinite Loops and Prevention
```cpp
// Intentional infinite loop
while(true){
    cout << "Enter 'q' to quit: ";
    char input;
    cin >> input;
    if(input == 'q') break;
}

// Accidental infinite loop (common mistakes)
int i = 0;
while(i < 10){
    cout << i << "\n";
    // Forgot to increment i!
}

// Prevention: always ensure loop variable changes
for(int i = 0; i < 10; i++){  // clear increment
    cout << i << "\n";
}
```

### Break and Continue
```cpp
#include <iostream>
using namespace std;

int main(){
    // Using break
    for(int i = 0; i < 10; i++){
        if(i == 5) break;  // exits loop when i is 5
        cout << i << "\n";
    }
    
    // Using continue
    for(int i = 0; i < 5; i++){
        if(i == 3) continue;  // skips printing 3
        cout << i << "\n";
    }
    
    return 0;
}
```

### Nested Loops
```cpp
#include <iostream>
using namespace std;

int main(){
    // Print a multiplication table
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 5; j++){
            cout << i * j << "\t";
        }
        cout << "\n";
    }
    
    return 0;
}
```

## Input and Output

### Basic Input
```cpp
#include <iostream>
using namespace std;

int main(){
    int age;
    cout << "Enter your age: ";
    cin >> age;
    cout << "You are " << age << " years old\n";
    
    return 0;
}
```

### Multiple Input
```cpp
#include <iostream>
using namespace std;

int main(){
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;
    cout << "Sum: " << (a + b + c) << "\n";
    
    return 0;
}
```

### Stream Manipulators
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double pi = 3.14159265;
    
    // Set precision
    cout << setprecision(4) << pi << "\n";  // 3.142
    
    // Fixed notation (decimal places)
    cout << fixed << setprecision(2) << pi << "\n";  // 3.14
    
    // Set width
    cout << setw(10) << "Name" << setw(10) << "Age" << "\n";
    cout << setw(10) << "Alice" << setw(10) << 25 << "\n";
    
    // Fill character
    cout << setfill('0') << setw(5) << 42 << "\n";  // 00042
    
    return 0;
}
```

### Reading Strings with Spaces
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string name;
    cout << "Enter your full name: ";
    getline(cin, name);  // reads entire line including spaces
    cout << "Hello, " << name << "\n";
    
    return 0;
}
```
- Use `cin >>` for single words (stops at whitespace)
- Use `getline(cin, string)` for entire lines

### Input Validation and Error Handling
```cpp
#include <iostream>
#include <limits>
using namespace std;

int main(){
    int age;
    cout << "Enter your age: ";
    
    // Check if input is valid
    if(cin >> age){
        cout << "You are " << age << " years old\n";
    } else {
        cout << "Invalid input!\n";
        cin.clear();  // clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
    }
    
    return 0;
}
```

### Formatting Output
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    // Boolean output
    bool flag = true;
    cout << boolalpha << flag << "\n";  // "true" instead of 1
    
    // Hexadecimal output
    int num = 255;
    cout << hex << num << "\n";  // ff
    cout << dec << num << "\n";  // 255 (back to decimal)
    
    // Scientific notation
    double big = 12345.6789;
    cout << scientific << big << "\n";  // 1.234568e+04
    
    return 0;
}
```
