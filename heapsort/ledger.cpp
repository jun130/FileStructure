// ledger.cpp
#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include "ledger.h"
#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

int Ledger::Pack (IOBuffer & buffer) const
{
	buffer.Clear();
	buffer.Pack(&Acct, sizeof(Acct));
	buffer.Pack(&Title, -1);
	for (int i=0; i<12; i++)
		buffer.Pack(&Balances[i], sizeof(Balances[i]));
	return TRUE;
}

int Ledger::Unpack (IOBuffer & buffer)
{
	buffer.Unpack(&Acct, sizeof(Acct));
	buffer.Unpack(&Title, sizeof(Title));
	for (int i=0; i<12; i++)
		buffer.Unpack(&Balances[i], sizeof(Balances[i]));
	return TRUE;
}

Ledger::Ledger ()
{
	Acct = 0;
	Title[0] = 0;
	for (int i=0; i<12; i++) Balances[i]=0.0;
}

Ledger::Ledger (int acct, char * title, double jan, double feb,
	double mar)
{
	Acct = acct;
	strcpy(Title, title);
	Balances[0] = jan;
	Balances[1] = feb;
	Balances[2] = mar;
	for (int i=3; i<12; i++) Balances[i]=0.0;
}

ostream & Ledger::Print (ostream & stream)
{
	stream.setf(ios::right,ios::adjustfield);
	stream << Acct <<'\t';
	stream.setf(ios::left,ios::adjustfield);
	stream <<setw(20)<<Title;
	stream.setf(ios::right,ios::adjustfield);
	stream.setf(ios::right|ios::fixed,ios::floatfield);
	stream.precision(2);
	for (int i = 0; i<12; i++)
	{
		if (Balances[i]<0.005 && i > 2)break;
		stream << '\t'<<setw(8)<<Balances[i];
	}
	stream <<endl;
	return stream;
}

ostream & Ledger::PrintHeader (ostream & stream)
{// print the report header for this account
	stream <<Acct<<'\t'<<Title<<endl;
	return stream;
}

ostream & PrintBalances (ostream & stream,
		double PreviousBalance, double CurrentBalance)
{// print balances line of report
	stream << "\t\t\t\tPrev. bal: "
		<<setw(8)<<setprecision(2)<<PreviousBalance
		<<"\tNew bal:\t"
		<<setw(8)<<setprecision(2)<<CurrentBalance<<endl;
	return stream;
}

ostream & Journal::PrintLine (ostream & stream)
{
	stream.setf(ios::right,ios::adjustfield);
	stream <<'\t'<<setw(6)<<CheckNum <<'\t';
	stream.setf(ios::left,ios::adjustfield);
	stream <<Date
		<<'\t'<<setw(30)<<Description;
	stream.setf(ios::right,ios::adjustfield);
	stream.setf(ios::right|ios::fixed,ios::floatfield);
	stream.precision(2);
	stream << '\t'<<setw(8)<<Amount<<endl;
	return stream;
}
int Journal::Pack (IOBuffer & buffer) const
{
	buffer.Clear();
	buffer.Pack(&Acct, sizeof(Acct));
	buffer.Pack(&CheckNum, sizeof(CheckNum));
	buffer.Pack(&Date, -1);
	buffer.Pack(&Description, -1);
	buffer.Pack(&Amount, sizeof(Amount));
	return TRUE;
}

int Journal::Unpack (IOBuffer & buffer)
{
	buffer.Unpack(&Acct, sizeof(Acct));
	buffer.Unpack(&CheckNum, sizeof(CheckNum));
	buffer.Unpack(&Date, -1);
	buffer.Unpack(&Description, sizeof(Description));
	buffer.Unpack(&Amount, sizeof(Amount));
	return TRUE;
}

Journal::Journal ()
{
	Acct = 0;
	CheckNum = 0;
	Date[0] = 0;
	Description[0] = 0;
	Amount = 0.0;
}

Journal::Journal (int acct, int checkNum, char* date,
	char * desc, double amt)
{
	Acct = acct;
	CheckNum = checkNum;
	strcpy(Date, date);
	strcpy(Description, desc);
	Amount = amt;
}

