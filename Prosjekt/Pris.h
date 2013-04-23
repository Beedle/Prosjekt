//pris

#pragma once

class Pris{
	private:
		//rom[0] for vanlig, [1] for dobbeltrom og [2] for sutie.
		float ukedag[3];
		float helg[3];

		int antPerioder;

		//spesielle priser
		float tilbudspris[365][3];
		int startdato[365];
		int sluttdato[365];
	public:
		Pris(string file);

		float getPris(int dato, int romtype);
};

