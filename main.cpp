#include <iostream>

int addNumbers(int a, int b) {
    return a + b;
}

int main() {
    int result = addNumbers(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}