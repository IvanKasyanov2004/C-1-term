#include <iostream>
using namespace std;

int my_power(int base, int power) {
    int m = 1;
    for(int i = 0; i < power; i++) {
        m = m * base;
    }
    return m;
}
int main() {
    int base;
    int power;
    cin >> base >> power;
    cout << my_power(base, power);
}