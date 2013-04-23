#include "Header.h"


using namespace std;


//oppretter Reg_post objekt.
Reg_Post::Reg_Post(){

	int temp = 0;

	//leser fra fil
	ifstream fil ("Reg_Post.DTA");
	if (fil){
		do{
			getline(fil, poster[++temp]);

		}while (!fil.eof());
	}

	//antallet elementer
	antall = temp;
}


//skirver info til skjermen.
void Reg_Post::display(){

	for(int x = 1; x <= antall; x++){
		cout << x << " - " << poster[x] << endl;
	}
}

int Reg_Post::getAntall()
{
	return antall;
}

//sender tilbake beskrivelden, eller "" hvis no ikke finnes.
string Reg_Post::beskrivelse(int no)
{
	if (no <= antall && no >= 0)
	{
		return poster[no];
	}
	else
	{
		return "";
	}
}