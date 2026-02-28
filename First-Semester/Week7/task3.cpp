#include <cmath>
#include <iostream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    char grade;
};

struct Book {
    string title;
    string author;
    string ISBN;
    double price;
    int pages;
};

struct Point {
    double x;
    double y;
};

void printStudent(const Student& s) {
    cout << "Student ID: " << s.id << ", Name: " << s.name
         << ", Age: " << s.age << ", Grade: " << s.grade << endl;
}

Student createStudent(int id, string name, int age, char grade) {
    Student s;
    s.id = id;
    s.name = name;
    s.age = age;
    s.grade = grade;
    return s;
}

double calculateDistance(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    Student s1 = createStudent(101, "Alice", 20, 'A');
    printStudent(s1);

    Book b1 = {"C++ Primer", "Lippman", "978-0321714114", 59.99, 976};
    cout << "Book: " << b1.title << " by " << b1.author
         << ", ISBN: " << b1.ISBN << endl;

    Point p1 = {0.0, 0.0};
    Point p2 = {3.0, 4.0};
    cout << "Distance between points: " << calculateDistance(p1, p2) << endl;

    return 0;
}
