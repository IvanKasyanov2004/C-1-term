#include <iostream>
using namespace std;

void minimax() {
    int min = 0;
    int max = 0;
    int n;
    int a;
    int b;
    cin >> n;
    cin >> a;
    for (int i = 0; i < n - 1; i++) {
        cin >> b;
        if (b < a) {
            min += 1;
        } else {
            max += 1;
        }
        a = b;
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