#include "Header.h"


class Rom: public Num_element {
	protected:
		int antSenger;
		bool frokost;
		List *reservasjoner;

	public:
		
	
};



class Singel: public Rom {
	protected:

	public:

};



class Dobbel: public Rom {
	protected:
		bool ekstraSeng;
		
	public:


};



class Suite: public Rom {
	protected:
		int sengerSuite;
		int kvm;
		string beskrivelse;

	public:



};