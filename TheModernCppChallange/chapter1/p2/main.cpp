#include <iostream>

unsigned int gcd(unsigned int const a, unsigned int const b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b = 0;
    std::cout << "Provide two numbers: ";
    std::cin >> a;
    std::cin >> b;

    int fgcd = gcd(a, b);

    std::cout << "Found: " << fgcd << std::endl;
    return 0;
}