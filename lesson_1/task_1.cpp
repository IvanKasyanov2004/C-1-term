#include <iostream>
#include <cmath>

int main() {
    float a = 1.34;
    float b = 10;
    float c = 4;
    float x1, x2;
    if (a == 0){
        std::cout << "a = 0";
    }
    else{
        x1 = (- b + sqrt(b*b - 4*a*c)) / (2*a);
        x2 = (- b - sqrt(b*b - 4*a*c)) / (2*a);
        std::cout << "x1 = " << x1 << " " << "x2 = " << x2;
    }
}