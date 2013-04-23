

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
						res = new Reservasjon(fra, til, ant, filnavn, temp);
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
							res = new Reservasjon(fra, til, ant, filnavn, temp);
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
				res = new Reservasjon(fra, til, ant, filnavn, temp);
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


//skriver ut reservasjon(er) med gitt navn og dato.
void Hotell::skrivReservasjon()
{
	//leser innskjekkerens navn.
	string navnet = les("\nHva er innsjekkerens navn?");
	int dato = timer.hent_dato();
	Rom *temp;
	bool funnetRom = false;

	//går igjennom alle rom i hotellet.
	for (int x = 0; x < 3; x++)
	{
		for (int y = 1; y <= rom[x]->no_of_elements(); y++)
		{
			//henter ut rommet
			temp = (Rom*)rom[x]->remove_no(y);


			//finner ut om det er reservert rom for dato i navn.
			if (temp->finnReservasjon(navnet, dato) && !funnetRom)
			{
				cout << temp->getid() << endl; //denne skal byttes ut med finere løsning.
				funnetRom = true; //setter permanent merke på om rum er funnet.

				temp->innsjekk(navnet, timer.hent_dato());
			}
			rom[x]->add(temp);
		}
	}

	if (!funnetRom)
	{
		cout << "Ingen reservasjon for dagens dato" << endl;
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
					if(!confirm("\nVil du fjerne?")){
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

void Hotell::displayResEier()
{
	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;

	string navn = les("Eierens navn:");

	//for alle typer rom
	for (int i = 0; i < 3; i++)
	{
		//for alle rom
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			
			tempRom = (Rom*)rom[i]->remove_no(j);
			rom[i]->add(tempRom);

			//henter listen over reservasjoner.
			tempList = (List*)tempRom->getlist();

			//alle reservasjonene til ett rom.
			for (int k = 1; k <= tempList->no_of_elements(); k++)
			{
				tempRes = (Reservasjon*)tempList->remove_no(k);
				tempList->add(tempRes);

				if (navn == tempRes->getNavn())
				{
					cout << tempRom->getid() << ' ';
				}
			}
		}
	}

	cout << endl;
}

void Hotell::displayOkkupant()
{
	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;
	bool funnetNr = false;
	bool funnetRes = false;

	int romNr;
	cout << "Ronmummer: ";
	cin >> romNr;

	//for alle typer rom
	for (int i = 0; i < 3; i++)
	{
		//for alle rom
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			
			tempRom = (Rom*)rom[i]->remove_no(j);
			rom[i]->add(tempRom);

			if (tempRom->getid() == romNr)
			{
				funnetNr = true;

				//henter listen over reservasjoner.
				tempList = (List*)tempRom->getlist();
				
				//alle reservasjonene til ett rom.
				for (int k = 1; k <= tempList->no_of_elements(); k++)
				{
					tempRes = (Reservasjon*)tempList->remove_no(k);
					tempList->add(tempRes);
					
					//hvis det er en reservasjon for dagens dato.
					if (timer.hent_dato() <= tempRes->getAvreise() && timer.hent_dato() >= tempRes->getAnkomst())
					{
						funnetRes = true;
						tempRes->display(true);
					}
				}
			}
		}
	}

	//hvis rommet eller reservasjonen ikke er funnet
	if (!funnetNr)
	{
		cout << "Romnummer ikke funnet" << endl;
	}
	else if (!funnetRes)
	{
		cout << "Ingen reservasjon i dag" << endl;
	}
}

void Hotell::ledigeRom(int nr)
{
	//midlertidlige variabler
	Rom* tempRom;
	List* tempResList;
	Reservasjon* tempRes;
	bool opptatt = false;

	//hvilket tidsrom vil du finne?
	int minDate = getdate("\nFra dato: ", timer.hent_dato());
	int maxDate = getdate("\nTil dato: ", minDate);

	//for alle rom av typen 'nr'
	for (int i = 1; i <= rom[nr]->no_of_elements(); i++)
	{
		tempRom = (Rom*)rom[nr]->remove_no(i);
		rom[nr]->add(tempRom);

		tempResList = (List*)tempRom->getlist();

		//for alle reservasjoner
		for (int j = 1; j <= tempResList->no_of_elements(); j++)
		{
			tempRes = (Reservasjon*)tempResList->remove_no(j);
			tempResList->add(tempRes);

			//hvis reservasjonen gjelder for 
			if (!(maxDate < tempRes->getAnkomst() || minDate > tempRes->getAvreise()))
			{
				opptatt = true;
			}
		}
		//hvis dette rommet ikke er opptatt
		if (!opptatt)
		{
			//skriv ut romnr
			cout << tempRom->getid() << ' ';
		}
	}
}

string Hotell::getNavn()
{
	return navn;
}

void Hotell::ledigTidRom()
{
	int romNr;				//rommet du vil ha
	bool funnet = false;	//er rommet funnet
	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;

	cout << "Hvilket romnummer?" << endl;
	cin >> romNr;

	//Alle romtypene
	for(int i = 0; i < 3; i++)
	{
		//Alle rommene
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			tempRom = (Rom*)rom[i]->remove_no(j);
			rom[i]->add(tempRom);

			//hvis rommet er riktig
			if (romNr == tempRom->getid())
			{
				tempList = tempRom->getlist();
				funnet = true;
				cout << "\nRommet er opptatt i perioden(e):\n";

				//hvis det ikke er noen reservasjoner
				if (tempList->no_of_elements() == 0)
				{
					cout << "Ingen reservasjoner" << endl;
				}
				else
				{
					//For alle reservasjonene
					for (int k = 1; k <= tempList->no_of_elements(); k++)
					{
						tempRes = (Reservasjon*)tempList->remove_no(k);
						tempList->add(tempRes);
						
						cout << '\t' << tempRes->getAnkomst() << "\t-\t" << tempRes->getAvreise() << endl;
					}
				}
			}
		}
	}

	//hvis rommet er funnet
	if (!funnet)
	{
		cout << "Romnummer ikke funnet." << endl;
	}
}

//endrer info etter type (1=annkomst, 2=avreise, 3 = begge)
void Hotell::endre(int type)
{
	bool funnet = false;	//er rommet funnet
	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;

	string eier = les("Romeier:");
	int origAnkomst = getdate("\nOriginal ankomst", timer.hent_dato());

	for (int i = 0; i < 3; i++)
	{
		//for alle rom
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			
			tempRom = (Rom*)rom[i]->remove_no(j);

			//henter listen over reservasjoner.
			tempList = (List*)tempRom->getlist();
			
			//alle reservasjonene til ett rom.
			for (int k = 1; k <= tempList->no_of_elements(); k++)
			{
				tempRes = (Reservasjon*)tempList->remove_no(k);
				
				//hvis det er en reservasjon for dagens dato.
				if (origAnkomst == tempRes->getAnkomst())
				{
					funnet = true;
					cout << "\nRomnummer: " << tempRom->getid() << endl;
					tempRes->display(false);

					if (confirm("\nVil du endre denne reservasjonen?"))
					{
						if (type == 1 || type == 3)
						{
							//endrer avreisen
							tempRes->setAnkomst(getdate("\nNy ankomst", timer.hent_dato()));
						}
						if (type == 2 || type == 3)
						{
							//endrer avreisen
							tempRes->setAvreise(getdate("\nNy avreise", timer.hent_dato()));
						}
						
					}
				}
				//setter tilbake
				tempList->add(tempRes);
				tempRom->replaceList(tempList);
			}
			rom[i]->add(tempRom);
		}
	}
	if (!funnet)
	{
		cout << "\nReservasjon ikke funnet" << endl;
	}
}

//bytter rom
void Hotell::byttRom()
{
	bool funnet = false;	//er rommet funnet
	bool brukt = false;
	Rom* tempRom1;
	List* tempList1;
	Reservasjon* tempRes1;
	Rom* tempRom2;
	List* tempList2;
	Reservasjon* tempRes2;
	int romNr1;
	int romNr2;
	int x;
	int y;
	int z;

	cout << "\nHvilket romnummer vil du flytte fra? ";
	cin >> romNr1;

	int ankomst = getdate("\nAnkomst", timer.hent_dato());

	
	for (int i = 0; i < 3; i++)
	{
		//for alle rom
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			tempRom1 = (Rom*)rom[i]->remove_no(j);
			rom[i]->add(tempRom1);

			if (tempRom1->getid() == romNr1)
			{
				//henter listen over reservasjoner.
				tempList1 = (List*)tempRom1->getlist();
				
				//alle reservasjonene til ett rom.
				for (int k = 1; k <= tempList1->no_of_elements(); k++)
				{
					tempRes1 = (Reservasjon*)tempList1->remove_no(k);
					tempList1->add(tempRes1);

					if (tempRes1->getAnkomst() == ankomst)
					{
						funnet = true;
						x = i;
						y = j;
						z = k;
					}
				}
			}
		}
	}

	if (!funnet)
	{
		cout << "\nReservasjon ikke funnet." << endl;
	}
	else
	{//sett inn i nytt rom
		
		cout << "\nHvilket romnummer vil du flytte til? ";
		cin >> romNr2;

		for (int i = 0; i < 3; i++)
		{
			//for alle rom
			for (int j = 1; j <= rom[i]->no_of_elements(); j++)
			{
				tempRom2 = (Rom*)rom[i]->remove_no(j);
				rom[i]->add(tempRom2);

				tempList2 = (List*)tempRom2->getlist();

				if (tempRom2->getid() == romNr2)
				{

					//alle reservasjonene til ett rom.
					for (int k = 1; k <= tempList1->no_of_elements(); k++)
					{
						tempRes2 = (Reservasjon*)tempList2->remove_no(k);
						tempList2->add(tempRes2);
	
						if (!(tempRes1->getAvreise() < tempRes2->getAnkomst() || tempRes1->getAnkomst() > tempRes2->getAvreise()))
						{
							brukt = true;
						}
					}
				}
			}
			if (!brukt)
			{
				//for alle rom
				for (int j = 1; j <= rom[i]->no_of_elements(); j++)
				{
					tempRom2 = (Rom*)rom[i]->remove_no(j);
		
					if (tempRom2->getid() == romNr2)
					{
						//henter listen over reservasjoner.
						
						//legger til reservasjonen.
						tempList2->add(tempRes1);
						tempRom2->replaceList(tempList2);
	
						//fjerner reservasjonen fra det gamle rommet.
						tempList1->destroy(z);
						tempRom1->replaceList(tempList1);
						rom[x]->destroy(y);
						rom[x]->add(tempRom1);
					}
					rom[i]->add(tempRom2);
				}
			}
		}
	}

	if (brukt)
	{
		cout << "\nDet rommet er opptatt." << endl;
	}
}


void Hotell::utskjekking()
{
	//filnavnet er egen variabel.
	ofstream fil;
	fil.open(filnavn+".HST");
	string navn;

	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;

	bool funnet = false;


	navn = les("\nUtskjekkers navn:");

	//for alle rom
	for (int x = 0; x < 3; x++)
	{
		for (int y = 1; y <= rom[x]->no_of_elements(); y++)
		{
			//henter ut rommet
			tempRom = (Rom*)rom[x]->remove_no(y);
			rom[x]->add(tempRom);

			tempList = tempRom->getlist();

			for (int z = 1; z <= tempList->no_of_elements(); z++)
			{
				tempRes = (Reservasjon*)tempList->remove_no(z);

				//hvis den er riktig
				if (navn == tempRes->getNavn() && timer.hent_dato() == tempRes->getAvreise())
				{
					funnet = true;

					tempRes->utskjekking(fil);
				}
				else
				{ //hvis det ikke er riktig reservasjon, sett den tilbake.
					tempList->add(tempRes);
				}
			}
		}
	}

	fil.close();
}

void Hotell::addRegning()
{
	int romNr;				//rommet du vil ha
	bool funnet = false;	//er rommet funnet
	Rom* tempRom;
	List* tempList;
	Reservasjon* tempRes;

	cout << "Hvilket romnummer?" << endl;
	cin >> romNr;

	//Alle romtypene
	for(int i = 0; i < 3; i++)
	{
		//Alle rommene
		for (int j = 1; j <= rom[i]->no_of_elements(); j++)
		{
			tempRom = (Rom*)rom[i]->remove_no(j);

			//hvis rommet er riktig
			if (romNr == tempRom->getid())
			{
				tempList = tempRom->getlist();
				//for alle reservasjoner
				for (int j = 0; j < tempList->no_of_elements(); j++)
				{
					tempRes = (Reservasjon*)tempList->remove_no(j);
					if (tempRes->getAnkomst() <= timer.hent_dato() && tempRes->getAvreise() >= timer.hent_dato())
					{
						funnet = true;
						//legg inn ting.
						tempRes->addRegning();
						tempList->add(tempRes);
						tempRom->replaceList(tempList);
					}
				}
			}
			rom[i]->add(tempRom);
		}
	}
}