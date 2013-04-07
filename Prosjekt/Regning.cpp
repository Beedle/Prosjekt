#include "Header.h"

using namespace std;


//constructor
Regning::Regning(int ID, ifstream &fil):Num_element(ID){

	fil.ignore();
	getline(fil, info);
}

//skriver til fil
void Regning::tofile(ofstream &fil){

	fil << number << " " << info << endl;
}

//viser data på skjerm.
void Regning::display(){

	cout << info << " - " << number << endl;
}