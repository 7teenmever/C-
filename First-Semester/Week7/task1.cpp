#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

string reverseString(const string& str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

int countVowels(const string& str) {
    int count = 0;
    for (char ch : str) {
        char lower = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            ++count;
        }
    }
    return count;
}

bool isPalindrome(const string& str) {
    string cleaned;
    for (char ch : str) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            cleaned += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
    }
    return cleaned == reverseString(cleaned);
}

string removeSpaces(const string& str) {
    string result;
    for (char ch : str) {
        if (!isspace(static_cast<unsigned char>(ch))) {
            result += ch;
        }
    }
    return result;
}

int main() {
    string text = "A man a plan a canal Panama";

    cout << "Original: " << text << endl;
    cout << "Reversed: " << reverseString(text) << endl;
    cout << "Vowel count: " << countVowels(text) << endl;
    cout << "Is palindrome: " << (isPalindrome(text) ? "Yes" : "No") << endl;
    cout << "Without spaces: " << removeSpaces(text) << endl;

    return 0;
}
