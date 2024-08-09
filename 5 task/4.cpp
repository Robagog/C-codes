#include <iostream>
#include <memory>
#include <random>
 
struct Node {
    uint32_t Key;
    int Priority;
    std::shared_ptr<Node> Left;
    std::shared_ptr<Node> Right;
 
    Node(uint32_t key)
        : Key(key)
        , Priority(rand())
        , Left(nullptr)
        , Right(nullptr)
    {}
};
 
using Node_ptr = std::shared_ptr<Node>;
 
Node_ptr merge(Node_ptr left, Node_ptr right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->Priority > right->Priority) {
        left->Right = merge(left->Right, right);
        return left;
    } else {
        right->Left = merge(left, right->Left);
        return right;
    }
}
 
void split(Node_ptr root, uint32_t key, Node_ptr &left, Node_ptr &right) {
    if (root == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }
    if (key > root->Key) {
        split(root->Right, key, root->Right, right);
        left = root;
    } else {
        split(root->Left, key, left, root->Left);
        right = root;
    }
}
 
void insert(Node_ptr &root, Node_ptr node) {
    if (root == nullptr) {
        root = node;
        return;
    }
    if (node->Priority > root->Priority) {
        split(root, node->Key, node->Left, node->Right);
        root = node;
    } else {
        if (node->Key < root->Key) {
            insert(root->Left, node);
        } else {
            insert(root->Right, node);
        }
    }
}
 
int32_t findPrevMin(Node_ptr root, uint32_t key) {
    if (root == nullptr) return -1;
 
    if (root->Key >= key) {
        int32_t leftResult = findPrevMin(root->Left, key);
        if (leftResult == -1) {
            return root->Key;
        } else {
            return leftResult;
        }
    }
    return findPrevMin(root->Right, key);
}
 
class Treap {
private:
    Node_ptr Root;
    uint32_t LastQueryResult;
 
public:
    Treap()
        : Root()
        , LastQueryResult(0)
    {}
 
    void Add(int32_t key) {
        key = (key + LastQueryResult) % 1000000000;
        if (Root == nullptr || findPrevMin(Root, key) != key) {
            insert(Root, std::make_shared<Node>(key));
        }
        LastQueryResult = 0;
 
    }
 
    uint32_t Next(uint32_t key) {
        LastQueryResult = findPrevMin(Root, key);
        return LastQueryResult;
    }
};
 
int main() {
    Treap treap;
    int cnt, n;
    std::vector<int> package;
    char c;
    std::cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        std::cin >> c >> n;
        if (c == '+') {
            treap.Add(n);
        } else {
            package.push_back(treap.Next(n));
        }
    }
    for (int i : package) {
       std::cout << i << std::endl;
    }
    return 0;
}