#include <iostream>
#include <chrono>

#ifndef N
#define N 40
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

void doubleSelectSort(int (&a)[N]){
    int index_min;
    int index_max;
    for(int i = 0; i < N/2; i++){
        index_min = i;
        index_max = N - 1 - i;
        for(int j = i; j < N - i; j++){
            if(a[j] < a[index_min]){
                index_min = j;
            }
            if(a[j] > a[index_max]){
                index_max = j;
            }
        }
        if(index_min != i){
            if(index_max == i){
                index_max = index_min;
            }
            swap(a[index_min], a[i]);
        }
        if(index_max != N - 1 - i){
            swap(a[index_max], a[N - 1 - i]);
        }
    }
}
int main(){
    int a[N];
    readArray(a);

     auto begin = std::chrono::steady_clock::now();
    for(unsigned cnt = 100000; cnt != 0 ; --cnt)
        doubleSelectSort(a);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "\n\n";
    std::cout << "time: " << time_span.count() << " ms" << std::endl;
    
    showArray(a);
    return 0;
}