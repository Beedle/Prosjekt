#include "Header.h"



using namespace std;




Suite::Suite(int ID, ifstream &file):Rom(ID, file){
	
	file >> kvm; file.ignore();
	getline(file, beskrivelse);
	antSenger += 4;
}



void Suite::toFile(ofstream &file){

	antSenger -= 4;
	Rom::toFile(file);
	antSenger += 4;

	cout << " " << kvm << " " << beskrivelse;
}



void Suite::display(){
	
	Rom::display();

	cout << "Suiten er " << kvm << " stor." << endl;
	cout << beskrivelse << endl;
}