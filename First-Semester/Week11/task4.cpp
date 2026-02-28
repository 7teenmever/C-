#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
using namespace std;

struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
};

struct RunResult {
    double ms;
    SortStats stats;
    bool sorted;
};

void bubbleSortCount(vector<int>& arr, SortStats& stats) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            ++stats.comparisons;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                ++stats.swaps;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int partitionCount(vector<int>& arr, int low, int high, SortStats& stats) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        ++stats.comparisons;
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
            ++stats.swaps;
        }
    }

    swap(arr[i + 1], arr[high]);
    ++stats.swaps;
    return i + 1;
}

void quickSortCountImpl(vector<int>& arr, int low, int high, SortStats& stats) {
    if (low < high) {
        int p = partitionCount(arr, low, high, stats);
        quickSortCountImpl(arr, low, p - 1, stats);
        quickSortCountImpl(arr, p + 1, high, stats);
    }
}

void quickSortCount(vector<int>& arr, SortStats& stats) {
    if (!arr.empty()) {
        quickSortCountImpl(arr, 0, static_cast<int>(arr.size()) - 1, stats);
    }
}

void mergeCount(vector<int>& arr, int left, int mid, int right, SortStats& stats) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        ++stats.comparisons;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        ++stats.swaps;
    }

    while (i < static_cast<int>(L.size())) {
        arr[k++] = L[i++];
        ++stats.swaps;
    }
    while (j < static_cast<int>(R.size())) {
        arr[k++] = R[j++];
        ++stats.swaps;
    }
}

void mergeSortCountImpl(vector<int>& arr, int left, int right, SortStats& stats) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSortCountImpl(arr, left, mid, stats);
    mergeSortCountImpl(arr, mid + 1, right, stats);
    mergeCount(arr, left, mid, right, stats);
}

void mergeSortCount(vector<int>& arr, SortStats& stats) {
    if (!arr.empty()) {
        mergeSortCountImpl(arr, 0, static_cast<int>(arr.size()) - 1, stats);
    }
}

template <typename SortFunc>
RunResult runSort(const vector<int>& input, SortFunc sorter) {
    vector<int> arr = input;
    SortStats stats;

    auto start = chrono::high_resolution_clock::now();
    sorter(arr, stats);
    auto end = chrono::high_resolution_clock::now();

    double elapsedMs = chrono::duration<double, milli>(end - start).count();
    bool ok = is_sorted(arr.begin(), arr.end());

    return {elapsedMs, stats, ok};
}

vector<int> generateRandomArray(int n, int minValue = 0, int maxValue = 1000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minValue, maxValue);

    vector<int> arr(n);
    for (int& x : arr) {
        x = dist(gen);
    }
    return arr;
}

void compareSortingAlgorithms() {
    vector<pair<string, vector<int>>> testCases;

    vector<int> randomArr = generateRandomArray(250);
    vector<int> sortedArr = randomArr;
    sort(sortedArr.begin(), sortedArr.end());

    vector<int> reverseArr = sortedArr;
    reverse(reverseArr.begin(), reverseArr.end());

    vector<int> fewUnique(250);
    for (int i = 0; i < 250; ++i) {
        fewUnique[i] = i % 5;
    }

    vector<int> manyDuplicates = generateRandomArray(250, 0, 20);

    testCases.push_back({"Random", randomArr});
    testCases.push_back({"Sorted", sortedArr});
    testCases.push_back({"Reverse", reverseArr});
    testCases.push_back({"FewUnique", fewUnique});
    testCases.push_back({"Duplicates", manyDuplicates});

    for (const auto& test : testCases) {
        cout << "\nCase: " << test.first << endl;
        cout << "Algorithm      Time(ms)  Comparisons  Swaps/Assign  Sorted" << endl;

        RunResult bubble = runSort(test.second, bubbleSortCount);
        RunResult quick = runSort(test.second, quickSortCount);
        RunResult merge = runSort(test.second, mergeSortCount);

        auto print = [](const string& name, const RunResult& r) {
            cout << name;
            if (name.size() < 14) {
                cout << string(14 - name.size(), ' ');
            }
            cout << r.ms << "      " << r.stats.comparisons
                 << "        " << r.stats.swaps
                 << "         " << (r.sorted ? "Yes" : "No") << endl;
        };

        print("Bubble", bubble);
        print("Quick", quick);
        print("Merge", merge);
    }
}

int partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void insertionSortRange(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void heapSortRange(vector<int>& arr, int low, int high) {
    make_heap(arr.begin() + low, arr.begin() + high + 1);
    sort_heap(arr.begin() + low, arr.begin() + high + 1);
}

void introSort(vector<int>& arr, int low, int high, int depthLimit) {
    while (high - low > 16) {
        if (depthLimit == 0) {
            heapSortRange(arr, low, high);
            return;
        }

        --depthLimit;
        int p = partitionLomuto(arr, low, high);

        if (p - low < high - p) {
            introSort(arr, low, p - 1, depthLimit);
            low = p + 1;
        } else {
            introSort(arr, p + 1, high, depthLimit);
            high = p - 1;
        }
    }

    insertionSortRange(arr, low, high);
}

void mergeForTim(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(leftPart.size()) && j < static_cast<int>(rightPart.size())) {
        if (leftPart[i] <= rightPart[j]) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }

    while (i < static_cast<int>(leftPart.size())) {
        arr[k++] = leftPart[i++];
    }
    while (j < static_cast<int>(rightPart.size())) {
        arr[k++] = rightPart[j++];
    }
}

void timSort(vector<int>& arr) {
    const int RUN = 32;
    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n; i += RUN) {
        insertionSortRange(arr, i, min(i + RUN - 1, n - 1));
    }

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                mergeForTim(arr, left, mid, right);
            }
        }
    }
}

struct Student {
    string name;
    int score;
    int id;
};

void bubbleSortStudents(vector<Student>& students) {
    for (size_t i = 0; i < students.size(); ++i) {
        for (size_t j = 0; j + 1 < students.size() - i; ++j) {
            if (students[j].score > students[j + 1].score) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

int studentPartition(vector<Student>& students, int low, int high) {
    int pivot = students[high].score;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (students[j].score <= pivot) {
            ++i;
            swap(students[i], students[j]);
        }
    }

    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSortStudents(vector<Student>& students, int low, int high) {
    if (low < high) {
        int p = studentPartition(students, low, high);
        quickSortStudents(students, low, p - 1);
        quickSortStudents(students, p + 1, high);
    }
}

void mergeStudents(vector<Student>& students, int left, int mid, int right) {
    vector<Student> L(students.begin() + left, students.begin() + mid + 1);
    vector<Student> R(students.begin() + mid + 1, students.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        if (L[i].score <= R[j].score) {
            students[k++] = L[i++];
        } else {
            students[k++] = R[j++];
        }
    }

    while (i < static_cast<int>(L.size())) {
        students[k++] = L[i++];
    }
    while (j < static_cast<int>(R.size())) {
        students[k++] = R[j++];
    }
}

void mergeSortStudents(vector<Student>& students, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSortStudents(students, left, mid);
    mergeSortStudents(students, mid + 1, right);
    mergeStudents(students, left, mid, right);
}

void printOrderForScore(const vector<Student>& students, int score, const string& label) {
    cout << label << " IDs with score " << score << ": ";
    for (const Student& s : students) {
        if (s.score == score) {
            cout << s.id << " ";
        }
    }
    cout << endl;
}

void testSortStability() {
    vector<Student> base = {
        {"Alice", 85, 1},
        {"Bob", 90, 2},
        {"Charlie", 85, 3},
        {"David", 88, 4}
    };

    vector<Student> bubble = base;
    vector<Student> quick = base;
    vector<Student> merge = base;

    bubbleSortStudents(bubble);
    quickSortStudents(quick, 0, static_cast<int>(quick.size()) - 1);
    mergeSortStudents(merge, 0, static_cast<int>(merge.size()) - 1);

    cout << "\nStability check (relative order for equal scores):" << endl;
    printOrderForScore(bubble, 85, "Bubble Sort");
    printOrderForScore(quick, 85, "Quick Sort");
    printOrderForScore(merge, 85, "Merge Sort");
    cout << "Expected stable order for score 85: IDs 1 then 3" << endl;
}

void printVector(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    compareSortingAlgorithms();

    vector<int> introData = {10, 7, 8, 9, 1, 5, 3, 2, 6, 4};
    int depthLimit = 2 * static_cast<int>(log2(max(1, static_cast<int>(introData.size()))));
    introSort(introData, 0, static_cast<int>(introData.size()) - 1, depthLimit);
    printVector(introData, "\nIntrosort result");

    vector<int> timData = {5, 21, 7, 23, 19, 10, 11, 13, 9, 17, 6};
    timSort(timData);
    printVector(timData, "TimSort-inspired hybrid result");

    testSortStability();
    return 0;
}
