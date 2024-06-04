#include "funciones.h"

void check_data (vector<input> &data_hub){ //funcion para verificar si los datos son correctos
    while (true){
        input data;
        cin>>data.year;
        cin.ignore(); //ignora el siguiente caracter ya que el siguiente caracter es un guion
        cin>>data.month;
        cin.ignore();
        cin>>data.day;
        cin.ignore(); //ignora el siguiente caracter ya que el siguiente caracter es un espacio
        cin>>data.event;
        if (data.month<1 || data.month>12){
            cout<<"Month value is invalid: "<<data.month<<endl; //como el dato esta fuera del rango se envia una alerta
            break; //se termina el bucle
        }
        if (data.day<1 || data.day>31){
            cout<<"Day value is invalid: "<<data.day<<endl; 
            break;          
        }
        //NOTA: No tomo el caso de doble guion ¿Porque? Porque si el usuario ingresa tres o mas guiones el programa tomara el dato como 0 y al estar 0 fuera del rango la condicional enviara una alerta
        //NOTA: Hay que preguntar al Ingeniero que mensaje enviar cuando se colocan varios guiones
        data_hub.push_back(data); //Como todos los datos son correctos, ingreso los datos al vector de estructuras
        break;
    }
}