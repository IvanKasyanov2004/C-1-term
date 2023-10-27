#include <iostream>

template <typename T, unsigned dim>
class Grid final{
    public:
        using value_type = T;
        using size_type = unsigned;

    private:
        T* data;
        size_type sizes[dim];

        void swap(Grid<T, dim>& lha, Grid<T, dim>& rha){
            std::swap(lha.sizes, rha.sizes);
            std::swap(rha.data, lha.data);
        }

    public:
        //конструктор, который выделяет память
        Grid(size_type sizes_prod_, size_type (sizes_)[]):data(new T[sizes_prod_]){
            for(size_type i = 0; i < dim; ++i){
                sizes[i] = sizes_[i];
            }
        }

        //конструктор, принимающий размеры сетки и значение в сетке
        template<typename... Args>
        Grid(T const& t, size_type size, Args... args): data(new T[get_sizes_prod()]){
            read_sizes(size, args...);
            for(size_type i = 0; i < get_sizes_prod(); ++i){
                data[i] = t;
            }
        }
        
        //конструктор для преобразования типов из T в Grid<T, 1>
        Grid(T const& t){
            data = new T[1];
            sizes[0] = 1;
            data[0] = t;
        }

        //конструктор копирования
        Grid(Grid<T, dim> const& other): data(new T[other.get_sizes_prod()]){
            for(size_type i = 0; i < dim; ++i){
                sizes[i] = other.sizes[i];
            }            
            for(size_type i = 0; i < other.get_sizes_prod(); ++i){
                data[i] = other.data[i];
            }
        }

        //конструктор перемещения
        Grid(Grid<T, dim>&& other): data(nullptr){
            swap(*this, other);
        };

        //оператор копирования
        Grid<T, dim>& operator=(Grid<T, dim>& other){
            if(this == &other){
                return *this;
            }
            Grid<T, dim> tmp = Grid(other);
            swap(*this, tmp);
            return *this;
        };

        //оператор перемещения
        Grid<T, dim>& operator=(Grid<T, dim>&& other){
            Grid<T, dim> tmp = Grid(std::move(other));
            swap(*this, tmp);
            return *this;
        };

        //деструктор
        ~Grid(){
            if(data != nullptr){
                delete[] data; 
            }
        }

        size_type get_size(size_type i) const{ //возвращает размер по i измерению
            return sizes[i];
        }

        T& get_data(size_type idx){ //возвращает элемент массива data с индексом idx
            return data[idx];
        }

        template<typename... Args>
        T operator()(size_type idx, Args... args) const{
            Grid<T, dim> indexes =  Grid<T, dim>(T(), idx, args...);  //создается сетка с размерами из индексов (чтобы запомнить и использовать индексы)
            size_type p = 1;
            size_type prod = get_sizes_prod();
            size_type data_idx = 0;  //вычисляется индекс ячейки в массиве data
            for(size_type i = 0; i < dim; ++i){
                p = p * get_size(i);
                data_idx += prod / p * indexes.sizes[i];
            }
            return data[data_idx];
        }

        template<typename... Args>
        T& operator()(size_type idx, Args... args){
            Grid<T, dim> indexes =  Grid<T, dim>(T(), idx, args...);  //создается сетка с размерами из индексов (чтобы запомнить и использовать индексы)
            size_type p = 1;
            size_type prod = get_sizes_prod();
            size_type data_idx = 0;  //вычисляется индекс ячейки в массиве data
            for(size_type i = 0; i < dim; ++i){
                p = p * get_size(i);
                data_idx += prod / p * indexes.sizes[i];
            }
            return data[data_idx];
        }

        void read_sizes(){}

        template<typename... Args> //считывание массива с размерами (рекурсия)
        void read_sizes(size_type size, Args... args){
            this->sizes[dim - 1 - sizeof...(args)] = size;
            read_sizes(args...);
        }

        size_type get_sizes_prod() const{ //выводит произведение размеров
            size_type prod = 1;
            for(size_type i = 0; i < dim; ++i){
                prod *= this->sizes[i];
            }
            return prod;
        }


        Grid<T, dim - 1> operator[](size_type first_idx) const{  //делает сетку из точек, у которых первая координата равна first_idx (срез)
            size_type slice_sizes[dim - 1];
            size_type prod = 1;
            for(size_type i = 0; i < dim - 1; ++i){
                slice_sizes[i] = sizes[i + 1];
                prod *= sizes[i + 1];
            }

            Grid<T, dim - 1> slice = Grid<T, dim - 1>(prod, slice_sizes);

            for(size_type i = 0; i < slice.get_sizes_prod(); ++i){
                slice.get_data(i) = data[get_sizes_prod() / sizes[0] * first_idx + i];
            }
            return slice;
        }
};

#include <cassert>
int main(){
    Grid<float,4> const g4(1.0f, 2, 3, 4, 5);
    Grid<float, 1> const g1(10.0);
    Grid<float,4> g4_copy = g4;

    Grid<float,3> const g3(1.0f, 2, 3, 4);
    assert(1.0f == g3(1, 1, 1));
    Grid<float,2> g2(2.0f, 2, 5); 
    assert(2.0f == g2(1, 1));
    g2 = g3[1];
    assert(1.0f == g2(1, 1));
}