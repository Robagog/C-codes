#include <iostream>
#include <vector>

using namespace std;

class TFenwickTree {
private:
    vector<uint64_t> Tree;
    
public:
    TFenwickTree(int N)
        : Tree(N)
    {}

    uint64_t FindSum(int left, int right) const {
        return Sum(right) - Sum(left - 1);
    }

    void Update(int idx, int value, int N) {
        while (idx < N) {
            Tree[idx] += value;
            idx = (idx | (idx + 1));
        }
    }

private:
    uint64_t Sum(int idx) const {
        uint64_t sum = 0;
        while (idx >= 0) {
            sum += Tree[idx];
            idx = (idx & (idx + 1)) - 1;
        }
        return sum;
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> arr(N);
    TFenwickTree tree(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        tree.Update(i, arr[i], N);
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        char c;
        cin >> c;
        if (c == 'u') {
            int pos, val;
            cin >> pos >> val;
            tree.Update(pos - 1, val - arr[pos - 1], N);
            arr[pos - 1] = val;
        } else if (c == 's') {
            int l, r;
            cin >> l >> r;
            cout << tree.FindSum(l - 1, r - 1) << " ";
        }
            
    }
    return 0;
}