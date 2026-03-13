#include "Course.h"
#include "Student.h"

#include <ostream>
#include <vector>
namespace brooklynpoly{

Course::Course(const std::string& courseName) : name(courseName){}

const std::string& Course::getName() const{
    return name;
}

std::ostream& operator<<(std::ostream& os, const Course& rhs){
    os << rhs.getName();
    if (rhs.students.size()== 0){
        os << "No students";
    }
    else{
        for(const Student* studentName : rhs.students){
            os << studentName->getName();
        }
    }
    return os;
}

bool Course::addStudent(Student* studPoint){
    for (const Student* courseStudents : students){
        if (courseStudents == studPoint){
            return false;
        }
    }
    students.push_back(studPoint);
    return studPoint->addCourse(this);

}

void Course::removeStudentsFromCourse(){
    for (Student* courseStudents : students){
        courseStudents->removedFromCourse(this);
    }
    students.clear();
}
}