#include <iostream>

#ifndef N
#define N 1
#endif

#ifndef M
#define M 3
#endif

void readArray(int (&a)[N][M]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            std::cin >> a[i][j];
        }
    }
}

void print_transposed(int (&a)[N][M]){
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            std::cout << a[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    int a[N][M];
    readArray(a);
    print_transposed(a);
}