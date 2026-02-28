#include "library.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {
std::string gradesToString(const Student& student) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(1);

    const double* grades = student.getGrades();
    std::size_t count = student.getGradeCount();

    for (std::size_t i = 0; i < count; ++i) {
        out << grades[i];
        if (i + 1 < count) {
            out << ";";
        }
    }

    return out.str();
}
}

namespace utils {
std::string trim(const std::string& s) {
    std::size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    std::size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }

    return s.substr(start, end - start);
}

std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

bool isValidName(const std::string& name) {
    std::string t = trim(name);
    if (t.empty()) {
        return false;
    }

    return t.find(',') == std::string::npos;
}

bool isValidId(int id) {
    return id > 0;
}

bool isValidAge(int age) {
    return age >= 3 && age <= 120;
}

bool isValidGrade(double grade) {
    return grade >= 0.0 && grade <= 100.0;
}

double calculateAverage(const double* grades, std::size_t count) {
    if (grades == nullptr || count == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        sum += grades[i];
    }

    return sum / static_cast<double>(count);
}

int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return minValue;
        }

        line = trim(line);

        try {
            std::size_t used = 0;
            long long value = std::stoll(line, &used);

            if (used != line.size()) {
                throw std::invalid_argument("Trailing chars");
            }

            if (value < minValue || value > maxValue) {
                std::cout << "Value must be between " << minValue << " and " << maxValue << "." << std::endl;
                continue;
            }

            return static_cast<int>(value);
        } catch (...) {
            std::cout << "Invalid integer input." << std::endl;
        }
    }
}

double readDouble(const std::string& prompt, double minValue, double maxValue) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return minValue;
        }

        line = trim(line);

        try {
            std::size_t used = 0;
            double value = std::stod(line, &used);

            if (used != line.size()) {
                throw std::invalid_argument("Trailing chars");
            }

            if (value < minValue || value > maxValue) {
                std::cout << "Value must be between " << minValue << " and " << maxValue << "." << std::endl;
                continue;
            }

            return value;
        } catch (...) {
            std::cout << "Invalid numeric input." << std::endl;
        }
    }
}

std::string readNonEmptyLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return "";
        }

        line = trim(line);
        if (!line.empty()) {
            return line;
        }

        std::cout << "Input cannot be empty." << std::endl;
    }
}

bool askYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            return false;
        }

        line = toLower(trim(line));
        if (line == "y" || line == "yes") {
            return true;
        }
        if (line == "n" || line == "no") {
            return false;
        }

        std::cout << "Please enter y or n." << std::endl;
    }
}
}

StudentList::StudentList() : head(nullptr), studentCount(0) {}

StudentList::~StudentList() {
    clear();
}

StudentList::Node* StudentList::findNodeById(int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->student.getId() == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

const StudentList::Node* StudentList::findNodeById(int id) const {
    const Node* current = head;
    while (current != nullptr) {
        if (current->student.getId() == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void StudentList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    studentCount = 0;
}

bool StudentList::addStudent(const Student& student) {
    if (findNodeById(student.getId()) != nullptr) {
        return false;
    }

    Node* newNode = new Node(student);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    ++studentCount;
    return true;
}

bool StudentList::deleteStudent(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->student.getId() == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        --studentCount;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->student.getId() != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    --studentCount;
    return true;
}

Student* StudentList::searchById(int id) {
    Node* node = findNodeById(id);
    if (node == nullptr) {
        return nullptr;
    }
    return &node->student;
}

const Student* StudentList::searchById(int id) const {
    const Node* node = findNodeById(id);
    if (node == nullptr) {
        return nullptr;
    }
    return &node->student;
}

Student* StudentList::searchByName(const std::string& name) {
    std::string target = utils::toLower(utils::trim(name));

    Node* current = head;
    while (current != nullptr) {
        if (utils::toLower(current->student.getName()) == target) {
            return &current->student;
        }
        current = current->next;
    }

    return nullptr;
}

const Student* StudentList::searchByName(const std::string& name) const {
    std::string target = utils::toLower(utils::trim(name));

    const Node* current = head;
    while (current != nullptr) {
        if (utils::toLower(current->student.getName()) == target) {
            return &current->student;
        }
        current = current->next;
    }

    return nullptr;
}

bool StudentList::updateStudent(int id, const std::string& newName, int newAge, const std::vector<double>& newGrades) {
    Node* node = findNodeById(id);
    if (node == nullptr) {
        return false;
    }

    node->student.setName(newName);
    node->student.setAge(newAge);

    if (!newGrades.empty()) {
        node->student.setGrades(newGrades.data(), newGrades.size());
    } else {
        node->student.setGrades(nullptr, 0);
    }

    return true;
}

void StudentList::displayAll() const {
    if (head == nullptr) {
        std::cout << "No students found." << std::endl;
        return;
    }

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(24) << "Name"
              << std::setw(8) << "Age"
              << std::setw(10) << "Average"
              << "Grades" << std::endl;

    std::cout << std::string(70, '-') << std::endl;

    const Node* current = head;
    while (current != nullptr) {
        const Student& s = current->student;
        std::cout << std::left
                  << std::setw(8) << s.getId()
                  << std::setw(24) << s.getName()
                  << std::setw(8) << s.getAge()
                  << std::setw(10) << std::fixed << std::setprecision(2) << s.averageGrade()
                  << gradesToString(s)
                  << std::endl;

        current = current->next;
    }
}

bool StudentList::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false;
    }

    clear();

    bool allGood = true;
    std::string line;
    while (std::getline(in, line)) {
        line = utils::trim(line);
        if (line.empty()) {
            continue;
        }

        Student student;
        if (!Student::fromCSV(line, student)) {
            allGood = false;
            continue;
        }

        if (!addStudent(student)) {
            allGood = false;
        }
    }

    return allGood;
}

bool StudentList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }

    const Node* current = head;
    while (current != nullptr) {
        out << current->student.toCSV() << "\n";
        current = current->next;
    }

    return true;
}

void StudentList::sortByIdAscending() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* current = head;

        while (current->next != nullptr) {
            if (current->student.getId() > current->next->student.getId()) {
                std::swap(current->student, current->next->student);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void StudentList::sortByNameAlphabetical() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* current = head;

        while (current->next != nullptr) {
            std::string left = utils::toLower(current->student.getName());
            std::string right = utils::toLower(current->next->student.getName());

            if (left > right) {
                std::swap(current->student, current->next->student);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void StudentList::sortByAverageDescending() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* current = head;

        while (current->next != nullptr) {
            if (current->student.averageGrade() < current->next->student.averageGrade()) {
                std::swap(current->student, current->next->student);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

std::size_t StudentList::size() const {
    return studentCount;
}

bool StudentList::empty() const {
    return studentCount == 0;
}

double StudentList::averageOfAllGrades() const {
    double sum = 0.0;
    std::size_t gradeTotal = 0;

    const Node* current = head;
    while (current != nullptr) {
        const double* grades = current->student.getGrades();
        std::size_t count = current->student.getGradeCount();

        for (std::size_t i = 0; i < count; ++i) {
            sum += grades[i];
            ++gradeTotal;
        }

        current = current->next;
    }

    if (gradeTotal == 0) {
        return 0.0;
    }

    return sum / static_cast<double>(gradeTotal);
}

double StudentList::highestGradeOverall() const {
    if (head == nullptr) {
        return 0.0;
    }

    bool found = false;
    double best = 0.0;

    const Node* current = head;
    while (current != nullptr) {
        const double* grades = current->student.getGrades();
        std::size_t count = current->student.getGradeCount();

        for (std::size_t i = 0; i < count; ++i) {
            if (!found || grades[i] > best) {
                best = grades[i];
                found = true;
            }
        }

        current = current->next;
    }

    return found ? best : 0.0;
}

double StudentList::lowestGradeOverall() const {
    if (head == nullptr) {
        return 0.0;
    }

    bool found = false;
    double low = 0.0;

    const Node* current = head;
    while (current != nullptr) {
        const double* grades = current->student.getGrades();
        std::size_t count = current->student.getGradeCount();

        for (std::size_t i = 0; i < count; ++i) {
            if (!found || grades[i] < low) {
                low = grades[i];
                found = true;
            }
        }

        current = current->next;
    }

    return found ? low : 0.0;
}

std::vector<Student> StudentList::topStudents(std::size_t n) const {
    std::vector<Student> result;
    result.reserve(studentCount);

    const Node* current = head;
    while (current != nullptr) {
        result.push_back(current->student);
        current = current->next;
    }

    std::sort(result.begin(), result.end(), [](const Student& a, const Student& b) {
        return a.averageGrade() > b.averageGrade();
    });

    if (result.size() > n) {
        result.resize(n);
    }

    return result;
}
