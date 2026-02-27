/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
  Sec Base
 */
#include <iostream>
using namespace std;

class Vector {
public:
    Vector() {
        theSize = 0;
        theCapacity = 0;
        data = nullptr;
    }

    //Vector(size_t size, int value = 0) {
    explicit Vector(size_t size, int value = 0) {
        theSize = theCapacity = size;

        data = new int[theCapacity];
        for (size_t index = 0; index < theCapacity; ++index) {
            data[index] = value;
        }
    }

    //
    // Copy control
    //

    //  Destructor
    ~Vector() {
        //delete data; // Not quite
        delete [] data;
    }

    //  Copy constructor
    Vector(const Vector& rhs) {
        // copy over the other values
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;

        // allocate a new array and copy the elements
        data = new int[theCapacity];
        for (size_t index = 0; index < theSize; ++index) {
            //*(data + index) = *(rhs.data + index); // Works. But don't.
            data[index] = rhs.data[index];

            /*
                what is the address of the first element in data?
                     data
                what is the value there?
                     *data
                what is the address of the second element in the array? 
                     Pointer arithmetic!!!!
                     data + 1
                what is the value there?
                     *(data + 1)
                     data[1]
             */
        }
    } // copy constructor

    //  Assignment operator
    Vector& operator=(const Vector& rhs)
    {
        // 0. Self assignment test
        if (&rhs != this) { // if NOT doing self assignment

            // 1. Free up our resources
            delete [] data;

            // 2. Allocate and copy over everything from rhs
            // copy over the other values
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;

            // allocate a new array and copy the elements
            data = new int[theCapacity];
            for (size_t index = 0; index < theSize; ++index) {
                data[index] = rhs.data[index];
            }
        }

        // 3. return ourself
        return *this;
    } // assignment operator

    void push_back(int val)
    {
        // Check that we have space and allocate more space if needed
        if (theSize == theCapacity) {
            if (theCapacity == 0) {
                delete [] data;
                theCapacity = 1;
                data = new int[1];
            } else {
                // Allocate a bigger array
                int* original = data;
                data = new int[2 * theCapacity];
                // and copy over the values
                for (size_t index = 0; index < theSize; ++index) {
                    data[index] = original[index];
                }
                // free up the original
                delete [] original;

                // update the capacity
                theCapacity *= 2;
            }
        }

        // insert the value in the next available slot
        data[theSize] = val;

        // bump our counter of slots
        ++theSize;
        
    } // push_back

    size_t size() const {
        return theSize;
    }

    void pop_back() {
        --theSize;
    }
    void clear() { theSize = 0; }

    // Square brackets
    //int operator[](size_t index) {
    int operator[](size_t index) const {
        return data[index];
    }
    
    //int& operator[](size_t index) const {
    int& operator[](size_t index) {
        return data[index];
    }

    // Ranged for
    // int* begin() {
    //     return data;
    //     //return &data[0];
    // }

    // int* end() {
    //     return data + theSize;
    //     //return &data[theSize];
    // }
    
    const int* begin() const {
        return data;
        //return &data[0];
    }

    const int* end() const {
        return data + theSize;
        //return &data[theSize];
    }
    
private:
    // ???
    size_t theSize;
    size_t theCapacity;
    int* data;
};

void printVector(const Vector& v) {
    // for (size_t i = 0; i < v.size(); ++i) {
    //     cout << v[i] << ' ';
    // }

    for (int val : v) {
        cout << val << ' ';
    }
    cout << endl;

    // for (int* p = v.begin(); p != v.end(); ++p) {
    //     *p = 28;
    // }
    
}

int main() {

    Vector v;  // Not templated.  Our Vector class can only hold ints.
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;

        /*
          v[i]
          v.operator[](i)
         */
    }

    Vector v2(v); // copy constructor
    Vector v3;    // default constructor
    v3 = v;       // assignment operator

    v[0] = 100;
    //v.operator[](0) = 100;

    // implicit conversion
    //v = 17;
    //v = Vector(17);

    printVector(v);
    printVector(v);

    //for (int val : v) {
    //for (int* p = v.begin(); p != v.end(); ++p) {
    for (const int* p = v.begin(); p != v.end(); ++p) {
        int val = *p;

        cout << val << ' ';
    }
    cout << endl;


}

