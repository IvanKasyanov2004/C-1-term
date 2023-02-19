#include <iostream>

#ifndef N
#define N 5
#endif

void readArray(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cin >> a[i];
    }
}
void showArray(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cout << a[i] << " ";
    }
}

void reverseArray(int (&a)[N]){
    int b[N] = {0};
    for (int i = 0; i < N; i++){
        b[i] = a[N - 1 - i];
    }
    for (int i = 0; i < N; i++){
        a[i] = b[i];
    }
}

int main(){
    int a[N];
    readArray(a);
    reverseArray(a);
    showArray(a);
}
