#include <iostream>
#include <vector>
#include <tuple>

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

vector<tuple<int, int, int>> FillGrid(int n, int m, const vector<vector<int>>& grid) {
    TDisjointSetUnion set(n * m);
    int numComponents = n * m;
    auto ConnectSets = [&set, &numComponents](int a, int b) {
        if (set.FindSet(a) != set.FindSet(b)) {
            set.UnionSets(a, b);
            --numComponents;
        }
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            
            if (grid[i][j] == 1) {
                ConnectSets(j + m * i, j + m * (i + 1));
            } else if (grid[i][j] == 2) {
                ConnectSets(j + m * i, (j + 1) + m * i);
            } else if (grid[i][j] == 3) {
                ConnectSets(j + m * i, j + m * (i + 1));
                ConnectSets(j + m * i, (j + 1) + m * i);
            }
        }
    }
    vector<tuple<int, int, int>> way;
    auto AddBridge = [&m, &way, &set, &numComponents](int a, int b, int weight) {
        if (set.FindSet(a) != set.FindSet(b)) {
            set.UnionSets(a, b);
            --numComponents;
            way.push_back({a / m, a % m, weight});
        }
    };
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            AddBridge(j + m * i, j + m * (i + 1), 1);
            if (numComponents == 1) {
                return way;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            AddBridge(j + m * i, (j + 1) + m * i, 2);
            if (numComponents == 1) {
                return way;
            }
        }
    }
    return {};
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid;
    grid.resize(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    vector<tuple<int, int, int>> way = FillGrid(n, m, grid);
    int sum = 0;
    for (const auto& i : way) {
        sum += get<2>(i);
    }
    cout << way.size() << " " << sum << endl;
    for (const auto& i : way) {
        cout << get<0>(i) + 1 << " " << get<1>(i) + 1 << " " << get<2>(i) << endl;
    }
    return 0;
}