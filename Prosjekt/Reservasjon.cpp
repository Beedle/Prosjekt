

#include "Header.h"

using namespace std;

extern Timer timer;


//oppretter ny reservasjon. Ankomst, avreise og antallet gjester som parameter
Reservasjon::Reservasjon(int ID, int dpt, int gje):Num_element(ID){

	//variabler settes lik parametre.
	beboere = gje;
	avreise = dpt;
	
	//leser inn navn
	navn = les("Navn det skal reserveres i");

	//antallet overnattinger, og leser pris for hver dag.
	overnattinger = timer.forskjell_datoer(ID, dpt);
	for (int x = 0; x <= overnattinger; x++){

		//må endres til å bruke pris objekt.
		pris[x] = timer.ukedagsnr(ID+x);
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
	//for(int x = 1; x <= beboere; x++){
	//	getline(fil, navn[x]);
	//}
	getline(fil, navn);


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
	//for (int x = 1; x <= beboere; x++){
	//	fil << navn[x] << endl;
	//}
	fil << navn << endl;


	//antallet regninger og regningene.
	Regning *temp;
	fil << regninger->no_of_elements() << endl;	
	for(int x = 1; x <= regninger->no_of_elements(); x++){
		temp = (Regning*)regninger->remove_no(x);
		regninger->add(temp);
		temp->tofile(fil);
	}


}

//skriver data. all om alle regningene
void Reservasjon::display(bool all){

		//skriver ut data.
	cout << "\n\nreservasjon tilhørende: " << navn << endl;
	cout << "Fra " << number << " til " << avreise << " ("
		 << overnattinger << " dager)" << endl;


	if(all && regninger->no_of_elements()){
		cout << "\nfølgende regninger: " << endl;
		regninger->display_list();
	}

}


//henter navn
string Reservasjon::getNavn(){
	return navn;
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
	return txt.compare(navn);
}