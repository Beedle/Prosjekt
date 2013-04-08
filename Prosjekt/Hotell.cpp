

#include "Header.h"

using namespace std;

extern Timer timer;

//Skriver ut data om hotellet.
void Hotell::display(){

	cout << "\n\n" << navn << endl;
	cout << "Kontakt" << endl;
	cout << "\tTelefon: " << telefon << endl;
	cout << "\tFax: " << fax << endl;
	cout << "\tPostaddresse: " << addresse << " " << postnummer << endl;

	cout << "\nFascilliteter" << endl;
	for (int x = 1; x <= antFascilliteter; x++){
		cout << "\t" << fascilliteter[x] << endl;
	}
	cout << "\n\n";
	_getch();
	
}



//skriver ut data om suitene.
void Hotell::displaySuite(){

	Suite *tempSuite;

	for (int x = 1; x <= rom[2]->no_of_elements(); x++){

		tempSuite = (Suite*)rom[2]->remove_no(x);
		rom[2]->add(tempSuite);
		tempSuite->display();
	}

	_getch();
}



//Hotell leser selv inn data fra fil.
Hotell::Hotell(string file){
	
	//Lagrer filnavnet
	filnavn = file;

	//henter filen
	ifstream fil (file+".DTA");
	if(fil){

		//navnet på hotellet
		getline(fil, navn);
	
		//postnummer og addresse
		fil >> postnummer; fil.ignore();
		getline(fil, addresse);
	
		//telefon fax og mail
		fil >> telefon >> fax; fil.ignore();
		getline(fil, mail);

		//priser for frokost og seng samt antallet fascilliteter
		fil >> frokost >> seng >> antFascilliteter;
		fil.ignore();

		for (int x = 1; x <= antFascilliteter; x++){
			getline(fil, fascilliteter[x]);
		}

		//masse variabler som brukes til å mellomlagre data.
		int trash;
		int ID;
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;

		for(int y = 0; y < 3; y++){

			//oppretter liste for romtypene
			//og leser inn antallet rom av gitt type
			rom[y] = new List(Sorted);
			fil >> trash;
			for (int x = 1; x <= trash; x++){

				//romnummer
				fil >> ID;

				//oppretter objekt og stapper det inn i gitt liste
				if(y == 0){
					tempSingel = new Singel(ID, fil);
					rom[y]->add(tempSingel);
				}
				
				else if (y == 1){
					tempDobbel = new Dobbel(ID, fil);
					rom[y]->add(tempDobbel);
				}
				
				else if (y == 2){
					tempSuite = new Suite (ID, fil);
					rom[y]->add(tempSuite);
				}

			}
		}

	}
}


//dekonstructoren gjør ikke noe mer spennende enn å
//skrive til fil atm. Bør sikkert slette div objekter.
Hotell::~Hotell(){

	tilfil();

}


//skriver data til fil.
void Hotell::tilfil(){

	//filnavnet er egen variabel.
	ofstream fil (filnavn+".DTA");

	//Statisk data
	fil << navn << endl;
	fil << postnummer << " " << addresse << endl;
	fil << telefon << " " << fax << " " << mail << endl;
	fil << frokost << " " << seng << " " << antFascilliteter << endl;

	//beskrivelse av fascillitetene.
	for(int x = 1; x <= antFascilliteter; x++){
		fil << fascilliteter[x] << endl;
	}


	for(int y = 0; y < 3; y++){

		//data om alle rom skriver seg selv.		
		Singel *tempSingel;
		Dobbel *tempDobbel;
		Suite  *tempSuite;
		
		fil << rom[y]->no_of_elements() << endl;
		for (int x = 1; x <= rom[y]->no_of_elements(); x++){

			if(y == 0){
				tempSingel = (Singel*)rom[y]->remove_no(x);
				rom[y]->add(tempSingel);
				tempSingel->toFile(fil);
			}

			else if (y == 1){
				tempDobbel = (Dobbel*)rom[y]->remove_no(x);
				rom[y]->add(tempDobbel);
				tempDobbel->toFile(fil);
			}

			else if (y == 2){
				tempSuite = (Suite*)rom[y]->remove_no(x);
				rom[y]->add(tempSuite);
				tempSuite->toFile(fil);
			}

			fil << endl;
		}

	}

}


//opprette en reservasjon
void Hotell::reserver(){

	//hjelpevariabler
	int temp;
	int fra;
	int til;
	int ant;

	//leser inn romtype
	do{
		cout << "\n\t1 - Singelrom";
		cout << "\n\t2 - Dobbeltrom";
		cout << "\n\t3 - Suite\n\n";

		//konverterer fra char til int, -1
		temp = les(true)-49;

	}while(temp != 0 && temp != 1 && temp != 2);

	//leser ankomst og avreise dato.
	fra = getdate("\nFra dato", timer.hent_dato());
	til = getdate("Til dato", fra);
	
	//antallet gjester.
	cout << "Antall gjester: ";
	cin >> ant;

	//midlertidige objekter.
	Rom *tempRom;
	List *list;
	Reservasjon *res;
	Reservasjon *tempRes1;
	Reservasjon *tempRes2;

	//for alle rommene
	for(int x = 1; x <= rom[temp]->no_of_elements(); x++){

		//henter ett rom fra listen
		tempRom = (Rom*)rom[temp]->remove_no(x);
		rom[temp]->add(tempRom);

		//Dersom det er plass på rommet.
		if(tempRom->getsenger() >= ant){

			//henter listen over reservasjoner, og går igjennom den
			list = (List*)tempRom->getlist();
			for(int y = 1; y <= list->no_of_elements(); y++){

				//henter reservasjoner
				tempRes1 = (Reservasjon*)list->remove_no(y);
				list->add(tempRes1);

				//sett at reservasjonen har dratt før ny ankomst
				if(tempRes1->getAvreise() <= fra){

					//dersom det er siste reservasjon, registreres ny
					if(y == list->no_of_elements()){
						res = new Reservasjon(fra, til, ant);
						list->add(res);

						//for å bryte ut av for-løkkene
						x = rom[temp]->no_of_elements()+1;
						y = list->no_of_elements()+1;

					}
					//dersom det er flere reservasjoner
					else{

						//neste reservasjon hentes
						tempRes2 = (Reservasjon*)list->remove_no(y+1);
						list->add(tempRes2);

						//det sjekker om denne ankommer før reservasjonen
						//som skal registreres reiser, registreres ny.
						if(tempRes2->getAnkomst() >= til){
							res = new Reservasjon(fra, til, ant);
							list->add(res);

							//for å bryte ut av for-løkkene
							x = rom[temp]->no_of_elements()+1;
							y = list->no_of_elements()+1;
						}

					}

				}

			}

			//dersom listen er tom for reservasjoner registreres ny
			if (!list->no_of_elements()){
				res = new Reservasjon(fra, til, ant);
				list->add(res);

				//bryte ut av for-løkken
				x = rom[temp]->no_of_elements()+1;
			}


		}
	}

	//feilmelding dersom det ikke finnes noe ledig.
	if(!rom[temp]->no_of_elements()){
		cout << "\n\nDesverre ingen ledige rom i den perioden" << endl;
	}
}


//skriver ut data om ett romnummer
void Hotell::displayrom(){

	//leser romnummer
	int trash;
	cout << "\nRomnummer: ";
	cin >> trash;

	//går igjennom alle rom i hotellet.
	Rom *temp;
	for (int x = 0; x < 3; x++){
		for(int y = 1; y <= rom[x]->no_of_elements(); y++){
			
			//henter ut rommet
			temp = (Rom*)rom[x]->remove_no(y);
			rom[x]->add(temp);

			//dersom det er korrekt vises data.
			if (temp->getid() == trash){
				temp->display(true);
			}
		}
	}

	_getch();
}



void Hotell::avbestille(string txt){

	Rom* tempRom;
	List *tempList;
	Reservasjon *tempRes;

	//Alle romtypene
	for(int x = 0; x < 3; x++){

		//alle rommene
		for (int y = 1; y <= rom[x]->no_of_elements(); y++){

			//henter ut rom.
			tempRom = (Rom*)rom[x]->remove_no(y);
			rom[x]->add(tempRom);

			//henter listen over reservasjoner.
			tempList = (List*)tempRom->getlist();

			//alle reservasjonene til ett rom.
			for (int z = 1; z <= tempList->no_of_elements(); z ++){

				//henter ut reservasjonen
				tempRes = (Reservasjon*)tempList->remove_no(z);

				//dersom det stemmer
				if (!tempRes->compNavn(txt)){

					//skriver ut reservasjonen og spør om den skal fjernes.
					tempRom->display(false);
					tempRes->display(false);
					if(!confirm()){
						tempList->add(tempRes);
					}
					//dersom det fjernes minker z, for å kompensere for
					//fjernet reservasjon.
					else (z--);
				}
				//dersom det ikke stemmer legges reservasjonen tilbake.
				else {
					tempList->add(tempRes);
				}
			}
		}
	}
}