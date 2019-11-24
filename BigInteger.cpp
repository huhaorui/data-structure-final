//
// Created by HHR on 2019/11/24.
//

#include "BigInteger.h"
#include "Node.h"
#include "stack.h"

BigInteger::BigInteger(string s) {
    if (s[0] == '-') {
        negative = true;
        s = s.substr(1);
    }
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
    if (negative) cout << '-';
    Node *tmp = num;
    stack stack1;
    while (tmp) {
        stack1.push(tmp->n);
        tmp = tmp->next;
    }
    while (!stack1.empty()) {
        cout << stack1.pop();
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

BigInteger BigInteger::operator+(BigInteger &n2) {
    BigInteger tmp;
    Node *num1 = this->num, *num2 = n2.num;
    int sign1 = this->negative ? -1 : 1, sign2 = n2.negative ? -1 : 1;
    while (num1 || num2) {
        if (num1 && num2) {
            tmp.add(num1->n * sign1 + num2->n * sign2);
            num1 = num1->next;
            num2 = num2->next;
        } else if (num1) {
            tmp.add(num1->n * sign1);
            num1 = num1->next;
        } else {
            tmp.add(num2->n * sign2);
            num2 = num2->next;
        }
    }
    tmp.num = tmp.num->next;
    Node *tmp2 = tmp.num;
    if (tmp.num->end() < 0) {
        tmp.negative = true;
        tmp2 = tmp.num;
        while (tmp2) {
            tmp2->n = -tmp2->n;
            tmp2 = tmp2->next;
        }
    }
    while (tmp2) {
        if (tmp2->n >= 10) {
            tmp2->next->n += tmp2->n / 10;
            tmp2->n %= 10;
        }
        tmp2 = tmp2->next;
    }
    return tmp;
}

BigInteger BigInteger::operator-(BigInteger &n) {
    BigInteger n2 = n;
    n2.negative = !n2.negative;
    BigInteger tmp = *this + n2;
    return tmp;
}
