#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void reverseQueue(queue<int>& q) {
    stack<int> st;

    while (!q.empty()) {
        st.push(q.front());
        q.pop();
    }

    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
}

void printQueue(queue<int> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<int> numbers;
    for (int i = 1; i <= 6; ++i) {
        numbers.push(i);
    }

    cout << "Original queue: ";
    printQueue(numbers);

    reverseQueue(numbers);

    cout << "Reversed queue: ";
    printQueue(numbers);

    return 0;
}
