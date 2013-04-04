#include "Header.h"

using namespace std;

Rom::Rom(int romnummer, int senger, bool frokost):Num_element(romnummer){

	antSenger = senger;
	inklFrokost = frokost;
	reservasjoner = new List(Sorted);

}


void Rom::display(){

	cout << "\nRomnummer: " << number << endl;
	cout << "\tAntall senger: " << antSenger << endl;
	
	cout << "\tFrokost er ";
	if(!inklFrokost) cout << "ikke ";
	cout << "inkludert" << endl;

}