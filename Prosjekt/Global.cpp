//Globale funksjoner


#include "Global.h"

#include <conio.h>
#include <iostream>

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
	cout << "\nKommando: ";
	do{
		trash = toupper(_getch());
	}while (trash < char(x) || trash > char(y));

	//skriver ut og returnerer tegnet.
	cout << trash << endl;
	return trash;
}
