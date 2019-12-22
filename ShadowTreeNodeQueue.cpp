//
// Created by HHR on 2019/12/19.
//

#include "ShadowTreeNodeQueue.h"

void ShadowTreeNodeQueue::push(ShadowTreeNode *node) {
    Node[++end] = node;
}

ShadowTreeNode *ShadowTreeNodeQueue::front() {
    return Node[begin];
}
