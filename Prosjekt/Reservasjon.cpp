

#include "Header.h"

using namespace std;

extern Timer timer;


//oppretter ny reservasjon. Ankomst, avreise og antallet gjester som parameter
Reservasjon::Reservasjon(int ID, int dpt, int gje, string filnavn, int type):Num_element(ID){

	Pris* prisen= new Pris(filnavn+".DTA");
	//variabler settes lik parametre.
	beboere = gje;
	avreise = dpt;
	
	//leser inn navn
	navn[0] = les("Navn det skal reserveres i");

	//antallet overnattinger, og leser pris for hver dag.
	overnattinger = timer.forskjell_datoer(ID, dpt);
	for (int x = 0; x <= overnattinger; x++){

		pris[x] = prisen->getPris(ID+x, type);
	}

	//oppretter liste
	regninger = new List(FIFO);
}



Reservasjon::Reservasjon(int ID, ifstream &fil):Num_element(ID){

	//avreise dato
	fil >> avreise;

	//antallet dager det skal overnattes, og pris for alle dagene
	overnattinger = timer.forskjell_datoer(ID, avreise);
	for (int x = 1; x <= overnattinger; x++){
		fil >> pris[x];
	}

	//status på seng, antallet beboere.
	//og navn på alle beboerene.
	fil >> seng >> beboere; fil.ignore();
	for(int x = 0; x < beboere; x++){
		getline(fil, navn[x]);
	}


	int trash;
	int sum;
	regninger = new List(Sorted);
	Regning *regning;

	//antallet regninger og regningene.
	fil >> trash;
	for(int x = 1; x <= trash; x++){

		fil >> sum;
		regning = new Regning(sum, fil);
		regninger->add(regning);
	}


}


//skriver til fil.
void Reservasjon::tofile(ofstream &fil){

	//ankomst og avreise, samt pris for antallet dager
	fil << number << " " << avreise;
	for(int x = 1; x <= timer.forskjell_datoer(number, avreise); x++){
		fil << " " << pris[x];
	}
	
	//status på ekstra seng
	fil << " " << seng << endl;
	
	//antallet beboere og navn på de
	fil << beboere << endl;
	for (int x = 0; x < beboere; x++){
		fil << navn[x] << endl;
	}


	//antallet regninger og regningene.
	Regning *temp;
	fil << regninger->no_of_elements() << endl;	
	for(int x = 1; x <= regninger->no_of_elements(); x++){
		temp = (Regning*)regninger->remove_no(x);
		regninger->add(temp);
		temp->tofile(fil);
	}


}

//skriver data. hvis all skriver også data om alle regninger
void Reservasjon::display(bool all){

		//skriver ut data.
	cout << "\n\nReservasjon tilhørende: " << navn[0] << endl;
	cout << "Fra " << number << " til " << avreise << " ("
		 << overnattinger << " dager)" << endl;

	//hvis all og det finnes regninger
	if(all && regninger->no_of_elements()){
		cout << "\nfølgende regninger: " << endl;
		regninger->display_list();
	}

}


//henter navn
string Reservasjon::getNavn(){
	return navn[0];
}


//henter avreise
int Reservasjon::getAvreise(){
	return avreise;
}

//henter ankomst
int Reservasjon::getAnkomst(){
	return number;
}

//sammenligner navn med input tekst.
bool Reservasjon::compNavn(string txt){
	return txt.compare(navn[0]);
}

//setter data
void Reservasjon::setAnkomst(int ny)
{
	number = ny;
	overnattinger = timer.forskjell_datoer(number, avreise);
	for (int i = 0; i <= overnattinger; i++){

		//må endres til å bruke pris objekt.
		pris[i] = timer.ukedagsnr(number+i);
	}
}

void Reservasjon::setAvreise(int ny)
{
	avreise = ny;
	overnattinger = timer.forskjell_datoer(number, avreise);
	for (int i = 0; i <= overnattinger; i++){

		//må endres til å bruke pris objekt.
		pris[i] = timer.ukedagsnr(number+i);
	}
}

void Reservasjon::addRegning()
{
	Reg_Post* regpost = new Reg_Post();
	Regning* tempRegning;
	char kommando;
	int pris;
	string beskrivelse;
	
	cout << "\nHvaslags regning ønsker du å legge til?" << endl;
	regpost->display();
	cout << regpost->getAntall() + 1 << " - Selvdefinert";

	kommando = les(true);

	//Hvis kommando har beskrivelse
	if (kommando >= 1 && kommando <= regpost->getAntall())
	{
		cout << "\n Hvor mye koster det (kr)?: ";
		cin >> pris;
		beskrivelse = regpost->beskrivelse(kommando);

		//lag ny regning
		tempRegning = new Regning(pris, beskrivelse);
		regninger->add(tempRegning);
	}
	else if (kommando == regpost->getAntall() + 1)
	{
		beskrivelse = les("Hva er regningen for?");
		cout << "\n Hvor mye koster det (kr)?: ";
		cin >> pris;

		//lag ny regning
		tempRegning = new Regning(pris, beskrivelse);
		regninger->add(tempRegning);
	}
	else
	{
		cout << "ERROR";
	}
	
}

void Reservasjon::utskjekking(ofstream &fil)
{
	int sum = 0;
	Regning* tempReg;

	int romleie = 0;
	for (int i = 0; i < overnattinger; i++)
	{
		romleie += pris[i];
		sum += pris[i];
	}

	cout << "Navn:\t" << navn[0] << endl
		 << "Annkomst:\t" << number << endl
		 << "Avreise:\t" << avreise << endl
		 << "Beboere:\t" << beboere << endl
		 << "Romleie (kr):\t" << romleie << endl << endl
		 << "Andre regninger:" << endl;

	fil << "Navn:\t" << navn[0] << endl
		<< "Annkomst:\t" << number << endl
		<< "Avreise:\t" << avreise << endl
		<< "Beboere:\t" << beboere << endl
		<< "Romleie (kr):\t" << romleie << endl << endl
		<< "Andre regninger:" << endl;

	int antRegninger = regninger->no_of_elements();

	//for alle regninger, skriv dem ut.
	for (int i = 1; i <= antRegninger; i++)
	{
		tempReg = (Regning*)regninger->remove();
		tempReg->display();
		tempReg->tofile(fil);
	}

	cout << endl << "Total:\t\t" << sum << endl;

	fil << endl << "Total:\t\t" << sum << endl << endl << endl;
}

void Reservasjon::innsjekk()
{
	//les inn alle navn.
	for (int x = 1; x < beboere; x++)
	{
		navn[x] = les("\nNavnet på beboer");
	}
}