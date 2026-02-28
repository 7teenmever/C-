#include <iostream>
using namespace std;

class Shape {
public:
    virtual ~Shape() = default;

    virtual void draw() const {
        cout << "Drawing generic Shape" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    void draw() const override {
        cout << "Drawing Circle with radius " << radius << endl;
    }
};

void processShape(Shape s) { 
    s.draw();
}

void processShapeFixed(const Shape& s) {  
    s.draw();
}

int main() {
    Circle c(5);

    cout << "Sliced call:" << endl;
    processShape(c); 

    cout << "Fixed call:" << endl;
    processShapeFixed(c); 

    return 0;
}
