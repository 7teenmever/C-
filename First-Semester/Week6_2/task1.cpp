#include <iostream>
#include <string>
using namespace std;

class Animal {
private:
    string name;
    int age;

public:
    Animal(const string& animalName, int animalAge) : name(animalName), age(animalAge) {}

    virtual ~Animal() = default;

    void eat() const {
        cout << name << " is eating." << endl;
    }

    void sleep() const {
        cout << name << " is sleeping." << endl;
    }

    virtual void makeSound() const {
        cout << name << " makes a generic animal sound." << endl;
    }

    void showInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Dog : public Animal {
public:
    Dog(const string& name, int age) : Animal(name, age) {}

    void makeSound() const override {
        cout << "Dog says: Woof!" << endl;
    }

    void fetch() const {
        cout << "Dog is fetching the ball." << endl;
    }
};

class Cat : public Animal {
public:
    Cat(const string& name, int age) : Animal(name, age) {}

    void makeSound() const override {
        cout << "Cat says: Meow!" << endl;
    }

    void climb() const {
        cout << "Cat is climbing a tree." << endl;
    }
};

class Bird : public Animal {
public:
    Bird(const string& name, int age) : Animal(name, age) {}

    void makeSound() const override {
        cout << "Bird says: Chirp!" << endl;
    }

    void fly() const {
        cout << "Bird is flying in the sky." << endl;
    }
};

int main() {
    Dog dog("Buddy", 3);
    Cat cat("Misty", 2);
    Bird bird("Sky", 1);

    dog.showInfo();
    dog.eat();
    dog.makeSound();
    dog.fetch();
    cout << endl;

    cat.showInfo();
    cat.sleep();
    cat.makeSound();
    cat.climb();
    cout << endl;

    bird.showInfo();
    bird.eat();
    bird.makeSound();
    bird.fly();

    return 0;
}
