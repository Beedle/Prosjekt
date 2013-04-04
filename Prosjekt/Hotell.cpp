

#include "Header.h"

using namespace std;



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
		fil >> frokost >> seng;

		//masse variabler som brukes til å mellomlagre data.
		int trash;
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;

		int romnummer;
		int senger;
		bool seng;
		bool frokost;
		int res;
		int kvm;
	
		//oppretter liste for singelrom
		//og leser inn data om alle rommene.
		rom[0] = new List(Sorted);
		fil >> trash;
		for (int x = 1; x <= trash; x++){

			fil >> romnummer >> senger >> frokost;
			tempSingel = new Singel(romnummer, senger, frokost);
			rom[0]->add(tempSingel);

			fil >> res;
			for(int y = 1; y <= res; y++){
				//lese inn reservasjon.
			}

		}

		//rom[1] = new List(Sorted);
		//fil >> trash;
		//for (int x = 1; x <= trash; x++){

		//	fil >> romnummer >> senger >> seng >> frokost;
		//	tempDobbel = new Dobbel(romnummer, senger, frokost);
		//	rom[0]->add(tempDobbel);

		//	fil >> res;
		//	for(int y = 1; y <= res; y++){
		//		//lese inn reservasjon.
		//	}

		//}


		//rom[2] = new List(Sorted);
		//fil >> trash;
		//for (int x = 1; x <= trash; x++){

		//	fil >> romnummer >> senger >> frokost;
		//	tempSuite = new Suite(romnummer, senger, frokost);
		//	rom[0]->add(tempSuite);

		//	fil >> res;
		//	for(int y = 1; y <= res; y++){
		//		//lese inn reservasjon.
		//	}

		//}

	
	
	}
}



//Skriver ut data om hotellet.
void Hotell::Data(){

	cout << "\n\t" << navn << endl;
	cout << "\tKontakt" << endl;
	cout << "\t\tTelefon: " << telefon << endl;
	cout << "\t\tFax: " << fax << endl;
	cout << "\t\tPostaddresse: " << addresse << " " << postnummer << endl;

	cout << "\n\tFascilliteter" << endl;
	
}