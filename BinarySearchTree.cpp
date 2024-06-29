//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jannatul Ferdush
// Date        : 6.09.2024
//============================================================================
#include <iostream>
#include <string>
#include "Bid.h" // Assume this file contains the definition of the Bid structure

using namespace std;

// Node structure for the binary search tree
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    Node() : left(nullptr), right(nullptr) {}
    Node(Bid aBid) : bid(aBid), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class definition
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Bid bid);
    Node* removeNode(Node* node, string bidId);
    Node* minValueNode(Node* node);
    Node* searchNode(Node* node, string bidId);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    void InOrder();
};

// Constructor
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    // Code to recursively delete nodes to free memory can be added here
}

void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        addNode(root, bid);
    }
}

void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (bid.bidId < node->bid.bidId) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            addNode(node->left, bid);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::Remove(string bidId) {
    root = removeNode(root, bidId);
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }

    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = minValueNode(node->right);
        node->bid = temp->bid;
        node->right = removeNode(node->right, temp->bid.bidId);
    }
    return node;
}

Node* BinarySearchTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Bid BinarySearchTree::Search(string bidId) {
    Node* result = searchNode(root, bidId);
    if (result != nullptr) {
        return result->bid;
    }
    else {
        return Bid(); // return an empty bid if not found
    }
}

Node* BinarySearchTree::searchNode(Node* node, string bidId) {
    if (node == nullptr || node->bid.bidId == bidId) {
        return node;
    }

    if (bidId < node->bid.bidId) {
        return searchNode(node->left, bidId);
    }
    else {
        return searchNode(node->right, bidId);
    }
}

void BinarySearchTree::InOrder() {
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    inOrder(node->left);
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
    inOrder(node->right);
}
