#include <cstring>
#include <iostream>
using namespace std;

#define USE_VIRTUAL_DESTRUCTOR 1

class Employee {
protected:
    char* name;

public:
    Employee(const char* employeeName) {
        size_t len = strlen(employeeName);
        name = new char[len + 1];
        strcpy(name, employeeName);
    }

#if USE_VIRTUAL_DESTRUCTOR
    virtual
#endif
    ~Employee() {
        cout << "Employee destructor called for: " << name << endl;
        delete[] name;
    }
};

class Manager : public Employee {
private:
    char* department;

public:
    Manager(const char* managerName, const char* dept) : Employee(managerName) {
        size_t len = strlen(dept);
        department = new char[len + 1];
        strcpy(department, dept);
    }

    ~Manager() {
        cout << "Manager destructor called for department: " << department << endl;
        delete[] department;
    }
};

int main() {
    Employee* e = new Manager("Alice", "Engineering");
    delete e;

    cout << endl;
    cout << "Set USE_VIRTUAL_DESTRUCTOR to 0 to see the issue:" << endl;
    cout << "Only Employee destructor runs, Manager resources leak." << endl;

    return 0;
}
