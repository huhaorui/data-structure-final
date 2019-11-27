//
// Created by HHR on 2019/11/27.
//

#ifndef DATA_STRUCTURE_FINAL_NODE_H
#define DATA_STRUCTURE_FINAL_NODE_H

#include <iostream>

using namespace std;

class Node {
public:
    Node(string &, string &);

    Node *left = nullptr;
    Node *right = nullptr;
    int height;//节点高度
    string getName() {
        return name;
    }

    string getPassword() {
        return password;
    }

private:
    string name;
    string password;
};


#endif //DATA_STRUCTURE_FINAL_NODE_H
