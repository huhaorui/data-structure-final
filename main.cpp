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
        cout << name << password << endl;
        root->addUser(name, password);
    }
    infile.close();
}

int main() {
    auto *tree = new AvlTree;
    readFile(tree);
    tree->print();
}