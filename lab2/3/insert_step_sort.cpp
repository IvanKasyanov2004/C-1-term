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
        show_array(a,l);
    }
}

int main(){
    int a[N];
    int l = 11;
    generate_array(a, l, 1001);
    show_array(a, l);
    insert_step_sort(a, 4, l);
}