/*
 * bits
 * print numbers by splitting a non negative integers
 * */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void printDigits(int n) {
  if (n < 10) {
    cout << n << ' ';
  } else {
    printDigits(n / 10);
    cout << n % 10 << ' ';
  }
}

void binPrintDigits(int n) {
  if (n < 2) {
    cout << n << ' ';
  } else {
    binPrintDigits(n / 2);
    cout << n % 2 << ' ';
  }
}

/* do it
 * int countBits(int n) {
  int result = countBits()
}*/

void foo() {
  vector<int> v;

  v.push_back(6);

  /*v[17] = 42;
  cout << v[17] << endl;*/

  v.at(17) = 42;
  cout << v.at(17) << endl;
}

void bar(int n) {
  if (n > 200) {
    // throw exception();
    throw out_of_range("n was too large");
  }
}

int main() {
  printDigits(2134567);
  cout << endl;
  binPrintDigits(177);
  cout << endl;

  // foo();
  try {
    foo();
  }
  // catch (exception ex) {
  // cerr << "Caught an exception. What is: " << ex.what() << endl;
  // }
  catch (const out_of_range &ex) {
    cerr << "Caught an out_of_range. What is: " << ex.what() << endl;
  } catch (exception &ex) {
    cerr << "Caught an exception. What is: " << ex.what() << endl;
  }

  cout << "still running";
}
