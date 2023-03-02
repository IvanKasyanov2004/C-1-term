#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
int const N = 20000;

int sum_search(int (&a)[N], int n, int k){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j != i and a[j] + a[i] == k){
                return i+1;
            }
        }   
    }
    return 0;
}

void generate_array(int (&a)[N]){
    int arr[ ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0 , 9);

    for(unsigned counter = 0; counter < N; counter++){
        a[counter] = arr[dstr(rng)];
    }  
}

void calculate_search_time(int (&a)[N], int number, int t){
    remove("sum_search.txt");
    std::ofstream out;
    out.open("sum_search.txt", std::ios::app);
    for(int i = 1; i < number + 1; i++){
        int n = i * N/number;
        generate_array(a);

        auto begin = std::chrono::steady_clock::now();
        for(unsigned cnt = t; cnt != 0 ; --cnt)
            sum_search(a, n, 20);
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
    calculate_search_time(a, 20, 10);
}