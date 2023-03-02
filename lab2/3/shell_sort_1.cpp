#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#ifndef N
#define N 200000
#endif

void generate_array(int (&a)[N], int l, int seed){
    int arr[ ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0 , 9);

    for(unsigned counter = 0; counter < l; counter++){
        a[counter] = arr[dstr(rng)];
    }  
}

void show_array(int (&a)[N], int l){
    for (int i = 0; i < l; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;    
}

void insert_step_sort(int (&a)[N], int d, int l){
    for(int k = 0; k < d; k++){
        for(int i = 1; k + i * d < l; i++){
            int tmp = a[k + i * d];
            for(int j = i - 1; j > -1; j--){
                if(tmp < a[k + j * d]){
                    a[k + (j + 1) * d] = a[k + j * d];
                }
                if(tmp >= a[k + j * d]){
                    a[k + (j + 1) * d] = tmp;
                    break;
                }
                if(j == 0){
                    a[k] = tmp;
                }
            }
        }
    }
}

void shell_sort_1(int (&a)[N], int l){
    int d = l;
    while(d > 0){
        insert_step_sort(a, d, l);
        d = d/2;
    }
}

void calculate_sort_time(int (&a)[N], int number, int t){
    remove("shell_sort_1_time.txt");
    std::ofstream out;
    out.open("shell_sort_1_time.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int l = i * N/number;
        generate_array(a, l, 1001);

        auto begin = std::chrono::steady_clock::now();
        for(unsigned cnt = t; cnt != 0 ; --cnt)
            shell_sort_1(a, l);
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
    int a[N];
    int l = 100;
    calculate_sort_time(a, 20, 100);
}