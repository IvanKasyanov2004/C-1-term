#include <iostream>
#include <cstring>
using namespace std;

char* resize(const char* buf, size_t size, size_t new_size){
    char* a = new char[new_size];
    if(size <= new_size){
        for(int i = 0; i < size; ++i){
            *(a + i) = *(buf + i);
        }
    }
    else{
        for(int i = 0; i < new_size; ++i){
            *(a + i) = *(buf + i);
        }
    }
    delete[] buf;
    return a;
}

int main(){
    char* a = new char[10];
    char* a_new;
    a_new = resize(a, 10, 15);
    delete[] a_new;
}