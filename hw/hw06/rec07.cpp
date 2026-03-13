/*
 Pragun Damani
  rec07.cpp
  CS2124
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here. Note, friend functions should have
// just their prototypes inside the class. Their definitions should
// appear below main.
class Rational{
friend ostream& operator<<(ostream& os, const Rational& rhs);
friend istream& operator>>(istream& is, Rational& rhs);
friend bool operator==(const Rational& lhs, const Rational& rhs);
friend bool operator<(const Rational& lhs, const Rational& rhs);
    void normalize(){
        int gcd = greatestCommonDivisor(nume,denom);
            if (!(gcd == 1 || gcd == -1 || gcd == 0)){
                nume /= gcd;
                denom /= gcd;
            }
        if (denom<0){
            nume*=-1;
            denom*=-1;
        }

    }

public:
    Rational(int gnume = 0, int gdenom = 1){
        nume = gnume;
        denom = gdenom;
    };

    Rational& operator+=(const Rational& rhs){
        nume = nume*rhs.denom + rhs.nume*denom;
        denom *= rhs.denom;

        int gcd = greatestCommonDivisor(nume,denom);

        normalize();

        return *this;
    }

   Rational& operator++(){
       nume += denom;
       return *this;
   }
   Rational operator++(int dummy){
       Rational result = *this;
       ++(*this);
       return result;
   }

   explicit operator bool()const{
       return nume!=0;
   }


private:
    int nume;
    int denom;
};

// Any functions that are not members oe friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rat);
Rational operator--(Rational& rat, int dummy);
int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;     // Implement += as a member
    cout << "a = " << a << endl;

    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why SHOULDN'T it compile?
    cout << "a-- -- = " << (a--) << endl;
    cout << "a = " << a << endl;

//     // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

//     // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalvesher(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members should have
// their definitions here...

ostream& operator<<(ostream& os, const Rational& rhs){
    os << rhs.nume << "/" << rhs.denom;
    return os;
}

istream& operator>>(istream& is, Rational& rhs){
    char garb;
    is >> rhs.nume >> garb >> rhs.denom;
    if (rhs.nume>garb){
        cerr << "Numertor larger than denom";
    }

    if (rhs.denom==0){
        cerr<< "denom divedes by 0";
    }

    rhs.normalize();

    return is;
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result = lhs;
    return result += rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.nume == rhs.nume && lhs.denom == rhs.denom);
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.nume*rhs.denom<rhs.nume*lhs.denom);
}

bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs<rhs || lhs==rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return (lhs<rhs || lhs==rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return (lhs>rhs || lhs==rhs);
}

Rational& operator--(Rational& rat){
    rat += -1;
    return rat;
}

Rational operator--(Rational& rat, int dummy){
    Rational res = rat;
    rat += -1;
    return res;
}
