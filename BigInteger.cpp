//
// Created by HHR on 2019/11/24.
//

#include "BigInteger.h"
#include "Node.h"

void BigInteger::display() {
    Node *tmp = num;
    while (tmp) {
        cout << tmp->n;
        tmp = tmp->next;
    }
}