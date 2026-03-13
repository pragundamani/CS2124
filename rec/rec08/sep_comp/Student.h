#include <string>
#include <ostream>
#include <vector>

#ifndef student_h
#define student_h

namespace brooklynpoly{
class Course;

class Student {
    friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const std::string& name);
    const std::string& getName() const;
    // Adding the course to the student's std::vector of courses.
    // Make sure this student is not already in that course.
    // (Don't fail silently.)
    // This method would be called from Registrar::enrollStudentInCourse.
    bool addCourse(Course*);

    // Removes the Course from the student's std::vector of Courses.
    // Needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    std::string name;
    std::vector<Course*> courses;

}; // Student class

}
#endif
