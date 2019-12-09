//
// Created by HHR on 2019/11/27.
//

#ifndef DATA_STRUCTURE_FINAL_AVLTREE_H
#define DATA_STRUCTURE_FINAL_AVLTREE_H

#include "Node.h"
#include "ShadowTreeNode.h"

class AvlTree {
public:
    Node *root;

    AvlTree() {
        root = nullptr;
    }

    static int getHeight(Node *tree) {
        if (tree != nullptr) return tree->getHeight();
        return -1;
    }

    void addUser(string &, string &);

    void print();

    static Node *addNode(Node *, string &, string &);

    static ShadowTreeNode *STreeBuild(Node *, ShadowTreeNode *, int);

    static Node *LeftSpin(Node *);

    static Node *RightSpin(Node *root);
};

#endif //DATA_STRUCTURE_FINAL_AVLTREE_H
