#include <iostream>

#ifndef N
#define N 10
#endif

void readArray(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cin >> a[i];
    }
}

int findLastZero(int (&a)[N]){
    int m;
    int l = 0;
    int r = N-1;
    while(l < r){
        m = (l + r) / 2;
        if(a[m] == 1){
            r = m;
        }
        else if(a[m] == 0 and a[m + 1] == 1){
            return m;
        }
        else{
            l = m + 1;
        }
    }
    return 0;
}

int main(){
    int a[N];
    readArray(a);
    std::cout << findLastZero(a);
}