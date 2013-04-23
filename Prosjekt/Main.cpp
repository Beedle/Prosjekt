//Gruppe 9

#include "Header.h"

using namespace std;

//globale Hotell, Timer og Reg_post objekt
Hotell *hotell;
Timer timer;
Reg_Post regpost;


int main(){

	//setter vinduets st�rrelse og plassering.
	//(n�dvendig ettersom menyen er st�rre enn standardvinduet)
	RECT desktopRect; //st�rrelsen p� skrivebordet
	GetWindowRect(GetDesktopWindow(), &desktopRect); //henter st�rrelsen p� skrivebordet
	HWND console = GetConsoleWindow(); //vinduet

	//flytter vinduet til midten av hovedskjermen (den hvor man har start bar) og gir det st�rrelse 670*desktoph�yde-120
	MoveWindow(console, desktopRect.right/2 - 335, 60, 670, desktopRect.bottom - 120, true);

	char kommando;

	//setter vindusnavnet
	SetConsoleTitle("Resepsjonsapp");
		
	//begynner med � �pne ett hotell.
	//Dummy og test er eneste med data atm.
	hotell = new Hotell(getfil());

	//setter vindusnavnet
	SetConsoleTitle(("Resepsjonsapp: " + hotell->getNavn()).c_str());
	

	do{

		menu();
		switch(kommando = les(false)){

				//utf�rer en reservasjon.
			case 'B': 
				hotell->reserver();
				break;

				//avbestiller reservajsoner, basert p� navn
			case 'A':
				hotell->avbestille(les("\nI hvilket navn st�r reservasjonen: "));
				break;

			case 'I': 
				hotell->skrivReservasjon();

				break;

			case 'U':
				hotell->utskjekking();
				break;

			case 'R':
				hotell->addRegning();
				break;

				//skriver data til fil.
			case 'T': 
				hotell->tilfil();
				break;

				//sletter hotell objektet og oppretter et nytt et.
			case 'H':
				delete hotell;
				hotell = new Hotell(getfil());
				//endrer vinduets navn
				SetConsoleTitle(("Resepsjonsapp: " + hotell->getNavn()).c_str());
				break;

			case 'E':
				cout << " ";
				switch(kommando = les(true)){
					//endre annkomst og/eller avreisedato f�r innsjekking
					case '1':
						do
						{
							kommando = les(true);
						} while (!(kommando >= 1 || kommando <= 3));

						hotell->endre(kommando);
						break;

						//endre avreisedato etter innsjekking
					case '2':
						hotell->endre(2);
						break;

						//bytte rom
					case '3':
						hotell->byttRom();
						break;

					default:
						cout << "\nUgyldig kommando\n";
						break;
				}
				break;

			case 'O':
				cout << " ";
				switch (kommando = les(true)){

						//viser data om hotellet.
					case '1':
						hotell->display();
						break;

						//viser data om alle suitene
					case '2':
						hotell->displaySuite();
						break;

						//Viser data over alle reservasjoner under ett gitt navn
					case '3':
						hotell->displayResEier();
						break;

						//Viser data om n�r ett rom er ledig
					case '4':
						hotell->ledigTidRom();
						break;

						//Viser data om ett gitt hotellrom.
					case '5':
						hotell->displayrom();
						break;

						//Viser data om alle data om rommets n�v�rende beboer
					case '6':
						hotell->displayOkkupant();
						break;

						//Viser data om alle ledige rom av en gitt type i en gitt tidsperiode
					case '7':
						cout << ' ';
						kommando = les(true);
						kommando--;

						if (kommando <= '2' && kommando >= '0')
						{
							hotell->ledigeRom(kommando - '0');
						}
						else
						{
							cout << "\nUgyldig kommando\n";
						}
						break;


					default:
						cout << "\nUgyldig kommando\n";
						break;

				}
				break;

			default:
				cout << "\nUgyldig kommando\n";
				break;

		}
	} while (kommando != 'Q');


	cout << "\n\nAvslutter program..." << endl;
	system("PAUSE");
	return 0;

}
