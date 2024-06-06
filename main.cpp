#include "funciones.h"

//g++ main.cpp funciones.cpp -o database

int main() {
    vector<input> data_hub; //creo un vector de estructuras que guardara los datos
    database_in(data_hub);

    while (true) {
        string command;
        cin>>command;
        cin.ignore();
        if (command == "Add" || command == "ADD" || command == "add") {
            check_data (data_hub); //como le entrada del comando esta en formato fecha-evento se usa check_data
            delete_identical_events (data_hub); //se elimina el evento si es repetido
            ascending_order (data_hub); //y luego se reoordenada de forma ascentende todo el vector data_hub
            ascending_order_event (data_hub); //ordeno los eventos
        }
        else if (command == "Del" || command == "DEL" || command == "del") {
            //codigo
        }
        else if (command == "Find" || command == "FIND" || command == "find") {
            //codigo
        }
        else if (command == "Print" || command == "PRINT" || command == "print") {
            //codigo
        }
        else {
            cout<<"Unknown command: "<<command<<endl;
        }
    }

    return 0;
}

