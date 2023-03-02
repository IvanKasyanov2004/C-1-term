#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
int const N = 2000000;

int sum_speed_search(int (&a)[N], int n, int k){
    for(int i = 0; i < n/2; i++){
        if(a[i] + a[n - 1 - i] == k){
            return i+1;
        }
    }
    if(n % 2 == 1){
        if(a[n/2] + a[n/2 - 1] == k){
            return n/2;
        }
        if(a[n/2] + a[n/2 + 1] == k){
            return n/2 + 1;
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
    remove("sum_speed_search.txt");
    std::ofstream out;
    out.open("sum_speed_search.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int n = i * N/number;
        generate_sorted_array(a, n);

        auto begin = std::chrono::steady_clock::now();
        for(unsigned cnt = t; cnt != 0 ; --cnt)
            sum_speed_search(a, n, 20);
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