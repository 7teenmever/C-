#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;
    double price;

public:
    Book() : title("Unknown"), author("Unknown"), pages(0), price(0.0) {}

    Book(const string& bookTitle, const string& bookAuthor)
        : title(bookTitle), author(bookAuthor), pages(0), price(0.0) {}

    Book(const string& bookTitle, const string& bookAuthor, int bookPages, double bookPrice)
        : title(bookTitle), author(bookAuthor), pages(bookPages), price(bookPrice) {}

    void displayInfo() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "Price: $" << price << endl;
    }
};

int main() {
    Book book1;
    Book book2("C++ Programming", "John Doe");
    Book book3("Data Structures", "Jane Smith", 300, 45.99);

    cout << "Book 1:" << endl;
    book1.displayInfo();
    cout << endl;

    cout << "Book 2:" << endl;
    book2.displayInfo();
    cout << endl;

    cout << "Book 3:" << endl;
    book3.displayInfo();

    return 0;
}
