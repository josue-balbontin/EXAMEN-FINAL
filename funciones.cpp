#include "funciones.h"

void database_in(vector<input> &data_hub){//funcion para exportar los datos del txt al programa.
    bool confiry=false,confirm=false,confird=false; //variables para confirmar si ya paso un suceso
    string word; // variable donde se guarda las palabras de doc 
    input data; // structura
    string texto; // texto que se recibe del documento
      ifstream database; // Se crea un tipo de dato para trabajar con los archivos
     database.open("database.txt",ios::in); // Se abre el archivo 
    if(database.fail()){ // En caso de que no se pueda abrir el archivo
        cout<<"No se encontro el archivo se va a proceder a crear uno nuevo...";
        database.open("database.txt",ios::app);
        cout<<endl;
        return ;
    }
    while(!database.eof()){ //mientras no se termine el documento no para
      getline(database,texto); // obtiene linea por linea del documento
        for(int i=0;i<texto.size();i++){ //mientras no llegue al final de la linea no para
            if(texto[i]!='y' && confiry==false){ // copia todo mientras no se detecte una y
                word=word+texto[i];
            }
            if(texto[i]=='y' && confiry==false){ // se detecta la y asi que se guarda una condicion bool de y para decir que se detecto y se guarda en data
                confiry=true;
                data.year=stoi(word);
                word="";
                continue;
            }
            if(texto[i]!='m' && confirm==false && confiry==true){
                word=word+texto[i];
            }
            if(texto[i]=='m' &&  confirm==false && confiry==true){
                confirm=true;
                data.month=stoi(word);
                word="";
                continue;
            }
              if(texto[i]!='d' && confird==false && confiry==true && confirm==true){
                word=word+texto[i];
            }
            if(texto[i]=='d' && confird==false && confiry==true && confirm==true){
                confird=true;
                data.day=stoi(word);
                word="";
                continue;
            }
           if(confird==true && confiry==true && confirm==true){ //si paso por todo lo anterior significa que lo sgt es el event
            word=word+texto[i];
           }
        }
        //guarda la ultima palabra "event"  limpia word y limpia los bool y hace pushback para continuar con la otra linea
        data.event=word;
        word="";
        confiry=false,confirm=false,confird=false; 
        data_hub.push_back(data);
    }
}

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
        database_out(data_hub);

    }
}

void database_out(const vector<input> &data){//funcion para agregar datos al txt
    remove("database.txt");
    ofstream database; // Se crea un tipo de dato para trabajar con los archivos
     database.open("database.txt",ios::app); // Se abre el archivo y si no existe se crea
    if(database.fail()){ // En caso de que no se pueda crear el archivo
        cout<<"no se pudo abrir el archivo";
    }
    for(int i =0;i<data.size();i++){    //se agregan los datos al archivo
    database<<data[i].year<<"y"<<data[i].month<<"m"<<data[i].day<<"d"<<data[i].event<<endl;
    }

}

void delete_identical_events (vector<input> &data_hub){ //elimina un evento si hay otro evento identico
    for (int i = 0; i<data_hub.size(); ++i){ //se recorre todos los elementos de data_hub
            for (int j = i+1; j<data_hub.size();){ //j iniciara en un elemento despues de i
                if (data_hub[j].year == data_hub[i].year && data_hub[j].month == data_hub[i].month && data_hub[j].day == data_hub[i].day 
                    && data_hub[j].event == data_hub[i].event) {
                    //si se encuentra un elemento con exactamente los mismos valores se elimina la copia
                    data_hub.erase(data_hub.begin() + j);    
                }
                else{
                    ++j; //Si no encuentra una copia ahi recien se incrementa j
                    //Ejemplo para que se entienda la logica: 
                    //Obviemos la fecha y digamos que hay un evento a, evento b, copia evento a, evento c, evento d
                    //i iniciara en evento a y j iniciara en evento b, se compara si evento a y evento b son iguales, como no lo son, j se incrementa
                    //i sigue en evento a y j ahora esta en copia evento a, como son iguales se elimina copia evento a, y al eliminarse quedaria asi:
                    //evento a, evento b, evento c, evento d, como habras notado j no cambia porque al eliminarse copia evento a, el evento c se fue para atras y ocupo su numero de indice            }
                    //si hubiera puesto que j se incrementaba en el for se saltaria al evento d y nunca hubieramos podido comparar el evento c
                }
            }
    }
}

void ascending_order (vector<input> &data_hub){ //funcion para ordenar de forma ascendente

    vector<input> data_hub_copy = data_hub; //creo una copia de data_hub para no alterarla
    vector<input> data_hub_orderly (data_hub.size()); //creo un vector vacio con "data_hub.size" valores donde agregare los datos ordenados
    while(data_hub_copy.size()>0){ //si la copia de data_hub se queda sin elementos se termina el bucle
            //de manera arbitraria pongo como minimo momentaneamente el primer valor de cada dato y por lo tanto el indice seria 0
            int index = 0;
            for (int i = 1; i<data_hub_copy.size(); ++i){ //el bucle recorrera cada dato de data_hub_copy
                if (data_hub_copy[i].year<data_hub_copy[index].year || (data_hub_copy[i].year == data_hub_copy[index].year && data_hub_copy[i].month<data_hub_copy[index].month) ||
                    (data_hub_copy[i].year == data_hub_copy[index].year && data_hub_copy[i].month == data_hub_copy[index].month && data_hub_copy[i].day<data_hub_copy[index].day)) {
                    // si se encuentra una fecha menor se actualiza el índice
                    index = i;
                }
            }
            data_hub_orderly.push_back(data_hub_copy[index]); //se agrega la fecha mas antigua de data_hub_copy, al vector data_hub_orderly
            data_hub_copy.erase(data_hub_copy.begin() + index); //se elimina esa fecha de data_hub_copy para que ya no la tome en cuenta
    }
    data_hub = data_hub_orderly; //data_hub toma los valores de data_hub_orderly
}


