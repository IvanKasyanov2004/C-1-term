#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
int const N = 2000000;

int binary_search(int (&a)[N], int n, int k){
    int l = 0;
    int r = n - 1;
    while (l <= r){
        int m = l + (r - l) / 2;
        if (a[m] == k){
            return m;
        }
        else if (a[m] < k){
            l = m + 1;
        }
        else{
            r = m - 1;
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
    remove("binary_search_average.txt");
    std::ofstream out;
    out.open("binary_search_average.txt", std::ios::app);

    int D = N/number/number/number;
    for(int j = 0; j < 3; j++){
        for(int i = 1; i < number + 1; i++){
            int n = i * D;
            generate_sorted_array(a, n);

            int arr[ ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
            unsigned seed = 1001;
            std::default_random_engine rng(seed);
            std::uniform_int_distribution<unsigned> dstr(0 , 9);

            auto begin = std::chrono::steady_clock::now();
            for(unsigned cnt = t; cnt != 0 ; --cnt){
                int r = arr[dstr(rng)];
                binary_search(a, n, r);
            }
            auto end = std::chrono::steady_clock::now();
            auto time_span =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            out << time_span.count() << " "; 
        }
        D = D * number;
    }

    out << std::endl;

    D = N/number/number/number;
    for(int j = 0; j < 3; j++){
        for(int i = 1; i < number + 1; i++){
            int n = i * D;
            out << n << " ";
        }
        D = D * number;
    }
    out.close(); 
}

int main(){
    int a[N] = {};
    calculate_search_time(a, 20, 2000000);
}