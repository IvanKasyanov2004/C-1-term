#include <iostream>

int main() {
    int a0 = 21;
    int b0 = 63;
    int a = a0;
    int b = b0;
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    std::cout << "НОД(" << a0 << "," << b0 << ") = " << b;
}