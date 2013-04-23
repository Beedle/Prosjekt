//Reservasjon, underklasse av num element for sortering på dato

#pragma once

#include "Listtool.h"
#include "Regning.h"
#include "Timer.h"

#include <fstream>
#include <string>

using namespace std;


class Reservasjon: public Num_element{
	private:
		int avreise;
		int overnattinger;
		int beboere;

		//bør endres til enum
		//1 - utilgjengelig
		//2 - tilgjengelig
		//3 - i bruk
		int seng;

		//liste over pris for antallet dager det overnattes
		//50 er midlertidig max const
		float pris[50];

		//navnet på alle beboerene.
		//10 er midlertidig max
		string navn[10];
		//string navn;

		//liste med regninger.
		List *regninger;

	public:
		//constructor
		Reservasjon(int ID, int dpt, int gje, string filnavn, int type);
		Reservasjon(int ID, ifstream &fil);

		//skriver til fil
		void tofile(ofstream &fil);

		//skriver ut data
		void display(bool all);

		//henter navn
		string getNavn();

		//henter avreise og ankomst
		int getAvreise();
		int getAnkomst();
		
		bool compNavn(string txt);

		//endrer data
		void setAnkomst(int ny);
		void setAvreise(int ny);

		//legger til regning
		void addRegning();

		//skriver ut ting til historiefil som regning.
		void utskjekking(ofstream &fil);

		//Spør om navnene på resten av okkupantene.
		void innsjekk();
};