#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <vector>
#include <memory>
#include <iostream>

enum VisitingOrder { InOrder, PreOrder, PostOrder };


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
    VisitingOrder order;

public:
    BinaryTree(): root{nullptr}, order{VisitingOrder::InOrder} {}
    BinaryTree(T val, VisitingOrder order=VisitingOrder::InOrder): root(std::make_unique<Node>(val)), order{order} {}

    BinaryTree(const BinaryTree& other): root{nullptr}, order{VisitingOrder::InOrder} {
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
        order = other.order;
    }

    BinaryTree& operator=(BinaryTree const& other){
        if(this == &other){
            return *this;
        }
        return BinaryTree(other);
    }

    BinaryTree (BinaryTree&& other) {
        std::swap(root, other.root);
        std::swap(order, other.order);
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

    bool contains(T const& val) {
        if(root == nullptr) {
            return false;
        }

        Node* curr = root.get();
        while(curr != nullptr) {
            if(curr->value == val) return true;
            curr = curr->value > val ? curr->left.get() : curr->right.get();
        }
        return false;
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

    void setOrder(VisitingOrder newOrder) {
        order = newOrder;
    }

    std::string print() const {
        if(root == nullptr) return "";
        switch(order){
        case VisitingOrder::InOrder:
            return recursiveInOrder(root.get());
        case VisitingOrder::PreOrder:
            return recursivePreOrder(root.get());
        case VisitingOrder::PostOrder:
            return recursivePostOrder(root.get());
        }
        throw std::invalid_argument("Order value invalid " + std::to_string(order));
    }

private:
    std::string recursiveInOrder(Node const* node) const {
        if(node == nullptr) return "";
        std::string retVal{" "};
        retVal += std::to_string(node->value);
        retVal += recursiveInOrder(node->left.get());
        retVal += recursiveInOrder(node->right.get());
        return retVal;
    }

    std::string recursivePreOrder(Node const* node) const {
        if(node == nullptr) return "";
        std::string retVal{recursivePreOrder(node->left.get())};
        retVal += " " + std::to_string(node->value);
        retVal += recursivePreOrder(node->right.get());
        return retVal;
    }

    std::string recursivePostOrder(Node const* node) const {
        if(node == nullptr) return "";
        std::string retVal{recursivePostOrder(node->left.get())};
        retVal += recursivePostOrder(node->right.get());
        retVal += " " + std::to_string(node->value);
        return retVal;
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& bt) {
    os << "[" << bt.print() << " ]";
    return os;
}

#endif // BINARYTREE_HPP
