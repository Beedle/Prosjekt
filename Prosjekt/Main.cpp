//Gruppe 9

#include "Header.h"

using namespace std;

//globale Hotell, Timer og Reg_post objekt
Hotell *hotell;
Timer timer;
Reg_Post regpost;



int main(){

	char kommando;
		
	//begynner med å åpne ett hotell.
	//Dummy og test er eneste med data atm.
	hotell = new Hotell(getfil());
	

	do{

		menu();
		switch(kommando = les(false)){

			case 'B': 

				hotell->reserver();
				break;

			case 'A': break;
			case 'I': break;
			case 'U': break;
			case 'R': break;

				//skriver data til fil.
			case 'T': 
				hotell->tilfil();
				break;

				//sletter hotell objektet og oppretter et nytt et.
			case 'H':
				delete hotell;
				hotell = new Hotell(getfil());
				break;

			case 'E':
				cout << " ";
				switch(kommando = les(true)){

					case '1': break;
					case '2': break;
					case '3': break;
					default: break;
				}
				break;

			case 'O':
				cout << " ";
				switch (kommando = les(true)){

						//viser data om hotellet.
					case '1': hotell->display(); break;

						//viser data om alle suitene
					case '2': hotell->displaySuite(); break;

					case '3': break;
					case '4': break;

						//viser data om ett gitt hotellrom.
					case '5': hotell->displayrom(); break;
					case '6': break;
					case '7': break;
					default: break;
				}
				break;

			default:break;

		}
	} while (kommando != 'Q');


	cout << "\n\nAvslutter program..." << endl;
	system("PAUSE");
	return 0;

}











