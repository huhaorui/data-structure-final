//
// Created by HHR on 2019/11/27.
//

#include <iostream>
#include <fstream>
#include "AvlTree.h"

using namespace std;

void GarbageCollecting(Node *root) {
    if (root->left) {
        GarbageCollecting(root->left);
    }
    if (root->right) {
        GarbageCollecting(root->right);
    }
    cout << "已释放：" << root->getName() << endl;
    delete root;
}

void readFile(AvlTree *root) {//从文件中读取Avl树的信息
    string name, password;
    ifstream infile;
    infile.open("database.dat", ios::in);
    while (infile >> name >> password) {
        root->addUser(name, password);
    }
    infile.close();
}

void SaveFile(AvlTree *root) {//将Avl树保存到文件
    root->save(root->root);
}

void PasswordReset(Node *user) {//修改密码功能
    string password;
    cout << "请输入原密码:";
    cin >> password;
    if (password != user->getPassword()) {
        cout << "密码错误" << endl;
        system("pause");
        return;
    }
    cout << "请输入新密码:";
    cin >> password;
    user->setPassword(password);
    cout << "成功" << endl;
    system("pause");
}

void AddUser(AvlTree *tree) {//添加用户功能
    string name, password;
    cout << "请输入姓名和密码:" << endl;
    cin >> name >> password;
    if (AvlTree::SearchNode(name, tree->root) != nullptr) {
        cout << "用户已存在" << endl;
        return;
    }
    tree->addUser(name, password);
    cout << "创建成功" << endl;
    tree->print();
}

void DeleteUser(AvlTree *tree) {//删除用户功能
    string name;
    cout << "请输入姓名" << endl;
    cin >> name;
    if (AvlTree::SearchNode(name, tree->root) == nullptr) {
        cout << "用户不存在" << endl;
        return;
    }
    if (name == "admin") {
        cout << "该用户不能被删除" << endl;
        return;
    }
    tree->removeUser(name);
    cout << "删除成功" << endl;
    tree->print();
}

void adminView(AvlTree *tree) {//管理员用户的界面
    while (true) {
        system("cls");
        cout << "你好,admin" << endl;
        cout << "1.正向打印树" << endl;
        cout << "2.添加用户" << endl;
        cout << "3.删除用户" << endl;
        cout << "4.退出" << endl;
        cout << "请选择你要进行的操作：";
        string op;
        cin >> op;
        switch (op[0]) {
            case '1':
                system("cls");
                tree->print();
                system("pause");
                break;
            case '2':
                system("cls");
                AddUser(tree);
                system("pause");
                break;
            case '3':
                system("cls");
                DeleteUser(tree);
                system("pause");
                break;
            case '4':
                break;
            default:
                cout << "错误" << endl;
        }
        if (op[0] == '4')break;
        SaveFile(tree);
    }
}

void userView(AvlTree *tree, Node *user) {//普通用户的界面
    while (true) {
        system("cls");
        cout << "你好," << user->getName() << endl;
        cout << "1.修改密码" << endl;
        cout << "2.退出" << endl;
        cout << "请选择你要进行的操作：";
        string op;
        cin >> op;
        if (op[0] == '1') {
            system("cls");
            PasswordReset(user);
            SaveFile(tree);
        } else if (op[0] == '2') {
            cout << "再见" << endl;
            break;
        }
    }
}

void loginSuccessful(AvlTree *tree, Node *user) {//登陆成功后，根据用户类别，跳转到对应的主界面
    if (user->getName() == "admin") {
        adminView(tree);
    } else {
        userView(tree, user);
    }
}

void login(AvlTree *tree) {//登陆界面
    string name, password;
    cout << "请输入账号:";
    cin >> name;
    Node *user = AvlTree::SearchNode(name, tree->root);
    if (user == nullptr) {
        cout << "用户不存在" << endl;
        system("pause");
        return;
    }
    cout << "请输入密码:";
    cin >> password;
    if (user->getPassword() == password) {
        cout << "登陆成功" << endl;
        loginSuccessful(tree, user);
    } else {
        cout << "密码错误" << endl;
        system("pause");
    }
}


int main() {
    auto *tree = new AvlTree;
    readFile(tree);
    while (true) {
        string op;
        system("cls");
        cout << "欢迎使用用户登陆管理系统" << endl;
        cout << "1.登陆" << endl;
        cout << "2.退出" << endl;
        cout << "请选择你要进行的操作：";
        cin >> op;
        system("cls");
        switch (op[0]) {
            case '1':
                login(tree);
                break;
            case '2':
                cout << "正在进行内存回收，请稍后\n";
                SaveFile(tree);
                GarbageCollecting(tree->root);
                exit(0);
            default:
                cout << "错误" << endl;
                system("pause");
        }
    }
}
