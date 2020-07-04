#include "ledgpost.h"

// list processing methods

LedgerProcess::LedgerProcess(int monthNumber)
: MasterTransactionProcess<int>(), LedgerFile(Lbuffer), JournalFile(Jbuffer)
{
	MonthNumber = monthNumber;
}

int LedgerProcess::InitializeList (int ListNumber, char * ListName)
{
	AccountNumber[ListNumber] = LowAcct;
	switch (ListNumber)
	{
		case 1: // initialize ledger file
			return LedgerFile.Open(ListName, ios::in);
		case 2: // initialize ledger file
			return JournalFile.Open(ListName, ios::in);
	}
	return FALSE;
}

int LedgerProcess::InitializeOutput (char * OutputListName)
{
	OutputList.open(OutputListName);
	return 1;
}

int LedgerProcess::NextItemInList (int ListNumber)
//get next item from this list
{
	switch (ListNumber)
	{
	case 1: return NextItemInLedger ();
	case 2: return NextItemInJournal ();
	}
	return FALSE;
}

int LedgerProcess::Item (int ListNumber)
// return current item from this list
{	return AccountNumber[ListNumber];}

int LedgerProcess::ProcessItem (int ListNumber)
// process the item in this list when it first appears
{
	switch (ListNumber)
	{
		case 1: // process new ledger object
			ledger.PrintHeader(OutputList);
		case 2: // process journal file
			journal.PrintLine(OutputList);
	}
	return TRUE;
}

int LedgerProcess::ProcessNewMaster ()//  when new master read
{// first step in proceesing master record
 // print the header and setup last month's balance
	ledger.PrintHeader(OutputList);
	ledger.Balances[MonthNumber] = ledger.Balances[MonthNumber-1];
	return TRUE;
}

int LedgerProcess::ProcessCurrentMaster ()// each transaction for a master
{// add the transaction amount to the balance for this month	
	ledger.Balances[MonthNumber] += journal.Amount;
	return TRUE;
}

int LedgerProcess::ProcessEndMaster ()// after all transactions for a master
{// print the balances line to output	
	PrintBalances(OutputList,ledger.Balances[MonthNumber-1],ledger.Balances[MonthNumber]);
	return TRUE;
}

int LedgerProcess::ProcessTransactionError ()// no master for transaction
{// print error message to standard error
	cerr<<"Error no account for journal"<<endl;
	cerr<<journal.Acct; 
	journal.PrintLine(cerr);
	return TRUE;
}

int LedgerProcess::FinishUp()
// complete the processing
{
	LedgerFile.Close(); 
	JournalFile.Close(); 
	OutputList.close();
	return TRUE;
}

int LedgerProcess::NextItemInLedger ()
{
	int res = LedgerFile . Read (ledger);
	if (res <= 0) 
	{
		AccountNumber[1] = HighAcct;
		return FALSE;
	}
	if (ledger.Acct <= AccountNumber[1])
	{	cerr<<"Ledger account out of order"<<endl; exit(0);}
	AccountNumber[1]=ledger.Acct;
	return TRUE;
}

int LedgerProcess::NextItemInJournal ()
{
	int res = JournalFile . Read (journal);
	if (res <= 0) 
	{
		AccountNumber[2] = HighAcct;
		return FALSE;
	}
	if (journal.Acct < AccountNumber[2])
	{	cerr<<"Journal account out of order"<<endl; exit(0);}
	AccountNumber[2]=journal.Acct;
	return TRUE;
}

int LedgerProcess::LowAcct = -1;
int LedgerProcess::HighAcct = 9999;


