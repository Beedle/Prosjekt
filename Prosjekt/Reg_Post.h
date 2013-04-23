

#pragma once

#include <string>

using namespace std;

class Reg_Post{
	private:
		string poster[10];
		int antall;

	public:
		Reg_Post();

		void display();
		int getAntall();
		//sender tilbake beskrivelden, eller NULL hvis no ikke finnes.
		string beskrivelse(int no);
};

