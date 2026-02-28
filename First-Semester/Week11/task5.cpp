#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> sortByFrequency(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) {
        ++freq[x];
    }

    vector<int> result = arr;
    sort(result.begin(), result.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) {
            return freq[a] > freq[b];
        }
        return a < b;
    });

    return result;
}

void sortColors(vector<int>& colors) {
    int low = 0;
    int mid = 0;
    int high = static_cast<int>(colors.size()) - 1;

    while (mid <= high) {
        if (colors[mid] == 0) {
            swap(colors[low++], colors[mid++]);
        } else if (colors[mid] == 1) {
            ++mid;
        } else {
            swap(colors[mid], colors[high--]);
        }
    }
}

void rearrangeNegatives(vector<int>& arr) {
    vector<int> negatives;
    vector<int> positives;

    for (int x : arr) {
        if (x < 0) {
            negatives.push_back(x);
        } else {
            positives.push_back(x);
        }
    }

    arr.clear();
    arr.insert(arr.end(), negatives.begin(), negatives.end());
    arr.insert(arr.end(), positives.begin(), positives.end());
}

struct Interval {
    int start;
    int end;
};

bool intervalLess(const Interval& a, const Interval& b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

void sortIntervalsBubble(vector<Interval>& intervals) {
    int n = static_cast<int>(intervals.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (intervalLess(intervals[j + 1], intervals[j])) {
                swap(intervals[j], intervals[j + 1]);
            }
        }
    }
}

int partitionIntervals(vector<Interval>& intervals, int low, int high) {
    Interval pivot = intervals[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (!intervalLess(pivot, intervals[j])) {
            ++i;
            swap(intervals[i], intervals[j]);
        }
    }
    swap(intervals[i + 1], intervals[high]);
    return i + 1;
}

void sortIntervalsQuick(vector<Interval>& intervals, int low, int high) {
    if (low < high) {
        int p = partitionIntervals(intervals, low, high);
        sortIntervalsQuick(intervals, low, p - 1);
        sortIntervalsQuick(intervals, p + 1, high);
    }
}

void mergeIntervals(vector<Interval>& intervals, int left, int mid, int right) {
    vector<Interval> L(intervals.begin() + left, intervals.begin() + mid + 1);
    vector<Interval> R(intervals.begin() + mid + 1, intervals.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        if (!intervalLess(R[j], L[i])) {
            intervals[k++] = L[i++];
        } else {
            intervals[k++] = R[j++];
        }
    }

    while (i < static_cast<int>(L.size())) {
        intervals[k++] = L[i++];
    }
    while (j < static_cast<int>(R.size())) {
        intervals[k++] = R[j++];
    }
}

void sortIntervalsMerge(vector<Interval>& intervals, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    sortIntervalsMerge(intervals, left, mid);
    sortIntervalsMerge(intervals, mid + 1, right);
    mergeIntervals(intervals, left, mid, right);
}

void sortIntervals(vector<Interval>& intervals) {
    if (!intervals.empty()) {
        sortIntervalsMerge(intervals, 0, static_cast<int>(intervals.size()) - 1);
    }
}

void printVector(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void printIntervals(const vector<Interval>& intervals, const string& label) {
    cout << label << ": ";
    for (const auto& in : intervals) {
        cout << "[" << in.start << "," << in.end << "] ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {4, 6, 2, 6, 4, 4, 1, 2};
    vector<int> byFreq = sortByFrequency(a);
    printVector(byFreq, "Sort by frequency");

    vector<int> colors = {2, 0, 2, 1, 1, 0};
    sortColors(colors);
    printVector(colors, "Sort colors (0,1,2)");

    vector<int> signs = {3, -1, 4, -5, -2, 6, 0, -7};
    rearrangeNegatives(signs);
    printVector(signs, "Negatives then positives (stable)");

    vector<Interval> intervals = {{5, 7}, {1, 3}, {1, 2}, {4, 6}, {3, 4}};

    vector<Interval> b1 = intervals;
    sortIntervalsBubble(b1);
    printIntervals(b1, "Intervals bubble sort");

    vector<Interval> b2 = intervals;
    sortIntervalsQuick(b2, 0, static_cast<int>(b2.size()) - 1);
    printIntervals(b2, "Intervals quick sort");

    vector<Interval> b3 = intervals;
    sortIntervals(b3);
    printIntervals(b3, "Intervals merge sort");

    return 0;
}
