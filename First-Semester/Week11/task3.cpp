#include <algorithm>
#include <cstdio>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

void printVector(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int v : arr) {
        cout << v << " ";
    }
    cout << endl;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSortTD(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSortTD(arr, left, mid);
    mergeSortTD(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSortBU(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int currSize = 1; currSize < n; currSize *= 2) {
        for (int left = 0; left < n - 1; left += 2 * currSize) {
            int mid = min(left + currSize - 1, n - 1);
            int right = min(left + 2 * currSize - 1, n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    long long inversions = 0;
    int i = 0, j = 0, k = left;

    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            inversions += static_cast<long long>(L.size() - i);
        }
    }

    while (i < static_cast<int>(L.size())) {
        arr[k++] = L[i++];
    }
    while (j < static_cast<int>(R.size())) {
        arr[k++] = R[j++];
    }

    return inversions;
}

long long countInversions(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    long long inversions = 0;

    inversions += countInversions(arr, left, mid);
    inversions += countInversions(arr, mid + 1, right);
    inversions += mergeAndCount(arr, left, mid, right);

    return inversions;
}

template <typename T, typename Compare>
void mergeCustom(vector<T>& arr, int left, int mid, int right, Compare comp) {
    vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        if (!comp(R[j], L[i])) {
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
}

template <typename T, typename Compare>
void mergeSortCustomImpl(vector<T>& arr, int left, int right, Compare comp) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSortCustomImpl(arr, left, mid, comp);
    mergeSortCustomImpl(arr, mid + 1, right, comp);
    mergeCustom(arr, left, mid, right, comp);
}

template <typename T, typename Compare>
void mergeSortCustom(vector<T>& arr, Compare comp) {
    if (!arr.empty()) {
        mergeSortCustomImpl(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

void inPlaceMerge(vector<int>& arr, int left, int mid, int right) {
    int start2 = mid + 1;

    if (arr[mid] <= arr[start2]) {
        return;
    }

    while (left <= mid && start2 <= right) {
        if (arr[left] <= arr[start2]) {
            ++left;
        } else {
            int value = arr[start2];
            int index = start2;

            while (index != left) {
                arr[index] = arr[index - 1];
                --index;
            }
            arr[left] = value;

            ++left;
            ++mid;
            ++start2;
        }
    }
}

void inPlaceMergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    inPlaceMergeSort(arr, left, mid);
    inPlaceMergeSort(arr, mid + 1, right);
    inPlaceMerge(arr, left, mid, right);
}

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1 != nullptr) ? l1 : l2;
    return dummy.next;
}

ListNode* mergeSortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* slow = head;
    ListNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* second = slow->next;
    slow->next = nullptr;

    ListNode* left = mergeSortList(head);
    ListNode* right = mergeSortList(second);

    return mergeLists(left, right);
}

ListNode* createList(initializer_list<int> values) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int value : values) {
        ListNode* node = new ListNode(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

void printList(ListNode* head, const string& label) {
    cout << label << ": ";
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

void externalMergeSort(const string& inputFile, const string& outputFile, int chunkSize) {
    ifstream input(inputFile);
    if (!input) {
        cout << "Cannot open input file: " << inputFile << endl;
        return;
    }

    vector<string> tempFiles;
    int chunkIndex = 0;

    while (true) {
        vector<int> chunk;
        chunk.reserve(chunkSize);

        int value;
        while (static_cast<int>(chunk.size()) < chunkSize && input >> value) {
            chunk.push_back(value);
        }

        if (chunk.empty()) {
            break;
        }

        sort(chunk.begin(), chunk.end());

        string tempName = "week11_chunk_" + to_string(chunkIndex++) + ".tmp";
        ofstream tempOut(tempName);
        for (int v : chunk) {
            tempOut << v << " ";
        }
        tempOut.close();
        tempFiles.push_back(tempName);

        if (input.eof()) {
            break;
        }
    }

    vector<ifstream> tempIns(tempFiles.size());
    for (size_t i = 0; i < tempFiles.size(); ++i) {
        tempIns[i].open(tempFiles[i]);
    }

    using Entry = tuple<int, int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> minHeap;

    for (size_t i = 0; i < tempIns.size(); ++i) {
        int firstValue;
        if (tempIns[i] >> firstValue) {
            minHeap.push({firstValue, static_cast<int>(i)});
        }
    }

    ofstream output(outputFile);
    while (!minHeap.empty()) {
        auto [val, fileIndex] = minHeap.top();
        minHeap.pop();
        output << val << " ";

        int nextValue;
        if (tempIns[fileIndex] >> nextValue) {
            minHeap.push({nextValue, fileIndex});
        }
    }

    for (auto& in : tempIns) {
        in.close();
    }

    for (const string& file : tempFiles) {
        remove(file.c_str());
    }
}

void timSortMerge(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }

    vector<pair<int, int>> runs;
    int n = static_cast<int>(arr.size());
    int i = 0;

    while (i < n) {
        int start = i;
        while (i + 1 < n && arr[i] <= arr[i + 1]) {
            ++i;
        }
        runs.push_back({start, i});
        ++i;
    }

    while (runs.size() > 1) {
        vector<pair<int, int>> mergedRuns;

        for (size_t j = 0; j < runs.size(); j += 2) {
            if (j + 1 < runs.size()) {
                int left = runs[j].first;
                int mid = runs[j].second;
                int right = runs[j + 1].second;
                merge(arr, left, mid, right);
                mergedRuns.push_back({left, right});
            } else {
                mergedRuns.push_back(runs[j]);
            }
        }

        runs.swap(mergedRuns);
    }
}

void kWayMerge(vector<vector<int>>& arrays, vector<int>& result) {
    result.clear();

    using Entry = tuple<int, int, int>;  // value, arrayIdx, elementIdx
    priority_queue<Entry, vector<Entry>, greater<Entry>> minHeap;

    for (int i = 0; i < static_cast<int>(arrays.size()); ++i) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    while (!minHeap.empty()) {
        auto [value, arrIdx, elemIdx] = minHeap.top();
        minHeap.pop();

        result.push_back(value);

        int nextIdx = elemIdx + 1;
        if (nextIdx < static_cast<int>(arrays[arrIdx].size())) {
            minHeap.push({arrays[arrIdx][nextIdx], arrIdx, nextIdx});
        }
    }
}

int main() {
    vector<int> a = {12, 11, 13, 5, 6, 7};
    mergeSortTD(a, 0, static_cast<int>(a.size()) - 1);
    printVector(a, "Top-down merge sort");

    vector<int> b = {38, 27, 43, 3, 9, 82, 10};
    mergeSortBU(b);
    printVector(b, "Bottom-up merge sort");

    vector<int> inv = {2, 4, 1, 3, 5};
    long long inversions = countInversions(inv, 0, static_cast<int>(inv.size()) - 1);
    cout << "Inversions count: " << inversions << endl;

    vector<int> c = {5, 2, 9, 1, 5, 6};
    mergeSortCustom(c, greater<int>());
    printVector(c, "Custom merge sort (desc)");

    vector<int> d = {10, 8, 2, 4, 7, 6, 5};
    inPlaceMergeSort(d, 0, static_cast<int>(d.size()) - 1);
    printVector(d, "In-place merge sort");

    ListNode* list = createList({4, 2, 1, 3, 5});
    printList(list, "List before merge sort");
    list = mergeSortList(list);
    printList(list, "List after merge sort");
    freeList(list);

    {
        ofstream input("week11_external_input.txt");
        input << "9 1 8 2 7 3 6 4 5";
    }
    externalMergeSort("week11_external_input.txt", "week11_external_output.txt", 3);

    ifstream sortedFile("week11_external_output.txt");
    vector<int> ext;
    int val;
    while (sortedFile >> val) {
        ext.push_back(val);
    }
    printVector(ext, "External merge sort output");

    vector<int> e = {1, 2, 5, 7, 3, 4, 6, 8, 0, 9};
    timSortMerge(e);
    printVector(e, "TimSort-inspired natural run merge");

    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {0, 3, 6, 9}};
    vector<int> merged;
    kWayMerge(arrays, merged);
    printVector(merged, "K-way merge");

    return 0;
}
