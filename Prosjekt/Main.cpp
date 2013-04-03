//Gruppe 9

#include "Header.h"

using namespace std;


Hotell *hotell;

int main(){

	char kommando;
	
	hotell = new Hotell(getfil());

	do{

		menu();
		switch(kommando = les(false)){

			case 'B': break;
			case 'A': break;
			case 'I': break;
			case 'U': break;
			case 'R': break;
			case 'T': break;
			case 'H': break;

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

					case '1': hotell->Data(); break;
					case '2': break;
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