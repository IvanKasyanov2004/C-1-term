#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>
using namespace std;
int const N = 200000;

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


std::mt19937 gen(static_cast<unsigned>(time(nullptr)));

int dice(int min, int max) {
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void generate_crystal(Cell* &cells_arr, int width){
    cells_arr = new Cell[width];
    for(int x = 0; x < width; x++){
        if(x == 0 or x == width - 1){
            cells_arr[x].border = 1;
        }
    }

    for(int x = 1; x < width - 1; x++){
        cells_arr[x].left = &cells_arr[x - 1];
        cells_arr[x].right = &cells_arr[x + 1];
    }
}

void generate_atoms(Atom* &atoms_arr, int atoms_number){
    atoms_arr = new Atom[atoms_number];
}

void add_atoms(Cell* &cells_arr, Atom* &atoms_arr, int width, int atoms_number){
    srand(time(0));
    int const  N = 1000000;
    int p = width;
    int arr[N] = {0};
    int count = 0;
    int index;

    while(count < atoms_number){
        index = dice(0, N) % p;
        if(arr[index] == 0){
            arr[index] = 1;
            count += 1;
        }
    }

    count = 0;
    for(int x = 0; x < width; x++){
        if(arr[x] == 1){
            atoms_arr[count].cell = &cells_arr[x];
            cells_arr[x].atom1 = &atoms_arr[count];
            count += 1;
        }
    }
}

void remove_atoms(Cell* &cells_arr, Atom* &atoms_arr, int atoms_number){
    for(int i = 0; i < atoms_number; i++){
        atoms_arr[i].cell->atom1 = nullptr;
        atoms_arr[i].cell_prev = nullptr;
        atoms_arr[i].cell = nullptr;
        atoms_arr[i].stop = 0;
    }
}

void delete_crystal(Cell* &cells_arr){
    delete[] cells_arr;
}

void delete_atoms(Atom* &atoms_arr){
    delete[] atoms_arr;
}

void show_atoms(Cell* &cells_arr, Atom* &atoms_arr, int width, int atoms_number){
    for(int x = 0; x < width; x++){
        if(cells_arr[x].atom1 == nullptr){
            cout << "-" << " ";
        }
        else if(cells_arr[x].atom1->stop == 1){
            cout << 2 << " ";
        }
        else if(cells_arr[x].atom1->stop == 0){
            cout << 1 << " ";
        }
    }
    cout << endl;
}

int move_atoms(Cell* &cells_arr, Atom* &atoms_arr, int width, int atoms_number){
    srand(time(0));
    int atoms_stopped = 0;
    int steps = 0;
    while(atoms_stopped < atoms_number){
        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].cell->border == 1 and atoms_arr[i].stop == 0){
                atoms_arr[i].stop = 1;
                atoms_stopped += 1;
            }
        }

        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].stop == 0){
                if(atoms_arr[i].cell->right->atom1 != nullptr){
                    atoms_arr[i].stop = 1;
                    atoms_stopped += 1;
                    if(atoms_arr[i].cell->right->atom1->stop == 0){
                        atoms_arr[i].cell->right->atom1->stop = 1;
                        atoms_stopped += 1;
                    }
                }
            }
        }

        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].stop == 0){
                if(atoms_arr[i].cell->left->atom1 != nullptr){
                    atoms_arr[i].stop = 1;
                    atoms_stopped += 1;
                    if(atoms_arr[i].cell->left->atom1->stop == 0){
                        atoms_arr[i].cell->left->atom1->stop = 1;
                        atoms_stopped += 1;
                    }
                }
            }
        }


        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].stop == 0){
                int way = dice(0, N) % 2;
                atoms_arr[i].cell_prev = atoms_arr[i].cell;
                if(way == 0){
                    atoms_arr[i].cell = atoms_arr[i].cell->right;
                }
                if(way == 1){
                    atoms_arr[i].cell = atoms_arr[i].cell->left;
                }
                atoms_arr[i].cell_prev->atom1 = nullptr;


                if(atoms_arr[i].cell->atom1 == nullptr){
                    atoms_arr[i].cell->atom1 = &atoms_arr[i];
                }
                else if(atoms_arr[i].cell->atom2 == nullptr){
                    atoms_arr[i].cell->atom2 = &atoms_arr[i];
                }
            }
        }

        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].cell->atom2 != nullptr){
                atoms_arr[i].cell->atom2->cell = atoms_arr[i].cell->atom2->cell_prev;
                atoms_arr[i].cell->atom2->cell->atom1 = &atoms_arr[i];
                atoms_arr[i].cell->atom2 = nullptr;
            }
        }  
        steps += 1;     
    }
    return steps;
}

void calculate_steps(Cell* &cells_arr, Atom* &atoms_arr, int sizes_number, int size_step, int rep_number, int atoms_number){
    remove("3.txt");
    std::ofstream out;
    out.open("3.txt", std::ios::app);
    for(int i = 1; i < sizes_number + 1; i++){
        int size = i * size_step;
        out << size << " ";
        generate_crystal(cells_arr, size);
        generate_atoms(atoms_arr, atoms_number);

        int sum_steps = 0;
        for(int j = 0; j < rep_number; j++){
            add_atoms(cells_arr, atoms_arr, size, atoms_number);
            sum_steps += move_atoms(cells_arr, atoms_arr, size, atoms_number);
            remove_atoms(cells_arr, atoms_arr, atoms_number);
        }

        out << sum_steps << endl;
        delete_atoms(atoms_arr);
        delete_crystal(cells_arr);
        }
    out.close(); 
}

void calculate_all_steps(Cell* &cells_arr, Atom* &atoms_arr, int sizes_number, int size_step, int rep_number){
    remove("3_all.txt");
    std::ofstream out;
    out.open("3_all.txt", std::ios::app);
    int atoms_numbers[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 17, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150};
    for(int k = 0; k < 30; k++){
        int atoms_number = atoms_numbers[k];
        for(int i = 1; i < sizes_number + 1; i++){
            int size = i * size_step;
            out << size << " ";
            generate_crystal(cells_arr, size);
            generate_atoms(atoms_arr, atoms_number);

            int sum_steps = 0;
            for(int j = 0; j < rep_number; j++){
                add_atoms(cells_arr, atoms_arr, size, atoms_number);
                sum_steps += move_atoms(cells_arr, atoms_arr, size, atoms_number);
                remove_atoms(cells_arr, atoms_arr, atoms_number);
            }

            out << sum_steps / rep_number << endl;
            delete_atoms(atoms_arr);
            delete_crystal(cells_arr);
            }
    }
    out.close(); 
}


int main(){
    Cell* cells_arr;
    Atom* atoms_arr;
    calculate_all_steps(cells_arr, atoms_arr, 15, 200, 200);
}