//Hotell

#pragma once

#include <string>
#include <fstream>

using namespace std;

class Hotell {
	private:
		string navn;
		string addresse;
		string mail;
		string filnavn;

		int postnummer;
		int telefon;
		int fax;
		int frokost;
		int seng;
		int antFascilliteter;

		string fascilliteter[10];

		//rom[0] for vanlig, [1] for dobbeltrom og [2] for sutie.
		List *rom[3];

	public:
		Hotell(string file);
		~Hotell();

		void tilfil();

		void Data();

};