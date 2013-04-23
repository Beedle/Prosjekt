//Superklassen til alle rommene.

#pragma once


#include "Listtool.h"

#include <string>
#include <fstream>



using namespace std;

class Rom: public Num_element {
	protected:
		int antSenger;
		bool inklFrokost;
		List *reservasjoner;

	public:
		//constructor med ID of fil.
		Rom(int ID, ifstream &file);

		//skriver til fil.
		void toFile(ofstream &file);
	
		//Viser data om rom
		void display(bool all);

		//leter etter reservasjon.
		bool finnReservasjon(string navn, int dato);
		
		//skriver ut reservasjonene.
		void reservasjon();

		//bytter ut listen
		void replaceList(List* liste);

		//returnerer en av de private variablene
		List *getlist();
		int getid();
		int getsenger();

		void innsjekk(string navn, int dato);
};
