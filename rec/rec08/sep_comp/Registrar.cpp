#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace brooklynpoly{

ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's report" << endl
         << "Courses: \n";
    for(const Course* courseName : rhs.courses){
        os << *courseName << endl;
    }
    os << "Students: \n";
    for(const Student* studentName : rhs.students){
        os << *studentName << endl;
    }
    return os;
}


bool Registrar::addCourse(const string& courseName){
    for (const Course* courseCurr : courses){
        if (courseName == courseCurr->getName()){
            cout << "course already in registrar";
            return false;
        }
    }
    Course* temp = new Course(courseName);
    courses.push_back(temp);
    return true;
}

bool Registrar::addStudent(const string& student){
    for (const Student* studentCurr : students){
        if (student == studentCurr->getName()){
            cout << "student already in registrar";
            return false;
        }
    }
    Student* temp = new Student(student);
    students.push_back(temp);
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
    for (Course* courseCurr : courses){
            if (courseName == courseCurr->getName()){
                for (Student* studentCurr : students){
                        if (studentName == studentCurr->getName()){
                            return courseCurr->addStudent(studentCurr);
                        }
                    }
                cout << "student does not exist";
                return false;
            }
        }
    return false;
}

bool Registrar::cancelCourse(const string& courseName){
    for (size_t index = 0; index < courses.size(); index++){
        if(courses[index]->getName()==courseName){
            courses[index]->removeStudentsFromCourse();
            for (size_t remover = index; remover+ 1 <courses.size(); remover++){
                courses[remover] = courses[remover+1];
            }
            courses.pop_back();
            return true;
        }
    }
    return false;
}

void Registrar::purge(){
    for(const Course* coursesCurr : courses){
        delete coursesCurr;
    }
    for(const Student* studentCurr : students){
        delete studentCurr;
    }
    courses.clear();
    students.clear();
}
}