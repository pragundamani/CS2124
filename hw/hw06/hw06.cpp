/*
 Pragun Damani: pd2752
 hw06.cpp
 Spring 2026
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigUnsigned {
    friend ostream& operator<<(ostream& os, const BigUnsigned& rhs);
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);

public:
    BigUnsigned(int value = 0) {
        if (value <= 0) {
            digits.push_back(0);
            return;
        }

        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }

    BigUnsigned(const string& str) {
        if (str.empty() || !isDigitChar(str[0])) {
            digits.push_back(0);
            return;
        }

        //take only starting sequence of digits
        size_t end = 0;
        while (end < str.size() && isDigitChar(str[end])) {
            ++end;
        }

        //skip leading zeros
        size_t firstNonZero = 0;
        while (firstNonZero < end && str[firstNonZero] == '0') {
            ++firstNonZero;
        }

        if (firstNonZero == end) {
            digits.push_back(0);
            return;
        }

        for (size_t index = end; index > firstNonZero; --index) {
            digits.push_back(str[index - 1] - '0');
        }
    }

    BigUnsigned& operator+=(const BigUnsigned& rhs) {
        const size_t rhsSize = rhs.digits.size();
        size_t maxSize = digits.size();
        if (rhsSize > maxSize) {
            maxSize = rhsSize;
        }

        if (digits.size() < maxSize) {
            digits.resize(maxSize, 0);
        }

        int carry = 0;
        for (size_t index = 0; index < maxSize; ++index) {
            const int rhsDigit = (index < rhsSize) ? rhs.digits[index] : 0;
            const int sum = digits[index] + rhsDigit + carry;
            digits[index] = sum % 10;
            carry = sum / 10;
        }

        if (carry != 0) {
            digits.push_back(carry);
        }

        trim();
        return *this;
    }

    BigUnsigned& operator++() {    //pre-increment
        *this += 1;
        return *this;
    }

    BigUnsigned operator++(int) {  //post-increment
        BigUnsigned old(*this);
        ++(*this);
        return old;
    }

    explicit operator bool() const {
        if (digits.size() == 1 && digits[0] == 0) {
            return false;
        }
        return true;
    }

private:
    static bool isDigitChar(char ch) {
        return ch >= '0' && ch <= '9';
    }

    void trim() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    vector<int> digits; //low-order digit first
};

//Any functions that are not members and not friends should have
//prototypes here.
//All non-member functions should have their definitions after main.
//prototypes
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs);
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);

int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    //+=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321000");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    //How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}//main

ostream& operator<<(ostream& os, const BigUnsigned& rhs) {
    for (size_t index = rhs.digits.size(); index > 0; --index) {
        os << rhs.digits[index - 1];
    }
    return os;
}

BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs) {
    lhs += rhs;
    return lhs;
}

bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return false;
    }

    for (size_t index = 0; index < lhs.digits.size(); ++index) {
        if (lhs.digits[index] != rhs.digits[index]) {
            return false;
        }
    }
    return true;
}

bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return lhs.digits.size() < rhs.digits.size();
    }

    for (size_t index = lhs.digits.size(); index > 0; --index) {
        if (lhs.digits[index - 1] != rhs.digits[index - 1]) {
            return lhs.digits[index - 1] < rhs.digits[index - 1];
        }
    }
    return false;
}

bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return rhs < lhs;
}

bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs < rhs);
}
