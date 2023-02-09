#include <iostream>
using namespace std;

int recursive_power(int base, int power) {
    if (power == 0) {
        return 1;
    }
    return recursive_power(base, power - 1) * base;
}

int main() {
    int base;
    int power;
    cin >> base >> power; 
    cout << recursive_power(base, power);
}