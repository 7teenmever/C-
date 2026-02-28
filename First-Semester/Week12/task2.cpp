#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> func1(int n) {
    vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(i * 2);
    }
    return result;
}

int func2(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * func2(n - 1);
}

vector<vector<int>> func3(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i + j;
        }
    }
    return matrix;
}

void printSpaceComplexityNotes() {
    cout << "Space Complexity Analysis:" << endl;
    cout << "func1: O(n) additional space for result vector" << endl;
    cout << "func2: O(n) recursion stack" << endl;
    cout << "func3: O(n^2) additional space for matrix" << endl;
}

int main() {
    printSpaceComplexityNotes();

    vector<int> v = func1(5);
    cout << "\nfunc1 output size: " << v.size() << endl;

    cout << "func2 factorial-like result for 5: " << func2(5) << endl;

    vector<vector<int>> m = func3(3);
    cout << "func3 matrix (3x3):" << endl;
    for (const auto& row : m) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
