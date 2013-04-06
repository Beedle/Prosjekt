//Dobbeltrom, underklasse av rom

#pragma once

#include "Rom.h"

#include <fstream>

using namespace std;


class Dobbel: public Rom {
	protected:
		bool ekstraSeng;
		
	public:
		//constructor med ID og fil
		Dobbel(int ID, ifstream &file);

		//Skriver data til fil
		void toFile(ofstream &file);

		//skriver data om filen
		void display();

};


