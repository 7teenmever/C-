#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;

    int sum = 0;
    int count = 0;

    for (int num : nums) {
        sum += num;
        if (prefixCount.count(sum - k)) {
            count += prefixCount[sum - k];
        }
        ++prefixCount[sum];
    }

    return count;
}

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> data;

public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        auto& vec = data[key];
        vec.push_back({timestamp, value});

        if (vec.size() >= 2 && vec[vec.size() - 2].first > vec.back().first) {
            sort(vec.begin(), vec.end());
        }
    }

    string get(string key, int timestamp) {
        auto it = data.find(key);
        if (it == data.end()) {
            return "";
        }

        const auto& vec = it->second;
        int left = 0;
        int right = static_cast<int>(vec.size()) - 1;
        int bestIndex = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (vec[mid].first <= timestamp) {
                bestIndex = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return bestIndex == -1 ? "" : vec[bestIndex].second;
    }
};

class Logger {
private:
    unordered_map<string, int> lastPrinted;

public:
    Logger() {}

    bool shouldPrintMessage(int timestamp, string message) {
        auto it = lastPrinted.find(message);
        if (it == lastPrinted.end() || timestamp - it->second >= 10) {
            lastPrinted[message] = timestamp;
            return true;
        }
        return false;
    }
};

int main() {
    vector<int> nums = {1, 1, 1};
    cout << "Subarrays with sum=2: " << subarraySum(nums, 2) << endl;

    TimeMap kv;
    kv.set("foo", "bar", 1);
    cout << "TimeMap get(foo,1): " << kv.get("foo", 1) << endl;
    cout << "TimeMap get(foo,3): " << kv.get("foo", 3) << endl;
    kv.set("foo", "bar2", 4);
    cout << "TimeMap get(foo,4): " << kv.get("foo", 4) << endl;
    cout << "TimeMap get(foo,5): " << kv.get("foo", 5) << endl;

    Logger logger;
    cout << boolalpha;
    cout << "Logger(1,foo): " << logger.shouldPrintMessage(1, "foo") << endl;
    cout << "Logger(2,bar): " << logger.shouldPrintMessage(2, "bar") << endl;
    cout << "Logger(3,foo): " << logger.shouldPrintMessage(3, "foo") << endl;
    cout << "Logger(11,foo): " << logger.shouldPrintMessage(11, "foo") << endl;

    return 0;
}
