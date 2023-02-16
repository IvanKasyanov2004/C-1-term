#include <iostream>
using namespace std;

int fibonacci(unsigned i) {
    if (i == 0){
        return 0;
    }
    if (i == 1){
        return 1;
    }
    return fibonacci(i - 1) + fibonacci(i - 2);
}
int main() {
    int k;
    cin >> k;
    cout << fibonacci(k);
}