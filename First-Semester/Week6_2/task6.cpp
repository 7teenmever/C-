#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
private:
    string registrationNumber;

public:
    Vehicle(const string& regNo) : registrationNumber(regNo) {}
    virtual ~Vehicle() = default;

    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;

    virtual void refuel() {
        cout << "Vehicle " << registrationNumber << " is being refueled with fuel." << endl;
    }

    string getRegistrationNumber() const {
        return registrationNumber;
    }
};

class Car : public Vehicle {
public:
    Car(const string& regNo) : Vehicle(regNo) {}

    void startEngine() override {
        cout << "Car " << getRegistrationNumber() << ": Engine started." << endl;
    }

    void stopEngine() override {
        cout << "Car " << getRegistrationNumber() << ": Engine stopped." << endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(const string& regNo) : Vehicle(regNo) {}

    void startEngine() override {
        cout << "Motorcycle " << getRegistrationNumber() << ": Engine started." << endl;
    }

    void stopEngine() override {
        cout << "Motorcycle " << getRegistrationNumber() << ": Engine stopped." << endl;
    }
};

class ElectricCar : public Vehicle {
public:
    ElectricCar(const string& regNo) : Vehicle(regNo) {}

    void startEngine() override {
        cout << "Electric car " << getRegistrationNumber() << ": Power system activated." << endl;
    }

    void stopEngine() override {
        cout << "Electric car " << getRegistrationNumber() << ": Power system deactivated." << endl;
    }

    void refuel() override {
        cout << "Electric car " << getRegistrationNumber() << " is charging the battery." << endl;
    }
};

int main() {
    // Vehicle v("AB-001"); // Error: cannot instantiate abstract class.

    vector<Vehicle*> vehicles;
    vehicles.push_back(new Car("CAR-101"));
    vehicles.push_back(new Motorcycle("MOTO-202"));
    vehicles.push_back(new ElectricCar("EV-303"));

    for (Vehicle* vehicle : vehicles) {
        vehicle->startEngine();
        vehicle->refuel();
        vehicle->stopEngine();
        cout << endl;
    }

    for (Vehicle* vehicle : vehicles) {
        delete vehicle;
    }

    return 0;
}
