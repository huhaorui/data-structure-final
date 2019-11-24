//
// Created by HHR on 2019/11/24.
//

#include "Node.h"

void Node::edit(int seat, int num) {
    Node *tmp = this;
    for (int x = 0; x < seat; x++) {
        tmp = tmp->next;
    }
    tmp->n = num;
}

int Node::get(int seat) {
    Node *tmp = this;
    for (int x = 0; x < seat; x++) {
        tmp = tmp->next;
    }
    return tmp->n;
}