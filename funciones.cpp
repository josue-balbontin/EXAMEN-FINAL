#include "funciones.h"

void database_in(vector<input> &data_hub){
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

void database_out(const vector<input> &data){
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
