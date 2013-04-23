//Regning underklasse av num element, for sortering på dato?

#pragma once

#include "Listtool.h"

#include <fstream>
#include <string>

using namespace std;


class Regning : public Num_element{
	private:
		string info;

	public:
		//constructor
		Regning(int ID, ifstream &fil);
		Regning(int ID, string input);

		//skriver til fil
		void tofile(ofstream &fil);

		//skriver ut data
		void display();
};