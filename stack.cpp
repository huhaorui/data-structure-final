//
// Created by HHR on 2019/11/24.
//

#include "stack.h"

void stack::push(int t) {
    n[num] = t;
    num++;
}

int stack::pop() {
    if (num > 0) {
        num--;
        return n[num];
    }
}