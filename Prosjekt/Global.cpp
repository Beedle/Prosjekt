//Globale funksjoner


#include "Header.h"

using namespace std;


//meget selvforklarende, skriver menyen...
void menu(){

	cout << "\nMenyvalg" << endl;
	cout << "\tB - Bestille rom" << endl;
	cout << "\tA - Avbestille rom" << endl;
	cout << "\tI - Insjekking" << endl;
	cout << "\tU - Utsjekking" << endl;
	cout << "\tR - Registrere regning" << endl;

	cout << "\tE - Endre" << endl;
	cout << "\t\t1 - Ankomst og/eller Avreise før insjekking" << endl;
	cout << "\t\t2 - Avreise etter innsjekking." << endl;
	cout << "\t\t3 - Rom" << endl;

	cout << "\tO - Oversikt" << endl;
	cout << "\t\t1 - Data over hotellet" << endl;
	cout << "\t\t2 - Beskrivelse av alle suitene" << endl;
	cout << "\t\t3 - Over alle reservasjoner under ett gitt navn" << endl;
	cout << "\t\t4 - Når ett rom er ledig" << endl;
	cout << "\t\t5 - Alle reservasjoner for ett rom." << endl;
	cout << "\t\t6 - Alle data om rommets nåværende beboer" << endl;
	cout << "\t\t7 - Alle ledige rom av en gitt type i en gitt tidsperiode" << endl;

	cout << "\tT - Skrive data til fil" << endl;
	cout << "\tH - Bytte hotell" << endl;

	cout << "\n\tQ - Avslutte programmet";

	cout << "\n\nKommando: ";
}


//leser ett tegn, og en bool for om det er tall eller bokstav.
char les(bool type){

	//div variabler som brukes
	char trash;
	int x;
	int y;

	//dersom type er satt som sann blir x og y satt til ascii
	//verdiene som grenser til tall.
	//og ascii verdiene til bokstaver ellers.
	if(type){x = 48; y = 57;}
	else{x = 65; y = 90;}
	
	//leser ett tegn til det er gyldig.
	do{
		trash = toupper(_getch());
	}while ((trash < char(x) || trash > char(y)) &&  trash != 'Q' );

	//skriver ut og returnerer tegnet.
	cout << trash;
	return trash;
}


//leser en tekststreng med gitt ledetekst.
string les(const char txt[]){

	string temp;

	//skriver ut ledeteksten og leser strengen
	//helt til strengen er lengre enn 1.
	do{
		cout << txt << " ";
		getline(cin, temp);
	} while (temp.length() < 1);

	return temp;
}


//henter navnet på filen til ett hotell.
string getfil(){
	
	string filnavn;
	string hotellnavn;
	string input;
	

	
	do{

		//leser navnet på hotellet
		//og åpner filen med navnene.
		input = les("Navn på hotellet");
		ifstream fil ("Hoteller.DTA");

		do{

			//for alle punktene leses forkortet navn
			//og fult navn.
			fil >> filnavn; fil.ignore();
			getline(fil, hotellnavn);

			//sammenligner fult navn med input.
			//om like returneres input strengen.
			if(!input.compare(hotellnavn)){
				return input;
			}


		//når filen slutter kommer en feilmelding.
		}while (!fil.eof());
		cout << "Ikke noe hotell som svarer til det navnet, prøv igjen." << endl;

	//kjører forevur :D
	}while (true);
}