#include <functional>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

void bubbleSortBasic(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortOptimized(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void cocktailSort(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }

    bool swapped = true;
    int start = 0;
    int end = static_cast<int>(arr.size()) - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

template <typename T, typename Compare>
void bubbleSortCustom(vector<T>& arr, Compare comp) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int countBubbleSortSwaps(vector<int>& arr) {
    vector<int> copy = arr;
    int swaps = 0;
    int n = static_cast<int>(copy.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (copy[j] > copy[j + 1]) {
                swap(copy[j], copy[j + 1]);
                ++swaps;
            }
        }
    }

    return swaps;
}

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* bubbleSortLinkedList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    bool swapped;
    do {
        swapped = false;
        ListNode* current = head;
        while (current->next != nullptr) {
            if (current->val > current->next->val) {
                swap(current->val, current->next->val);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    return head;
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

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

void printVector(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {5, 1, 4, 2, 8};
    vector<int> b = a;
    vector<int> c = a;

    bubbleSortBasic(a);
    bubbleSortOptimized(b);
    cocktailSort(c);

    printVector(a, "Basic bubble");
    printVector(b, "Optimized bubble");
    printVector(c, "Cocktail sort");

    vector<int> d = {4, 2, 9, 1, 7};
    bubbleSortCustom(d, greater<int>());
    printVector(d, "Custom comparator (desc)");

    vector<int> e = {3, 2, 1, 4};
    cout << "Bubble sort swaps needed: " << countBubbleSortSwaps(e) << endl;

    ListNode* list = createList({9, 3, 7, 1, 5});
    cout << "Linked list before sort: ";
    printList(list);
    list = bubbleSortLinkedList(list);
    cout << "Linked list after sort: ";
    printList(list);
    freeList(list);

    return 0;
}
