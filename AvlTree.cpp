//
// Created by HHR on 2019/11/27.
//
#include "AvlTree.h"
#include "ShadowTreeNode.h"
#include "ShadowTreeNodeQueue.h"
#include <cmath>
#include <fstream>

int max(int a, int b) {
    return a > b ? a : b;
}

void AvlTree::save(Node *tree) {
    if (tree == nullptr) {//如果根节点是空指针，说明这棵子树已经完成了遍历，即可退出
        return;
    }
    fstream out;
    if (tree == root) {//如果该节点是根节点，说明文件输出刚刚开始，则清除原有文件，否则在文件尾追加
        out.open("database.dat", ios::out);
    } else {
        out.open("database.dat", ios::out | ios::app);
    }
    out << tree->getName() << " " << tree->getPassword() << endl;
    out.close();
    save(tree->left);//递归遍历左子树
    save(tree->right);//递归遍历右子树
}

void AvlTree::addUser(string &name, string &password) {
    if (SearchNode(name, root) != nullptr) return;//如果用户已经存在，则不添加
    root = addNode(root, name, password);//调用addNode函数添加节点
}

void AvlTree::removeUser(string &name) {
    if (SearchNode(name, root) == nullptr) return;//如果用户不存在，则不删除
    root = remove(root, name);//调用remove函数删除节点
}

Node *AvlTree::addNode(Node *pNode, string &name, string &password) {
    if (pNode == nullptr) { //找到空的插入点，创建一个新的Node，并返回插入点
        pNode = new Node(name, password);
        return pNode;
    } else if (name < pNode->getName()) {//要插入左边
        pNode->left = addNode(pNode->left, name, password);
        if (getHeight(pNode->left) - getHeight(pNode->right) == 2) {//平衡因子为2，发生了不平衡
            if (name < pNode->left->getName()) {//添加的节点在左子树的左子树内，采用右旋操作
                pNode = RightSpin(pNode);
            } else {//添加的节点在左子树的右子树内，采用先左旋再右旋操作
                pNode->left = LeftSpin(pNode->left);
                pNode = RightSpin(pNode);
            }
        }
    } else {
        pNode->right = addNode(pNode->right, name, password);
        if (getHeight(pNode->right) - getHeight(pNode->left) == 2) {//平衡因子为2，发生了不平衡
            if (name > pNode->right->getName()) {//添加的节点在右子树的右子树内，采用左旋操作
                pNode = LeftSpin(pNode);
            } else {//添加的节点在右子树的左子树内，采用先右旋再左旋操作
                pNode->right = RightSpin(pNode->right);
                pNode = LeftSpin(pNode);
            }
        }
    }
    pNode->setHeight(max(getHeight(pNode->left), getHeight(pNode->right)) + 1);//获取完成插入后新的树的高度
    return pNode;
}

Node *AvlTree::SearchNode(const string &name, Node *root) {
    if (root == nullptr) return nullptr;//如果节点为空，说明找不到需要的节点，返回空指针
    if (root->getName() == name) {//如果节点内容与查找值相同，返回找到的节点指针
        return root;
    } else if (root->getName() > name) {//如果节点的内容比查找值大，说明目标节点在左子树，递归进入查找
        return SearchNode(name, root->left);
    } else {//否则去右子树查找
        return SearchNode(name, root->right);
    }
}

Node *AvlTree::remove(Node *root, const string &name) {
    if (root == nullptr) return nullptr;//如果节点是空的，说明要删除的东西不存在，返回空指针
    if (name < root->getName()) {//如果节点的内容比查找值大，说明目标节点在左子树，递归进入
        root->left = remove(root->left, name);
        if (getHeight(root->right) - getHeight(root->left) == 2) {//如果平衡因子为2，说明发生了失衡，需要旋转
            Node *right = root->right;//右子树比较深，说明右子树需要进行旋转
            if (getHeight(right->left) > getHeight(right->right)) {//如果右子树的左子树比较深，执行先右旋再左旋
                root->right = RightSpin(root->right);
                root = LeftSpin(root);
            } else {//否则直接左旋
                root = LeftSpin(root);
            }
        }
    } else if (name > root->getName()) {//如果用户名比当前节点要大，说明要删除的节点在右子树，递归进入
        root->right = remove(root->right, name);
        if (getHeight(root->left) - getHeight(root->right) == 2) {//如果平衡因子为2，说明发生了失衡，需要旋转
            Node *left = root->left;//左子树比较深，说明左子树需要进行旋转
            if (getHeight(left->left) < getHeight(left->right)) {//如果左子树的右子树比较深，执行先左旋再右旋
                root->left = LeftSpin(root->left);
                root = RightSpin(root);
            } else {//否则直接右旋
                root = RightSpin(root);
            }
        }
    } else {//既不偏大，也不偏小，显然是找到了删除点
        if (root->left != nullptr && root->right != nullptr) {//两侧都存在子树
            if (getHeight(root->left) > getHeight(root->right)) {//如果左子树比较深
                Node *toRemove = maxNode(root->left);//删除点的内容会被左子树的最大值替换，所以找到左子树的最大值
                root->setName(toRemove->getName());//将根节点（也就是要删除的节点）的信息替换为左子树的最大节点
                root->setPassword(toRemove->getPassword());
                root->left = remove(root->left, toRemove->getName());//删除左子树最大的节点
            } else {
                Node *toRemove = minNode(root->right);//删除点的内容会被右子树的最小值替换，所以找到右子树的最小值
                root->setName(toRemove->getName());
                root->setPassword(toRemove->getPassword());
                root->right = remove(root->right, toRemove->getName());
            }
        } else {//如果至少有一侧是空的，那就直接把一棵子树提高
            Node *tmp = root;
            if (root->left != nullptr) {//如果左子树存在，就将右节点提高
                root = root->left;
            } else {//否则将左节点提高
                root = root->right;
            }
            delete tmp;//删除根节点
        }
    }
    if (root != nullptr) {
        root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);
    }
    return root;
}

Node *AvlTree::maxNode(Node *root) {
    if (root->right != nullptr) {//如果右子树存在，说明最大的节点在右子树内
        return maxNode(root->right);//递归查找右子树
    }
    return root;//如果右子树不存在，说明该节点即为最大的节点
}

Node *AvlTree::minNode(Node *root) {
    if (root->left != nullptr) {//如果左子树存在，说明最小的节点在左子树内
        return minNode(root->left);//递归查找左子树
    }
    return root;//如果左子树不存在，说明该节点即为最大的节点
}

void AvlTree::print() {
    if (root == nullptr) return;//如果根节点不存在，显然是不需要打印的，返回
    ShadowTreeNode *ShadowTree = nullptr;
    ShadowTree = ShadowTreeBuild(root, ShadowTree, 1);//开始时，应该打印在第一行
    ShadowTreeNodeQueue queue;//建立一个打印队列
    queue.push(ShadowTree);
    int MaxRow = 1, MaxColumn = 0;
    int MaxLength = getMaxLength(this);//设置内容的最大长度，以对齐树
    while (!queue.empty()) {//如果打印队列非空
        ShadowTreeNode *pShadowTreeNode = queue.front();//取出队列第一项
        queue.pop();
        if (pShadowTreeNode->row > MaxRow) {//如果行数超过了最大行数，说明要开始打印下一行
            cout << endl;//换行
            MaxRow = pShadowTreeNode->row;//重设最大行数
            MaxColumn = 0;
        }
        string tmpName = pShadowTreeNode->name;
        while (tmpName.length() < MaxLength) {//检查名字有没有过长，如果太长，就将其截断，否则在后面补上空格
            tmpName += ' ';
            if (tmpName.length() < MaxLength) {
                tmpName = string(" ").append(tmpName);
            }
        }
        for (int i = 1; i < pShadowTreeNode->column - MaxColumn; i++) {//输出前置的空格
            for (int j = 0; j < MaxLength; j++) cout << ' ';
        }
        cout << tmpName;
        MaxColumn = pShadowTreeNode->column;
        if (pShadowTreeNode->left != nullptr) queue.push(pShadowTreeNode->left);//如果左子树非空，将其加入打印队列
        if (pShadowTreeNode->right != nullptr) queue.push(pShadowTreeNode->right);
    }
    cout << endl;
}

ShadowTreeNode *AvlTree::ShadowTreeBuild(Node *Tree, ShadowTreeNode *ShadowTree, int TreeRow) {
    if (Tree != nullptr) {
        static int TreeColumn;//这个变量需要static，保证不变
        if (TreeRow == 1) {
            TreeColumn = 1;//第一行只有一列
        }
        ShadowTree = new ShadowTreeNode();
        ShadowTree->left = ShadowTreeBuild(Tree->left, ShadowTree->left, TreeRow + 1);//递归建立左子树
        ShadowTree->column = TreeColumn++;//设置影子树节点的内容
        ShadowTree->row = TreeRow;
        ShadowTree->name = Tree->getName();
        ShadowTree->right = ShadowTreeBuild(Tree->right, ShadowTree->right, TreeRow + 1);//递归建立右子树
    }
    return ShadowTree;
}

Node *AvlTree::RightSpin(Node *root) {
    Node *left = root->left;
    root->left = left->right;
    left->right = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);//旋转后，重设树的高度
    left->setHeight(max(getHeight(left->left), getHeight(left->right)) + 1);
    return left;
}

Node *AvlTree::LeftSpin(Node *root) {
    Node *right = root->right;
    root->right = right->left;
    right->left = root;
    root->setHeight(max(getHeight(root->left), getHeight(root->right)) + 1);//旋转后，重设树的高度
    right->setHeight(max(getHeight(right->left), getHeight(right->right)) + 1);
    return right;
}


int AvlTree::getMaxLength(Node *Tree) {
    int maxLength = Tree->getName().length();
    if (Tree->left) {
        maxLength = max(maxLength, getMaxLength(Tree->left));
    }
    if (Tree->right) {
        maxLength = max(maxLength, getMaxLength(Tree->right));
    }
    return maxLength;
}

int AvlTree::getMaxLength(AvlTree *pTree) {
    return getMaxLength(pTree->root);
}
