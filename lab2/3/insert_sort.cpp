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

void show_array(int (&a)[N], int l){
    for (int i = 0; i < l; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;    
}

void insert_sort(int (&a)[N], int l){
    for(int i = 1; i < l; i++){
        int tmp = a[i];
        for(int j = i - 1; j > -1; j--){
            if(tmp < a[j]){
                a[j + 1] = a[j]; 
            }
            if(tmp >= a[j]){
                a[j + 1] = tmp; 
                break;
            }
            if(j == 0){
                a[0] = tmp;
            }
        }
    }
}

int main(){
    int a[N];
    int l = 100;
    generate_array(a, l, 100);
    show_array(a, l);
    insert_sort(a, l);
    show_array(a, l);
}