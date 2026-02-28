#ifndef STUDENT_H
#define STUDENT_H

#include <cstddef>
#include <string>

class Student {
private:
    std::string name;
    int id;
    int age;
    double* grades;
    std::size_t gradeCount;

    void copyFrom(const Student& other);

public:
    Student();
    Student(const std::string& name, int id, int age, const double* grades, std::size_t count);
    Student(const Student& other);
    Student& operator=(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;
    ~Student();

    void setName(const std::string& newName);
    void setId(int newId);
    void setAge(int newAge);
    void setGrades(const double* newGrades, std::size_t count);
    void setGradeAt(std::size_t index, double grade);

    const std::string& getName() const;
    int getId() const;
    int getAge() const;
    const double* getGrades() const;
    std::size_t getGradeCount() const;

    double averageGrade() const;
    double highestGrade() const;
    double lowestGrade() const;

    void displayInfo() const;

    std::string toCSV() const;
    static bool fromCSV(const std::string& line, Student& outStudent);
};

#endif
