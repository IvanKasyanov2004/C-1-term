#include <iostream>
#include <random>

#ifndef N
#define N 10
#endif

void generate_array(int (&a)[N]){
    int arr[ ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0 , 9);

    for(unsigned counter = 0; counter < N; counter++){
        a[counter] = arr[dstr(rng)];
    }  
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void show_array(int (&a)[N]){
    for (int i = 0; i < N; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;    
}

void step_step(int (&a)[N], unsigned const begin_idx, unsigned const end_idx, int n){
    for(int i = 0; i < N - n; i++){
        if(a[i] > a[i + n]){
            swap(a[i], a[i + n]);
        }
        show_array(a);
    }
}

int main(){
    int a[N];
    generate_array(a);
    show_array(a);
    step_step(a, 0, N - 1, 1);
}