#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> findDuplicates(vector<int>& nums) {
    unordered_set<int> seen;
    vector<int> duplicates;

    for (int num : nums) {
        if (seen.count(num)) {
            duplicates.push_back(num);
        } else {
            seen.insert(num);
        }
    }
    return duplicates;
}

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;

    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        int complement = target - nums[i];
        if (numToIndex.find(complement) != numToIndex.end()) {
            return {numToIndex[complement], i};
        }
        numToIndex[nums[i]] = i;
    }
    return {};
}

void rotateMatrix(vector<vector<int>>& matrix) {
    int n = static_cast<int>(matrix.size());

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void printComplexityNotes() {
    cout << "Complexity Notes:" << endl;
    cout << "findDuplicates: Time O(n), Space O(n)" << endl;
    cout << "twoSum (hash map): Time O(n), Space O(n)" << endl;
    cout << "rotateMatrix (in-place): Time O(n^2), Space O(1)" << endl;
}

int main() {
    printComplexityNotes();

    vector<int> nums = {1, 3, 2, 3, 4, 1, 5};
    vector<int> dup = findDuplicates(nums);
    cout << "\nDuplicates: ";
    for (int x : dup) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> nums2 = {2, 7, 11, 15};
    vector<int> ans = twoSum(nums2, 9);
    cout << "Two sum indices for target 9: ";
    if (ans.size() == 2) {
        cout << ans[0] << ", " << ans[1] << endl;
    } else {
        cout << "not found" << endl;
    }

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "\nMatrix before rotation:" << endl;
    printMatrix(matrix);

    rotateMatrix(matrix);
    cout << "Matrix after rotation:" << endl;
    printMatrix(matrix);

    return 0;
}
