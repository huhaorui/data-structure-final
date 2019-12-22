//
// Created by HHR on 2019/12/19.
//
#include "ShadowTreeNode.h"

#ifndef DATA_STRUCTURE_FINAL_SHADOWTREENODEQUEUE_H
#define DATA_STRUCTURE_FINAL_SHADOWTREENODEQUEUE_H


class ShadowTreeNodeQueue {
public:
    ShadowTreeNode *Node[1000] = {nullptr};
    int begin = 0, end = -1;//begin是队列头，end是队列尾，当begin>end时，说明队列为空

    bool empty() {
        return begin > end;
    }

    void push(ShadowTreeNode *node);

    void pop() {
        begin++;
    }

    ShadowTreeNode *front();
};


#endif //DATA_STRUCTURE_FINAL_SHADOWTREENODEQUEUE_H
