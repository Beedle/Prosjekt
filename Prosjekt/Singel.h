//Singelrom, underklasse av rom




#pragma once

#include "Rom.h"

#include <fstream>


using namespace std;


class Singel: public Rom {
	protected:

	public:
		//constructor med ID og fil
		Singel(int ID, ifstream &file);

		//Skriver data til fil
		void toFile(ofstream &file);

		//skriver data om filen
		void display();
};
