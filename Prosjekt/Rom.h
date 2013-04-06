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
		Rom(int ID, ifstream &file);

		void toFile(ofstream &file);
	
		void display();
};
