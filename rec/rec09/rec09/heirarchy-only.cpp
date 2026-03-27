#include <cstddef>
#include <vector>
#include <iostream>
#include <ostream>
using namespace std;

class PrintedMaterial {
friend ostream& operator<<(ostream& os, const PrintedMaterial& rhs){
    os << rhs.numOfPages;
    return os;
}
public:
    PrintedMaterial(unsigned numPages) : numOfPages(numPages) { }
    //virtual void displayNumPages() const { cout << numOfPages << endl; }
    virtual void displayNumPages() const = 0; 
    //creates error unable to make object of abstract class
    
private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages ) : PrintedMaterial(numPages) {}

    void displayNumPages() const override { 
        PrintedMaterial::displayNumPages();
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages) : PrintedMaterial(numPages) {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numOfIndexPages) 
        : Book(numPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages() const override { 
        PrintedMaterial::displayNumPages();
        cout << " Index pages: " << numOfIndexPages << endl; 
    }
private:
    unsigned numOfIndexPages = 0;
};

class Novel : public Book {
public:
    Novel(unsigned numPages) : Book(numPages) {}

    void displayNumPages() const override { 
        PrintedMaterial::displayNumPages();
    }

private:
};

// tester/modeler code
int main() {
    TextBook text(5430,23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();

    //PrintedMaterial pm = text;
    //pm.displayNumPages();
    //PrintedMaterial* pmPtr;
    //pmPtr = &text;
    //pmPtr->displayNumPages();

    vector<PrintedMaterial*> printedStuff;
    printedStuff.push_back(&text);
    printedStuff.push_back(&novel);
    printedStuff.push_back(&mag);

    for(size_t i = 0; i<printedStuff.size(); i++){
        printedStuff[i]->displayNumPages();
    }

    for(PrintedMaterial* pmPtr : printedStuff){
        pmPtr->displayNumPages();
    }
}
