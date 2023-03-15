#include <iostream>
using namespace std;

int read_array(int* &array){
    int a = 1;
    int i = 0;
    while(a != 0){
        cin >> a;
        if(a == 0){
            break;
        }
        int* array_tmp = new int[i + 1];
        for(int j = 0; j < i; ++j){
            *(array_tmp + j) = *(array + j);
        }
        array_tmp[i] = a;
        delete[] array;
        array = new int[i + 1];
        for(int f = 0; f < i + 1; ++f){
            *(array + f) = *(array_tmp + f);
        }
        i += 1;
    }
    return i;
}

void change_array(int* array, int N){
    for(int i = 0; i < N - 1; ++i){
        cout << array[i] - array[i + 1] << " ";
    }
    cout << endl;
}
int main(){
    int* array = new int[1];
    int N;
    N = read_array(array);
    change_array(array, N);
    delete[] array;
}