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

void insert_step_sort(int (&a)[N], int d, int l, int &s){
    for(int k = 0; k < d; k++){
        for(int i = 1; k + i * d < l; i++){
            int tmp = a[k + i * d];
            for(int j = i - 1; j > -1; j--){
                if(tmp < a[k + j * d]){
                    a[k + (j + 1) * d] = a[k + j * d];
                    s += 1;
                }
                if(tmp >= a[k + j * d]){
                    a[k + (j + 1) * d] = tmp;
                    s += 1;
                    break;
                }
                if(j == 0){
                    a[k] = tmp;
                    s += 1;
                }
            }
        }
    }
}

int hibbard(int l){
    for(int i = 0; i > -1; i++){
        if(pow(2,i)-1 > l){
            return i - 1;
        }
    }
}

void shell_sort_2(int (&a)[N], int l, int &s){
    for(int i = hibbard(l); i > 0; i--){
        int d = pow(2,i) - 1;
        insert_step_sort(a, d, l, s);
    }
}

void calculate_sort_swap(int (&a)[N], int number, int t){
    remove("shell_sort_2_swap.txt");
    std::ofstream out;
    out.open("shell_sort_2_swap.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int l = i * N/number;

        int s = 0;
        for(unsigned cnt = t; cnt != 0 ; --cnt){
            generate_array(a, l, t);
            shell_sort_2(a, l, s);
        }

        out << s/t << " ";
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
    calculate_sort_swap(a, 20, 20);
}