//
// Created by HHR on 2019/11/27.
//

#include "AvlTree.h"
#include "ShadowTreeNode.h"
#include <queue>

void AvlTree::addUser(string &name, string &password) {
    root = addNode(root, name, password);
}

Node *AvlTree::addNode(Node *pNode, string &name, string &password) {
    if (pNode == nullptr) { //树为空的情况
        pNode = new Node(name, password);
        return pNode;
    } else if (name < pNode->getName()) {//要插入左边
        pNode->left = addNode(pNode->left, name, password);
        if (getHeight(pNode->left) - getHeight(pNode->right) == 2) {
            if (name < pNode->left->getName()) {
                cout << "1.发生了右旋" << endl;
                pNode = RightSpin(pNode);
            } else {
                cout << "2.先左旋再右旋" << endl;
                pNode->left = LeftSpin(pNode->left);
                pNode = RightSpin(pNode);
            }
        }
    } else {
        pNode->right = addNode(pNode->right, name, password);
        if (getHeight(pNode->right) - getHeight(pNode->left) == 2) {
            if (name > pNode->right->getName()) {
                cout << "3.发生了左旋" << endl;
                pNode = LeftSpin(pNode);
            } else {
                cout << "4.先右旋再左旋" << endl;
                pNode->right = RightSpin(pNode->right);
                pNode = LeftSpin(pNode);
            }
        }
    }
    pNode->setHeight(max(getHeight(pNode->left), getHeight(pNode->right)) + 1);
    //TODO 旋转树
    return pNode;
}

void AvlTree::print() {
    if (root == nullptr) return;
    ShadowTreeNode *SRoot = nullptr;
    SRoot = STreeBuild(root, SRoot, 1);
    queue<ShadowTreeNode *> queue;
    queue.push(SRoot);
    int MaxRow = 1, MaxColumn = 0;
    int MaxLength = 6;
    while (!queue.empty()) {
        ShadowTreeNode *pShadowTreeNode = queue.front();
        queue.pop();
        if (pShadowTreeNode->row > MaxRow) {
            cout << endl;
            MaxRow = pShadowTreeNode->row;
            MaxColumn = 0;
        }
        string tmpName = pShadowTreeNode->name;
        if (tmpName.length() > MaxLength) {
            tmpName[MaxLength - 1] = '.';
        } else {
            for (int i = tmpName.length(); i < MaxLength; i++)
                tmpName[i] = ' ';
        }
        for (int i = 1; i < pShadowTreeNode->column - MaxColumn; i++) {
            for (int j = 0; j < MaxLength; j++) cout << ' ';
        }
        for (int i = 0; i < MaxLength; i++) {
            cout << tmpName[i];
        }
        MaxColumn = pShadowTreeNode->column;
        if (pShadowTreeNode->left != nullptr) queue.push(pShadowTreeNode->left);
        if (pShadowTreeNode->right != nullptr) queue.push(pShadowTreeNode->right);
    }
}

ShadowTreeNode *AvlTree::STreeBuild(Node *Tree, ShadowTreeNode *ShadowTree, int TreeRow) {
    if (Tree != nullptr) {
        static int TreeColumn;
        if (TreeRow == 1) {
            TreeColumn = 1;
        }
        ShadowTree = new ShadowTreeNode();
        ShadowTree->left = STreeBuild(Tree->left, ShadowTree->left, TreeRow + 1);
        ShadowTree->column = TreeColumn++;
        ShadowTree->row = TreeRow;
        ShadowTree->name = Tree->getName();
        ShadowTree->right = STreeBuild(Tree->right, ShadowTree->right, TreeRow + 1);
    }
    return ShadowTree;
}

Node *AvlTree::RightSpin(Node *root) {
    Node *left = root->left;
    root->left = left->right;
    left->right = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    left->setHeight(max(getHeight(left->left), getHeight(left->right)) + 1);
    return left;
}

Node *AvlTree::LeftSpin(Node *root) {
    Node *right = root->right;
    root->right = right->left;
    right->left = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    right->setHeight(max(getHeight(right->left), getHeight(right->right)) + 1);
    return right;
}