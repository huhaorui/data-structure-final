//
// Created by HHR on 2019/11/30.
//

#ifndef DATA_STRUCTURE_FINAL_SHADOWTREENODE_H
#define DATA_STRUCTURE_FINAL_SHADOWTREENODE_H

#include <iostream>

using namespace std;

class ShadowTreeNode {
public:
    ShadowTreeNode() {
        left = nullptr;
        right = nullptr;
        name = "";
    }

    int row{};
    int column{};
    string name;
    ShadowTreeNode *left;
    ShadowTreeNode *right;
};


#endif //DATA_STRUCTURE_FINAL_SHADOWTREENODE_H
