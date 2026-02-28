#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    int employeeId;
    double salary;
    string department;

public:
    Employee() : name(""), employeeId(0), salary(0.0), department("Unassigned") {}

    bool setName(const string& newName) {
        if (newName.empty()) {
            cout << "Invalid name: cannot be empty." << endl;
            return false;
        }
        name = newName;
        return true;
    }

    bool setEmployeeId(int newEmployeeId) {
        if (newEmployeeId <= 0) {
            cout << "Invalid employee ID: must be positive." << endl;
            return false;
        }
        employeeId = newEmployeeId;
        return true;
    }

    bool setSalary(double newSalary) {
        if (newSalary < 0) {
            cout << "Invalid salary: cannot be negative." << endl;
            return false;
        }
        salary = newSalary;
        return true;
    }

    void setDepartment(const string& newDepartment) {
        department = newDepartment;
    }

    string getName() const {
        return name;
    }

    int getEmployeeId() const {
        return employeeId;
    }

    double getSalary() const {
        return salary;
    }

    string getDepartment() const {
        return department;
    }

    void giveRaise(double percentage) {
        if (percentage <= 0) {
            cout << "Raise percentage must be positive." << endl;
            return;
        }
        salary += salary * (percentage / 100.0);
    }

    void transferDepartment(const string& newDepartment) {
        department = newDepartment;
    }
};

int main() {
    Employee emp;

    emp.setName("");
    emp.setEmployeeId(-10);
    emp.setSalary(-5000.0);

    emp.setName("Alice Johnson");
    emp.setEmployeeId(101);
    emp.setSalary(5000.0);
    emp.setDepartment("Engineering");

    cout << "Before raise:" << endl;
    cout << "Name: " << emp.getName() << endl;
    cout << "ID: " << emp.getEmployeeId() << endl;
    cout << "Salary: " << emp.getSalary() << endl;
    cout << "Department: " << emp.getDepartment() << endl;

    emp.giveRaise(10.0);
    emp.transferDepartment("Product");

    cout << endl << "After raise and transfer:" << endl;
    cout << "Name: " << emp.getName() << endl;
    cout << "ID: " << emp.getEmployeeId() << endl;
    cout << "Salary: " << emp.getSalary() << endl;
    cout << "Department: " << emp.getDepartment() << endl;

    return 0;
}
