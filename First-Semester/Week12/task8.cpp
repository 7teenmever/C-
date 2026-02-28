#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> twoSumBruteForce(vector<int>& nums, int target) {
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        for (int j = i + 1; j < static_cast<int>(nums.size()); j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

vector<int> twoSumOptimized(vector<int>& nums, int target) {
    unordered_map<int, int> indexByValue;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        int need = target - nums[i];
        if (indexByValue.count(need)) {
            return {indexByValue[need], i};
        }
        indexByValue[nums[i]] = i;
    }

    return {};
}

int findDuplicateNaive(vector<int>& nums) {
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        for (int j = i + 1; j < static_cast<int>(nums.size()); j++) {
            if (nums[i] == nums[j]) {
                return nums[i];
            }
        }
    }
    return -1;
}

int findDuplicateOptimized(vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) {
            return x;
        }
        seen.insert(x);
    }
    return -1;
}

bool isPermutationNaive(string s1, string s2) {
    if (s1.length() != s2.length()) {
        return false;
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
}

bool isPermutationOptimized(string s1, string s2) {
    if (s1.length() != s2.length()) {
        return false;
    }

    unordered_map<char, int> count;
    for (char c : s1) {
        ++count[c];
    }
    for (char c : s2) {
        auto it = count.find(c);
        if (it == count.end() || it->second == 0) {
            return false;
        }
        --(it->second);
    }

    return true;
}

void printComplexitySummary() {
    cout << "Complexity Summary:" << endl;
    cout << "twoSumBruteForce: Time O(n^2), Space O(1)" << endl;
    cout << "twoSumOptimized: Time O(n), Space O(n)" << endl;
    cout << "findDuplicateNaive: Time O(n^2), Space O(1)" << endl;
    cout << "findDuplicateOptimized: Time O(n), Space O(n)" << endl;
    cout << "isPermutationNaive: Time O(n log n), Space O(1) extra (ignoring sort internals)" << endl;
    cout << "isPermutationOptimized: Time O(n), Space O(k) where k is character set" << endl;
}

int main() {
    printComplexitySummary();

    vector<int> nums = {2, 7, 11, 15};
    vector<int> brute = twoSumBruteForce(nums, 9);
    vector<int> opt = twoSumOptimized(nums, 9);

    cout << "\nTwoSum brute indices: ";
    if (brute.size() == 2) {
        cout << brute[0] << ", " << brute[1] << endl;
    } else {
        cout << "none" << endl;
    }

    cout << "TwoSum optimized indices: ";
    if (opt.size() == 2) {
        cout << opt[0] << ", " << opt[1] << endl;
    } else {
        cout << "none" << endl;
    }

    vector<int> dup = {1, 3, 4, 2, 2};
    cout << "Find duplicate naive: " << findDuplicateNaive(dup) << endl;
    cout << "Find duplicate optimized: " << findDuplicateOptimized(dup) << endl;

    string s1 = "listen", s2 = "silent";
    cout << boolalpha;
    cout << "Permutation naive: " << isPermutationNaive(s1, s2) << endl;
    cout << "Permutation optimized: " << isPermutationOptimized(s1, s2) << endl;

    return 0;
}
