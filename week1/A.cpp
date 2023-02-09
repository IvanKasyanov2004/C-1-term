#include <iostream>
using namespace std;

void pal(int n0) {
    int n = n0;
    int m = 0;
    while (n > 0) {
        m = m * 10 + n % 10;
        n = n / 10;
    }
    if (n0 == m) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
int main() {
    int k;
    cin >> k;
    pal(k);
}