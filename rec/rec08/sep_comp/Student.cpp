#include "Course.h"
#include "Student.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace brooklynpoly{

Student::Student(const string& name) : name(name){}

const string& Student::getName() const{
    return name;
}
    
ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.getName();
    if (rhs.courses.size()==0){
        os << "No courses";
    }
    else{
        for(const Course* courseName : rhs.courses){
            os << courseName->getName() << endl;
        }
    }
    return os;
}

bool Student::addCourse(Course* courseName){
    for (const Course* courseCurr : courses){
        if (courseName == courseCurr){
            cout<< "student already in course ";
            return false;
        }
    }
    courses.push_back(courseName);
    return true;
}

void Student::removedFromCourse(Course* courseName){
    for (size_t index = 0; index < courses.size(); index++){
        if(courses[index]==courseName){
            for (size_t remover = index; remover+ 1 <courses.size(); remover++){
                courses[remover] = courses[remover+1];
            }
            courses.pop_back();
            return;
        }
    }
}}