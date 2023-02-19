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

void moveNegativeToEnd(int (&a)[N]){
    int b[N] = {0};
    int j = 0;
    for(int i = 0; i < N; i++){      
        if(a[i] >= 0){
            b[j] = a[i];
            j += 1;        
            }
        }
    for(int i = 0; i < N; i++){      
        if(a[i] < 0){
            b[j] = a[i];
            j += 1;        
            }
        }
    
    for(int i = 0; i < N; i++){
        a[i] = b[i];
    }
}

int main(){
    int a[N];
    readArray(a);
    moveNegativeToEnd(a);
    showArray(a);
}