/*
  Pragun Damani
  rec08_single_simple.cpp
  spring 2026
 */

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class Student; // forward declaration

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName) : name(courseName){}
    const string& getName() const {
        return name;
    }

    // Adding the student to this course's vector of students.
    // Make sure the student is not already in this course.
    // (Don't fail silently.)
    // This would be called from Registrar::enrollStudentInCourse.
    bool addStudent(Student*);

    // Tell all the students in this course that they are no longer in it.
    // This would be called from Registrar::cancelCourse.
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
}; // Course class

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name) : name(name) {};
    const string& getName() const{
        return name;
    }

    // Adding the course to the student's vector of courses.
    // Make sure this student is not already in that course.
    // (Don't fail silently.)
    // This method would be called from Registrar::enrollStudentInCourse.
    bool addCourse(Course*);

    // Removes the Course from the student's vector of Courses.
    // Needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;

}; // Student class

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    // This default constructor just initializes the two empty vectors.
    // " = default" means we are using the system provided constructor.
    // You don't have to implement anything for this function.
    Registrar() = default;

    // Creates a new course on the heap, if none with courseName
    // exists in Registrar's courses vector. Don't fail silently.
    bool addCourse(const string& courseName);

    // Creates a new student on the heap, if none with studentName
    // exists in Registrar's students vector. Don't fail silently.
    bool addStudent(const string&);

    // If a student with studentName and a course with courseName exist,
    // then enroll the student in the course. Note, don't fail silently.
    // Do not create any new Student or Course objects.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course courseName and remove it
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string& courseName) const{
        for (size_t index = 0; index < courses.size(); index++){
            if(courses[index]->getName()==courseName){
                return index;
            }
        }
        return courses.size();
    };

    size_t findCourse(const string& studName) const {
        for (size_t index = 0; index < students.size(); index++){
            if(students[index]->getName()==studName){
                return index;
            }
        }
        return students.size();
    };

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

ostream& operator<<(ostream& os, const Course& rhs){
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

bool Course::addStudent(Student* studPoint){
    for (const Student* courseStudents : students){
        if (courseStudents == studPoint){
            cout << "student already in course ";
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

bool Student::addCourse(Course* courseName){
    for (const Course* courseCurr : courses){
        if (courseName == courseCurr){
            cout << "student already in course ";
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
