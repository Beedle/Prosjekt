#include "Header.h"

using namespace std;


//constructor, sender ID videre
Rom::Rom(int ID, ifstream &file):Num_element(ID){

	//lager en ny liste med reservasjoner
	reservasjoner = new List(Sorted);

	//leser inn antallet reservasjoner og reservasjonene
	int trash;
	file >> trash; file.ignore();
	for(int x = 1; x <= trash; x++){

		//leser inn hvordan pokker reservasjonen blir seende ut.
	}


	//leser inn antall senger for rommet og om frokost er inkludert
	file >> antSenger >> inklFrokost;

}


//selvforklarende
void Rom::display(){

	cout << "\n\nRomnummer: " << number << endl;
	cout << "\tAntall senger: " << antSenger << endl;
	
	cout << "\tFrokost er ";
	if(!inklFrokost) cout << "ikke ";
	cout << "inkludert" << endl;

}


//skriver til fil.
void Rom::toFile(ofstream &file){

	//romnummer og antallet reservasjoner.
	file << number << " " << reservasjoner->no_of_elements() << endl;

	for(int x = 1; x <= reservasjoner->no_of_elements(); x++){
		//skriver reservasjonene til fil.
		// * må slutte med endl;
	}


	file << antSenger << " " << inklFrokost;

}