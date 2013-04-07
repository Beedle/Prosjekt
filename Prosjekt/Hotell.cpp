

#include "Header.h"

using namespace std;



//Skriver ut data om hotellet.
void Hotell::display(){

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
	_getch();
	
}



//skriver ut data om suitene.
void Hotell::displaySuite(){

	Suite *tempSuite;

	for (int x = 1; x <= rom[2]->no_of_elements(); x++){

		tempSuite = (Suite*)rom[2]->remove_no(x);
		rom[2]->add(tempSuite);
		tempSuite->display();
	}

	_getch();
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
		int ID;
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;

		for(int y = 0; y < 3; y++){

			//oppretter liste for romtypene
			//og leser inn antallet rom av gitt type
			rom[y] = new List(Sorted);
			fil >> trash;
			for (int x = 1; x <= trash; x++){

				//romnummer
				fil >> ID;

				//oppretter objekt og stapper det inn i gitt liste
				if(y == 0){
					tempSingel = new Singel(ID, fil);
					rom[y]->add(tempSingel);
				}
				
				else if (y == 1){
					tempDobbel = new Dobbel(ID, fil);
					rom[y]->add(tempDobbel);
				}
				
				else if (y == 2){
					tempSuite = new Suite (ID, fil);
					rom[y]->add(tempSuite);
				}

			}
		}

	}
}


//dekonstructoren gjør ikke noe mer spennende enn å
//skrive til fil atm. Bør sikkert slette div objekter.
Hotell::~Hotell(){

	tilfil();

}


//skriver data til fil.
void Hotell::tilfil(){

	//filnavnet er egen variabel.
	ofstream fil (filnavn+".DTA");

	//Statisk data
	fil << navn << endl;
	fil << postnummer << " " << addresse << endl;
	fil << telefon << " " << fax << " " << mail << endl;
	fil << frokost << " " << seng << " " << antFascilliteter << endl;

	//beskrivelse av fascillitetene.
	for(int x = 1; x <= antFascilliteter; x++){
		fil << fascilliteter[x] << endl;
	}


	for(int y = 0; y < 3; y++){

		//data om alle singelrom skriver seg selv.

		
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;
		
		fil << rom[y]->no_of_elements() << endl;
		for (int x = 1; x <= rom[y]->no_of_elements(); x++){

			if(y == 0){
				tempSingel = (Singel*)rom[y]->remove_no(x);
				rom[y]->add(tempSingel);
				tempSingel->toFile(fil);
			}

			else if (y == 1){
				tempDobbel = (Dobbel*)rom[y]->remove_no(x);
				rom[y]->add(tempDobbel);
				tempDobbel->toFile(fil);
			}

			else if (y == 2){
				tempSuite = (Suite*)rom[y]->remove_no(x);
				rom[y]->add(tempSuite);
				tempSuite->toFile(fil);
			}

			fil << endl;
		}

	}

}