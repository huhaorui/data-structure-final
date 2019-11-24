#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
    string num;
    cin >> num;
    BigInteger n1(num);
    n1.display();
    return 0;
}