//
// Created by HHR on 2019/11/27.
//
#ifndef DATA_STRUCTURE_FINAL_AVLTREE_H
#define DATA_STRUCTURE_FINAL_AVLTREE_H

#include "Node.h"
#include "ShadowTreeNode.h"

class AvlTree {
public:
    Node *root;

    AvlTree() {//默认构造函数，初始化root指针，防止出现悬挂指针的现象
        root = nullptr;
    }

    static int getHeight(Node *tree) {//静态成员函数，用于获得树的高度
        if (tree != nullptr) return tree->getHeight();
        return -1;//如果节点不存在，那么它的高度是-1
    }

    void addUser(string &, string &);//添加用户功能
    void print();//使用影子树正向打印树
    static Node *addNode(Node *pNode, string &name, string &password);//静态成员函数，用于添加节点
    static ShadowTreeNode *ShadowTreeBuild(Node *Tree, ShadowTreeNode *ShadowTree, int TreeRow);//静态成员函数，用于生成影子树
    static Node *LeftSpin(Node *);//静态成员函数，将二叉树左旋
    static Node *RightSpin(Node *);//静态成员函数，将二叉树右旋
    static Node *SearchNode(const string &, Node *);//静态成员函数，搜索用户名对应的节点，返回指向它的指针
    static Node *remove(Node *, const string &);//静态成员函数，删除一个节点
    static Node *maxNode(Node *);//静态成员函数，返回左子树的最大节点，在删除节点时被调用
    static Node *minNode(Node *);//静态成员函数，返回右子树的最小节点，在删除节点时被调用
    void removeUser(string &);//删除用户名对应的用户
    void save(Node *);//保存树到文件
};

#endif //DATA_STRUCTURE_FINAL_AVLTREE_H
