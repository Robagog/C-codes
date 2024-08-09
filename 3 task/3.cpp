#include <iostream>
#include <vector>


using namespace std;

class TDisjointSetUnion {
private:
    mutable vector<int> Parent;
    vector<int> Rank;

public:
    TDisjointSetUnion(int n) 
        : Parent(n)
        , Rank(n, 0)
    {
        for (int i = 0; i < n; ++i) {
             Parent[i] = i;
        }
    }

    int FindSet(int v) const {
        if (v != Parent[v]) {
            Parent[v] = FindSet(Parent[v]);
        }
        return Parent[v];
    }

    void UnionSets(int a, int b) {
        a = FindSet(a);
        b = FindSet(b);
        if (a != b) {
            if (Rank[a] < Rank[b]) {
                swap(a, b);
            }  
            Parent[b] = a;
            if (Rank[a] == Rank[b]) {
                ++Rank[a];
            } 
        }
    }
};

int FindMinimumBridges(int n, const vector<pair<int, int>>& bridges) {
    TDisjointSetUnion set(n);
    int numComponents = n;
    int num = 0;
    for (const auto& bridge : bridges) {
        if (set.FindSet(bridge.first) != set.FindSet(bridge.second)) {
            set.UnionSets(bridge.first, bridge.second);
            numComponents--;
            if (numComponents == 1) {
                 return num + 1;
            }
        }
        ++num;
    }

    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> bridges;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        bridges.emplace_back(x, y);
    }
    cout << FindMinimumBridges(n, bridges);
    return 0;
}