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

void check_data (string command, vector<input> &data_hub);
void database_out(const vector<input> &data);
void database_in(vector<input> &data_hub);
void delete_identical_events (vector<input> &data_hub);
void ascending_order (vector<input> &data_hub);
void print (vector<input> &data_hub);
void del (int del_year, int del_month, int del_day, string del_event, vector <input> &data_hub);
