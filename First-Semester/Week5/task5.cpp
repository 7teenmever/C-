#include <iostream>
using namespace std;

int** create2DArray(int rows, int cols) {
    int** arr = new int*[rows];

    for(int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    return arr;
}
void free2DArray(int** arr, int rows) {
    for(int i = 0; i < rows; i++) {
        delete[] arr[i];
    }

    delete[] arr;
}

void fillAndPrint2DArray(int** arr, int rows, int cols) {
    cout << "Enter elements:\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << "[" << i << "][" << j << "]: ";
            cin >> arr[i][j];
        }
    }

    cout << "\nArray:\n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;
    cout << "Enter rows: ";
    cin >> rows;
    cout << "Enter cols: ";
    cin >> cols;
    int** arr = create2DArray(rows, cols);
    fillAndPrint2DArray(arr, rows, cols);
    free2DArray(arr, rows);
    return 0;
}