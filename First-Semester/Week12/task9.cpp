#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> usage;  // front = most recent
    unordered_map<int, list<pair<int, int>>::iterator> pos;

public:
    explicit LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) {
            return -1;
        }

        usage.splice(usage.begin(), usage, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {
            it->second->second = value;
            usage.splice(usage.begin(), usage, it->second);
            return;
        }

        if (static_cast<int>(usage.size()) == capacity) {
            int oldKey = usage.back().first;
            usage.pop_back();
            pos.erase(oldKey);
        }

        usage.push_front({key, value});
        pos[key] = usage.begin();
    }
};

class AutoCompleteSystem {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        bool isWord = false;

        ~TrieNode() {
            for (auto& entry : children) {
                delete entry.second;
            }
        }
    };

    TrieNode* root;
    unordered_map<string, int> frequency;

    void insertToTrie(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isWord = true;
    }

    void collectWords(TrieNode* node, string& current, vector<string>& out) const {
        if (node == nullptr) {
            return;
        }
        if (node->isWord) {
            out.push_back(current);
        }
        for (const auto& entry : node->children) {
            current.push_back(entry.first);
            collectWords(entry.second, current, out);
            current.pop_back();
        }
    }

public:
    AutoCompleteSystem() : root(new TrieNode()) {}

    ~AutoCompleteSystem() {
        delete root;
    }

    void addWord(const string& word, int freq = 1) {
        insertToTrie(word);
        frequency[word] += freq;
    }

    vector<string> suggest(const string& prefix, int k) const {
        TrieNode* node = root;
        for (char c : prefix) {
            auto it = node->children.find(c);
            if (it == node->children.end()) {
                return {};
            }
            node = it->second;
        }

        vector<string> candidates;
        string current = prefix;
        collectWords(node, current, candidates);

        sort(candidates.begin(), candidates.end(), [&](const string& a, const string& b) {
            int fa = 0;
            int fb = 0;

            auto ita = frequency.find(a);
            if (ita != frequency.end()) {
                fa = ita->second;
            }

            auto itb = frequency.find(b);
            if (itb != frequency.end()) {
                fb = itb->second;
            }

            if (fa != fb) {
                return fa > fb;
            }
            return a < b;
        });

        if (static_cast<int>(candidates.size()) > k) {
            candidates.resize(k);
        }
        return candidates;
    }
};

class URLShortener {
private:
    unordered_map<string, string> shortToLong;
    unordered_map<string, string> longToShort;
    long long counter = 1;

    string encodeBase62(long long num) const {
        const string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (num == 0) {
            return "0";
        }

        string code;
        while (num > 0) {
            code.push_back(chars[num % 62]);
            num /= 62;
        }
        reverse(code.begin(), code.end());
        return code;
    }

public:
    string shorten(const string& longUrl) {
        auto it = longToShort.find(longUrl);
        if (it != longToShort.end()) {
            return it->second;
        }

        string code;
        do {
            code = encodeBase62(counter++);
        } while (shortToLong.count(code));

        shortToLong[code] = longUrl;
        longToShort[longUrl] = code;
        return code;
    }

    string restore(const string& code) const {
        auto it = shortToLong.find(code);
        if (it == shortToLong.end()) {
            return "";
        }
        return it->second;
    }
};

int main() {
    cout << "LRU Cache demo:" << endl;
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cout << "get(1) = " << cache.get(1) << endl;
    cache.put(3, 30);  // evicts key 2
    cout << "get(2) = " << cache.get(2) << endl;

    cout << "\nAutoComplete demo:" << endl;
    AutoCompleteSystem ac;
    ac.addWord("apple", 5);
    ac.addWord("app", 7);
    ac.addWord("apricot", 3);
    ac.addWord("apply", 4);

    vector<string> suggestions = ac.suggest("ap", 3);
    cout << "Top suggestions for 'ap': ";
    for (const string& s : suggestions) {
        cout << s << " ";
    }
    cout << endl;

    cout << "\nURL Shortener demo:" << endl;
    URLShortener shortener;
    string longUrl = "https://example.com/very/long/url";
    string code = shortener.shorten(longUrl);
    cout << "Short code: " << code << endl;
    cout << "Restored URL: " << shortener.restore(code) << endl;

    return 0;
}
