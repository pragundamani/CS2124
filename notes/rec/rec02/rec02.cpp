/*
Pragun Damani pd2752
  rec02.cpp
  spring 2026
*/

#include <cstddef>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct ChemFormula {
    vector<string> name;
    int carbs = 0;
    int hyds = 0;
};

void openFile(ifstream& hydrocarbs);
size_t formSearcher(int carboNum, int hydroNum, const vector<ChemFormula>& formulas);
void addToVector(const string& name, int carbonNum, int hydroNum, vector<ChemFormula>& formulas);
void fileReader(ifstream& hydrocarbs, vector<ChemFormula>& formulas);
void hydrocarbPrinter(const vector<ChemFormula>& formulas);
void sortingBasic(vector<ChemFormula>& formulas);

int main() {
    vector<ChemFormula> knownHydrocarbs;
    //open file
    //ifstream hydrocarbs("hydrocarbs.txt")
    // openfile(hydrocarbs)
    ifstream hydrocarbs;
    openFile(hydrocarbs);
    fileReader(hydrocarbs, knownHydrocarbs);
    
    cout << endl << "unsorted" << endl;
    hydrocarbPrinter(knownHydrocarbs);
    
    cout << endl << "sorted" << endl;
    sortingBasic(knownHydrocarbs);
    hydrocarbPrinter(knownHydrocarbs);
    return 0;
}

void openFile(ifstream& hydrocarbs){
    string fileName = "hydrocarbs.txt";
    cout << "File name? ";
    // cin>> fileName;
    hydrocarbs.open(fileName);
    
    while (!hydrocarbs){
        cout << "File didnt open \nPlease try again\n";
        cin>> fileName;
        hydrocarbs.open(fileName);
    }
    cout << endl;
}

size_t formSearcher(int carboNum, int hydroNum, const vector<ChemFormula>& formulas){
    size_t returner = size(formulas);
    
    for(size_t index = 0; index<size(formulas); index++){
        if (formulas[index].carbs == carboNum && formulas[index].hyds == hydroNum){
            returner = index;
            return returner;
        }
    }
    return returner;
}

void addToVector(const string& name, int carbonNum, int hydroNum, vector<ChemFormula>& formulas){
    size_t formulasSize = size(formulas);
    size_t location = formSearcher(carbonNum,hydroNum,formulas);
    if (formulasSize == location){
        ChemFormula tempFormula;
        tempFormula.carbs = carbonNum; 
        tempFormula.hyds = hydroNum;
        tempFormula.name.push_back(name);
        
        formulas.push_back(tempFormula);
    }
    else{
        formulas[location].name.push_back(name);
    }
}

void fileReader(ifstream& hydrocarbs, vector<ChemFormula>& formulas){
    //reading file
    string name;
    char carbon = 'C';
    int carboNum = 0;
    char hydrogen = 'H';
    int hydroNum = 0;
    while (hydrocarbs>>name>>carbon>>carboNum>>hydrogen>>hydroNum){
        addToVector(name, carboNum, hydroNum, formulas);
    }
}

void hydrocarbPrinter(const vector<ChemFormula>& formulas){
    for(const ChemFormula& form : formulas){
        cout << "C" << form.carbs << "H" << form.hyds << " ";
        for (const string& formName : form.name){
            cout << formName << " ";
        }
        cout << endl;
    }
}

void sortingBasic(vector<ChemFormula>& formulas){
    for(size_t index = 0; index < size(formulas); index++){
        for (size_t j_index = 0; j_index<index; j_index++){
            if (formulas[j_index].carbs > formulas[j_index+1].carbs){
                ChemFormula temp = formulas[j_index];
                formulas[j_index] = formulas[j_index+1];
                formulas[j_index+1] = temp;
            }
            else if ((formulas[j_index].carbs == formulas[j_index+1].carbs)
               &&(formulas[j_index].hyds>formulas[j_index+1].hyds)){    
                    ChemFormula temp = formulas[j_index];
                    formulas[j_index] = formulas[j_index+1];
                    formulas[j_index+1] = temp;
            }
        }
    }
}
