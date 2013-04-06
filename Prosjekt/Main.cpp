//Gruppe 9

#include "Header.h"

using namespace std;


Hotell *hotell;



int main(){

	char kommando;
	
	//begynner med å åpne ett hotell.
	//Dummy og test er eneste med data atm.
	hotell = new Hotell(getfil());


	do{

		menu();
		switch(kommando = les(false)){

			case 'B': break;
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

			case 'O':
				cout << " ";
				switch (kommando = les(true)){

						//viser data om hotellet.
					case '1': hotell->display(); break;

						//viser data om alle suitene
					case '2': hotell->displaySuite(); break;
					case '3': break;
					case '4': break;
					case '5': break;
					case '6': break;
					case '7': break;
					default: break;
				}

			default:break;

		}
	} while (kommando != 'Q');


	cout << "\n\nAvslutter program..." << endl;
	system("PAUSE");
	return 0;

}











