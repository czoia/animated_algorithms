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
                tmp = tmp->right.get();
            } else if(val < tmp->value) {
                prev = tmp;
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

    bool deleteElement(T const& val){
        if(root == nullptr) return false;
        return recursiveDelete(root, val);
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

    auto getItem(Node const* node, T const& val){
        if(node == nullptr) return nullptr;

        if(node->value < val) return getItem(node->left, val);
        else if(node->value > val) return getItem(node->right, val);
        return node;
    }

    bool recursiveDelete(std::unique_ptr<Node>& node, T const& val){
        /**
         * Delete of an element in a binary tree has three cases:
         * 1) node is a leaf -> just delete it
         * 2) node with one child -> made the child the node
         * 3) node with two child -> swap the value with the lowest value of
         *    the right child and then delete the node as per 1,2
        */

        if(node == nullptr) return false;

        if(node->value == val){
            if(node->left != nullptr && node->right != nullptr){
                // third case,
                // find the leftmost descendant in the right subtree
                Node* parent = node.get();
                Node* leftmost = node->right.get();
                while(leftmost->left != nullptr){
                    parent = leftmost;
                    leftmost = leftmost->left.get();
                }
                node->value = leftmost->value;
                removeNode(node->right);
                return true;
            } else {
                removeNode(node);
                return true;
            }
        }
        // else
        return val < node->value ? recursiveDelete(node->left, val)
                                 : recursiveDelete(node->right, val);
    }

    void removeNode(std::unique_ptr<Node>& node){
        /**
         * Auxiliary function for removing a node.
         * This function cover the first and second case of a node delation:
         * node is a leaf or has only one child.
         * Note that in case of leaf, doesn't really matter which node we pick
         * up, will be always null.
         * So, if the situation is something like:
         *      5
         *   4     8
         * 1          9
         *  and we need to delete 8, the firt condition is met, and the right
         *  node is taken.
         *  If we want to delete a leaf (e.g. 9), then again, the first
         *  condition is met and right will be assign to node (in this case,
         *  with value null).
         *  In case we want to delete 4, the first consition fails, so we left
         *  node (1) will be substitute to 4.
        */
        if(node->left == nullptr){
            // second case, one child. Make the child the parent
            node = std::move(node->right);
        } else {
            // second case and first case.
            node = std::move(node->left);
        }
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& bt) {
    os << "[" << bt.print() << " ]";
    return os;
}

#endif // BINARYTREE_HPP
