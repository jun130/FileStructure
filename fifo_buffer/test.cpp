#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "person.h"

Person MaryAmes;
Person AlanMason;

template <class IOB>
void testBuffer (IOB & Buff, char * myfile)
{
	Person person;
	int result;
	int recaddr1, recaddr2, recaddr3, recaddr4;

	// Test writing
	//Buff . Print (cout);
	ofstream TestOut (myfile,ios::out);
	result = Buff . WriteHeader (TestOut);
	cout << "write header "<<result<<endl;
	MaryAmes . Pack (Buff);
	//Buff . Print (cout);
	recaddr1 = Buff . Write (TestOut);
	cout << "write at "<<recaddr1<<endl;
	AlanMason. Pack (Buff);
	//Buff . Print (cout);
	recaddr2 = Buff . Write (TestOut);
	cout << "write at "<<recaddr2<<endl;
	TestOut . close ();

	// test reading
	ifstream TestIn (myfile, ios::in);
	result = Buff . ReadHeader (TestIn);
	cout <<"read header "<<result<<endl;
	Buff . DRead (TestIn, recaddr1);
	person . Unpack (Buff);
	person . Print (cout, "First record:");
	Buff . DRead (TestIn, recaddr2);
	person . Unpack (Buff);
	person . Print (cout, "Second record:");
}

void InitPerson()
{
	cout << "Initializing 3 Persons"<<endl;
	strcpy (MaryAmes.LastName, "Ames");
	strcpy (MaryAmes.FirstName, "Mary");
	strcpy (MaryAmes.Address, "123 Maple");
	strcpy (MaryAmes.City, "Stillwater");
	strcpy (MaryAmes.State, "OK");
	strcpy (MaryAmes.ZipCode, "74075");
	MaryAmes . Print (cout);
	strcpy (AlanMason.LastName, "Mason");
	strcpy (AlanMason.FirstName, "Alan");
	strcpy (AlanMason.Address, "90 Eastgate");
	strcpy (AlanMason.City, "Ada");
	strcpy (AlanMason.State, "OK");
	strcpy (AlanMason.ZipCode, "74820");
	AlanMason . Print (cout);
}

void testFixedField ()
{
	cout <<"Testing Fixed Field Buffer"<<endl;
	FixedFieldBuffer Buff (6);
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "fixlen.dat");
}

void testLength ()
{
	cout << "\nTesting LengthTextBuffer"<<endl;
	LengthFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "length.dat");
}

void testDelim ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	DelimFieldBuffer::SetDefaultDelim ('|');
	DelimFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "delim.dat");
}

int main(int argc, char ** argv)
{
	InitPerson();
	testFixedField ();
	testLength ();
	testDelim ();
}