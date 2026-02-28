#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

int lomutoPartition(vector<int>& arr, int low, int high) {
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

void quickSortLomuto(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = lomutoPartition(arr, low, high);
        quickSortLomuto(arr, low, pivotIndex - 1);
        quickSortLomuto(arr, pivotIndex + 1, high);
    }
}

int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            ++i;
        } while (arr[i] < pivot);

        do {
            --j;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pivotIndex);
        quickSortHoare(arr, pivotIndex + 1, high);
    }
}

int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return mid;
    }
    if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return low;
    }
    return high;
}

void quickSortMedianPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = medianOfThree(arr, low, high);
        swap(arr[pivotIndex], arr[high]);
        int p = lomutoPartition(arr, low, high);
        quickSortMedianPivot(arr, low, p - 1);
        quickSortMedianPivot(arr, p + 1, high);
    }
}

int randomPartition(vector<int>& arr, int low, int high) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return lomutoPartition(arr, low, high);
}

void quickSortTailRecursive(vector<int>& arr, int low, int high) {
    while (low < high) {
        int p = lomutoPartition(arr, low, high);

        if (p - low < high - p) {
            quickSortTailRecursive(arr, low, p - 1);
            low = p + 1;
        } else {
            quickSortTailRecursive(arr, p + 1, high);
            high = p - 1;
        }
    }
}

int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (k <= 0 || k > high - low + 1) {
        return -1;
    }

    int targetIndex = low + k - 1;
    while (low <= high) {
        int p = lomutoPartition(arr, low, high);
        if (p == targetIndex) {
            return arr[p];
        }
        if (p < targetIndex) {
            low = p + 1;
        } else {
            high = p - 1;
        }
    }

    return -1;
}

void threeWayPartition(vector<int>& arr, int low, int high, int& left, int& right) {
    int pivot = arr[high];
    left = low;
    right = high;
    int i = low;

    while (i <= right) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[left]);
            ++i;
            ++left;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[right]);
            --right;
        } else {
            ++i;
        }
    }
}

void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    int left, right;
    threeWayPartition(arr, low, high, left, right);
    quickSort3Way(arr, low, left - 1);
    quickSort3Way(arr, right + 1, high);
}

void quickSortIterative(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }

    stack<pair<int, int>> st;
    st.push({0, static_cast<int>(arr.size()) - 1});

    while (!st.empty()) {
        auto range = st.top();
        st.pop();

        int low = range.first;
        int high = range.second;
        if (low >= high) {
            continue;
        }

        int p = lomutoPartition(arr, low, high);
        if (p - 1 > low) {
            st.push({low, p - 1});
        }
        if (p + 1 < high) {
            st.push({p + 1, high});
        }
    }
}

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* getTail(ListNode* node) {
    while (node != nullptr && node->next != nullptr) {
        node = node->next;
    }
    return node;
}

ListNode* partitionList(ListNode* start, ListNode* end, ListNode*& newStart, ListNode*& newEnd) {
    ListNode* pivot = end;
    ListNode* prev = nullptr;
    ListNode* current = start;
    ListNode* tail = pivot;

    newStart = nullptr;
    newEnd = nullptr;

    while (current != pivot) {
        if (current->val < pivot->val) {
            if (newStart == nullptr) {
                newStart = current;
            }
            prev = current;
            current = current->next;
        } else {
            ListNode* nextNode = current->next;
            if (prev != nullptr) {
                prev->next = current->next;
            }
            current->next = nullptr;
            tail->next = current;
            tail = current;
            current = nextNode;
        }
    }

    if (newStart == nullptr) {
        newStart = pivot;
    }

    newEnd = tail;
    return pivot;
}

ListNode* quickSortListRecur(ListNode* head, ListNode* end) {
    if (head == nullptr || head == end) {
        return head;
    }

    ListNode* newStart = nullptr;
    ListNode* newEnd = nullptr;

    ListNode* pivot = partitionList(head, end, newStart, newEnd);

    if (newStart != pivot) {
        ListNode* temp = newStart;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newStart = quickSortListRecur(newStart, temp);

        temp = getTail(newStart);
        temp->next = pivot;
    }

    pivot->next = quickSortListRecur(pivot->next, newEnd);
    return newStart;
}

ListNode* quickSortList(ListNode* head) {
    return quickSortListRecur(head, getTail(head));
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

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

void printVector(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {10, 7, 8, 9, 1, 5};
    vector<int> b = a;
    vector<int> c = a;
    vector<int> d = a;
    vector<int> e = {5, 3, 8, 4, 2, 7, 1, 10};

    quickSortLomuto(a, 0, static_cast<int>(a.size()) - 1);
    quickSortHoare(b, 0, static_cast<int>(b.size()) - 1);
    quickSortMedianPivot(c, 0, static_cast<int>(c.size()) - 1);
    quickSortTailRecursive(d, 0, static_cast<int>(d.size()) - 1);

    printVector(a, "Lomuto");
    printVector(b, "Hoare");
    printVector(c, "Median pivot");
    printVector(d, "Tail-recursive");

    int kth = quickSelect(e, 0, static_cast<int>(e.size()) - 1, 4);
    cout << "4th smallest (quick select): " << kth << endl;

    vector<int> f = {4, 9, 4, 2, 4, 7, 4, 1};
    quickSort3Way(f, 0, static_cast<int>(f.size()) - 1);
    printVector(f, "3-way quick sort");

    vector<int> g = {12, 11, 13, 5, 6, 7};
    quickSortIterative(g);
    printVector(g, "Iterative quick sort");

    ListNode* list = createList({30, 3, 4, 20, 5});
    cout << "List before quick sort: ";
    printList(list);
    list = quickSortList(list);
    cout << "List after quick sort: ";
    printList(list);
    freeList(list);

    return 0;
}
