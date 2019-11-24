//
// Created by HHR on 2019/11/24.
//

#ifndef DATA_STRUCTURE_FINAL_STACK_H
#define DATA_STRUCTURE_FINAL_STACK_H


class stack {
public:
    int n[10000] = {0};
    int num;

    void push(int);

    int pop();

    stack() {
        num = 0;
    }

    bool empty() {
        return !num;
    }
};


#endif //DATA_STRUCTURE_FINAL_STACK_H
