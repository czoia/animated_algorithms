#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <vector>
#include <memory>

template<class T>
struct TreeNode{
public:
    T value;
    std::unique_ptr<struct TreeNode> left;
    std::unique_ptr<struct TreeNode> right;

    TreeNode(T const& val): value{val}, left(nullptr), right(nullptr) {}
};

template<class T>
class BinaryTree
{
    typedef TreeNode<T> Node;
private:
    std::unique_ptr<Node> root;

public:
    BinaryTree(): root{nullptr} {}
    BinaryTree(T val): root(std::make_unique<Node>(val)) {}

    BinaryTree(const BinaryTree& other): root{nullptr} {
        std::vector<Node*> remaining;
        Node* curr = other.root.get();
        while(curr){
            insert(curr->value);
            if(curr->right){
                remaining.push_back(curr->right.get());
            }
            if(curr->left){
                curr = curr->left.get();
            } else if(remaining.empty()){
                break;
            } else {
                curr = remaining.back();
                remaining.pop_back();
            }
        }
    }

    BinaryTree& operator=(BinaryTree const& other){
        if(this == &other){
            return *this;
        }
        return BinaryTree(other);
    }

    BinaryTree (BinaryTree&& other) {
        std::swap(root, other.root);
    }

    void insert(T const& val){
        if(root == nullptr){
            root = std::make_unique<Node>(val);
            return;
        }
        Node* prev;
        Node* tmp = root.get();
        while(tmp != nullptr){
            if (val > tmp->value) {
                prev = tmp;
//                tmp = &(*tmp)->right;
                tmp = tmp->right.get();
            } else if(val < tmp->value) {
                prev = tmp;
//                tmp = &(*tmp)->left;
                tmp = tmp->left.get();
            }
        }
        if(prev->value > val){
            prev->left = std::make_unique<Node>(val);
        } else {
            prev->right = std::make_unique<Node>(val);
        }
    }

    BinaryTree& operator+=(const T& n){
        insert(n);
        return *this;
    }

    const T getRootValue() {
        return root.get()->value;
    }

    const Node* getRootLeft() const {
        return root->left.get();
    }

    const Node* getRootRight() const {
        return root->right.get();
    }
};

#endif // BINARYTREE_HPP
