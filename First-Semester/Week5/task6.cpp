#include <cstring>
#include <iostream>
using namespace std;

// Create an array of pointers to strings and implement:
// 1. Sorting strings alphabetically
// 2. Finding the longest string
// 3. Concatenating all strings

void stringArrayOperations(const char *strings[], int count) {
    if (count <= 0) {
        cout << "No strings provided." << endl;
        return;
    }

    const char **sorted = new const char *[count];
    for (int i = 0; i < count; ++i) {
        sorted[i] = strings[i];
    }

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                const char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    cout << "Sorted strings alphabetically: ";
    for (int i = 0; i < count; ++i) {
        cout << sorted[i];
        if (i < count - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    const char *longest = strings[0];
    for (int i = 1; i < count; ++i) {
        if (strlen(strings[i]) > strlen(longest)) {
            longest = strings[i];
        }
    }
    cout << "Longest string: " << longest << endl;

    int totalLength = 0;
    for (int i = 0; i < count; ++i) {
        totalLength += strlen(strings[i]);
        if (i < count - 1) {
            totalLength += 1;
        }
    }

    char *concatenated = new char[totalLength + 1];
    concatenated[0] = '\0';

    for (int i = 0; i < count; ++i) {
        strcat(concatenated, strings[i]);
        if (i < count - 1) {
            strcat(concatenated, " ");
        }
    }

    cout << "Concatenated string: " << concatenated << endl;

    delete[] sorted;
    delete[] concatenated;
}

int main() {
    const char *words[] = {"apple", "zebra", "computer", "book", "programming"};
    int count = 5;

    stringArrayOperations(words, count);
    return 0;
}
