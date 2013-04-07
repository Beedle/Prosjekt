//Reservasjon, underklasse av num element for sortering p� dato

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

		//b�r endres til enum
		//1 - utilgjengelig
		//2 - tilgjengelig
		//3 - i bruk
		int seng;

		//liste over pris for antallet dager det overnattes
		//20 er midlertidig max const
		float pris[20];

		//navnet p� alle beboerene.
		//10 er midlertidig max
		string navn[10];

		//liste med regninger.
		List *regninger;

	public:
		//constructor
		Reservasjon(int ID, ifstream &fil);

		//skriver til fil
		void tofile(ofstream &fil);

		//skriver ut data
		void display();
};