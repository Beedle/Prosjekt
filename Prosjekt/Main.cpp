//Gruppe 9

#include "Global.h"

#include <iostream>

using namespace std;

int main(){

	char kommando;

	do{

		menu();
		switch(kommando = les(false)){

			case 'B':
			case 'A':
			case 'I':
			case 'U':
			case 'R':
			case 'T':
			case 'H':

			case 'E':
				cout << " ";
				switch(kommando = les(true)){

					case '1':
					case '2':
					case '3':
					default: break;
				}

			case 'O':
				cout << " ";
				switch (kommando = les(true)){

					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					default: break;
				}

			default:break;

		}
	} while (kommando != 'Q');




	system ("PAUSE");
	return 0;
}