#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;

public:
    DynamicArray(int arraySize) {
        if (arraySize <= 0) {
            arraySize = 1;
        }
        size = arraySize;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void setValue(int index, int value) {
        if (index < 0 || index >= size) {
            cout << "Index out of range." << endl;
            return;
        }
        data[index] = value;
    }

    void display() const {
        cout << "Array elements: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    DynamicArray arr(5);

    for (int i = 0; i < 5; ++i) {
        arr.setValue(i, (i + 1) * 10);
    }

    arr.display();

    return 0;
}
