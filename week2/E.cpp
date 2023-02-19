#include <iostream>

#ifndef N
#define N 3
#endif

void readArray(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cin >> a[i];
    }
}
void showArray(int (&a)[2 * N]){
    for (int i = 0; i < 2 * N; i++){
        std::cout << a[i] << " ";
    }
}

void mergeArrays(int (&a)[N], int (&b)[N], int (&c)[2 * N]){
    for(int i = 0; i < 2 * N; i++){
        c[i] = 0;
    }
    int i = 0;
    int j = 0;
    while(i < N and j < N){
        if(a[i] <= b[j]){
            c[i + j] = a[i];
            i = i + 1;
        }
        if(a[i] > b[j]){
            c[i + j] = b[j];
            j = j + 1;
        }
    }
}

int main(){
    int a[N];
    int b[N];
    int c[2 * N];
    readArray(a);
    readArray(b);
    mergeArrays(a, b, c);
    showArray(c);
}

