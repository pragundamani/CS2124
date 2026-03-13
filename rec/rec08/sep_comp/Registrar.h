#include "Student.h"
#include "Course.h"

#include <string>
#include <ostream>
#include <vector>

#ifndef registrar_h
#define registrar_h

namespace brooklynpoly{

class Registrar {
    friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
public:
    // This default constructor just initializes the two empty std::vectors.
    // " = default" means we are using the system provided constructor.
    // You don't have to implement anything for this function.
    Registrar() = default;

    // Creates a new course on the heap, if none with courseName
    // exists in Registrar's courses std::vector. Don't fail silently.
    bool addCourse(const std::string& courseName);

    // Creates a new student on the heap, if none with studentName
    // exists in Registrar's students std::vector. Don't fail silently.
    bool addStudent(const std::string&);

    // If a student with studentName and a course with courseName exist,
    // then enroll the student in the course. Note, don't fail silently.
    // Do not create any new Student or Course objects.
    bool enrollStudentInCourse(const std::string& studentName,
                               const std::string& courseName);

    // Unenroll the students from the course courseName and remove it
    // from the Registrar.
    bool cancelCourse(const std::string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    std::vector<Course*> courses;
    std::vector<Student*> students;
}; // Registrar

}
#endif