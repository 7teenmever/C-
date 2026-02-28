#include "library.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
const std::string kDataFile = "First-Semester/FinalProject/students.txt";

void showMenu() {
    std::cout << "\n===== Student Management System =====" << std::endl;
    std::cout << "1. Add student" << std::endl;
    std::cout << "2. Display all students" << std::endl;
    std::cout << "3. Search student by ID or name" << std::endl;
    std::cout << "4. Update student record" << std::endl;
    std::cout << "5. Delete student record" << std::endl;
    std::cout << "6. Display statistics" << std::endl;
    std::cout << "7. Sort students" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

std::vector<double> readGradesFromUser() {
    int gradeCount = utils::readInt("Enter number of grades (1-20): ", 1, 20);
    std::vector<double> grades;
    grades.reserve(static_cast<std::size_t>(gradeCount));

    for (int i = 0; i < gradeCount; ++i) {
        double g = utils::readDouble("Grade " + std::to_string(i + 1) + " (0-100): ", 0.0, 100.0);
        grades.push_back(g);
    }

    return grades;
}

void addStudentFlow(StudentList& students) {
    std::string name;
    while (true) {
        name = utils::readNonEmptyLine("Enter student name: ");
        if (utils::isValidName(name)) {
            break;
        }
        std::cout << "Invalid name. Name must not be empty and must not contain commas." << std::endl;
    }

    int id = utils::readInt("Enter student ID (>0): ", 1, std::numeric_limits<int>::max());
    if (students.searchById(id) != nullptr) {
        std::cout << "A student with this ID already exists." << std::endl;
        return;
    }

    int age = utils::readInt("Enter age (3-120): ", 3, 120);
    std::vector<double> grades = readGradesFromUser();

    Student s;
    s.setName(name);
    s.setId(id);
    s.setAge(age);
    s.setGrades(grades.data(), grades.size());

    if (!students.addStudent(s)) {
        std::cout << "Failed to add student." << std::endl;
        return;
    }

    if (!students.saveToFile(kDataFile)) {
        std::cout << "Warning: student added, but failed to save file." << std::endl;
    }

    std::cout << "Student added successfully." << std::endl;
}

void searchFlow(StudentList& students) {
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }

    std::cout << "1. Search by ID" << std::endl;
    std::cout << "2. Search by name" << std::endl;
    int choice = utils::readInt("Select option: ", 1, 2);

    if (choice == 1) {
        int id = utils::readInt("Enter student ID: ", 1, std::numeric_limits<int>::max());
        Student* s = students.searchById(id);
        if (s == nullptr) {
            std::cout << "Student not found." << std::endl;
            return;
        }
        s->displayInfo();
    } else {
        std::string name = utils::readNonEmptyLine("Enter student name: ");
        Student* s = students.searchByName(name);
        if (s == nullptr) {
            std::cout << "Student not found." << std::endl;
            return;
        }
        s->displayInfo();
    }
}

void updateFlow(StudentList& students) {
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }

    int id = utils::readInt("Enter student ID to update: ", 1, std::numeric_limits<int>::max());
    Student* existing = students.searchById(id);

    if (existing == nullptr) {
        std::cout << "Student not found." << std::endl;
        return;
    }

    std::string newName;
    while (true) {
        newName = utils::readNonEmptyLine("Enter new name: ");
        if (utils::isValidName(newName)) {
            break;
        }
        std::cout << "Invalid name. Name must not be empty and must not contain commas." << std::endl;
    }

    int newAge = utils::readInt("Enter new age (3-120): ", 3, 120);
    std::vector<double> newGrades = readGradesFromUser();

    if (!students.updateStudent(id, newName, newAge, newGrades)) {
        std::cout << "Failed to update student." << std::endl;
        return;
    }

    if (!students.saveToFile(kDataFile)) {
        std::cout << "Warning: update successful, but failed to save file." << std::endl;
    }

    std::cout << "Student updated successfully." << std::endl;
}

void deleteFlow(StudentList& students) {
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }

    int id = utils::readInt("Enter student ID to delete: ", 1, std::numeric_limits<int>::max());
    if (!students.deleteStudent(id)) {
        std::cout << "Student not found." << std::endl;
        return;
    }

    if (!students.saveToFile(kDataFile)) {
        std::cout << "Warning: delete successful, but failed to save file." << std::endl;
    }

    std::cout << "Student deleted successfully." << std::endl;
}

void statsFlow(const StudentList& students) {
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total students: " << students.size() << std::endl;
    std::cout << "Average grade of all records: " << students.averageOfAllGrades() << std::endl;
    std::cout << "Highest grade: " << students.highestGradeOverall() << std::endl;
    std::cout << "Lowest grade: " << students.lowestGradeOverall() << std::endl;

    std::vector<Student> top = students.topStudents(3);
    if (!top.empty()) {
        std::cout << "Top students:" << std::endl;
        for (std::size_t i = 0; i < top.size(); ++i) {
            std::cout << i + 1 << ". " << top[i].getName() << " (ID: " << top[i].getId()
                      << ", Avg: " << top[i].averageGrade() << ")" << std::endl;
        }
    }
}

void sortFlow(StudentList& students) {
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }

    std::cout << "Sort options:" << std::endl;
    std::cout << "1. By ID (ascending)" << std::endl;
    std::cout << "2. By Name (alphabetical)" << std::endl;
    std::cout << "3. By Average Grade (descending)" << std::endl;

    int choice = utils::readInt("Select sort option: ", 1, 3);
    if (choice == 1) {
        students.sortByIdAscending();
    } else if (choice == 2) {
        students.sortByNameAlphabetical();
    } else {
        students.sortByAverageDescending();
    }

    if (!students.saveToFile(kDataFile)) {
        std::cout << "Warning: sorted in memory, but failed to save file." << std::endl;
    }

    std::cout << "Students sorted successfully." << std::endl;
}
}

int main() {
    StudentList students;

    {
        std::ifstream file(kDataFile);
        if (file.good()) {
            if (!students.loadFromFile(kDataFile)) {
                std::cout << "Warning: some lines could not be loaded from file." << std::endl;
            }
            std::cout << "Loaded " << students.size() << " student(s) from file." << std::endl;
        } else {
            std::cout << "No existing data file found. Starting with empty records." << std::endl;
        }
    }

    bool running = true;
    while (running) {
        showMenu();
        int option = utils::readInt("Choose option (1-8): ", 1, 8);

        switch (option) {
            case 1:
                addStudentFlow(students);
                break;
            case 2:
                students.displayAll();
                break;
            case 3:
                searchFlow(students);
                break;
            case 4:
                updateFlow(students);
                break;
            case 5:
                deleteFlow(students);
                break;
            case 6:
                statsFlow(students);
                break;
            case 7:
                sortFlow(students);
                break;
            case 8:
                running = false;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
                break;
        }
    }

    if (!students.saveToFile(kDataFile)) {
        std::cout << "Warning: failed to save on exit." << std::endl;
    }

    std::cout << "Exiting Student Management System." << std::endl;
    return 0;
}
