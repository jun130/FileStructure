#include "recfile.h"
#include "length.h"
#include "ledger.h"

Ledger L1(101,"Checking Account #1",1032.57,2114.56,5219.23);	
Ledger L2(102,"Checking Account #2",543.78,3094.17,1321.20);	
Ledger L3(505,"Advertising expense",25.00,25.00,25.00);
Ledger L4(510,"Auto expenses",195.40,307.92,501.12);
Ledger L5(515,"Bank charges",0.00,0.00,0.00);
Ledger L6(520,"Books and publications",27.95,27.95,87.40);
Ledger L7(525,"Interest expense",103.50,255.20,380.27);
Ledger L8(535,"Miscellaneous expense",12.45,17.87,23.87);
Ledger L9(540,"Office expense",57.50,105.25,138.37);
Ledger L10(545,"Postage and shipping",21.00,27.63,57.45);
Ledger L11(550,"Rent",500.00,1000.00,1500.00);
Ledger L12(555,"Supplies",112.00,167.50,2441.80);	


Journal J1(101, 1271, "04/02/86", "Auto expense", -78.70);
Journal J2(101, 1272, "04/02/97", "Rent", -500.00);
Journal J3(101, 1273, "04/04/97", "Advertising", -87.50);
Journal J4(101, 1274, "04/02/97", "Auto expense", -31.83);
Journal J5(102, 670, "04/02/97", "Office expense", -32.78);
Journal J6(505, 1273, "04/04/97", "Newspaper ad re: new product", 87.50);
Journal J7(510, 1271, "04/02/97", "Tune up and minor repair", 78.70);
Journal J8(510, 1274, "04/09/97", "Oil change", 31.83);
Journal J9(540, 670, "04/02/97", "Printer cartridge", 32.78);
Journal J10(550, 1272, "04/02/97", "Rent for April", 500.00);

void main()
{
	LengthFieldBuffer Lbuffer;
	RecordFile<Ledger> ledgerFile(Lbuffer);
	ledgerFile.Create("ledger.dat",ios::out|ios::in);
	ledgerFile.Write(L1);
	ledgerFile.Write(L2);
	ledgerFile.Write(L3);
	ledgerFile.Write(L4);
	ledgerFile.Write(L5);
	ledgerFile.Write(L6);
	ledgerFile.Write(L7);
	ledgerFile.Write(L8);
	ledgerFile.Write(L9);
	ledgerFile.Write(L10);
	ledgerFile.Write(L11);
	ledgerFile.Write(L12);
	ledgerFile.Close();

	LengthFieldBuffer Jbuffer;
	RecordFile<Journal> journalFile(Jbuffer);
	journalFile.Create("journal.dat",ios::out|ios::in);
	journalFile.Write(J1);
	journalFile.Write(J2);
	journalFile.Write(J3);
	journalFile.Write(J4);
	journalFile.Write(J5);
	journalFile.Write(J6);
	journalFile.Write(J7);
	journalFile.Write(J8);
	journalFile.Write(J9);
	journalFile.Write(J10);

	journalFile.Close();

	int res;

	RecordFile<Ledger> lFile(Lbuffer);
	lFile.Open("ledger.dat", ios::in);
	Ledger ledger;
	while (1)
	{
		res=lFile.Read(ledger);
		if (res<=0) break;
		ledger.Print(cout);
	}
	RecordFile<Journal> jFile(Jbuffer);
	jFile.Open("journal.dat", ios::in);
	Journal journal;
	while (1)
	{
		res=jFile.Read(journal);
		if (res<=0) break;
		journal.PrintLine(cout);
	}
}