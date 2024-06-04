#include "funciones.h"

//g++ main.cpp funciones.cpp -o database

int main() {
    vector<input> data_hub; //creo un vector de estructuras que guardara los datos
    database_in(data_hub);
    check_data (data_hub);
    return 0;
}