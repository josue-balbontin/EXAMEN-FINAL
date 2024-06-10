#include "funciones.h"

void database_in (vector<input> &data_hub){//funcion para exportar los datos del txt al programa.
    bool confiry = false, confirm = false, confird = false; 
    string word; 
    input data; 
    string texto; 
    ifstream database; 
    database.open("database.txt", ios::in); 
    if (database.fail()){ 
        cout<<"No se encontro el archivo se va a proceder a crear uno nuevo...";
        database.open("database.txt",ios::app);
        cout<<endl;
        return ;
    }
    while (!database.eof()){ 
      getline(database,texto); 
        for (int i = 0; i < texto.size(); ++i){ 
            if (texto[i] != 'y' && confiry == false){ 
                word=word+texto[i];
            }
            if (texto[i] == 'y' && confiry == false){ 
                confiry = true;
                data.year = stoi(word);
                word = "";
                continue;
            }
            if (texto[i] != 'm' && confirm == false && confiry == true){
                word = word + texto[i];
            }
            if (texto[i] == 'm' &&  confirm == false && confiry == true){
                confirm = true;
                data.month = stoi(word);
                word = "";
                continue;
            }
            if (texto[i] != 'd' && confird == false && confiry == true && confirm == true){
                word = word + texto[i];
            }
            if (texto[i] == 'd' && confird == false && confiry == true && confirm == true){
                confird = true;
                data.day = stoi(word);
                word = "";
                continue;
            }
            if (confird == true && confiry == true && confirm == true){ 
                word = word + texto[i];
           }
        }
        //guarda la ultima palabra "event"  limpia word y limpia los bool y hace pushback para continuar con la otra linea
        data.event = word;
        word = "";
        confiry = false, confirm = false, confird = false; 
        data_hub.push_back(data);
    }
    data_hub.erase(data_hub.end());
}

void database_out (const vector<input> &data){//funcion para agregar datos al txt
    remove("database.txt");
    ofstream database; 
    database.open("database.txt", ios::app); 
    if (database.fail()){ 
        cout<<"no se pudo abrir el archivo";
    }
    for (int i = 0; i < data.size(); ++i){ 
        database<<data[i].year<<"y"<<data[i].month<<"m"<<data[i].day<<"d"<<data[i].event<<endl;
    }            
}

void check_data (string command, vector<input> &data_hub){ //funcion para verificar si los datos son correctos
    input data; 
    string date, event;
    string info; 
    getline(cin,info); 
    string event_no_spaces; 
    string year, month, day, extra = ""; 
    unsigned short int script = 0 ,script_control=0 ; 
    bool first_negation = false, second_negation = false; 
    bool pass = true; 
    for(int i =0;i<info.size();++i){
        if(info[i]=='-'){
            ++script;
        }
    }
    for(int i =0; i<info.size();i++){
        if(script_control<=script && pass != false){
            if(info[i]=='-'){
                ++script_control;
            }
            if(script_control==script && info[i]==' '){
                pass=false;
            } 
            if(pass==true){
             date=date+info[i];
            }
        }
        else{
        event=event+info[i];
        }
    }
    script=0;
    pass=true;
    for (int i = 0; i < date.size(); ++i){ 
        if (date[i] == '0' || date[i] == '1' || date[i] == '2' || date[i] == '3' || date[i] == '4' || date[i] == '5' || date[i] == '6' || date[i] == '7' || date[i] == '8' || date[i] == '9' || date[i] == '-' || date[i]=='+'){ 
            if (date[i] == '-' && i != 0){ 
                ++script;   
                if (date[i+1] == '-'){ 
                    if (script == 1){ 
                        first_negation = true;
                    }
                    if (script == 2){   
                        second_negation = true;
                    }
                    ++i; 
                }    
            }
            if (script == 0){ 
                year = year + date[i];
            }
            if (script == 1){ 
                month = month + date[i];
            }
            if (script == 2){ 
                day = day + date[i];
            }
            if (script > 2){ 
                extra = extra + date[i];
            }
            if (extra.size() > 0){ 
                cout<<"Wrong date format:"<<date<<endl;
                pass = false;
                break;
            }
        }
        else{ 
            cout<<"Wrong date format:"<<date<<endl;
            pass = false;
            break;
        }
    }
    //se comprueba si hay +
    unsigned short int mas=0;
    bool mas_true=false,wrong_format=false;
    for(int i=0;i<year.size();i++){
        if(year[i]=='+'){
            mas++;
        }
        if(year[0]=='-' && year[1]=='+' || i==0 && year[i]=='+'){
            mas_true=true;
        }
        if(mas>1){
             mas_true=false;
            break;
        }
    }
    if(mas_true==true){
        if(year[0]=='-'){
            year.erase(1,1);
        }
        else{
            year.erase(year.begin());
            
        }
    }
    if(mas_true==false && mas>0){
        wrong_format=true;
    }
     mas=0;mas_true=false;
    for(int i=0;i<month.size();i++){
        if(month[i]=='+'){
            mas++;
        }
        if(month[1]=='+'){
            mas_true=true;
        }
        if(mas>1){
             mas_true=false;
            break;
        }
    }
    if(mas_true==true){
        month.erase(1,1);
    }
    if(mas_true==false && mas>0){
         wrong_format=true;
    }
      mas=0;mas_true=false;
    for(int i=0;i<day.size();i++){
        if(day[i]=='+'){
            mas++;
        }
        if(day[1]=='+'){
            mas_true=true;
        }
        if(mas>1){
             mas_true=false;
            break;
        }
    }
    if(mas_true==true){
        day.erase(1,1);
    }
    if(mas_true==false && mas>0){
       wrong_format=true;
    }
    if(wrong_format==true){
         cout<<"Wrong date format:"<<date<<endl;
        pass = false;
    }
    if (pass == true){ //en caso de que todo lo anterior este bien hay que verificar si hay negativos y si no se pasa de la fecha
        if (first_negation == true){ 
            cout<<"Month value is invalid: "<< month<<endl;
        }
        else if (second_negation == true){
            cout<<"Day value is invalid: "<<day<<endl;
        }
        else if(abs(stoi(month)) > 12 || abs(stoi(month)) == 0 ){ 
            cout<<"Month value is invalid: "<<abs(stoi(month))<<endl;
        }
        else if(abs(stoi(day)) > 31 || abs(stoi(day)) == 0 ){ 
            cout<<"Day value is invalid: "<<abs(stoi(day))<<endl;
        }
        else{ // en caso de que todo este bien 
            data.year = stoi(year); 
            data.month = abs(stoi(month));
            data.day = abs(stoi(day));
            for (int i = 0; i < event.size(); ++i){ 
                if (event[i] == ' '){
                    continue;
                }
                else{
                    event_no_spaces = event_no_spaces + event[i];
                }
            }
            data.event = event_no_spaces;
            //Hasta aqui se garantiza que el formato y la fecha es valida
            if ((command == "add" || command == "ADD" || command == "Add") && data.event != ""){
                data_hub.push_back(data); 
                database_out(data_hub);
            }
            if (command == "del" || command == "DEL" || command == "Del"){
                del (data.year, data.month, data.day, data.event, data_hub);
            }
            if (command == "find" || command == "FIND" || command == "Find"){
                find (data.year, data.month, data.day, data_hub);
            }
        }
    }
}

void delete_identical_events (vector<input> &data_hub){ 
    for (int i = 0; i<data_hub.size(); ++i){ 
            for (int j = i+1; j<data_hub.size();){ 
                if (data_hub[j].year == data_hub[i].year && data_hub[j].month == data_hub[i].month && data_hub[j].day == data_hub[i].day 
                    && data_hub[j].event == data_hub[i].event){
                    //si se encuentra un elemento con exactamente los mismos valores se elimina la copia
                    data_hub.erase(data_hub.begin() + j);    
                }
                else{
                    ++j; 
                }
            }
    }
}

void ascending_order(vector<input> &data_hub) {
    //ordenar la fecha
    vector<input> data_hub_copy = data_hub; 
    vector<input> data_hub_orderly; 
    while(data_hub_copy.size() > 0){ 
            int index = 0;
            for (int i = 1; i < data_hub_copy.size(); ++i){ 
                if (data_hub_copy[i].year < data_hub_copy[index].year || (data_hub_copy[i].year == data_hub_copy[index].year && data_hub_copy[i].month < data_hub_copy[index].month) ||
                    (data_hub_copy[i].year == data_hub_copy[index].year && data_hub_copy[i].month == data_hub_copy[index].month && data_hub_copy[i].day < data_hub_copy[index].day)) {
                    // si se encuentra una fecha menor se actualiza el índice
                    index = i;
                }
            }
            data_hub_orderly.push_back(data_hub_copy[index]); 
            data_hub_copy.erase(data_hub_copy.begin() + index); 
    }
    data_hub = data_hub_orderly; 
    // Ordenar el evento alfabéticamente según el valor de comparacion de strings
    for (int i = 0; i < data_hub.size(); ++i) {
        for (int j = i + 1; j < data_hub.size(); ++j) {
            if (data_hub[j].year == data_hub[i].year && data_hub[j].month == data_hub[i].month && data_hub[j].day == data_hub[i].day && data_hub[j].event != data_hub[i].event) {
                string first_event = data_hub[i].event;
                string second_event = data_hub[j].event;
                if (second_event < first_event) {
                    swap(data_hub[i].event, data_hub[j].event);
                }
            }
        }
    }
}

void print(vector<input> data_hub) {
    for (int i = 0; i < data_hub.size(); ++i) {
        if (data_hub[i].year >= 0) {
            for (int j = to_string(data_hub[i].year).size(); j < 4; ++j) {
                cout<<"0";
            }
            cout<<data_hub[i].year<<"-";
            if (data_hub[i].month < 10) {
                cout<<"0";
            }
            cout<<data_hub[i].month<<"-";
            if (data_hub[i].day < 10) {
                cout<<"0";
            }
            cout<<data_hub[i].day<<" ";
        }
        else {
            cout<<"-";
            for (int j = to_string(abs(data_hub[i].year)).size(); j < 4; ++j) {
                cout<<"0";
            }
            cout<<abs(data_hub[i].year)<<"-";
            if (data_hub[i].month < 10) {
                cout<<"0";
            }
            cout<<data_hub[i].month<<"-";
            if (data_hub[i].day < 10) {
                cout<<"0";
            }
            cout<<data_hub[i].day<<" ";
        }
        // Imprimir todos los eventos de la misma fecha en una línea
        string print_event = data_hub[i].event;
        for (int j = i + 1; j < data_hub.size();) {
            if (data_hub[j].year == data_hub[i].year &&
                data_hub[j].month == data_hub[i].month &&
                data_hub[j].day == data_hub[i].day) {
                print_event += " " + data_hub[j].event;
                data_hub.erase(data_hub.begin() + j);
            }
            else {
                ++j;
            }
        }
        cout<<print_event<<endl;
    }
}

void del (int del_year, int del_month, int del_day, string del_event, vector <input> &data_hub){ //funcion para eliminar eventos
    int confirmation = 0;
    if (del_event != ""){ 
        for (int i = 0; i<data_hub.size();){
            if (data_hub[i].year == del_year && data_hub[i].month == del_month && data_hub[i].day == del_day && data_hub[i].event == del_event){
                data_hub.erase(data_hub.begin() + i);
                cout<<"Deleted successfully"<<endl;
                ++confirmation;
            }
            else{
                ++i;
            }
        }
        if (confirmation == 0){
            cout<<"Event not found"<<endl;
        }
    }
    else{
        for (int i = 0; i<data_hub.size();){
            if (data_hub[i].year == del_year && data_hub[i].month == del_month && data_hub[i].day == del_day){
                data_hub.erase(data_hub.begin() + i);
                ++confirmation;
            }
            else{
                ++i;
            }
        }
        cout<<"Deleted "<<confirmation<<" events"<<endl;
    }
}

void find (int find_year, int find_month, int find_day, vector<input> data_hub) {
    for (int i = 0; i < data_hub.size(); ++i) {
        if (data_hub[i].year == find_year && data_hub[i].month == find_month && data_hub[i].day == find_day) {
            cout<<data_hub[i].event<<endl;
        }
    }
}

