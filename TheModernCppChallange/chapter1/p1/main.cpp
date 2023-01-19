#include <iostream>

int main() {

    int limit = 0;
    int sum = 0;
    std::cout << "Provide a limit: ";
    std::cin >> limit;

    for (int i=0; i<=limit; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    std::cout << std::endl << "Sum: " << sum << std::endl;

    return 0;
}