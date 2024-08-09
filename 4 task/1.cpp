#include <iostream>
#include <memory>

using namespace std;

struct Node {
public:
    int Value;
    unique_ptr<Node> Left;
    unique_ptr<Node> Right;

    Node(int value) 
        : Value(value)
        , Left(nullptr)
        , Right(nullptr)
    {}
};

class TBinarySearchTree {
private:
    unique_ptr<Node> Root;

public:
    TBinarySearchTree()
        : Root(nullptr)
    {}

    void Insert(int value) {
        if (Root == nullptr) {
            Root = make_unique<Node>(value);
        } else {
            InsertRecursive(Root, value);
        }
    }

    int Height() const {
        return HeightRecursive(Root);
    }

private:
    int HeightRecursive(const unique_ptr<Node>& node) const {
        if (node == nullptr) {
            return 0;
        } else {
            int leftHeight = HeightRecursive(node->Left);
            int rightHeight = HeightRecursive(node->Right);
            return max(leftHeight, rightHeight) + 1;
        }
    }
    
    void InsertRecursive(unique_ptr<Node>& node, int value) {
        if (value < node->Value) {
            if (node->Left == nullptr) {
                node->Left = make_unique<Node>(value);
            } else {
                InsertRecursive(node->Left, value);
            }
        } else if (value > node->Value) {
            if (node->Right == nullptr) {
                node->Right = make_unique<Node>(value);
            } else {
                InsertRecursive(node->Right, value);
            }
        }
    }
};

int main() {
    TBinarySearchTree tree;
    int num;
    while (true) {
        cin >> num;
        if (num == 0) {
            break;
        }
        tree.Insert(num);
    }
    cout << tree.Height();
    return 0;
}