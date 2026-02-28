#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SortingVisualizer {
private:
    vector<int> data;

    static void printArray(const vector<int>& arr, const string& label) {
        cout << label << ": ";
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }

    int partitionWithSteps(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        cout << "Pivot = " << pivot << " (index " << high << ")" << endl;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
                printArray(arr, "  After swap");
            }
        }

        swap(arr[i + 1], arr[high]);
        printArray(arr, "  After placing pivot");
        return i + 1;
    }

    void mergeWithSteps(vector<int>& arr, int left, int mid, int right) {
        vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

        cout << "Merging ranges [" << left << "," << mid << "] and ["
             << mid + 1 << "," << right << "]" << endl;

        int i = 0, j = 0, k = left;
        while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < static_cast<int>(L.size())) {
            arr[k++] = L[i++];
        }
        while (j < static_cast<int>(R.size())) {
            arr[k++] = R[j++];
        }

        printArray(arr, "  After merge");
    }

public:
    explicit SortingVisualizer(const vector<int>& initial) : data(initial) {}

    void bubbleSortWithSteps() {
        vector<int> arr = data;
        printArray(arr, "Bubble start");

        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    printArray(arr, "After swap");
                }
            }
        }

        printArray(arr, "Bubble sorted");
    }

    void quickSortWithSteps(vector<int>& arr, int low, int high) {
        if (low < high) {
            cout << "Partitioning range [" << low << "," << high << "]" << endl;
            int p = partitionWithSteps(arr, low, high);
            quickSortWithSteps(arr, low, p - 1);
            quickSortWithSteps(arr, p + 1, high);
        }
    }

    void mergeSortWithSteps(vector<int>& arr, int left, int right) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;
        mergeSortWithSteps(arr, left, mid);
        mergeSortWithSteps(arr, mid + 1, right);
        mergeWithSteps(arr, left, mid, right);
    }
};

int main() {
    SortingVisualizer visualizer({5, 1, 4, 2, 8});
    visualizer.bubbleSortWithSteps();

    vector<int> quickData = {10, 7, 8, 9, 1, 5};
    cout << "\nQuick sort steps:" << endl;
    visualizer.quickSortWithSteps(quickData, 0, static_cast<int>(quickData.size()) - 1);

    cout << "Quick sorted: ";
    for (int x : quickData) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> mergeData = {12, 11, 13, 5, 6, 7};
    cout << "\nMerge sort steps:" << endl;
    visualizer.mergeSortWithSteps(mergeData, 0, static_cast<int>(mergeData.size()) - 1);

    cout << "Merge sorted: ";
    for (int x : mergeData) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
