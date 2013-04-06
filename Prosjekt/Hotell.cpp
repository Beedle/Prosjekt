

#include "Header.h"

using namespace std;



//Skriver ut data om hotellet.
void Hotell::Data(){

	cout << "\n\n" << navn << endl;
	cout << "Kontakt" << endl;
	cout << "\tTelefon: " << telefon << endl;
	cout << "\tFax: " << fax << endl;
	cout << "\tPostaddresse: " << addresse << " " << postnummer << endl;

	cout << "\nFascilliteter" << endl;
	for (int x = 1; x <= antFascilliteter; x++){
		cout << "\t" << fascilliteter[x] << endl;
	}
	cout << "\n\n";
	_getche();
	
}

//Hotell leser selv inn data fra fil.
Hotell::Hotell(string file){
	
	//Lagrer filnavnet
	filnavn = file;

	//henter filen
	ifstream fil (file+".DTA");
	if(fil){

		//navnet på hotellet
		getline(fil, navn);
	
		//postnummer og addresse
		fil >> postnummer; fil.ignore();
		getline(fil, addresse);
	
		//telefon fax og mail
		fil >> telefon >> fax; fil.ignore();
		getline(fil, mail);

		//priser for frokost og seng samt antallet fascilliteter
		fil >> frokost >> seng >> antFascilliteter;
		fil.ignore();

		for (int x = 1; x <= antFascilliteter; x++){
			getline(fil, fascilliteter[x]);
		}

		//masse variabler som brukes til å mellomlagre data.
		int trash;
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;

		int ID;		

		//oppretter liste for singelrom
		//og leser inn data om alle rommene.
		rom[0] = new List(Sorted);
		fil >> trash;
		for (int x = 1; x <= trash; x++){

			fil >> ID;
			tempSingel = new Singel(ID, fil);
			rom[0]->add(tempSingel);
		}
	}
}

Hotell::~Hotell(){

	tilfil();

}


void Hotell::tilfil(){

	ofstream fil (filnavn+".DTA");

	fil << navn << endl;
	fil << postnummer << " " << addresse << endl;
	fil << telefon << " " << fax << " " << mail << endl;
	fil << frokost << " " << seng << " " << antFascilliteter << endl;

	for(int x = 1; x <= antFascilliteter; x++){
		fil << fascilliteter[x] << endl;
	}


	Singel *tempSingel;
	fil << rom[0]->no_of_elements() << endl;
	for (int x = 1; x <= rom[0]->no_of_elements(); x++){

		tempSingel = (Singel*)rom[0]->remove_no(x);
		rom[0]->add(tempSingel);

		tempSingel->toFile(fil);


	}




}