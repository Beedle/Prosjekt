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

	//dersom alle reservasjonene skulle v�re med.
	
	Reservasjon *temp;
	if (all)
	{
		for (int x = 1; x <= reservasjoner->no_of_elements(); x ++){
			temp = (Reservasjon*)reservasjoner->remove_no(x);
			reservasjoner->add(temp);
			temp->display(all);
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
			
		//fjerner og legger til reservasjonen, og skriver s� til fil.
		temp = (Reservasjon*)reservasjoner->remove_no(x);
		reservasjoner->add(temp);
		temp->tofile(file);
	}

	//antallet senger og om frokost er inkludert.
	file << antSenger << " " << inklFrokost;

}

bool Rom::finnReservasjon(string navn, int dato)
{

	//hjelpedata
	Reservasjon *temp;
	bool returnVal = false;

	//kj�r til du er i slutten av listen.
	for (int x = 1; x <= reservasjoner->no_of_elements(); x++)
	{
		//fjerner og legger til igjen reservasjonsobjektet for � f� pekeren
		temp = (Reservasjon*)reservasjoner->remove_no(x);
		reservasjoner->add(temp);

		if (navn == temp->getNavn() && dato == temp->getAnkomst())
		{
			//hvis navn og dato passer, returner true.
			returnVal = true;
		}
	}

	return returnVal;
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

void Rom::replaceList(List* liste)
{
	reservasjoner = liste;
}

void Rom::innsjekk(string navn, int dato)
{
	//hjelpedata
	Reservasjon *temp;

	//kj�r til du er i slutten av listen.
	for (int x = 1; x <= reservasjoner->no_of_elements(); x++)
	{
		//fjerner reservasjonsobjektet
		temp = (Reservasjon*)reservasjoner->remove_no(x);

		if (navn == temp->getNavn() && dato == temp->getAnkomst())
		{
			//hvis navn og dato passer, kj�r innskjekk p� reservasjonen.
			temp->innsjekk();
		}
		reservasjoner->add(temp);
	}

}