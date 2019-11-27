//
// Created by HHR on 2019/11/27.
//

#ifndef DATA_STRUCTURE_FINAL_AVLTREE_H
#define DATA_STRUCTURE_FINAL_AVLTREE_H


#include "Node.h"

class AvlTree {
public:
    Node *root;

    AvlTree() {
        root = nullptr;
    }

    void addUser(string &, string &);

    static Node *addNode(Node *, string &, string &);
};


#endif //DATA_STRUCTURE_FINAL_AVLTREE_H
