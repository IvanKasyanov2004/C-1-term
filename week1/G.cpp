#include <iostream>
using namespace std;

void minimax() {
    int min = 0;
    int max = 0;
    int n;
    int a, b ,c;
    cin >> n;
    cin >> a;
    cin >> b;
    for (int i = 0; i < n - 2; i++) {
        cin >> c;
        if (a < b and b > c) {
            max += 1;
        }
        if (a > b and b < c) {
            min += 1;
        }
        a = b;
        b = c;
    }
    if (max == min) {
        cout << "EQUAL";
    }
    if (max > min) {
        cout << "MAX";
    }
    if (max < min) {
        cout << "MIN";
    }
}

int main() {
    minimax();
}