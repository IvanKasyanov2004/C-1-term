#include <iostream>
using namespace std;

int main(){
    double a = 9;
    double* ptr = &a;
    *ptr = 0;
    cout << "Указатель: " << ptr << " Значение: " << *ptr << endl;
    cout << "Указатель: " << (ptr-3) << " Значение: " << *(ptr-3) << endl;
    cout << "Указатель: " << (ptr+5) << " Значение: " << *(ptr+5) << endl;
}