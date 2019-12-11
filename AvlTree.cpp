//
// Created by HHR on 2019/11/27.
//

#include "AvlTree.h"
#include "ShadowTreeNode.h"
#include <queue>
#include <fstream>

void AvlTree::save(Node *tree)        //用递归方式保存信息到数据库文件
{
    if (tree == nullptr)
        return;
    fstream out;
    if (tree == root) out.open("database.dat", ios::out);
    else out.open("database.dat", ios::out | ios::app);
    out << tree->getName() << " " << tree->getPassword() << endl;
    out.close();
    save(tree->left);
    save(tree->right);
}

void AvlTree::addUser(string &name, string &password) {
    if (SearchNode(name, root) != nullptr) return;
    root = addNode(root, name, password);
}

void AvlTree::removeUser(string &name) {
    root = remove(root, name);
}

Node *AvlTree::addNode(Node *pNode, string &name, string &password) {
    if (pNode == nullptr) { //树为空的情况
        pNode = new Node(name, password);
        return pNode;
    } else if (name < pNode->getName()) {//要插入左边
        pNode->left = addNode(pNode->left, name, password);
        if (getHeight(pNode->left) - getHeight(pNode->right) == 2) {
            if (name < pNode->left->getName()) {
                pNode = RightSpin(pNode);
            } else {
                pNode->left = LeftSpin(pNode->left);
                pNode = RightSpin(pNode);
            }
        }
    } else {
        pNode->right = addNode(pNode->right, name, password);
        if (getHeight(pNode->right) - getHeight(pNode->left) == 2) {
            if (name > pNode->right->getName()) {
                pNode = LeftSpin(pNode);
            } else {
                pNode->right = RightSpin(pNode->right);
                pNode = LeftSpin(pNode);
            }
        }
    }
    pNode->setHeight(max(getHeight(pNode->left), getHeight(pNode->right)) + 1);
    return pNode;
}

Node *AvlTree::SearchNode(const string &name, Node *root) {
    if (root == nullptr) return nullptr;
    if (root->getName() == name) {
        return root;
    } else if (root->getName() > name) {
        return SearchNode(name, root->left);
    } else {
        return SearchNode(name, root->right);
    }
}

Node *AvlTree::remove(Node *root, const string &name) {
    if (root == nullptr) return nullptr;
    if (name < root->getName()) {
        root->left = remove(root->left, name);
        if (getHeight(root->right) - getHeight(root->left) == 2) {
            Node *right = root->right;
            if (getHeight(right->left) > getHeight(right->right)) {
                root->right = RightSpin(root->right);
                root = LeftSpin(root);
            } else {
                root = LeftSpin(root);
            }
        }
    } else if (name > root->getName()) {
        root->right = remove(root->right, name);
        if (getHeight(root->left) - getHeight(root->right) == 2) {
            Node *left = root->left;
            if (getHeight(left->left) < getHeight(left->right)) {
                root->left = LeftSpin(root->left);
                root = RightSpin(root);
            } else {
                root = RightSpin(root);
            }
        }
    } else {//找到删除点
        if (root->left != nullptr && root->right != nullptr) {//两侧都存在
            if (getHeight(root->left) > getHeight(root->right)) {//如果左侧比较深
                Node *toRemove = maxNode(root->left);
                root->setName(toRemove->getName());
                root->setPassword(toRemove->getPassword());
                root->left = remove(root->left, toRemove->getName());
            } else {
                Node *toRemove = minNode(root->right);
                root->setName(toRemove->getName());
                root->setPassword(toRemove->getPassword());
                root->right = remove(root->right, toRemove->getName());
            }
        } else {
            Node *tmp = root;
            if (root->left != nullptr) {
                root = root->left;
            } else {
                root = root->right;
            }
            delete tmp;
        }
    }
    if (root != nullptr) {
        root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    }
    return root;
}

//TODO 删除节点
Node *AvlTree::maxNode(Node *root) {
    if (root->right != nullptr) {
        return maxNode(root->right);
    }
    return root;
}

Node *AvlTree::minNode(Node *root) {
    if (root->left != nullptr) {
        return maxNode(root->left);
    }
    return root;
}

void AvlTree::print() {
    if (root == nullptr) return;
    ShadowTreeNode *SRoot = nullptr;
    SRoot = STreeBuild(root, SRoot, 1);
    queue<ShadowTreeNode *> queue;
    queue.push(SRoot);
    int MaxRow = 1, MaxColumn = 0;
    int MaxLength = 6;
    while (!queue.empty()) {
        ShadowTreeNode *pShadowTreeNode = queue.front();
        queue.pop();
        if (pShadowTreeNode->row > MaxRow) {
            cout << endl;
            MaxRow = pShadowTreeNode->row;
            MaxColumn = 0;
        }
        string tmpName = pShadowTreeNode->name;
        if (tmpName.length() > MaxLength) {
            tmpName[MaxLength - 1] = '.';
        } else {
            for (int i = tmpName.length(); i < MaxLength; i++)
                tmpName.append(" ");
        }
        for (int i = 1; i < pShadowTreeNode->column - MaxColumn; i++) {
            for (int j = 0; j < MaxLength; j++) cout << ' ';
        }
        for (int i = 0; i < MaxLength; i++) {
            cout << tmpName[i];
        }
        MaxColumn = pShadowTreeNode->column;
        if (pShadowTreeNode->left != nullptr) queue.push(pShadowTreeNode->left);
        if (pShadowTreeNode->right != nullptr) queue.push(pShadowTreeNode->right);
    }
    cout << endl;
}

ShadowTreeNode *AvlTree::STreeBuild(Node *Tree, ShadowTreeNode *ShadowTree, int TreeRow) {
    if (Tree != nullptr) {
        static int TreeColumn;
        if (TreeRow == 1) {
            TreeColumn = 1;
        }
        ShadowTree = new ShadowTreeNode();
        ShadowTree->left = STreeBuild(Tree->left, ShadowTree->left, TreeRow + 1);
        ShadowTree->column = TreeColumn++;
        ShadowTree->row = TreeRow;
        ShadowTree->name = Tree->getName();
        ShadowTree->right = STreeBuild(Tree->right, ShadowTree->right, TreeRow + 1);
    }
    return ShadowTree;
}

Node *AvlTree::RightSpin(Node *root) {
    Node *left = root->left;
    root->left = left->right;
    left->right = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    left->setHeight(max(getHeight(left->left), getHeight(left->right)) + 1);
    return left;
}

Node *AvlTree::LeftSpin(Node *root) {
    Node *right = root->right;
    root->right = right->left;
    right->left = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    right->setHeight(max(getHeight(right->left), getHeight(right->right)) + 1);
    return right;
}