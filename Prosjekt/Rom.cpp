#include "Header.h"

using namespace std;



Rom::Rom(int ID, ifstream &file):Num_element(ID){

	file >> antSenger >> inklFrokost;
	reservasjoner = new List(Sorted);

	int trash;
	file >> trash; file.ignore();
	for(int x = 1; x <= trash; x++){

		//leser inn reservasjoner.
	}

}


void Rom::display(){

	cout << "\nRomnummer: " << number << endl;
	cout << "\tAntall senger: " << antSenger << endl;
	
	cout << "\tFrokost er ";
	if(!inklFrokost) cout << "ikke ";
	cout << "inkludert" << endl;

}

void Rom::toFile(ofstream &file){

	file << number << " " << antSenger << " " << inklFrokost << " "
		 << reservasjoner->no_of_elements() << endl;

}