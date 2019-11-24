//
// Created by HHR on 2019/11/24.
//

#ifndef DATA_STRUCTURE_FINAL_NODE_H
#define DATA_STRUCTURE_FINAL_NODE_H


class Node {
public:
    int n;
    Node *next;

    explicit Node(int n) {
        this->n = n;
        next = nullptr;
    }

    Node() {
        n = 0;
        next = nullptr;
    };

    void edit(int seat, int num);

    int get(int seat);

    int end();
};


#endif //DATA_STRUCTURE_FINAL_NODE_H
