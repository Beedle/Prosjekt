

#include "Header.h"

using namespace std;



//Hotell leser selv inn data fra fil.
Hotell::Hotell(string file){
	
	//Lagrer filnavnet
	filnavn = file;

	//henter filen
	ifstream fil (file+".DTA");

	//navnet på hotellet
	getline(fil, navn);
	
	//postnummer og addresse
	fil >> postnummer; fil.ignore();
	getline(fil, addresse);
	
	//telefon fax og mail
	fil >> telefon >> fax; fil.ignore();
	getline(fil, mail);

	//priser for frokost og seng.
	fil >> frokost >> seng;
	
}



//Skriver ut data om hotellet.
void Hotell::Data(){

	cout << "\n\t" << navn << endl;
	cout << "\tKontakt" << endl;
	cout << "\t\tTelefon: " << telefon << endl;
	cout << "\t\tFax: " << fax << endl;
	cout << "\t\tPostaddresse: " << addresse << " " << postnummer << endl;
}