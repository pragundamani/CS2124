/*
Pragun Damani pd2752
  rec05.cpp
  spring 2026
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section;

class LabWorker {
public:
    friend ostream& operator<<(ostream& os, const LabWorker& worker);
    LabWorker(const string& name);
    void addSection(Section& sec);
    void addGrade(const string& studentName, int grade, int week);

private:
    string name;
    Section* section;
};

class Section {
private:
    class TimeSlot {
    public:
        friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot);
        TimeSlot(const string& day, int hour);
        
    private:
        string day;
        int hour;
    };
    
    class StudentRecord {
    public:
        friend ostream& operator<<(ostream& os, const StudentRecord& student);
        StudentRecord(const string& name);
        void addGrade(int grade, int week);
        const string& getName() const;
        ~StudentRecord() { cout << "Deleting " << name << endl; }
        StudentRecord(const StudentRecord& old) : name(old.name), grades(old.grades) {}

    private:
        string name;
        vector<int> grades;
    };

    friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot);
    friend ostream& operator<<(ostream& os, const StudentRecord& student);
    
    string sectionName;
    TimeSlot timeSlot;
    vector<StudentRecord*> students;

public:
    friend ostream& operator<<(ostream& os, const Section& section);
    Section(const string& sectionName, const string& day, int hour);
    void addStudent(const string& studentName);
    void addGrade(const string& studentName, int grade, int week);
    ~Section() {
        cout << "Section " << sectionName << " is being deleted" << endl;
        for (size_t i = 0; i < students.size(); ++i) {
            delete students[i];
        }
    }
    Section(const Section& old) : sectionName(old.sectionName), timeSlot(old.timeSlot) {
        for (size_t i = 0; i < old.students.size(); ++i) {
            students.push_back(new StudentRecord(*old.students[i]));
        }
    }
};


LabWorker::LabWorker(const string& name) : name(name), section(nullptr) {}

void LabWorker::addSection(Section& sec) {
    section = &sec;
}

void LabWorker::addGrade(const string& studentName, int grade, int week) {
    if (section != nullptr) {
        section->addGrade(studentName, grade, week);
    }
}

Section::Section(const string& sectionName, const string& day, int hour)
    : sectionName(sectionName), timeSlot(day, hour) {}

void Section::addStudent(const string& studentName) {
    students.push_back(new StudentRecord(studentName));
}

void Section::addGrade(const string& studentName, int grade, int week) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == studentName) {
            students[i]->addGrade(grade, week);
            return;
        }
    }
}

Section::TimeSlot::TimeSlot(const string& day, int hour)
    : day(day), hour(hour) {}

Section::StudentRecord::StudentRecord(const string& name) 
    : name(name), grades(14, -1) {}

void Section::StudentRecord::addGrade(int grade, int week) {
    if (week >= 1 && week <= 14) {
        grades[week - 1] = grade;
    }
}

const string& Section::StudentRecord::getName() const {
    return name;
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main

ostream& operator<<(ostream& os, const LabWorker& worker) {
    os << worker.name;
    if (worker.section != nullptr) {
        os << " has " << *worker.section;
    } else {
        os << " does not have a section\n";
    }
    return os;
}

ostream& operator<<(ostream& os, const Section& section) {
    os << "Section: " << section.sectionName << ", " << section.timeSlot
       << ", Students:";
    if (section.students.size() == 0) {
        os << " None\n";
    } else {
        os << "\n";
        for (size_t i = 0; i < section.students.size(); ++i) {
            os << *section.students[i] << "\n";
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot) {
    os << "Time slot: [Day: " << timeSlot.day << ", Start time: ";
    if (timeSlot.hour < 12) {
        os << timeSlot.hour << "am]";
    } else if (timeSlot.hour == 12) {
        os << "12pm]";
    } else {
        os << (timeSlot.hour - 12) << "pm]";
    }
    return os;
}

ostream& operator<<(ostream& os, const Section::StudentRecord& student) {
    os << "Name: " << student.name << ", Grades: ";
    for (size_t i = 0; i < student.grades.size(); ++i) {
        os << student.grades[i] << " ";
    }
    return os;
}
