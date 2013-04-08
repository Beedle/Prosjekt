#include "Header.h"

using namespace std;


//constructor, sender ID videre
Rom::Rom(int ID, ifstream &file):Num_element(ID){

	
	//lager en ny liste med reservasjoner
	reservasjoner = new List(Sorted);

	//leser inn antallet reservasjoner og reservasjonene
	int trash;
	int resID;
	Reservasjon *res;
	file >> trash; file.ignore();
	for(int x = 1; x <= trash; x++){
		file >> resID;
		res = new Reservasjon(resID, file);
		reservasjoner->add(res);
	}


	//leser inn antall senger for rommet og om frokost er inkludert
	file >> antSenger >> inklFrokost;

}

//viser data
void Rom::display(bool all){
	cout << "\n\nRomnummer: " << number << endl;
	cout << "\tAntall senger: " << antSenger << endl;
	
	cout << "\tFrokost er ";
	if(!inklFrokost) cout << "ikke ";
	cout << "inkludert" << endl;

	//dersom alle reservasjonene skulle være med.
	if (all && reservasjoner->no_of_elements()){
		Reservasjon *tempRes;

		//går igjennom alle reservasjonene og skriver de ut
		//inkluderer ikke regningene.
		cout << "\nFølgende reservasjoner:" << endl;
		for (int x = 1; x <= reservasjoner->no_of_elements(); x++){

			tempRes = (Reservasjon*)reservasjoner->remove_no(x);
			reservasjoner->add(tempRes);
			tempRes->display(false);
		}
	}
}



//skriver til fil.
void Rom::toFile(ofstream &file){

	//romnummer og antallet reservasjoner.
	file << number << " " << reservasjoner->no_of_elements() << endl;

	//skriver reservasjoner til fil.
	Reservasjon *temp;
	for(int x = 1; x <= reservasjoner->no_of_elements(); x++){
			
		//fjerner og legger til reservasjonen, og skriver så til fil.
		temp = (Reservasjon*)reservasjoner->remove_no(x);
		reservasjoner->add(temp);
		temp->tofile(file);
	}

	//antallet senger og om frokost er inkludert.
	file << antSenger << " " << inklFrokost;

}



//returnerer listen i klassen.
List* Rom::getlist(){
	return reservasjoner;
}

//returnerer romnummer
int Rom::getid(){
	return number;
}

//returnerer antallet senger
int Rom::getsenger(){
	return antSenger;
}