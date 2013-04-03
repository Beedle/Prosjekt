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

		int antFasciliteter;

	public:
		Hotell(string file);

		void Data();

};