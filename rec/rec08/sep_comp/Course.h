#include <string>
#include <ostream>
#include <vector>

#ifndef Course_cpp
#define Course_cpp

namespace brooklynpoly { 

class Student;

class Course {
    friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const std::string& courseName);
    const std::string& getName() const;

    // Adding the student to this course's vector of students.
    // Make sure the student is not already in this course.
    // (Don't fail silently.)
    // This would be called from Registrar::enrollStudentInCourse.
    bool addStudent(Student*);

    // Tell all the students in this course that they are no longer in it.
    // This would be called from Registrar::cancelCourse.
    void removeStudentsFromCourse();

private:
    std::string name;
    std::vector<Student*> students;
}; // Course class

}
#endif