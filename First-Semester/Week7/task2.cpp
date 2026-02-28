#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string capitalizeWords(const string& str) {
    string result = str;
    bool startOfWord = true;

    for (size_t i = 0; i < result.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(result[i]);
        if (isspace(ch)) {
            startOfWord = true;
            continue;
        }

        if (isalpha(ch)) {
            if (startOfWord) {
                result[i] = static_cast<char>(toupper(ch));
            } else {
                result[i] = static_cast<char>(tolower(ch));
            }
        }
        startOfWord = false;
    }

    return result;
}

string compressString(const string& str) {
    if (str.empty()) {
        return "";
    }

    string compressed;
    int runLength = 1;

    for (size_t i = 1; i <= str.size(); ++i) {
        if (i < str.size() && str[i] == str[i - 1]) {
            ++runLength;
        } else {
            compressed += str[i - 1];
            compressed += to_string(runLength);
            runLength = 1;
        }
    }

    return compressed;
}

int countSubstring(const string& str, const string& substr) {
    if (substr.empty() || substr.size() > str.size()) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i + substr.size() <= str.size(); ++i) {
        if (str.compare(i, substr.size(), substr) == 0) {
            ++count;
        }
    }
    return count;
}

string longestWord(const string& str) {
    istringstream iss(str);
    string token;
    string best;

    while (iss >> token) {
        size_t left = 0;
        size_t right = token.size();

        while (left < right && ispunct(static_cast<unsigned char>(token[left]))) {
            ++left;
        }
        while (right > left && ispunct(static_cast<unsigned char>(token[right - 1]))) {
            --right;
        }

        string cleaned = token.substr(left, right - left);
        if (cleaned.size() > best.size()) {
            best = cleaned;
        }
    }

    return best;
}

int main() {
    string sentence = "hello world from C++ programming";

    cout << "Capitalized: " << capitalizeWords(sentence) << endl;
    cout << "Compressed aaabbc: " << compressString("aaabbc") << endl;
    cout << "Occurrences of 'ana' in 'bananana': " << countSubstring("bananana", "ana") << endl;
    cout << "Longest word: " << longestWord("Coding in modern C++ is powerful and expressive.") << endl;

    return 0;
}
