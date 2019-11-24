//
// Created by HHR on 2019/11/24.
//

#ifndef DATA_STRUCTURE_FINAL_BIGINTEGER_H
#define DATA_STRUCTURE_FINAL_BIGINTEGER_H

#include <iostream>
#include "Node.h"

using namespace std;

class BigInteger {
public:
    Node *num;

    explicit BigInteger(const string &s) {
        Node *head = new Node(s[0] - '0');
        for (int i = 1; i < s.length(); i++) {
            Node *tmp = new Node(s[i] - '0');
            tmp->next = head;
            head = tmp;
        }
        num = head;
    }

    void display();
};


#endif //DATA_STRUCTURE_FINAL_BIGINTEGER_H
