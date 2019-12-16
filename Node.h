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
        //std::move为C++11标准新增加的功能，可以在传输string类型遍历时，避免不必要的析构操作，提高代码效率
        //https://www.cnblogs.com/SZxiaochun/p/8017349.html
    }

    void setPassword(basic_string<char> _password) {
        password = std::move(_password);
        //std::move为C++11标准新增加的功能，可以在传输string类型遍历时，避免不必要的析构操作，提高代码效率
        //https://www.cnblogs.com/SZxiaochun/p/8017349.html
    }

private:
    string name;
    string password;
    int height;//节点高度
};

#endif //DATA_STRUCTURE_FINAL_NODE_H