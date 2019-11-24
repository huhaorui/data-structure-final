//
// Created by HHR on 2019/11/24.
//

#include "BigInteger.h"
#include "Node.h"

BigInteger::BigInteger(const string &s) {
    Node *head = new Node(s[0] - '0');
    for (int i = 1; i < int(s.size()); i++) {
        Node *tmp = new Node(s[i] - '0');
        tmp->next = head;
        head = tmp;
    }
    num = head;
}

BigInteger::BigInteger() {
    num = new Node();
}

void BigInteger::display() {
    Node *tmp = num;
    while (tmp) {
        cout << tmp->n;
        tmp = tmp->next;
    }
}

void BigInteger::add(int n) {
    Node *tmp = num;
    while (tmp->next) {
        tmp = tmp->next;
    }
    Node *t = new Node(n);
    tmp->next = t;
}

BigInteger BigInteger::operator+(BigInteger n2) {
    BigInteger tmp;
    Node *num1 = this->num, *num2 = n2.num;
    while (num1 || num2) {
        if (num1 && num2) {
            tmp.add(num1->n + num2->n);
            num1 = num1->next;
            num2 = num2->next;
        } else if (num1) {
            tmp.add(num1->n);
            num1 = num1->next;
        } else {
            tmp.add(num2->n);
            num2 = num2->next;
        }
    }
    tmp.num = tmp.num->next;
    return tmp;
}

