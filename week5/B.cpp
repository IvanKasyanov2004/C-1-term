#include <iostream>
using namespace std;

void generate_array(int *array, int N){
    for(int i = 0; i < N; ++i){
        array[i] = i;
    }
}

void change_array(int *array, int N){
    for(int i = 0; i < N; i = i + 2){
        *(array + i) = (*(array + i)) * (*(array + i));
    }
}

void show_array_value(int *array, int N){
    for(int i = 0; i < N; ++i){
        cout << array[i] << " ";
    }   
    cout << endl;
}

void show_array_pointer(int *array, int N){
    for(int i = 0; i < N; ++i){
        cout << (array + i) << " ";
    }   
    cout << endl;
}



int main(){
    int const N = 10;
    short int a = 9;
    short int* ptr1 = &a;
    cout << ptr1 << endl;

    int *array = new int[N];

    generate_array(array, N);
    show_array_pointer(array, N);
    show_array_value(array, N);

    change_array(array, N);
    show_array_value(array, N);
    delete[] array;
}