#include <iostream>

unsigned int gcd(unsigned int const a, unsigned int const b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a = 21;
    int b = 6;

    int fgcd = gcd(a, b);

    int lcm = a * b / fgcd;
    std::cout << lcm;
    return 0;
}