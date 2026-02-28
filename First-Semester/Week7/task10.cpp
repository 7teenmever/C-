#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    string address;
};

static void writeString(ofstream& out, const string& value) {
    size_t len = value.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(value.data(), static_cast<streamsize>(len));
}

static bool readString(ifstream& in, string& value) {
    size_t len = 0;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!in) {
        return false;
    }

    value.resize(len);
    in.read(&value[0], static_cast<streamsize>(len));
    return static_cast<bool>(in);
}

struct ContactManager {
    Contact contacts[500];
    int contactCount;
    const string filename = "contacts.dat";

    ContactManager() : contactCount(0) {}

    void addContact() {
        if (contactCount >= 500) {
            cout << "Contact list is full." << endl;
            return;
        }

        Contact c;
        cout << "Enter name: ";
        getline(cin, c.name);
        cout << "Enter phone: ";
        getline(cin, c.phone);
        cout << "Enter email: ";
        getline(cin, c.email);
        cout << "Enter address: ";
        getline(cin, c.address);

        contacts[contactCount++] = c;
    }

    void addContact(const Contact& c) {
        if (contactCount >= 500) {
            cout << "Contact list is full." << endl;
            return;
        }
        contacts[contactCount++] = c;
    }

    void searchContact(const string& name) {
        for (int i = 0; i < contactCount; ++i) {
            if (contacts[i].name == name) {
                cout << "Found: " << contacts[i].name << " | " << contacts[i].phone
                     << " | " << contacts[i].email << " | " << contacts[i].address << endl;
                return;
            }
        }
        cout << "Contact not found: " << name << endl;
    }

    void deleteContact(const string& name) {
        for (int i = 0; i < contactCount; ++i) {
            if (contacts[i].name == name) {
                for (int j = i; j < contactCount - 1; ++j) {
                    contacts[j] = contacts[j + 1];
                }
                --contactCount;
                cout << "Deleted contact: " << name << endl;
                return;
            }
        }
        cout << "Contact not found: " << name << endl;
    }

    void sortContacts() {
        sort(contacts, contacts + contactCount, [](const Contact& a, const Contact& b) {
            return a.name < b.name;
        });
    }

    void exportToCSV(const string& csvFilename) {
        ofstream out(csvFilename);
        if (!out) {
            cout << "Could not export to CSV." << endl;
            return;
        }

        out << "Name,Phone,Email,Address\n";
        for (int i = 0; i < contactCount; ++i) {
            out << '"' << contacts[i].name << "\",";
            out << '"' << contacts[i].phone << "\",";
            out << '"' << contacts[i].email << "\",";
            out << '"' << contacts[i].address << "\"\n";
        }
    }

    void saveContactsBinary() {
        ofstream out(filename, ios::binary);
        if (!out) {
            cout << "Could not save contacts to binary file." << endl;
            return;
        }

        out.write(reinterpret_cast<const char*>(&contactCount), sizeof(contactCount));
        for (int i = 0; i < contactCount; ++i) {
            writeString(out, contacts[i].name);
            writeString(out, contacts[i].phone);
            writeString(out, contacts[i].email);
            writeString(out, contacts[i].address);
        }
    }

    void loadContactsBinary() {
        ifstream in(filename, ios::binary);
        if (!in) {
            cout << "No binary contacts file found." << endl;
            return;
        }

        int loadedCount = 0;
        in.read(reinterpret_cast<char*>(&loadedCount), sizeof(loadedCount));
        if (!in) {
            cout << "Invalid contacts file." << endl;
            return;
        }

        if (loadedCount < 0) {
            loadedCount = 0;
        }
        if (loadedCount > 500) {
            loadedCount = 500;
        }

        contactCount = 0;
        for (int i = 0; i < loadedCount; ++i) {
            Contact c;
            if (!readString(in, c.name) ||
                !readString(in, c.phone) ||
                !readString(in, c.email) ||
                !readString(in, c.address)) {
                break;
            }
            contacts[contactCount++] = c;
        }
    }

    void displayAll() {
        if (contactCount == 0) {
            cout << "No contacts available." << endl;
            return;
        }

        for (int i = 0; i < contactCount; ++i) {
            cout << contacts[i].name << " | " << contacts[i].phone
                 << " | " << contacts[i].email << " | " << contacts[i].address << endl;
        }
    }
};

int main() {
    ContactManager manager;

    manager.addContact({"Alice", "+1-555-1000", "alice@example.com", "New York"});
    manager.addContact({"Bob", "+1-555-2000", "bob@example.com", "Chicago"});
    manager.addContact({"Carol", "+1-555-3000", "carol@example.com", "San Francisco"});

    manager.sortContacts();
    cout << "Sorted contacts:" << endl;
    manager.displayAll();

    cout << "\nSearch Bob:" << endl;
    manager.searchContact("Bob");

    cout << "\nDelete Alice:" << endl;
    manager.deleteContact("Alice");
    manager.displayAll();

    manager.saveContactsBinary();

    ContactManager loaded;
    loaded.loadContactsBinary();

    cout << "\nLoaded from binary:" << endl;
    loaded.displayAll();

    loaded.exportToCSV("contacts.csv");
    cout << "Exported CSV to contacts.csv" << endl;

    return 0;
}
