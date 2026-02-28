#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void func1(int n) {
    for (int i = 0; i < n; i++) {
        cout << i << " ";
    }
    cout << endl;
}

void func2(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(" << i << "," << j << ") ";
        }
    }
    cout << endl;
}

void func3(int n) {
    int i = 1;
    while (i < n) {
        i *= 2;
    }
    cout << "func3 reached i = " << i << endl;
}

void func4(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            if (j == 99) {
                cout << i << " ";
            }
        }
    }
    cout << endl;
}

pair<long long, long long> func5(const vector<int>& arr) {
    long long sum = 0;
    long long product = 1;

    for (int num : arr) {
        sum += num;
    }
    for (int num : arr) {
        product *= num;
    }

    return {sum, product};
}

void func6(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << "(" << i << "," << j << ") ";
        }
    }
    cout << endl;
}

int func7(int n) {
    if (n <= 1) {
        return n;
    }
    return func7(n - 1) + func7(n - 2);
}

void func8(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr.size(); j++) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
    }
    cout << endl;
}

void printBigONotes() {
    cout << "Big-O Analysis:" << endl;
    cout << "func1: O(n)" << endl;
    cout << "func2: O(n^2)" << endl;
    cout << "func3: O(log n)" << endl;
    cout << "func4: O(n) because inner loop is constant (100)" << endl;
    cout << "func5: O(n) + O(n) = O(n)" << endl;
    cout << "func6: O(n^2) (triangular nested loop)" << endl;
    cout << "func7: O(2^n)" << endl;
    cout << "func8: O(n log n + n^2) = O(n^2)" << endl;
}

int main() {
    printBigONotes();

    cout << "\nSmall run demo:" << endl;
    func1(5);
    func2(2);
    func3(20);
    func4(3);

    vector<int> arr = {1, 2, 3};
    auto [sum, product] = func5(arr);
    cout << "func5 sum = " << sum << ", product = " << product << endl;

    func6(3);
    cout << "func7(6) = " << func7(6) << endl;

    vector<int> arr2 = {3, 1, 2};
    func8(arr2);

    return 0;
}
