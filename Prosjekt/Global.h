//Globale funksjoner


#pragma once

#include "Hotell.h"

#include <string>


using namespace std;


string les(const char txt[]);
char les(bool type);

//leser dato, med minimum
int getdate(string txt, int min);

void menu();

void fraFil(string file, Hotell *hotell);

//henter respektiv fil.
string getfil();

bool confirm(const char txt[]);