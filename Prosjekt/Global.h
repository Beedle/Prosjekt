//Globale funksjoner


#pragma once

#include "Hotell.h"

#include <string>


using namespace std;


string les(const char txt[]);
char les(bool type);

void menu();

void fraFil(string file, Hotell *hotell);

//henter respektiv fil.
string getfil();