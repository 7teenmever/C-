#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    bool isAvailable;

public:
    Book() : isbn(""), title(""), author(""), isAvailable(true) {}

    Book(const string& bookIsbn, const string& bookTitle, const string& bookAuthor)
        : isbn(bookIsbn), title(bookTitle), author(bookAuthor), isAvailable(true) {}

    string getIsbn() const {
        return isbn;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool getIsAvailable() const {
        return isAvailable;
    }

    bool borrowBook() {
        if (!isAvailable) {
            return false;
        }
        isAvailable = false;
        return true;
    }

    bool returnBook() {
        if (isAvailable) {
            return false;
        }
        isAvailable = true;
        return true;
    }

    void displayStatus() const {
        cout << "ISBN: " << isbn
             << ", Title: " << title
             << ", Author: " << author
             << ", Status: " << (isAvailable ? "Available" : "Borrowed")
             << endl;
    }
};

class Library {
private:
    Book* books;
    int capacity;
    int count;

public:
    Library(int maxBooks) : capacity(maxBooks), count(0) {
        if (capacity <= 0) {
            capacity = 1;
        }
        books = new Book[capacity];
    }

    ~Library() {
        delete[] books;
    }

    bool addBook(const Book& book) {
        if (count >= capacity) {
            cout << "Library is full. Cannot add more books." << endl;
            return false;
        }
        books[count] = book;
        ++count;
        return true;
    }

    Book* findBookByISBN(const string& isbn) {
        for (int i = 0; i < count; ++i) {
            if (books[i].getIsbn() == isbn) {
                return &books[i];
            }
        }
        return nullptr;
    }

    void displayAllBooks() const {
        if (count == 0) {
            cout << "No books in library." << endl;
            return;
        }
        for (int i = 0; i < count; ++i) {
            books[i].displayStatus();
        }
    }
};

int main() {
    Library library(5);

    library.addBook(Book("978-1", "C++ Basics", "Author A"));
    library.addBook(Book("978-2", "Data Structures", "Author B"));
    library.addBook(Book("978-3", "Algorithms", "Author C"));

    cout << "Initial library status:" << endl;
    library.displayAllBooks();

    Book* book = library.findBookByISBN("978-2");
    if (book != nullptr && book->borrowBook()) {
        cout << endl << "Borrowed book: " << book->getTitle() << endl;
    }

    if (book != nullptr && book->returnBook()) {
        cout << "Returned book: " << book->getTitle() << endl;
    }

    cout << endl << "Final library status:" << endl;
    library.displayAllBooks();

    return 0;
}
