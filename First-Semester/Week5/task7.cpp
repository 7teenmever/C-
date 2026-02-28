#include <iostream>
using namespace std;

// Use function pointers to apply different operations on array elements

void applyOperation(int arr[], int size, int (*operation)(int)) {
    for (int i = 0; i < size; ++i) {
        arr[i] = operation(arr[i]);
    }
}

int square(int x) { return x * x; }
int doubleValue(int x) { return x * 2; }
int increment(int x) { return x + 1; }

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;

    int squared[] = {1, 2, 3, 4, 5};
    int doubled[] = {1, 2, 3, 4, 5};
    int incremented[] = {1, 2, 3, 4, 5};

    applyOperation(squared, size, square);
    applyOperation(doubled, size, doubleValue);
    applyOperation(incremented, size, increment);

    cout << "Original array: ";
    printArray(numbers, size);
    cout << "After square: ";
    printArray(squared, size);
    cout << "After doubleValue: ";
    printArray(doubled, size);
    cout << "After increment: ";
    printArray(incremented, size);

    return 0;
}
