#include <iostream>
using namespace std;

class Temperature {
private:
    double celsius;

public:
    Temperature() : celsius(0.0) {}

    bool setCelsius(double value) {
        if (value < -273.15) {
            cout << "Invalid temperature: below absolute zero." << endl;
            return false;
        }
        celsius = value;
        return true;
    }

    double getCelsius() const {
        return celsius;
    }

    double getFahrenheit() const {
        return (celsius * 9.0 / 5.0) + 32.0;
    }

    double getKelvin() const {
        return celsius + 273.15;
    }
};

int main() {
    Temperature temp;

    temp.setCelsius(25.0);
    cout << "Celsius: " << temp.getCelsius() << endl;
    cout << "Fahrenheit: " << temp.getFahrenheit() << endl;
    cout << "Kelvin: " << temp.getKelvin() << endl;

    temp.setCelsius(-300.0);

    return 0;
}
