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

void check_data (string command, vector<input> &data_hub){ //funcion para verificar si los datos son correctos
        input data; //le doy nombre a mi estructura
        string user_input, copy_user_input, event_input, copy_event_input, date_string;
        char ignore, ignore_again;
        getline(cin, user_input); //Se guarda la línea completa después de add como una string llamada user_input
        copy_user_input = user_input; //copio la string que ingreso el usuario
        stringstream copy_data_memory (copy_user_input); //creo un area de memoria temporal para extraer solo la fecha independientemente si esta bien o mal
        copy_data_memory>>date_string; //extraigo solamente la primera string que seria la fecha
        
        stringstream data_memory (user_input); //Se crea una área de memoria temporal (como un almacen) que utilizaremos para almacenar los datos antes de usarlos. A diferencia de un string, un stringstream lo podemos usar para extraer los datos almacenados como numeros o chars
        
        if (!(data_memory>>data.year>>ignore>>data.month>>ignore_again>>data.day) || ignore != '-' || ignore_again != '-') {
            //verifico que el formato de la fecha sea correcto
            cout<<"Wrong date format: "<<date_string<<endl; //debido a que el formato es incorrecto le mando la string que extraje anteriormente
            return;
        }
        
        getline(data_memory, event_input); //si hay un evento tambien lo extraigo como una sola linea
        for (int i = 0; i<event_input.size(); ++i){ //creo un bucle para eliminar los espacios
            if (event_input[i]!=' '){
                copy_event_input = copy_event_input + event_input[i];                  
            }
        }
        
        data.event = copy_event_input; //se copia el evento sin espacios en data.event

        if (data.month<1 || data.month>12){
            cout<<"Month value is invalid: "<<data.month<<endl; //como el dato esta fuera del rango se envia una alerta
            return;
        }
        if (data.day<1 || data.day>31){
            cout<<"Day value is invalid: "<<data.day<<endl; 
            return;
        }
        //Hasta aqui se garantiza que el formato y la fecha es valida
        //Dependiendo de cada comando:
        if ((command == "add" || command == "ADD" || command == "Add") && data.event != ""){
            data_hub.push_back(data); //Como todos los datos son correctos, ingreso los datos al vector de estructuras
            database_out(data_hub);
        }
        if (command == "del" || command == "DEL" || command == "Del"){
            int del_year = data.year;
            int del_month = data.month;
            int del_day = data.day;
            string del_event = data.event;
            remove (del_year, del_month, del_day, del_event, data_hub);
        }
}

void database_out(const vector<input> &data){//funcion para agregar datos al txt
    remove("database.txt");
    ofstream database; // Se crea un tipo de dato para trabajar con los archivos
    database.open("database.txt",ios::app); // Se abre el archivo y si no existe se crea
    if (database.fail()){ // En caso de que no se pueda crear el archivo
        cout<<"no se pudo abrir el archivo";
    }
    for (int i =0;i<data.size();i++){ //se agregan los datos al archivo
        database<<data[i].year<<"y"<<data[i].month<<"m"<<data[i].day<<"d"<<data[i].event<<endl;
    }

}

void delete_identical_events (vector<input> &data_hub){ //elimina un evento si hay otro evento identico
    for (int i = 0; i<data_hub.size(); ++i){ //se recorre todos los elementos de data_hub
            for (int j = i+1; j<data_hub.size();){ //j iniciara en un elemento despues de i
                if (data_hub[j].year == data_hub[i].year && data_hub[j].month == data_hub[i].month && data_hub[j].day == data_hub[i].day 
                    && data_hub[j].event == data_hub[i].event){
                    //si se encuentra un elemento con exactamente los mismos valores se elimina la copia
                    data_hub.erase(data_hub.begin() + j);    
                }
                else if (data_hub[j].year == data_hub[i].year && data_hub[j].month == data_hub[i].month && data_hub[j].day == data_hub[i].day 
                    && data_hub[j].event != data_hub[i].event){ //si se encuentra un elemento con la misma fecha pero con diferente evento se suma al evento que se ingreso primero el evento que se ingreso despues
                    data_hub[i].event = data_hub[i].event + " " + data_hub[j].event;
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
    vector<input> data_hub_orderly; //creo un vector vacio donde agregare los datos ordenados
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

void ascending_order_event (vector<input> &data_hub){//funcion para ordenar los eventos de forma desendiente osea a,b,c,d....
    string word;
    bool menor=false;
    vector<string> evento; //vector para guardar todos los eventos y compararlos
    for(int i=0 ;i<data_hub.size();i++){ //inicia un bucle para que se ejecute para todos las structuras que hayan
        for(int j=0;j<data_hub[i].event.size();j++){ // separa las palabras y lo pone en el vector
            if(data_hub[i].event[j]==' '){
                evento.push_back(word);
                word="";
            }
            else{
                word=word+data_hub[i].event[j];
            }
        }
        evento.push_back(word);
        word="";
        while(evento.size()>1){ //mientras el vector no sea menor a 1 de tamaño no par "se estan quitando valores al vector"
            for(int k=0;k<evento.size();k++){
                for(int l=0;l<evento.size();l++){
                    if(evento[k]<=evento[l] && l!=k){
                        menor=true;
                    }
                else if (l!=k){
                    menor=false;
                    break;
                }
                }
                if(menor==true){
                    word=word+evento[k]+" ";
                    evento.erase(evento.begin()+k);
                    menor=false;
                    break;
                }
            }
        } //se completan algunos pasos y se  deja limpio para la sgt interaccion
        word=word+evento[0];
        data_hub[i].event=word;
        evento={""};
        evento.clear();
        word="";
    }
}

void print (vector<input> &data_hub){
    for (int i = 0; i < data_hub.size(); ++i){
        if (data_hub[i].year >= 0){
            for (int j = to_string(data_hub[i].year).size(); j < 4; ++j){
                cout<<"0";
            }
            cout<<data_hub[i].year<<"-";
            if (data_hub[i].month < 10){
                cout<<"0";
            }
            cout<<data_hub[i].month<<"-";
            if (data_hub[i].day < 10){
                cout<<"0";
            }
            cout<<data_hub[i].day<<" "<<data_hub[i].event<<endl;
        }
        else{
            cout<<"-";
            for (int j = to_string(abs(data_hub[i].year)).size(); j < 4; ++j){
                cout<<"0";
            }
            cout<<abs(data_hub[i].year)<<"-";
            if (data_hub[i].month < 10){
                cout<<"0";
            }
            cout<<data_hub[i].month<<"-";
            if (data_hub[i].day < 10){
                cout<<"0";
            }
            cout<<data_hub[i].day<<" "<<data_hub[i].event<<endl;
        }
    }
}

void remove (int del_year, int del_month, int del_day, string del_event, vector <input> &data_hub){ //funcion para eliminar eventos
    if (del_event != ""){ 
        for (int i = 0; i<data_hub.size();){
            if (data_hub[i].year == del_year && data_hub[i].month == del_month && data_hub[i].day == del_day && data_hub[i].event == del_event){
                data_hub.erase(data_hub.begin() + i);
            }
            else{
                ++i;
            }
        }
    }
    else{
        for (int i = 0; i<data_hub.size();){
            if (data_hub[i].year == del_year && data_hub[i].month == del_month && data_hub[i].day == del_day){
                data_hub.erase(data_hub.begin() + i);
            }
            else{
                ++i;
            }
        }
    }
}