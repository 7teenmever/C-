#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool writeToFile(const string& filename, const string& content) {
    ofstream out(filename);
    if (!out) {
        return false;
    }
    out << content;
    return true;
}

string readFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        return "";
    }

    ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

void copyFile(const string& source, const string& destination) {
    ifstream in(source, ios::binary);
    if (!in) {
        cout << "Cannot open source file: " << source << endl;
        return;
    }

    ofstream out(destination, ios::binary);
    if (!out) {
        cout << "Cannot open destination file: " << destination << endl;
        return;
    }

    out << in.rdbuf();
}

int countLines(const string& filename) {
    ifstream in(filename);
    if (!in) {
        return 0;
    }

    int lines = 0;
    string line;
    while (getline(in, line)) {
        ++lines;
    }
    return lines;
}

int main() {
    string source = "week7_task5_source.txt";
    string destination = "week7_task5_copy.txt";

    string content = "Line one\nLine two\nLine three\n";
    if (writeToFile(source, content)) {
        cout << "Write successful." << endl;
    }

    cout << "Read content:\n" << readFromFile(source) << endl;

    copyFile(source, destination);
    cout << "Copied file to: " << destination << endl;

    cout << "Line count in source: " << countLines(source) << endl;

    return 0;
}
