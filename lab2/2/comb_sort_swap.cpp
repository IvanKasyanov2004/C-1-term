#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#ifndef N
#define N 20000
#endif

void generate_array(int (&a)[N], int l, int seed){
    int arr[ ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0 , 9);

    for(unsigned counter = 0; counter < l; counter++){
        a[counter] = arr[dstr(rng)];
    }  
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void show_array(int (&a)[N], int l){
    for (int i = 0; i < l; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;    
}

void step_step(int (&a)[N], int l, int n, int &s){
    for(int i = 0; i < l - n; i++){
        if(a[i] > a[i + n]){
            swap(a[i], a[i + n]);
            s += 1;
        }
    }
}

void comb_sort(int (&a)[N], int l, int &s){
    for(int n = l; n > 0; n--){
        step_step(a, l, n, s);
    }
}

void calculate_sort_time(int (&a)[N], int number, int t){
    remove("comb_sort_swap.txt");
    std::ofstream out;
    out.open("comb_sort_swap.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int l = i * N/number;

        int s = 0;
        for(unsigned cnt = t; cnt != 0 ; --cnt){
            generate_array(a, l, t);
            comb_sort(a, l, s);
        }

        out << s << " ";
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
    calculate_sort_time(a, 20, 10);
}