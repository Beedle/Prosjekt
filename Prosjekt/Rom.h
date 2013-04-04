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
		Rom(int romnummer, int senger, bool frokost);
	
		void display();
};