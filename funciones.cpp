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

void print_bd(const vector<input> &data_hub){ // funcion para imprimir todo lo que esta en el vector
    for(int i=0;i<data_hub.size();i++){ // ciclo que recorre todo el vector
        if(data_hub[i].year>=0){ // si año es mayor a 0
        for(int j=to_string(data_hub[i].year).size();j<4;j++){
             cout<<0;
        }
        cout<<data_hub[i].year<<"-";
        if(data_hub[i].month<10){ //si mes es menor a 10
            cout<<0;
        }
        cout<<data_hub[i].month<<"-"<<data_hub[i].day<<" "<<data_hub[i].event<<endl;
        }
        if(data_hub[i].year<0){ //si año es menor a 0
            cout<<"-";
        for(int j=to_string(abs(data_hub[i].year)).size();j<4;j++){
             cout<<0;
        }
        cout<<abs(data_hub[i].year)<<"-";
        if(data_hub[i].month<10){ //si mes es menor a 10
            cout<<0;
        }
        cout<<data_hub[i].month<<"-"<<data_hub[i].day<<" "<<data_hub[i].event<<endl;
        }
        
        
        }
    }

void check_data (vector<input> &data_hub){ // funcion para checkear la informacion y hacer el add
    input data; //variable para hacer el push
    string date,event;cin>>date;getline(cin,event); //variable de entrada la fecha "date" y el evento "event"
    string evento;  //el evento sin espacios
    string year,month,day,extra="";  //valores para el trabajo
    unsigned short int guion=0; //contador de guiones
    bool nega1=false,nega2=false; //saber si hay un negativo
    bool pass=true; // en caso de que todo este bien 
    for(int i=0; i<date.size();i++){ //se hace un bucle que recorra toda la strin de date 1-1-1 
        if(date[i]=='0' || date[i]=='1' || date[i]=='2' || date[i]=='3' || date[i]=='4' || date[i]=='5' || date[i]=='6' || date[i]=='7' || date[i]=='8' || date[i]=='9' || date[i]=='-'){ // verifica si no hay una letra o signo raro
            if(date[i]=='-' && i!=0){ // en caso de que se halle un guion 
                 guion++;   //suma un guion y de paso usarlo como punto de control
                if(date[i+1]=='-'){ //si hay un gion despues de un gion se lo toma como si hubiera un negativo y no se imprime
                    if(guion==1){ //toma el caso de que si hay un negativo  cuando hay solo un gion por obvias rasones seria el del mes
                        nega1=true;
                    }
                    if(guion==2){   //lo mismo que el anterior pero para dia 
                        nega2=true;
                    }
                    i++; //suma i una vez para que haci no se tome en cuenta el guion del negativo
                }
            }
            if(guion==0){ //si no hay ningun guion por obstante seria  año
                year=year+date[i];
            }
             if(guion==1){ // seria mes
       
                month=month+date[i];
            }
             if(guion==2){ //seria dia
                day=day+date[i];
            }
            if(guion>2){ //si hay mas guiones entonces eso no esta en ninguno de esos valores o esta mal escrito
                extra=extra+date[i];
            }
            if(extra.size()>0){ //por obstante el formato estaria mal e imprime el error
                cout<<"Wrong date format:"<<date<<endl;
                pass=false;
                break;
            }
        }
        else{ //si se detecta una palabra o caracter no numero ni guion
            cout<<"Wrong date format:"<<date<<endl;
            pass=false;
            break;
        }
    }

        if(pass==true){ //en caso de que todo lo anterior este bien hay que verificar si hay negativos y si no se pasa de la fecha
           if(nega1==true){ //en caso de que se detecte el negativo del mes como true entonces esta mal 
                cout<<"Month value is invalid: "<< month<<endl;
           }
           else if(nega2==true){// lo mismo que el anterior pero para dia 
            cout<<"Day value is invalid: "<<day<<endl;
           }
            else if(abs(stoi(month))>12 || abs(stoi(month))==0 ){ // en caso de que el mes sea mayor a doce o 0 "no puede ser negativo por que ya se comprueba y pro el valor absoulo que se usa pro que se guarda en la variable como -mes-dia por los guiones que separan las fechas"
                cout<<"Month value is invalid: "<< abs(stoi(month))<<endl;
            }
             else if(abs(stoi(day))>31 || abs(stoi(day))==0 ){ //lo mismo que el anterior pero para el caso dia
                cout<<"Day value is invalid: "<< abs(stoi(day))<<endl;
            }
            else{ // en caso de que todo este bien 
                data.year=stoi(year); //se guarda en la variable imput
                data.month=abs(stoi(month));
                data.day=abs(stoi(day));
               for(int i=0 ;i<event.size();i++){ // funcion para quitar los espacios de event y no producir problemaas
                    if(event[i]==' '){
                        continue;
                    }
                    else{
                        evento=evento+event[i];
                    }
               }
               data.event=evento;
               data_hub.push_back(data);
            }
        }
        else{

        }

}