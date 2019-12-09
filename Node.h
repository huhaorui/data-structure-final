//
// Created by HHR on 2019/11/27.
//

#ifndef DATA_STRUCTURE_FINAL_NODE_H
#define DATA_STRUCTURE_FINAL_NODE_H

#include <iostream>
#include <utility>

using namespace std;

class Node {
public:

    Node(string &, string &);

    Node *left = nullptr;
    Node *right = nullptr;

    string getName() {
        return name;
    }

    string getPassword() {
        return password;
    }

    int getHeight() {
        return height;
    }


    void setHeight(int);

    void setName(basic_string<char> _name) {
        name = std::move(_name);
    }

    void setPassword(basic_string<char> _password) {
        password = std::move(_password);
    }

private:
    string name;
    string password;
    int height;//节点高度
};


#endif //DATA_STRUCTURE_FINAL_NODE_H
