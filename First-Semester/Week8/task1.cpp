#include <iostream>
#include <stack>
#include <string>
using namespace std;

string reverseStringUsingStack(const string& input) {
    stack<char> chars;
    for (char ch : input) {
        chars.push(ch);
    }

    string reversed;
    reversed.reserve(input.size());

    while (!chars.empty()) {
        reversed += chars.top();
        chars.pop();
    }

    return reversed;
}

int main() {
    string text = "Hello Stack";
    cout << "Original: " << text << endl;
    cout << "Reversed: " << reverseStringUsingStack(text) << endl;
    return 0;
}
