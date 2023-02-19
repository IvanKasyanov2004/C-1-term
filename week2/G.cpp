#include <iostream>

#ifndef N
#define N 5
#endif

void readArray(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cin >> a[i];
    }
}

int findUnique(int (&a)[N]){
    if(N == 1){
        return a[0];
    }
    int m = a[0];
    for(int i = 1; i < N; i++){
        m = m ^ a[i];
    }
    return m;
}

int main(){
    int a[N];
    readArray(a);
    std::cout << findUnique(a);
}