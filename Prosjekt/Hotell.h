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

		//10, bare for en midlertidig max.
		string fascilliteter[10];

		//rom[0] for vanlig, [1] for dobbeltrom og [2] for sutie.
		List *rom[3];

	public:
		//constructor som tar filnavn som parameter.
		Hotell(string file);
		~Hotell();

		void tilfil();

		void reserver();
		void avbestille(string txt);

		//endrer info etter type (1=annkomst, 2=avreise, 3 = begge)
		void endre(int type);

		//skriver ut reservasjon(er) med gitt navn og dato.
		void skrivReservasjon();

		//viser på skjerm.
		void display();
		void displaySuite();
		void displayrom();

		string getNavn();

		void displayResEier();

		void displayOkkupant();

		void ledigeRom(int nr);

		void ledigTidRom();

		void byttRom();

		void utskjekking();

		void addRegning();
};