//Suite, underklasse av rom

#pragma once

#include "Rom.h"
#include <string>
#include <fstream>

using namespace std;


class Suite: public Rom {
	private:
		int kvm;
		string beskrivelse;

	public:
		//constructor med ID og fil
		Suite(int ID, ifstream &file);

		//Skriver data til fil
		void toFile(ofstream &file);

		//skriver data om filen
		void display();

};
