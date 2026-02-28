#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    double price;
    int pages;
};

struct Library {
    Book books[100];
    int count;

    Library() : count(0) {}

    void addBook(const Book& book) {
        if (count >= 100) {
            cout << "Library is full. Cannot add more books." << endl;
            return;
        }
        books[count++] = book;
    }

    Book* findBookByISBN(const string& isbn) {
        for (int i = 0; i < count; ++i) {
            if (books[i].ISBN == isbn) {
                return &books[i];
            }
        }
        return nullptr;
    }

    void listBooksByAuthor(const string& author) {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (books[i].author == author) {
                cout << books[i].title << " (ISBN: " << books[i].ISBN << ")" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found for author: " << author << endl;
        }
    }

    void removeBook(const string& isbn) {
        for (int i = 0; i < count; ++i) {
            if (books[i].ISBN == isbn) {
                for (int j = i; j < count - 1; ++j) {
                    books[j] = books[j + 1];
                }
                --count;
                cout << "Removed book with ISBN: " << isbn << endl;
                return;
            }
        }
        cout << "Book not found: " << isbn << endl;
    }

    void displayAll() {
        cout << "Library has " << count << " books:" << endl;
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << books[i].title << " by " << books[i].author
                 << " | ISBN: " << books[i].ISBN << endl;
        }
    }
};

int main() {
    Library lib;

    lib.addBook({"C++ Basics", "John Doe", "111", 19.99, 200});
    lib.addBook({"Advanced C++", "John Doe", "222", 29.99, 350});
    lib.addBook({"Data Structures", "Jane Smith", "333", 24.99, 280});

    lib.displayAll();
    cout << endl;

    Book* found = lib.findBookByISBN("222");
    if (found != nullptr) {
        cout << "Found: " << found->title << " by " << found->author << endl;
    }

    cout << "\nBooks by John Doe:" << endl;
    lib.listBooksByAuthor("John Doe");

    cout << endl;
    lib.removeBook("111");
    lib.displayAll();

    return 0;
}
