#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    static constexpr double PI = 3.14159265358979323846;
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * PI * radius;
    }

    void draw() const override {
        cout << "Drawing Circle (radius = " << radius << ")" << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void draw() const override {
        cout << "Drawing Rectangle (" << width << " x " << height << ")" << endl;
    }
};

class Triangle : public Shape {
private:
    double a;
    double b;
    double c;

public:
    Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {}

    double area() const override {
        double s = perimeter() / 2.0;
        double value = s * (s - a) * (s - b) * (s - c);
        if (value <= 0) {
            return 0.0;
        }
        return sqrt(value);
    }

    double perimeter() const override {
        return a + b + c;
    }

    void draw() const override {
        cout << "Drawing Triangle (sides = " << a << ", " << b << ", " << c << ")" << endl;
    }
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle(3.0));
    shapes.push_back(new Rectangle(4.0, 5.0));
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));

    for (Shape* shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->area() << endl;
        cout << "Perimeter: " << shape->perimeter() << endl;
        cout << endl;
    }

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
