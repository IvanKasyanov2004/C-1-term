#include <iostream>

#ifndef N
#define N 2
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
    std::cout << std::endl;   
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void reverse(int (&a)[N], int index){
    for(int i = 0; i < (index+1)/2; i++){
        swap(a[i], a[index - i]);
    }
}

void pancakeSort(int (&a)[N]){
    for(int n = N; n > 1; n--){
        int index_max = n - 1;
        for(int j = 0; j < n; j++){
            if(a[j] > a[index_max]){
                index_max = j;
            }
        }
        if(index_max != n - 1){
            reverse(a, index_max);
            reverse(a, n - 1);
        }
    }
}

int main(){
    int a[N];
    readArray(a);
    pancakeSort(a);
    showArray(a);
}
