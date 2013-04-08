


#include "Header.h"


using namespace std;



Singel::Singel(int ID, ifstream &file):Rom(ID, file){
	//singel har ingen ekstra data i forhold til rom
	//derfor er den tom.

}



void Singel::toFile(ofstream &file){

	//samme som over, men med skriving til fil.
	Rom::toFile(file);
}



void Singel::display(){
	
	//Samme som over, men vise data.
	Rom::display(false);
}