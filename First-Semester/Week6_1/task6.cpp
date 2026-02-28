#include <cmath>
#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point() : x(0), y(0) {}

    Point(int value) : x(value), y(value) {}

    Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    double distanceFromOrigin() const {
        return sqrt(static_cast<double>(x * x + y * y));
    }

    void displayCoordinates() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    Point p1;
    Point p2(5);
    Point p3(3, 4);

    cout << "Point p1: ";
    p1.displayCoordinates();
    cout << ", distance from origin: " << p1.distanceFromOrigin() << endl;

    cout << "Point p2: ";
    p2.displayCoordinates();
    cout << ", distance from origin: " << p2.distanceFromOrigin() << endl;

    cout << "Point p3: ";
    p3.displayCoordinates();
    cout << ", distance from origin: " << p3.distanceFromOrigin() << endl;

    return 0;
}
