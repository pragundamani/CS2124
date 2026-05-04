#include <cassert>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct MyException : public out_of_range {
  MyException(const string &whatString, int val)
      : out_of_range(whatString), val(val) {}
  int val;
};

void bar(int n) {
  assert(n <= 200);

  if (n > 200) {
    throw out_of_range("n was too large");
  }
}

void foo(int n) { bar(n); }

int main() {
  try {
    foo(300);
  }

  catch (const MyException &ex) {
    cout << "Caught exception what is " << ex.what() << endl
         << " n was " << ex.val << endl;
  }
}
