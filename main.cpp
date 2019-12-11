//
// Created by HHR on 2019/11/27.
//

#include <iostream>
#include <fstream>
#include "AvlTree.h"

using namespace std;

void readFile(AvlTree *root) {
    string name, password;
    ifstream infile;
    infile.open("database.dat", ios::in);
    while (infile >> name >> password) {
        root->addUser(name, password);
    }
    infile.close();
}

void PasswordReset(Node *user) {
    string password;
    cout << "请输入原密码";
    cin >> password;
    if (password != user->getPassword()) {
        cout << "密码错误" << endl;
        return;
    }
    cout << "请输入新密码";
    cin >> password;
    user->setPassword(password);
    cout << "成功";
}

void AddUser(AvlTree *tree) {
    string name, password;
    cout << "请输入姓名和密码" << endl;
    cin >> name >> password;
    tree->addUser(name, password);
    cout << "创建成功" << endl;
    tree->print();
}

void DeleteUser(AvlTree *tree) {
    string name;
    cout << "请输入姓名" << endl;
    cin >> name;
    tree->removeUser(name);
    tree->print();
}

void adminView(AvlTree *tree) {
    while (true) {
        cout << "你好,admin" << endl;
        cout << "1.正向打印树" << endl;
        cout << "2.添加节点" << endl;
        cout << "3.删除用户" << endl;
        cout << "4.退出" << endl;
        char op;
        cin >> op;
        switch (op) {
            case '1':
                tree->print();
                break;
            case '2':
                AddUser(tree);
                break;
            case '3':
                DeleteUser(tree);
                break;
            case '4':
                exit(0);
            default:
                cout << "错误" << endl;
        }
    }
}

void userView(Node *user) {
    cout << "你好," << user->getName() << endl;
    cout << "1.修改密码" << endl;
    cout << "2.退出" << endl;
    char op;
    cin >> op;
    if (op == '1') {
        PasswordReset(user);
    } else {
        cout << "再见" << endl;
        exit(0);
    }
}

void loginSuccessful(Node *user, AvlTree *tree) {
    if (user->getName() == "admin") {
        adminView(tree);
    } else {
        userView(user);
    }
}

void login(AvlTree *tree) {
    string name, password;
    cout << "请输入账号:";
    cin >> name;
    Node *user = AvlTree::SearchNode(name, tree->root);
    if (user == nullptr) {
        cout << "用户不存在" << endl;
        return;
    }
    cout << "请输入密码:";
    cin >> password;
    if (user->getPassword() == password) {
        cout << "登陆成功" << endl;
        loginSuccessful(user, tree);
    } else {
        cout << "密码错误" << endl;
    }
}

bool menu(AvlTree *tree) {
    char op;
    cout << "1.登陆" << endl;
    cout << "2.退出" << endl;
    cin >> op;
    system("cls");
    switch (op) {
        case '1':
            login(tree);
        case '2':
            return false;
        default:
            cout << "错误" << endl;
            system("pause");
    }
    return true;
}

int main() {
    auto *tree = new AvlTree;
    readFile(tree);
    tree->print();
    system("pause");
    while (menu(tree)) {
    }
}
