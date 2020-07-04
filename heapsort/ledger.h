// ledger.h
#ifndef LEDGER_H
#define LEDGER_H

#include <fstream.h>
#include <string.h>
#include "iobuffer.h"

class Ledger
{public:
	int Acct;
	char Title [30];
	double Balances[12];
	int Pack(IOBuffer & buffer) const;
	int Unpack (IOBuffer & buffer);
	ostream & Print (ostream &);
	ostream & PrintHeader (ostream &);
	Ledger ();
	Ledger (int, char *, double, double, double);
};

ostream & PrintBalances (ostream & stream,
		double PreviousBalance, double CurrentBalance);

class Journal
{public:
	int Acct;
	int CheckNum;
	char Date[10];
	char Description[30];
	double Amount;
	int Pack (IOBuffer &) const;
	int Unpack (IOBuffer &);
	ostream & PrintLine (ostream &);
	Journal ();
	Journal (int, int, char*, char*, double);
};

#endif