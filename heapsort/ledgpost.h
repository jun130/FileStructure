// ledgpost.h

#ifndef LEDGPOST_H
#define LEDGPOST_H

#include "mastrans.h"
#include "ledger.h"
#include "recfile.h"
#include "length.h"

class LedgerProcess: public MasterTransactionProcess<int>
// ledger processing of a ledger file and a journal file
// the item type is int to represent an account number
{public:
	LedgerProcess(int monthNumber); // constructor

	// Basic list processing methods
	int InitializeList (int ListNumber, char * List1Name);
	int InitializeOutput (char * OutputListName);
	int NextItemInList (int ListNumber); //get next item from this list
	int Item (int ListNumber); // return current item from this list
	int ProcessItem (int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing

	// master/transaction methods
	virtual int ProcessNewMaster ();//  when new master read
	virtual int ProcessCurrentMaster ();// each transaction for a master
	virtual int ProcessEndMaster ();// after all transactions for a master
	virtual int ProcessTransactionError ();// no master for transaction

protected:
	// members
	int MonthNumber; // number of month to be processed
	LengthFieldBuffer Lbuffer, Jbuffer; // buffers for files
	RecordFile<Ledger> LedgerFile ; // list 1
	RecordFile<Journal> JournalFile;// list 2
	int AccountNumber [3]; // current item in each list
	Ledger ledger; // current ledger object
	Journal journal; // current journal object
	ofstream OutputList; // text output file for post method
	static int LowAcct;// lower than the lowest account number
	static int HighAcct;// higher than the highest account number

	int NextItemInLedger ();
	int NextItemInJournal ();
};

#endif
