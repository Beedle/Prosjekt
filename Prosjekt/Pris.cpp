#include "Header.h"

extern Timer timer;

Pris::Pris(string file)
{
	ifstream fil;
	fil.open(file+".PRS");
	string crap; //variabel for å lese inn unødvendig 'crap' som bare er der for å gjøre filen mer lesbar

	if(fil)
	{
		//leser inn normale priser.
		fil >> crap >> crap >> ukedag[0];
		fil >> crap >> ukedag[1];
		fil >> crap >> ukedag[2];
		
		fil >> crap >> crap >> helg[0];
		fil >> crap >> helg[1];
		fil >> crap >> helg[2];

		fil >> crap >> antPerioder;

		//for alle perioder
		for (int i = 0; i < antPerioder; i++)
		{
			//leser inn tilbudsdata
			fil >> crap >> startdato[i] >> crap >> sluttdato[i];
			fil >> crap >> crap >> tilbudspris[i][0];
			fil >> crap >> tilbudspris[i][1];
			fil >> crap >> tilbudspris[i][2];
		}
	}
	else
	{
		cout << "\n\nPrisfil ikke funnet " << file << ".PRS" << endl;
	}
	fil.close();
}

//returnerer prisen for gjeldende dato og romtype.
float Pris::getPris(int dato, int romtype)
{
	bool funnet = false;
	int dagnr;

	for (int i = 0; i < antPerioder; i++)
	{
		if (dato >= startdato[i] && dato <= sluttdato[i])
		{
			//hvis det finnes en tilbudspris for perioden
			funnet = true;

			return tilbudspris[i][romtype];
		}
	}

	if (!funnet)
	{
		dagnr = timer.ukedagsnr(dato);
		//hvis det ikke er en helg
		if (dagnr != 5 && dagnr != 6)
		{
			return ukedag[romtype];
		}
		else
		{
			return helg[romtype];
		}
	}
}