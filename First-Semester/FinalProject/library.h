#ifndef LIBRARY_H
#define LIBRARY_H

#include "Student.h"

#include <cstddef>
#include <string>
#include <vector>

namespace utils {
std::string trim(const std::string& s);
std::string toLower(const std::string& s);
bool isValidName(const std::string& name);
bool isValidId(int id);
bool isValidAge(int age);
bool isValidGrade(double grade);
double calculateAverage(const double* grades, std::size_t count);

int readInt(const std::string& prompt, int minValue, int maxValue);
double readDouble(const std::string& prompt, double minValue, double maxValue);
std::string readNonEmptyLine(const std::string& prompt);
bool askYesNo(const std::string& prompt);
}

class StudentList {
private:
    struct Node {
        Student student;
        Node* next;

        explicit Node(const Student& s) : student(s), next(nullptr) {}
    };

    Node* head;
    std::size_t studentCount;

    Node* findNodeById(int id);
    const Node* findNodeById(int id) const;
    void clear();

public:
    StudentList();
    ~StudentList();

    StudentList(const StudentList&) = delete;
    StudentList& operator=(const StudentList&) = delete;

    bool addStudent(const Student& student);
    bool deleteStudent(int id);

    Student* searchById(int id);
    const Student* searchById(int id) const;

    Student* searchByName(const std::string& name);
    const Student* searchByName(const std::string& name) const;

    bool updateStudent(int id, const std::string& newName, int newAge, const std::vector<double>& newGrades);

    void displayAll() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    void sortByIdAscending();
    void sortByNameAlphabetical();
    void sortByAverageDescending();

    std::size_t size() const;
    bool empty() const;

    double averageOfAllGrades() const;
    double highestGradeOverall() const;
    double lowestGradeOverall() const;
    std::vector<Student> topStudents(std::size_t n) const;
};

#endif
