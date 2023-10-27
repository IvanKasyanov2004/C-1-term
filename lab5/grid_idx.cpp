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

        class RowConst{
            friend class Grid;
            private:
                const Grid<T>& grid;
                size_type y_idx;
                size_type x_size;
            
            public:
                RowConst(const Grid<T>& grid, size_type y_idx, size_type x_size): grid(grid), y_idx(y_idx), x_size(x_size){}

                T operator[](size_type x_idx) const{
                    return grid.data[y_idx * x_size + x_idx];
                }
        };

        RowConst operator[](size_type y_idx) const{
            RowConst row = RowConst(*this, y_idx, x_size);
            return row;
        }

        class Row{
            friend class Grid;
            private:
                Grid<T>& grid;
                size_type y_idx;
                size_type x_size;
            
            public:
                Row(Grid<T>& grid, size_type y_idx, size_type x_size): grid(grid), y_idx(y_idx), x_size(x_size){}

                T& operator[](size_type x_idx){
                    return grid.data[y_idx * x_size + x_idx];
                }
        };

        Row operator[](size_type y_idx){
            Row row = Row(*this, y_idx, x_size);
            return row;
        }
};

#include <cassert>
int main(){
    Grid<float> g(3, 2, 0.0f); 
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());
    for(Grid<int>::size_type y_idx = 0; y_idx != g.get_y_size(); ++y_idx){
        for(Grid<int>::size_type x_idx = 0; x_idx != g.get_x_size(); ++x_idx){
            assert(0.0f == g[y_idx][x_idx]);
        }
    }
    for(Grid<int>::size_type y_idx = 0; y_idx != g.get_y_size(); ++y_idx){
        for(Grid<int>::size_type x_idx = 0; x_idx != g.get_x_size(); ++x_idx){
            g[y_idx][x_idx] = 1.0f;
        }
    }
    for(Grid<int>::size_type y_idx = 0; y_idx != g.get_y_size(); ++y_idx){
        for(Grid<int>::size_type x_idx = 0; x_idx != g.get_x_size(); ++x_idx){
            assert(1.0f == g(y_idx , x_idx)); 
            return 0;
        }
    }
}