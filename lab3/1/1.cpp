#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
using namespace std;


struct Atom;

struct Cell{
    Cell* right = nullptr;
    Cell* left = nullptr;
    Cell* up = nullptr;
    Cell* down = nullptr;
    Atom* atom1 = nullptr;
    Atom* atom2 = nullptr;
    Atom* atom3 = nullptr;
    Atom* atom4 = nullptr;
    int border = 0;
};

struct Atom{
    Cell* cell;
    Cell* cell_prev;
    int stop = 0;
};

void generate_crystal(Cell** &cells_arr, Atom* &atoms_arr, int width, int height){
    cells_arr = new Cell*[width];
    for(int i = 0; i < width; i++){
        cells_arr[i] = new Cell[height];
    }
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(x == 0 or y == 0 or x == width - 1 or y == height - 1){
                cells_arr[x][y].border = 1;
            }
        }
    }

    for(int y = 1; y < height - 1; y++){
        for(int x = 1; x < width - 1; x++){
            cells_arr[x][y].left = &cells_arr[x - 1][y];
            cells_arr[x][y].right = &cells_arr[x + 1][y];
            cells_arr[x][y].up = &cells_arr[x][y - 1];
            cells_arr[x][y].down = &cells_arr[x][y + 1];
        }
    }
}

void generate_atoms(Atom* &atoms_arr, int atoms_number){
    atoms_arr = new Atom[atoms_number];
}

void add_atoms(Cell** &cells_arr, Atom* &atoms_arr, int width, int height, int atoms_number){
    int const  N = 1000000;
    int p = width * height;
    int arr[N] = {0};
    int count = 0;
    int index;

    while(count < atoms_number){
        index = rand() % p;
        if(arr[index] == 0){
            arr[index] = 1;
            count += 1;
        }
    }

    count = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(arr[y * width + x] == 1){
                atoms_arr[count].cell = &cells_arr[x][y];
                cells_arr[x][y].atom1 = &atoms_arr[count];
                count += 1;
            }
        }
    }
}

void remove_atoms(Cell** &cells_arr, Atom* &atoms_arr, int width, int height, int atoms_number){
    for(int i = 0; i < atoms_number; i++){
        atoms_arr[i].cell->atom1 = nullptr;
        atoms_arr[i].cell_prev = nullptr;
        atoms_arr[i].cell = nullptr;
        atoms_arr[i].stop = 0;
    }
}

void delete_crystal(Cell** &cells_arr, Atom* &atoms_arr, int width, int height){
    for(int i = 0; i < width; i++){
        delete[] cells_arr[i];
    }
    delete[] cells_arr;
}

void delete_atoms(Atom* &atoms_arr){
    delete[] atoms_arr;
}

int move_atom(Cell** &cells_arr, Atom* &atoms_arr){
    int atoms_stopped = 0;
    int steps = 0;
    while(atoms_stopped < 1){
        if(atoms_arr[0].cell->border == 1){
            atoms_stopped += 1;
            break;
        }
        int way = rand() % 4;
        if(way == 0){
            atoms_arr[0].cell_prev = atoms_arr[0].cell;
            atoms_arr[0].cell = atoms_arr[0].cell_prev->right;
            atoms_arr[0].cell_prev->atom1 = nullptr;
            atoms_arr[0].cell->atom1 = &atoms_arr[0];
        }
        if(way == 1){
            atoms_arr[0].cell_prev = atoms_arr[0].cell;
            atoms_arr[0].cell = atoms_arr[0].cell_prev->left;
            atoms_arr[0].cell_prev->atom1 = nullptr;
            atoms_arr[0].cell->atom1 = &atoms_arr[0];
        }
        if(way == 2){
            atoms_arr[0].cell_prev = atoms_arr[0].cell;
            atoms_arr[0].cell = atoms_arr[0].cell_prev->up;
            atoms_arr[0].cell_prev->atom1 = nullptr;
            atoms_arr[0].cell->atom1 = &atoms_arr[0];
        }
        if(way == 3){
            atoms_arr[0].cell_prev = atoms_arr[0].cell;
            atoms_arr[0].cell = atoms_arr[0].cell_prev->down;
            atoms_arr[0].cell_prev->atom1 = nullptr;
            atoms_arr[0].cell->atom1 = &atoms_arr[0];
        }
        steps += 1;
    }
    return steps;
}

void calculate_time(Cell** &cells_arr, Atom* &atoms_arr, int sizes_number, int size_step, int rep_number){
    remove("1.txt");
    std::ofstream out;
    out.open("1.txt", std::ios::app);
    for(int i = 1; i < sizes_number + 1; i++){
        int size = i * size_step;
        out << size << " ";
        generate_crystal(cells_arr, atoms_arr, size, size);
        generate_atoms(atoms_arr, 1);

        auto begin = std::chrono::steady_clock::now();
        for(int j = 0; j < rep_number; j++){
            add_atoms(cells_arr, atoms_arr, size, size, 1);
            move_atom(cells_arr, atoms_arr);
            remove_atoms(cells_arr, atoms_arr, size, size, 1);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        int t1 = time_span.count();

        begin = std::chrono::steady_clock::now();
        for(int j = 0; j < rep_number; j++){
            add_atoms(cells_arr, atoms_arr, size, size, 1);
            remove_atoms(cells_arr, atoms_arr, size, size, 1);
        }
        end = std::chrono::steady_clock::now();
        time_span =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        int t2 = time_span.count();

        out << t1 - t2 << endl;

        delete_atoms(atoms_arr);
        delete_crystal(cells_arr, atoms_arr, size, size);
        }
    out.close(); 
}

void calculate_steps(Cell** &cells_arr, Atom* &atoms_arr, int sizes_number, int size_step, int rep_number){
    remove("1_steps.txt");
    std::ofstream out;
    out.open("1_steps.txt", std::ios::app);
    for(int i = 1; i < sizes_number + 1; i++){
        int size = i * size_step;
        out << size << " ";
        generate_crystal(cells_arr, atoms_arr, size, size);
        generate_atoms(atoms_arr, 1);

        int sum_steps = 0;
        for(int j = 0; j < rep_number; j++){
            add_atoms(cells_arr, atoms_arr, size, size, 1);
            sum_steps += move_atom(cells_arr, atoms_arr);
            remove_atoms(cells_arr, atoms_arr, size, size, 1);
        }

        out << sum_steps << endl;
        delete_atoms(atoms_arr);
        delete_crystal(cells_arr, atoms_arr, size, size);
        }
    out.close(); 
}

int main(){
    Cell** cells_arr;
    Atom* atoms_arr;
    calculate_steps(cells_arr, atoms_arr, 20, 50, 1000);
}