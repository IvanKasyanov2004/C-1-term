#include <iostream>
using namespace std;

void leap(int n) {
    if (n % 4 == 0 and n % 100 != 0 or n % 400 == 0) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}

int main() {
    int n;
    cin >> n;
    leap(n);
}