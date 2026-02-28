#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    char grade;

public:
    void setName(const string& studentName) {
        name = studentName;
    }

    void setAge(int studentAge) {
        age = studentAge;
    }

    void setGrade(char studentGrade) {
        grade = studentGrade;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    char getGrade() const {
        return grade;
    }

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Grade: " << grade << endl;
    }
};

int main() {
    Student student1;

    student1.setName("Alice");
    student1.setAge(20);
    student1.setGrade('A');

    student1.displayInfo();

    return 0;
}
