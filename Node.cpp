//
// Created by HHR on 2019/11/27.
//

#include "Node.h"

Node::Node(string &name, string &password) {
    this->name = name;
    this->password = password;
    height = 0;
}

void Node::setHeight(int i) {
    this->height = i;
}
