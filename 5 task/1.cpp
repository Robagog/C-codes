#include <iostream>
#include <vector>

using namespace std;

class TSegmentTree {
private:
    vector<pair<int, int>> Tree;
    
public:
    TSegmentTree(int N)
        : Tree(4 * N)
    {}

    void BuildSegmentTree(const vector<int>& arr, int end, int node = 1, int start = 0) {
        if (start == end) {
            Tree[node] = make_pair(start + 1, arr[start]);
        } else {
            int mid = (start + end) / 2;
            BuildSegmentTree(arr, mid, 2 * node, start);
            BuildSegmentTree(arr, end, 2 * node + 1, mid + 1);
            if (Tree[2 * node].second > Tree[2 * node + 1].second) {
                Tree[node] = Tree[2 * node];
            } else {
                Tree[node] = Tree[2 * node + 1];
            }
        }
    }

    pair<int, int> FindMax(int left, int right, int end, int start = 1, int node = 1) const {
        if (start > right || end < left) {
            return make_pair(0,-1);
        }
        if (left <= start && end <= right) {
            return Tree[node];
        }
        int mid = (start + end) / 2;
        pair<int, int> leftMax = FindMax(left, right, mid, start, 2 * node);
        pair<int, int> rightMax = FindMax(left, right, end, mid + 1, 2 * node + 1);
        if (leftMax.second > rightMax.second) {
            return leftMax;
        } else {
            return rightMax;
        }
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    TSegmentTree tree(N);
    tree.BuildSegmentTree(arr, N - 1);
    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int left, right;
        cin >> left >> right;
        pair<int, int> maxElem = tree.FindMax(left, right, N);
        cout << maxElem.first << " ";
    }
    return 0;
}