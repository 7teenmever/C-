#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

static inline void hashCombine(size_t& seed, size_t value) {
    seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class Person {
public:
    string firstName;
    string lastName;
    int age;

    Person(string fn, string ln, int a) : firstName(std::move(fn)), lastName(std::move(ln)), age(a) {}

    struct Hash {
        size_t operator()(const Person& p) const {
            size_t seed = 0;
            hashCombine(seed, hash<string>{}(p.firstName));
            hashCombine(seed, hash<string>{}(p.lastName));
            hashCombine(seed, hash<int>{}(p.age));
            return seed;
        }
    };

    bool operator==(const Person& other) const {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               age == other.age;
    }
};

class Point {
public:
    int x;
    int y;

    Point(int xVal, int yVal) : x(xVal), y(yVal) {}

    struct Hash {
        size_t operator()(const Point& p) const {
            size_t seed = 0;
            hashCombine(seed, hash<int>{}(p.x));
            hashCombine(seed, hash<int>{}(p.y));
            return seed;
        }
    };

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

int main() {
    unordered_set<Person, Person::Hash> people;
    people.insert(Person("John", "Doe", 25));
    people.insert(Person("Jane", "Doe", 30));
    people.insert(Person("John", "Doe", 25));  // duplicate

    cout << "Unique people count: " << people.size() << endl;

    unordered_map<Point, string, Point::Hash> pointLabels;
    pointLabels[Point(1, 2)] = "A";
    pointLabels[Point(3, 4)] = "B";
    pointLabels[Point(1, 2)] = "A-Updated";

    cout << "Point(1,2) label: " << pointLabels[Point(1, 2)] << endl;
    cout << "Point(3,4) label: " << pointLabels[Point(3, 4)] << endl;

    return 0;
}
