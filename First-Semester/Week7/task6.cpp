#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    char grade;
};

void saveStudentsToFile(const Student students[], int count, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Could not open file for writing: " << filename << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        out << students[i].id << ","
            << students[i].name << ","
            << students[i].age << ","
            << students[i].grade << "\n";
    }
}

Student* loadStudentsFromFile(const string& filename, int& count) {
    ifstream in(filename);
    if (!in) {
        count = 0;
        return nullptr;
    }

    vector<Student> temp;
    string line;

    while (getline(in, line)) {
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

        Student s;
        s.id = stoi(idStr);
        s.name = name;
        s.age = stoi(ageStr);
        s.grade = gradeStr.empty() ? 'F' : gradeStr[0];
        temp.push_back(s);
    }

    count = static_cast<int>(temp.size());
    if (count == 0) {
        return nullptr;
    }

    Student* loaded = new Student[count];
    for (int i = 0; i < count; ++i) {
        loaded[i] = temp[i];
    }

    return loaded;
}

void appendStudentToFile(const Student& student, const string& filename) {
    ofstream out(filename, ios::app);
    if (!out) {
        cout << "Could not open file for append: " << filename << endl;
        return;
    }

    out << student.id << ","
        << student.name << ","
        << student.age << ","
        << student.grade << "\n";
}

int main() {
    string filename = "week7_students.csv";

    Student initial[3] = {
        {1, "Alice", 20, 'A'},
        {2, "Bob", 21, 'B'},
        {3, "Charlie", 19, 'A'}
    };

    saveStudentsToFile(initial, 3, filename);
    appendStudentToFile({4, "Diana", 22, 'A'}, filename);

    int count = 0;
    Student* loaded = loadStudentsFromFile(filename, count);

    cout << "Loaded students: " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << loaded[i].id << " | " << loaded[i].name << " | "
             << loaded[i].age << " | " << loaded[i].grade << endl;
    }

    delete[] loaded;
    return 0;
}
