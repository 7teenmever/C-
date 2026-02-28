#include "Student.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
std::vector<std::string> splitByChar(const std::string& input, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        parts.push_back(token);
    }

    return parts;
}
}

void Student::copyFrom(const Student& other) {
    name = other.name;
    id = other.id;
    age = other.age;
    gradeCount = other.gradeCount;

    if (gradeCount == 0) {
        grades = nullptr;
        return;
    }

    grades = new double[gradeCount];
    for (std::size_t i = 0; i < gradeCount; ++i) {
        grades[i] = other.grades[i];
    }
}

Student::Student() : name(""), id(0), age(0), grades(nullptr), gradeCount(0) {}

Student::Student(const std::string& name, int id, int age, const double* grades, std::size_t count)
    : name(name), id(id), age(age), grades(nullptr), gradeCount(0) {
    setGrades(grades, count);
}

Student::Student(const Student& other) : name(""), id(0), age(0), grades(nullptr), gradeCount(0) {
    copyFrom(other);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] grades;
        grades = nullptr;
        gradeCount = 0;
        copyFrom(other);
    }
    return *this;
}

Student::Student(Student&& other) noexcept
    : name(std::move(other.name)),
      id(other.id),
      age(other.age),
      grades(other.grades),
      gradeCount(other.gradeCount) {
    other.grades = nullptr;
    other.gradeCount = 0;
    other.id = 0;
    other.age = 0;
}

Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        delete[] grades;

        name = std::move(other.name);
        id = other.id;
        age = other.age;
        grades = other.grades;
        gradeCount = other.gradeCount;

        other.grades = nullptr;
        other.gradeCount = 0;
        other.id = 0;
        other.age = 0;
    }
    return *this;
}

Student::~Student() {
    delete[] grades;
}

void Student::setName(const std::string& newName) {
    name = newName;
}

void Student::setId(int newId) {
    id = newId;
}

void Student::setAge(int newAge) {
    age = newAge;
}

void Student::setGrades(const double* newGrades, std::size_t count) {
    delete[] grades;
    grades = nullptr;
    gradeCount = 0;

    if (newGrades == nullptr || count == 0) {
        return;
    }

    grades = new double[count];
    gradeCount = count;

    for (std::size_t i = 0; i < count; ++i) {
        grades[i] = newGrades[i];
    }
}

void Student::setGradeAt(std::size_t index, double grade) {
    if (index < gradeCount) {
        grades[index] = grade;
    }
}

const std::string& Student::getName() const {
    return name;
}

int Student::getId() const {
    return id;
}

int Student::getAge() const {
    return age;
}

const double* Student::getGrades() const {
    return grades;
}

std::size_t Student::getGradeCount() const {
    return gradeCount;
}

double Student::averageGrade() const {
    if (gradeCount == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (std::size_t i = 0; i < gradeCount; ++i) {
        sum += grades[i];
    }

    return sum / static_cast<double>(gradeCount);
}

double Student::highestGrade() const {
    if (gradeCount == 0) {
        return 0.0;
    }

    double best = grades[0];
    for (std::size_t i = 1; i < gradeCount; ++i) {
        if (grades[i] > best) {
            best = grades[i];
        }
    }

    return best;
}

double Student::lowestGrade() const {
    if (gradeCount == 0) {
        return 0.0;
    }

    double low = grades[0];
    for (std::size_t i = 1; i < gradeCount; ++i) {
        if (grades[i] < low) {
            low = grades[i];
        }
    }

    return low;
}

void Student::displayInfo() const {
    std::cout << "ID: " << id << " | Name: " << name << " | Age: " << age << " | Avg: "
              << std::fixed << std::setprecision(2) << averageGrade() << " | Grades: ";

    for (std::size_t i = 0; i < gradeCount; ++i) {
        std::cout << grades[i];
        if (i + 1 < gradeCount) {
            std::cout << ";";
        }
    }

    std::cout << std::endl;
}

std::string Student::toCSV() const {
    std::ostringstream out;
    out << id << "," << name << "," << age << ",";

    for (std::size_t i = 0; i < gradeCount; ++i) {
        out << grades[i];
        if (i + 1 < gradeCount) {
            out << ";";
        }
    }

    return out.str();
}

bool Student::fromCSV(const std::string& line, Student& outStudent) {
    std::vector<std::string> fields = splitByChar(line, ',');
    if (fields.size() != 4) {
        return false;
    }

    try {
        int parsedId = std::stoi(fields[0]);
        std::string parsedName = fields[1];
        int parsedAge = std::stoi(fields[2]);

        std::vector<double> parsedGrades;
        if (!fields[3].empty()) {
            std::vector<std::string> gradeTokens = splitByChar(fields[3], ';');
            for (const std::string& token : gradeTokens) {
                if (!token.empty()) {
                    parsedGrades.push_back(std::stod(token));
                }
            }
        }

        Student tmp;
        tmp.setId(parsedId);
        tmp.setName(parsedName);
        tmp.setAge(parsedAge);
        if (!parsedGrades.empty()) {
            tmp.setGrades(parsedGrades.data(), parsedGrades.size());
        }

        outStudent = std::move(tmp);
        return true;
    } catch (...) {
        return false;
    }
}
