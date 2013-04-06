


#include "Header.h"


using namespace std;



Singel::Singel(int ID, ifstream &file):Rom(ID, file){
	

}


void Singel::display(){
	Rom::display();

}

void Singel::toFile(ofstream &file){

	Rom::toFile(file);

}