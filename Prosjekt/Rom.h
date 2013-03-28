//Superklassen til alle rommene.

#pragma once


#include "Listtool.h"
#include <string>

using namespace std;

class Rom: public Num_element {
	protected:
		int antSenger;
		bool frokost;
		List *reservasjoner;

	public:
		
	
};