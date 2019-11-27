//
// Created by HHR on 2019/11/27.
//

#include "AvlTree.h"

void AvlTree::addUser(string &name, string &password) {
    root = addNode(root, name, password);
}

Node *AvlTree::addNode(Node *pNode, string &name, string &password) {
    if (pNode == nullptr) { //树为空的情况
        pNode = new Node(name, password);
        return pNode;
    } else if (name < pNode->getName()) {//要插入左边
        pNode->left = addNode(pNode->left, name, password);
    } else {
        pNode->right = addNode(pNode->right, name, password);
    }
    //旋转树
    return pNode;
}