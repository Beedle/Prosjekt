#include "Header.h"

using namespace std;





Dobbel::Dobbel(int ID, ifstream &file):Rom(ID, file){
	
	file >> ekstraSeng; file.ignore();
}



void Dobbel::toFile(ofstream &file){

	Rom::toFile(file);
	file << " " << ekstraSeng;
}



void Dobbel::display(){
	
	Rom::display();

	cout << "Det er ";
	if (!ekstraSeng) cout << "ikke ";
	cout << "mulighet for ekstra seng." << endl;
}

