#include <iostream>
#include <stdexcept>
using namespace std;

class ArrayStack {
private:
    int* data;
    int capacity;
    int topIndex;

public:
    explicit ArrayStack(int maxSize)
        : data(nullptr), capacity(maxSize), topIndex(-1) {
        if (capacity <= 0) {
            throw invalid_argument("Capacity must be positive");
        }
        data = new int[capacity];
    }

    ~ArrayStack() {
        delete[] data;
    }

    void push(int value) {
        if (size() == capacity) {
            throw overflow_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    int pop() {
        if (isEmpty()) {
            throw underflow_error("Stack underflow");
        }
        return data[topIndex--];
    }

    int top() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }
};

int main() {
    ArrayStack st(3);

    try {
        st.push(10);
        st.push(20);
        st.push(30);
        cout << "Top: " << st.top() << endl;

        st.push(40);
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    try {
        while (!st.isEmpty()) {
            cout << "Popped: " << st.pop() << endl;
        }
        st.pop();
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}
