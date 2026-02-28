#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }

    string add(const string& a, const string& b) {
        return a + b;
    }
};

int main() {
    Calculator calc;

    cout << "add(int, int): " << calc.add(3, 4) << endl;
    cout << "add(double, double): " << calc.add(2.5, 4.1) << endl;
    cout << "add(int, int, int): " << calc.add(1, 2, 3) << endl;
    cout << "add(string, string): " << calc.add("Hello, ", "World!") << endl;

    return 0;
}
