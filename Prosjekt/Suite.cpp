#include "Header.h"



using namespace std;



//leser data fra fil.
Suite::Suite(int ID, ifstream &file):Rom(ID, file){
	
	file >> kvm; file.ignore();
	getline(file, beskrivelse);
	antSenger += 4;
}


//skriver til fil;
void Suite::toFile(ofstream &file){

	//tar - og + 4, sånn at det som blir skrevet til fil
	//er antallet senger i forhold til 4, som alle suitene har.
	antSenger -= 4;
	Rom::toFile(file);
	antSenger += 4;

	file << " " << kvm << " " << beskrivelse;
}


//skriver data
void Suite::display(){
	
	Rom::display(false);

	cout << "\tSuiten er " << kvm << " kvadratmeter" << endl;
	cout << "\t" << beskrivelse << "\n\n";
}