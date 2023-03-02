#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#ifndef N
#define N 1000000
#endif

int full_search(int (&a)[N], int n, int k){
    for(int i = 0; i < n; i++){
        if(a[i] == k){
            return i;
        }
    }
    return 0;
}

void generate_sorted_array(int (&a)[N], int n){
    for(int i = 0; i < 10; i++){
        for(int j = i * n/10; j < (i + 1) * n/10; j++){
            a[j] = i;
        }
    }
}

void calculate_search_time(int (&a)[N], int number, int t){
    remove("full_search.txt");
    std::ofstream out;
    out.open("full_search.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int n = i * N/number;
        generate_sorted_array(a, n);

        auto begin = std::chrono::steady_clock::now();
        for(unsigned cnt = t; cnt != 0 ; --cnt)
            full_search(a, n, 10);
        auto end = std::chrono::steady_clock::now();
        auto time_span =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        out << time_span.count() << " "; 
    }
    out << std::endl;
    for(int i = 1; i < number + 1; i++){
        int n = i * N/number;
        out << n << " ";
    }
    out.close(); 
}

int main(){
    int a[N] = {0};
    calculate_search_time(a, 20, 1000);
}