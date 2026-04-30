/*
  The STL. Standard Template Library
  26S - Sec C
*/

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename T, typename U> T myFind(T start, T stop, U target) {
  for (T iter = start; iter != stop; ++iter) {
    // if (*iter == target) return iter;
    if (*iter == target) {
      // foo();
      return iter;
    }
  }
  return stop;
}

template <typename T, typename U> T myFind_if(T start, T stop, U pred) {
  for (T iter = start; iter != stop; ++iter) {
    if (pred(*iter))
      return iter;
  }
  return stop;
}

// Predicate
bool isEven(int val) { return val % 2 == 0; }

int main() {
  cout << "running";
  char arr[] = "Bjarne Stroustrup";
  int len = 17;
  sort(arr, arr + len);

  list<char> lc(arr, arr + len);

  vector<char> vc(lc.begin(), lc.end());

  list<char>::iterator where1 = find(lc.begin(), lc.end(), 'n');
  vector<char>::iterator where2 = find(vc.begin(), vc.end(), 'n');
  char *where3 = find(arr, arr + len, 'n');

  list<int> li{17, -3, 6, 28, 13};
  list<int>::iterator where4 = find_if(li.begin(), li.end(), isEven);
  auto where5 = find_if(li.begin(), li.end(), isEven);
  // where5 = find_if(li.begin(), li.end(), val % 2 == 0);
  where5 = find_if(li.begin(), li.end(), [](int val) { return val % 2 == 0; });
  // lambda is defined by: [] (param) {expression;}

  int divisor; //     \/ this is lambda capure, makes a copy from local scope
  auto y = [divisor](int val) { return val % 2 == 0; };

  auto x = 17.0;
  // auto y; // Won't compile because C++ cannot infer the type of y
}
