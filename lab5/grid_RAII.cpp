#include <iostream>

template <typename T>
class Grid final{
    public:
        using value_type = T;   //using - создание псевдонимов
        using size_type = unsigned;

    private:
        T* data;
        size_type y_size;
        size_type x_size;

        void swap(Grid<T>& lha, Grid<T>& rha){
            std::swap(lha.y_size, rha.y_size);
            std::swap(lha.x_size, rha.x_size);
            std::swap(rha.data, lha.data);
        }

    public:
        //конструктор c двумя параметрами
        Grid(size_type y_size, size_type x_size): data(new T[y_size * x_size]), y_size(y_size), x_size(x_size){
            for(size_type x = 0; x < x_size; ++x){
                for(size_type y = 0; y < y_size; ++y){
                    (*this)(y, x) = T();
                }
            }            
        }

        //конструктор c тремя параметрами
        Grid(size_type y_size, size_type x_size, T const& t): data(new T[y_size * x_size]), y_size(y_size), x_size(x_size){
            for(size_type x = 0; x < x_size; ++x){
                for(size_type y = 0; y < y_size; ++y){
                    (*this)(y, x) = t;
                }
            }            
        }

        //конструктор для преобразования типов из T в Grid<T>
        Grid(T const& t){
            data = new T[1];
            y_size = 1;
            x_size = 1;
            data[0] = t;
        }

        //конструктор копирования
        Grid(Grid<T> const& other): data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size) {
            for(size_type x = 0; x < x_size; ++x){
                for(size_type y = 0; y < y_size; ++y){
                    (*this)(y, x) = other(y, x);
                }
            }
        }

        //конструктор перемещения
        Grid(Grid<T>&& other): data(nullptr), y_size(0), x_size(0){
            swap(*this, other);
        };

        //оператор копирования
        Grid<T>& operator=(Grid<T>& other){
            if(this == &other){
                return *this;
            }
            Grid<T> tmp = Grid(other);
            swap(*this, tmp);
            return *this;
        };

        //оператор перемещения
        Grid<T>& operator=(Grid<T>&& other){
            Grid<T> tmp = Grid(std::move(other));
            swap(*this, tmp);
            return *this;
        };

        //деструктор
        ~Grid(){
            if(data != nullptr){
                delete[] data; 
            }
        }

        T operator()(size_type y_idx, size_type x_idx) const{
            return data[y_idx * x_size + x_idx];
        }
        T& operator()(size_type y_idx, size_type x_idx){
            return data[y_idx * x_size + x_idx];
        }
        Grid<T>& operator=(T const& t){
            for (auto it = data, end = data + x_size * y_size; it != end; ++it){
                *it = t;
            }
            return *this;
        }
        size_type get_y_size() const{
            return y_size;
        }
        size_type get_x_size() const{ 
            return x_size;
        }

        void print(){
            for(size_type y = 0; y < y_size; ++y){
                for(size_type x = 0; x < x_size; ++x){
                    std::cout << (*this)(y, x) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
};

int main(){ 
    //применение класса
    Grid<float> gr1 = Grid<float>(2, 5);
    gr1.print();
    gr1 = 3;
    gr1.print();

    Grid<float> gr2 = Grid<float>(gr1);
    gr2.print();

    Grid<float> gr3 = gr2;
    gr2.print();

    Grid<float> gr4 = Grid<float>(std::move(gr3));
    gr4.print();

    Grid<float> gr0 = Grid<float>(10.0);
    gr0.print();

    Grid<float> gr5 = Grid<float>(5, 5, 0.5);
    gr5.print();
}