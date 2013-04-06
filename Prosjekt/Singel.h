//Singelrom, underklasse av rom




#pragma once

#include "Rom.h"

#include <fstream>


using namespace std;


class Singel: public Rom {
	protected:

	public:
		Singel(int ID, ifstream &file);

		void display();

		void toFile(ofstream &file);
};
