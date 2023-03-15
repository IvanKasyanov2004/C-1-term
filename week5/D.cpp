#include <iostream>
using namespace std;

void input_array(int* &ptr, size_t N);
void reverse(int* ptr, size_t N);
void print(const int* ptr, size_t N);

void input_array(int* &ptr, size_t N){
    ptr = new int[N];
    for(int i = 0; i < N; ++i){
        cin >> *(ptr + i);
    }
}

void print(const int* ptr, size_t N){
    for(int i = 0; i < N; ++i){
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

void reverse(int* ptr, size_t N){
    int* tmp = new int[N];
    for(int i = 0; i < N; ++i){
        *(tmp + i) = *(ptr + i);
    }
    for(int i = 0; i < N; ++i){
        *(ptr + i) = *(tmp + N - 1 - i);
    }
    delete[] tmp;
}

int main(){
    int N = 0;
    int* ptr = new int[1];
    cin >> N;
    input_array(ptr, N);
    reverse(ptr, N);
    print(ptr, N);
    delete[] ptr;
    return 0;
}