#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct input{ //creo las estructuras de los datos que vamos a utilizar
    int year;
    int month;
    int day;
    string event;
};

void check_data (vector<input> &data_hub);
void database_out(const vector<input> &data);
void database_in(vector<input> &data_hub);
void delete_identical_events (vector<input> &data_hub);
