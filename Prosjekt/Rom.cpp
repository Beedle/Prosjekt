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


//skriver ut alle reservasjonene
void Rom::reservasjon(){
	
	//data om rommet, praktisk.
	display();

	//midlertidig reservasjons objekt
	Reservasjon *temp;

	//fjernet og legger til igjen reservasjonsobjektet for å
	//få pekeren, deretter vises data.
	for (int x = 1; x <= reservasjoner->no_of_elements(); x++){
		temp = (Reservasjon*)reservasjoner->remove_no(x);
		reservasjoner->add(temp);
		temp->display();
	}

	//dersom det ikke finnes noen reservasjoner kommer en melding.
	if (!reservasjoner->no_of_elements()){
		cout << "\nIngen registrerte reservasjonere." << endl;
	}

}