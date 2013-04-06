#include "Header.h"


using namespace std;



Reg_Post::Reg_Post(){

	int temp = 0;

	ifstream fil ("Reg_Post.DTA");
	if (fil){
		do{
			getline(fil, poster[++temp]);

		}while (!fil.eof());
	}

	antall = temp;
}


void Reg_Post::display(){

	for(int x = 1; x <= antall; x++){
		cout << x << " - " << poster[x] << endl;
	}
}