

#include "Header.h"

using namespace std;

extern Timer timer;

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
	for(int x = 1; x <= beboere; x++){
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
	for (int x = 1; x <= beboere; x++){
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


//data om reservasjonen.
void Reservasjon::display(){

	cout << "Fra " << number << " til " << avreise << " ("
		 << overnattinger << " dager)" << endl;

	//mangler data.

}