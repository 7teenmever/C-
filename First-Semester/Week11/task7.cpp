#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

struct TestResult {
    string name;
    double averageMs;
    double averageComparisons;
    double averageSwaps;
    bool allCorrect;
};

class SortingBenchmark {
private:
    vector<int> generateRandomArray(int n) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 10000);

        vector<int> arr(n);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    vector<int> generateSortedArray(int n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        return arr;
    }

    vector<int> generateReverseSortedArray(int n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = n - i;
        }
        return arr;
    }

    vector<int> generateFewUniqueArray(int n, int uniqueCount) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, uniqueCount - 1);

        vector<int> arr(n);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    vector<int> generateNearlySortedArray(int n) {
        vector<int> arr = generateSortedArray(n);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> idxDist(0, n - 1);

        for (int i = 0; i < n / 20; ++i) {
            int a = idxDist(gen);
            int b = idxDist(gen);
            swap(arr[a], arr[b]);
        }
        return arr;
    }

    vector<vector<int>> generateTestCases() {
        return {
            generateRandomArray(1000),
            generateSortedArray(1000),
            generateReverseSortedArray(1000),
            generateFewUniqueArray(1000, 5),
            generateNearlySortedArray(1000)
        };
    }

    static int partition(vector<int>& arr, int low, int high, long long& comparisons, long long& swaps) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            ++comparisons;
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
                ++swaps;
            }
        }
        swap(arr[i + 1], arr[high]);
        ++swaps;
        return i + 1;
    }

    static void quickSortImpl(vector<int>& arr, int low, int high, long long& comparisons, long long& swaps) {
        if (low < high) {
            int p = partition(arr, low, high, comparisons, swaps);
            quickSortImpl(arr, low, p - 1, comparisons, swaps);
            quickSortImpl(arr, p + 1, high, comparisons, swaps);
        }
    }

    static void bubbleSort(vector<int>& arr, long long& comparisons, long long& swaps) {
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                ++comparisons;
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    ++swaps;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }

    static void quickSort(vector<int>& arr, long long& comparisons, long long& swaps) {
        if (!arr.empty()) {
            quickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1, comparisons, swaps);
        }
    }

    static void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons, long long& swaps) {
        vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
            ++comparisons;
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
            ++swaps;
        }

        while (i < static_cast<int>(L.size())) {
            arr[k++] = L[i++];
            ++swaps;
        }
        while (j < static_cast<int>(R.size())) {
            arr[k++] = R[j++];
            ++swaps;
        }
    }

    static void mergeSortImpl(vector<int>& arr, int left, int right, long long& comparisons, long long& swaps) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;
        mergeSortImpl(arr, left, mid, comparisons, swaps);
        mergeSortImpl(arr, mid + 1, right, comparisons, swaps);
        merge(arr, left, mid, right, comparisons, swaps);
    }

    static void mergeSort(vector<int>& arr, long long& comparisons, long long& swaps) {
        if (!arr.empty()) {
            mergeSortImpl(arr, 0, static_cast<int>(arr.size()) - 1, comparisons, swaps);
        }
    }

public:
    template <typename Func>
    TestResult benchmark(Func sortFunc, const string& name) {
        vector<vector<int>> testCases = generateTestCases();

        double totalMs = 0.0;
        double totalComparisons = 0.0;
        double totalSwaps = 0.0;
        bool allCorrect = true;

        for (const auto& test : testCases) {
            vector<int> arr = test;
            long long comparisons = 0;
            long long swaps = 0;

            auto start = chrono::high_resolution_clock::now();
            sortFunc(arr, comparisons, swaps);
            auto end = chrono::high_resolution_clock::now();

            totalMs += chrono::duration<double, milli>(end - start).count();
            totalComparisons += static_cast<double>(comparisons);
            totalSwaps += static_cast<double>(swaps);
            allCorrect = allCorrect && is_sorted(arr.begin(), arr.end());
        }

        int n = static_cast<int>(testCases.size());
        return {
            name,
            totalMs / n,
            totalComparisons / n,
            totalSwaps / n,
            allCorrect
        };
    }

    void runBenchmarks() {
        vector<TestResult> results;

        results.push_back(benchmark(
            [](vector<int>& arr, long long& c, long long& s) { bubbleSort(arr, c, s); },
            "Bubble Sort"));

        results.push_back(benchmark(
            [](vector<int>& arr, long long& c, long long& s) { quickSort(arr, c, s); },
            "Quick Sort"));

        results.push_back(benchmark(
            [](vector<int>& arr, long long& c, long long& s) { mergeSort(arr, c, s); },
            "Merge Sort"));

        cout << "Algorithm       Avg Time(ms)  Avg Comparisons  Avg Swaps  Correct" << endl;
        for (const auto& result : results) {
            cout << result.name;
            if (result.name.size() < 15) {
                cout << string(15 - result.name.size(), ' ');
            }
            cout << result.averageMs << "      "
                 << result.averageComparisons << "      "
                 << result.averageSwaps << "      "
                 << (result.allCorrect ? "Yes" : "No") << endl;
        }
    }
};

int main() {
    SortingBenchmark benchmark;
    benchmark.runBenchmarks();
    return 0;
}
