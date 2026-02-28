#include <iostream>
using namespace std;

class Base {
public:
    void show() {
        cout << "Base" << endl;
    }
};

class Derived : public Base {
public:
    void show() {
        cout << "Derived" << endl;
    }
};

class FixedBase {
public:
    virtual ~FixedBase() = default;

    virtual void show() {
        cout << "Base" << endl;
    }
};

class FixedDerived : public FixedBase {
public:
    void show() override {
        cout << "Derived" << endl;
    }
};

int main() {
    cout << "Buggy version (missing virtual):" << endl;
    Base* ptr1 = new Derived();
    ptr1->show();  
    delete ptr1;

    cout << endl;
    cout << "Fixed version (with virtual):" << endl;
    FixedBase* ptr2 = new FixedDerived();
    ptr2->show();  
    delete ptr2;

    return 0;
}
