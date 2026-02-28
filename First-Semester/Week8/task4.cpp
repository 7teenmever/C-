#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

class StackUsingQueues {
private:
    queue<int> q1;
    queue<int> q2;

public:
    void push(int value) {
        q2.push(value);

        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        swap(q1, q2);
    }

    int pop() {
        if (q1.empty()) {
            throw underflow_error("Stack underflow");
        }

        int value = q1.front();
        q1.pop();
        return value;
    }

    int top() const {
        if (q1.empty()) {
            throw underflow_error("Stack is empty");
        }

        return q1.front();
    }

    bool isEmpty() const {
        return q1.empty();
    }

    int size() const {
        return static_cast<int>(q1.size());
    }
};

int main() {
    StackUsingQueues st;

    st.push(5);
    st.push(10);
    st.push(15);

    cout << "Top: " << st.top() << endl;
    cout << "Size: " << st.size() << endl;

    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;

    try {
        cout << "Pop: " << st.pop() << endl;
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}
