#include <iostream>
using namespace std;

int zeros(int n) {
    int z = 0;
    int i = 5;
    while (i <= n) {
        z += n / i;
        i = i * 5;
    }
    return z;
}
int main() {
    int n0;
    cin >> n0;
    cout << zeros(n0);
}