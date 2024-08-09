#include <iostream>
#include <vector>
#include <list>

using namespace std;

class TSetOfStrings {
private:
    const int TableSize = 1000003;
    vector<list<string>> HashTable;

public:
    TSetOfStrings()
        : HashTable(TableSize)
    {}

    void AddString(const string& str) {
        int hash = HashFunction(str);
        HashTable[hash].push_back(str);
    }

    void RemoveString(const string& str) {
        int hash = HashFunction(str);
        HashTable[hash].remove(str);
    }

    bool IsInSet(const string& str) const {
        int hash = HashFunction(str);
        for (const auto& s : HashTable[hash]) {
            if (s == str) {
                return true;
            }
        }
        return false;
    }

private:
    int HashFunction(const string& str) const {
        int hash = 0;
        int p = 31;
        int pow = 1;
        for (const auto& c : str) {
            hash = (hash + (c - 'a' + 1) * pow) % TableSize;
            pow = (pow * p) % TableSize;
        }
        return hash;
    }
    
};

int main() {
    TSetOfStrings setOfStrings;
    string op;
    while (cin >> op) {
        if (op == "#")
            break;
        string str;
        cin >> str;
        if (op == "+") {
            setOfStrings.AddString(str);
        } else if (op == "-") {
            setOfStrings.RemoveString(str);
        } else if (op == "?") {
            if (setOfStrings.IsInSet(str)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}