#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

char firstNonRepeatingChar(const string& s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        ++freq[c];
    }

    for (char c : s) {
        if (freq[c] == 1) {
            return c;
        }
    }

    return '\0';
}

bool areArraysEqual(vector<int>& arr1, vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    unordered_map<int, int> count;
    for (int x : arr1) {
        ++count[x];
    }

    for (int x : arr2) {
        auto it = count.find(x);
        if (it == count.end() || it->second == 0) {
            return false;
        }
        --(it->second);
    }

    return true;
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> resultSet;

    for (int x : nums2) {
        if (set1.count(x)) {
            resultSet.insert(x);
        }
    }

    return vector<int>(resultSet.begin(), resultSet.end());
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& entry : groups) {
        result.push_back(entry.second);
    }

    return result;
}

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> set(nums.begin(), nums.end());
    int best = 0;

    for (int x : set) {
        if (!set.count(x - 1)) {
            int current = x;
            int length = 1;

            while (set.count(current + 1)) {
                ++current;
                ++length;
            }
            best = max(best, length);
        }
    }

    return best;
}

int main() {
    string s = "swiss";
    char c = firstNonRepeatingChar(s);
    cout << "First non-repeating in '" << s << "': "
         << (c == '\0' ? string("none") : string(1, c)) << endl;

    vector<int> a1 = {1, 2, 2, 3};
    vector<int> a2 = {2, 1, 3, 2};
    cout << "Arrays equal (any order): " << (areArraysEqual(a1, a2) ? "Yes" : "No") << endl;

    vector<int> n1 = {1, 2, 2, 1};
    vector<int> n2 = {2, 2};
    vector<int> inter = intersection(n1, n2);
    cout << "Intersection: ";
    for (int x : inter) {
        cout << x << " ";
    }
    cout << endl;

    vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> groups = groupAnagrams(words);
    cout << "Grouped anagrams:" << endl;
    for (const auto& g : groups) {
        for (const string& w : g) {
            cout << w << " ";
        }
        cout << endl;
    }

    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << "Longest consecutive sequence length: " << longestConsecutive(nums) << endl;

    return 0;
}
