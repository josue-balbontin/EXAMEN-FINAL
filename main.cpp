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
            check_data (command, data_hub);
            database_out(data_hub);
        }
        else if (command == "Del" || command == "DEL" || command == "del") {
            check_data (command, data_hub);
        }
        else if (command == "Find" || command == "FIND" || command == "find") {
            //codigo
            cout<<"mostrando find";
        }
        else if (command == "Print" || command == "PRINT" || command == "print") {
            delete_identical_events(data_hub);
            ascending_order(data_hub);
            print(data_hub);
            database_out(data_hub);

        }
        else {
            cout<<"Unknown command: "<<command<<endl;
        }
    }

    return 0;
}

