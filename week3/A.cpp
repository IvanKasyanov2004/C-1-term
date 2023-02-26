#include <iostream>
#include <chrono>

#ifndef N
#define N 100
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

void selectSort(int (&a)[N]){
    int index_min;
    for(int i = 0; i < N; i++){
        index_min = i;
        for(int j = i; j < N; j++){
            if(a[j] < a[index_min]){
                index_min = j;
            }
        }
        if(index_min != i){
            swap(a[index_min], a[i]);
            }
        }
}


int main(){
    int a[N];
    readArray(a);

    auto begin = std::chrono::steady_clock::now();
    for(unsigned cnt = 100000; cnt != 0 ; --cnt)
        selectSort(a);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "\n\n";
    std::cout << "time: " << time_span.count() << " ms" << std::endl;
    
    showArray(a);
}