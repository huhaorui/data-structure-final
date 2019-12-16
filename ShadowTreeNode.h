//
// Created by HHR on 2019/11/30.
//

#ifndef DATA_STRUCTURE_FINAL_SHADOWTREENODE_H
#define DATA_STRUCTURE_FINAL_SHADOWTREENODE_H

#include <iostream>

using namespace std;

class ShadowTreeNode {
public:
    int row = 0;
    int column = 0;
    string name = "";
    ShadowTreeNode *left = nullptr;
    ShadowTreeNode *right = nullptr;
};


#endif //DATA_STRUCTURE_FINAL_SHADOWTREENODE_H
