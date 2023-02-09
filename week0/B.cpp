#include <iostream>

int main() {
    int a;
    std::cin >> a;
    int b;
    int k = 0;
    b = a / 2 + 1;
    for (int i = 2; i <= b; i++) {
        if (a % i == 0){
            k = k + 1;
        }
    }
    if ((k == 0) or (a == 2)) {
        std::cout << a << " - простое";
    } else {
        std::cout << a << " - составное";
    }
}