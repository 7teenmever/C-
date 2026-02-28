#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    char grade;
};

struct StudentManager {
    Student students[100];
    int studentCount;
    const string filename = "students.txt";

    StudentManager() : studentCount(0) {}

    void addStudent() {
        if (studentCount >= 100) {
            cout << "Student list is full." << endl;
            return;
        }

        Student s;
        cout << "Enter ID: ";
        cin >> s.id;
        cin.ignore();

        cout << "Enter name: ";
        getline(cin, s.name);

        cout << "Enter age: ";
        cin >> s.age;

        cout << "Enter grade: ";
        cin >> s.grade;

        students[studentCount++] = s;
    }

    void addStudent(const Student& s) {
        if (studentCount >= 100) {
            cout << "Student list is full." << endl;
            return;
        }
        students[studentCount++] = s;
    }

    void displayAllStudents() {
        if (studentCount == 0) {
            cout << "No students available." << endl;
            return;
        }

        for (int i = 0; i < studentCount; ++i) {
            cout << students[i].id << " | " << students[i].name
                 << " | Age: " << students[i].age
                 << " | Grade: " << students[i].grade << endl;
        }
    }

    void searchStudent(int id) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                cout << "Found: " << students[i].name << ", Grade " << students[i].grade << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void saveToFile() {
        ofstream out(filename);
        if (!out) {
            cout << "Could not save to file." << endl;
            return;
        }

        for (int i = 0; i < studentCount; ++i) {
            out << students[i].id << ","
                << students[i].name << ","
                << students[i].age << ","
                << students[i].grade << "\n";
        }
    }

    void loadFromFile() {
        ifstream in(filename);
        if (!in) {
            cout << "No saved file found." << endl;
            return;
        }

        studentCount = 0;
        string line;
        while (getline(in, line) && studentCount < 100) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string idStr;
            string name;
            string ageStr;
            string gradeStr;

            if (!getline(ss, idStr, ',')) {
                continue;
            }
            if (!getline(ss, name, ',')) {
                continue;
            }
            if (!getline(ss, ageStr, ',')) {
                continue;
            }
            if (!getline(ss, gradeStr)) {
                continue;
            }

            students[studentCount].id = stoi(idStr);
            students[studentCount].name = name;
            students[studentCount].age = stoi(ageStr);
            students[studentCount].grade = gradeStr.empty() ? 'F' : gradeStr[0];
            ++studentCount;
        }
    }

    void updateStudentGrade(int id, char newGrade) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                students[i].grade = newGrade;
                cout << "Grade updated for " << students[i].name << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }
};

int main() {
    StudentManager manager;

    manager.addStudent({1, "Alice", 20, 'A'});
    manager.addStudent({2, "Bob", 21, 'B'});
    manager.addStudent({3, "Charlie", 22, 'C'});

    cout << "Initial list:" << endl;
    manager.displayAllStudents();

    cout << "\nSearch ID 2:" << endl;
    manager.searchStudent(2);

    cout << "\nUpdating grade for ID 3 to A" << endl;
    manager.updateStudentGrade(3, 'A');

    cout << "\nAfter update:" << endl;
    manager.displayAllStudents();

    manager.saveToFile();

    StudentManager loaded;
    loaded.loadFromFile();
    cout << "\nLoaded from file:" << endl;
    loaded.displayAllStudents();

    return 0;
}
