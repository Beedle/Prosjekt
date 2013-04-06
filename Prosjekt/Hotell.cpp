

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

				

		//oppretter liste for singelrom
		//og leser inn data om alle rommene.
		rom[0] = new List(Sorted);
		fil >> trash;
		for (int x = 1; x <= trash; x++){

			fil >> ID;
			tempSingel = new Singel(ID, fil);
			rom[0]->add(tempSingel);
		}


		//oppretter liste for singelrom
		//og leser inn data om alle rommene.
		rom[1] = new List(Sorted);
		fil >> trash;
		for (int x = 1; x <= trash; x++){

			fil >> ID;
			tempDobbel = new Dobbel(ID, fil);
			rom[1]->add(tempDobbel);
		}


		//oppretter liste for singelrom
		//og leser inn data om alle rommene.
		rom[2] = new List(Sorted);
		fil >> trash;
		for (int x = 1; x <= trash; x++){

			fil >> ID;
			tempSuite = new Suite(ID, fil);
			rom[2]->add(tempSuite);
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


	//data om alle singelrom skriver seg selv.
	Singel *tempSingel;
	fil << rom[0]->no_of_elements() << endl;
	for (int x = 1; x <= rom[0]->no_of_elements(); x++){

		tempSingel = (Singel*)rom[0]->remove_no(x);
		rom[0]->add(tempSingel);
		tempSingel->toFile(fil);
		fil << endl;
	}


	Dobbel *tempDobbel;
	fil << rom[1]->no_of_elements() << endl;
	for (int x = 1; x <= rom[1]->no_of_elements(); x++){

		tempDobbel = (Dobbel*)rom[1]->remove_no(x);
		rom[1]->add(tempDobbel);
		tempDobbel->toFile(fil);
		fil << endl;
	}


	Suite *tempSuite;
	fil << rom[2]->no_of_elements() << endl;
	for (int x = 1; x <= rom[2]->no_of_elements(); x++){

		tempSuite = (Suite*)rom[2]->remove_no(x);
		rom[2]->add(tempSuite);
		tempSuite->toFile(fil);
		fil << endl;
	}


}