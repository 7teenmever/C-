#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct TextStats {
    int charCount;
    int wordCount;
    int lineCount;
    int sentenceCount;
    string mostFrequentWord;
};

static string normalizeWord(const string& token) {
    string cleaned;
    for (char ch : token) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            cleaned += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
    }
    return cleaned;
}

TextStats analyzeTextFile(const string& filename) {
    TextStats stats = {0, 0, 0, 0, ""};
    ifstream in(filename);
    if (!in) {
        return stats;
    }

    map<string, int> frequency;
    string line;

    while (getline(in, line)) {
        ++stats.lineCount;
        stats.charCount += static_cast<int>(line.size());

        for (char ch : line) {
            if (ch == '.' || ch == '!' || ch == '?') {
                ++stats.sentenceCount;
            }
        }

        stringstream ss(line);
        string token;
        while (ss >> token) {
            string word = normalizeWord(token);
            if (!word.empty()) {
                ++stats.wordCount;
                ++frequency[word];
            }
        }
    }

    int best = 0;
    for (const auto& entry : frequency) {
        if (entry.second > best) {
            best = entry.second;
            stats.mostFrequentWord = entry.first;
        }
    }

    return stats;
}

void findAndReplaceInFile(const string& filename,
                          const string& findStr,
                          const string& replaceStr) {
    if (findStr.empty()) {
        return;
    }

    ifstream in(filename);
    if (!in) {
        return;
    }

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    size_t pos = 0;
    while ((pos = content.find(findStr, pos)) != string::npos) {
        content.replace(pos, findStr.length(), replaceStr);
        pos += replaceStr.length();
    }

    ofstream out(filename);
    out << content;
}

void sortFileLines(const string& filename) {
    ifstream in(filename);
    if (!in) {
        return;
    }

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    sort(lines.begin(), lines.end());

    ofstream out(filename);
    for (const string& l : lines) {
        out << l << "\n";
    }
}

int main() {
    string filename = "week7_text.txt";

    ofstream init(filename);
    init << "C++ is fast. C++ is powerful!\n";
    init << "Text analysis helps with coding.\n";
    init << "Is this useful? Yes, it is.\n";
    init.close();

    TextStats stats = analyzeTextFile(filename);
    cout << "Chars: " << stats.charCount << endl;
    cout << "Words: " << stats.wordCount << endl;
    cout << "Lines: " << stats.lineCount << endl;
    cout << "Sentences: " << stats.sentenceCount << endl;
    cout << "Most frequent word: " << stats.mostFrequentWord << endl;

    findAndReplaceInFile(filename, "C++", "CPP");
    sortFileLines(filename);

    cout << "\nSorted and replaced file content:\n";
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }

    return 0;
}
