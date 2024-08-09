#include <iostream>
#include <vector>

using namespace std;

class TSegmentTree {
private:
    vector<uint64_t> Tree;
    
public:
    TSegmentTree(int N)
        : Tree(4 * N)
    {}

    void BuildSegmentTree(const vector<int>& arr, int end, int node = 1, int start = 0) {
        if (start == end) {
            Tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            BuildSegmentTree(arr, mid, 2 * node, start);
            BuildSegmentTree(arr, end, 2 * node + 1, mid + 1);
            Tree[node] = Tree[2 * node + 1] + Tree[2 * node];
        }
    }

    uint64_t FindSum(int left, int right, int end, int start = 1, int node = 1) const {
        if (start > right || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return Tree[node];
        }
        int mid = (start + end) / 2;
        uint64_t leftSum = FindSum(left, right, mid, start, 2 * node);
        uint64_t rightSum = FindSum(left, right, end, mid + 1, 2 * node + 1);
        return leftSum + rightSum;
    }

    void Replace(int pose, int value, int end, int start = 1, int node = 1) {
        if (start == end) {
            Tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (pose <= mid) {
                Replace(pose, value, mid, start, 2 * node);
            } else {
                Replace(pose, value, end, mid + 1,  2 * node + 1);
            }
            Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
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
    int M;
    cin >> M;
    for (int i = 1; i <= M; i++) {
        char c;
        cin >> c;
        if (c == 'u') {
            int pos, val;
            cin >> pos >> val;
            tree.Replace(pos, val, N);
        } else if (c == 's') {
            int l, r;
            cin >> l >> r;
            cout << tree.FindSum(l, r, N) << " ";
        }
            
    }
    return 0;
}