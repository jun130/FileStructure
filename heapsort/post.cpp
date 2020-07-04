// post.cpp

#include <fstream.h>
#include <string.h>
#include "recfile.h"
#include "length.h"
#include "ledgpost.h"

const int Month = 3; // processing for April

int main ()
{
	LedgerProcess Posting(Month);
	Posting.PostTransactions("ledger.dat","journal.dat","ledger.txt");
	return 1;
}

