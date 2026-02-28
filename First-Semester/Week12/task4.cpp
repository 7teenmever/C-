#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class SimpleHashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<list<pair<int, string>>> table;

    int hashFunction(int key) const {
        int idx = key % TABLE_SIZE;
        return idx < 0 ? idx + TABLE_SIZE : idx;
    }

public:
    SimpleHashTable() : table(TABLE_SIZE) {}

    void insert(int key, const string& value) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    string get(int key) {
        int index = hashFunction(key);
        for (const auto& entry : table[index]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return "";
    }

    bool remove(int key) {
        int index = hashFunction(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }

    bool contains(int key) {
        return !get(key).empty();
    }

    void printState() {
        cout << "Current table entries:" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (!table[i].empty()) {
                cout << "Bucket " << i << ": ";
                for (const auto& entry : table[i]) {
                    cout << "(" << entry.first << "," << entry.second << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    SimpleHashTable ht;

    ht.insert(1, "Alice");
    ht.insert(101, "Bob");   // collision with 1 when TABLE_SIZE=100
    ht.insert(55, "Charlie");

    cout << "Get 1: " << ht.get(1) << endl;
    cout << "Get 101: " << ht.get(101) << endl;
    cout << "Contains 55: " << (ht.contains(55) ? "Yes" : "No") << endl;

    ht.insert(1, "AliceUpdated");
    cout << "Get 1 after update: " << ht.get(1) << endl;

    cout << "Remove 101: " << (ht.remove(101) ? "Removed" : "Not found") << endl;
    cout << "Contains 101: " << (ht.contains(101) ? "Yes" : "No") << endl;

    ht.printState();
    return 0;
}
