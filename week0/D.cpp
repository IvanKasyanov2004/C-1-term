#include <iostream>
#include <vector>

int main() {
    int c;
    std::cin >> c;
    int s = 0;
    int f = 0;
    int g = 0;
    std::vector <int> sum;
    for (int i = 0; i <= c; i++) {
        for (int j = 0; j <= c; j++) {
            if (i*i + j*j == c) {
                s = i + j;
                f = 0;
                for (int k = 0; k < sum.size(); k++) {
                    if (sum[k] == s) {
                        f = 1;
                    }
                }
                if (f == 0) {
                    sum.push_back(s);
                    std::cout << i << " " << j << std::endl;
                    g = g + 1;
                }
            }
        }
    }
    if (g == 0) {
        std::cout << "Таких чисел нет";
    }
}