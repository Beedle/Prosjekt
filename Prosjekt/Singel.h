//Singelrom, underklasse av rom




#pragma once

#include "Rom.h"



using namespace std;


class Singel: public Rom {
	protected:

	public:
		Singel(int romnummer, int senger, bool frokost);

		void display();
};
