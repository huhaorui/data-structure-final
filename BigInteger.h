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

    explicit BigInteger(const string &s);

    BigInteger();

    void display();//暂时为反向输出
    void add(int);

    BigInteger operator+(BigInteger n2);
};


#endif //DATA_STRUCTURE_FINAL_BIGINTEGER_H
