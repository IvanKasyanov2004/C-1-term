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
    std::mt19937 gen(static_cast<unsigned>(time(nullptr))); // seed the generator
    std::uniform_int_distribution<> distr(0, 100000); // define the range
    while(count < atoms_number){
        index = distr(gen) % p;
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

int move_atoms(Cell** &cells_arr, Atom* &atoms_arr, int atoms_number){
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
                if(atoms_arr[i].cell->up->atom1 != nullptr){
                    atoms_arr[i].stop = 1;
                    atoms_stopped += 1;
                    if(atoms_arr[i].cell->up->atom1->stop == 0){
                        atoms_arr[i].cell->up->atom1->stop = 1;
                        atoms_stopped += 1;
                    }
                }
            }
        }

        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].stop == 0){
                if(atoms_arr[i].cell->down->atom1 != nullptr){
                    atoms_arr[i].stop = 1;
                    atoms_stopped += 1;
                    if(atoms_arr[i].cell->down->atom1->stop == 0){
                        atoms_arr[i].cell->down->atom1->stop = 1;
                        atoms_stopped += 1;
                    }
                }
            }
        }      


        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].stop == 0){
                int way = rand() % 4;
                atoms_arr[i].cell_prev = atoms_arr[i].cell;
                if(way == 0){
                    atoms_arr[i].cell = atoms_arr[i].cell->right;
                }
                if(way == 1){
                    atoms_arr[i].cell = atoms_arr[i].cell->left;
                }
                if(way == 2){
                    atoms_arr[i].cell = atoms_arr[i].cell->up;
                }
                if(way == 3){
                    atoms_arr[i].cell = atoms_arr[i].cell->down;
                }
                atoms_arr[i].cell_prev->atom1 = nullptr;


                if(atoms_arr[i].cell->atom1 == nullptr){
                    atoms_arr[i].cell->atom1 = &atoms_arr[i];
                }
                else if(atoms_arr[i].cell->atom2 == nullptr){
                    atoms_arr[i].cell->atom2 = &atoms_arr[i];
                }
                else if(atoms_arr[i].cell->atom3 == nullptr){
                    atoms_arr[i].cell->atom3 = &atoms_arr[i];
                }
                else if(atoms_arr[i].cell->atom4 == nullptr){
                    atoms_arr[i].cell->atom4 = &atoms_arr[i];
                } 
            }
        }

        for(int i = 0; i < atoms_number; i++){
            if(atoms_arr[i].cell->atom2 != nullptr){
                atoms_arr[i].cell->atom2->cell = atoms_arr[i].cell->atom2->cell_prev;
                atoms_arr[i].cell->atom2 = nullptr;
            }
            if(atoms_arr[i].cell->atom3 != nullptr){
                atoms_arr[i].cell->atom3->cell = atoms_arr[i].cell->atom3->cell_prev;
                atoms_arr[i].cell->atom3 = nullptr;
            }
            if(atoms_arr[i].cell->atom4 != nullptr){
                atoms_arr[i].cell->atom4->cell = atoms_arr[i].cell->atom4->cell_prev;
                atoms_arr[i].cell->atom4 = nullptr;
            }
        }   
        steps += 1;     
    }
    return steps;
}

void calculate_steps(Cell** &cells_arr, Atom* &atoms_arr, int sizes_number, int size_step, int rep_number, int atoms_number){
    remove("2_11.txt");
    std::ofstream out;
    out.open("2_11.txt", std::ios::app);
    for(int i = 1; i < sizes_number + 1; i++){
        int size = i * size_step;
        out << size << " ";
        generate_crystal(cells_arr, atoms_arr, size, size);
        generate_atoms(atoms_arr, atoms_number);

        int sum_steps = 0;
        for(int j = 0; j < rep_number; j++){
            add_atoms(cells_arr, atoms_arr, size, size, atoms_number);
            sum_steps += move_atoms(cells_arr, atoms_arr, atoms_number);
            remove_atoms(cells_arr, atoms_arr, size, size, atoms_number);
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
    calculate_steps(cells_arr, atoms_arr, 20, 25, 200, 400);
}