#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
    string num1, num2;
    //cin >> num1 >> num2;
    BigInteger n1(
            "0");
    BigInteger n2(
            "-12234");
    BigInteger n3 = n1 + n2;
    n3.display();
    return 0;
}