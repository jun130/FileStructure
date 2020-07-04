#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "person.h"
#include "buffile.h"
#include "recfile.h"

Person MaryAmes;
Person AlanMason;

template <class IOB>
void testBuffer (IOB & Buff, char * myfile)
{
	Person person; int result; int recaddr1, recaddr2;

	// Test writing
	RecordFile<Person> TestOut (Buff);
	result = TestOut . Create (myfile,ios::in|ios::out);
	cout << "create file "<<result<<endl;
	if (!result)
	{	cout << "Unable to create file "<<myfile<<endl; return;}
	recaddr1 = TestOut . Write (MaryAmes);
	cout << "write at "<<recaddr1<<endl;
	recaddr2 = TestOut . Write (AlanMason);
	cout << "write at "<<recaddr2<<endl;
	TestOut . Close ();

	// test reading
	RecordFile<Person> TestIn (Buff);
	TestIn . Open (myfile, ios::in);
	TestIn . Read (person, recaddr1);
	person . Print (cout, "First record:");
	TestIn . Read (person, recaddr2);
	person . Print (cout, "Second record:");
	result = TestIn . Read (person, recaddr2*2);
	if (result != -1) cout<<"Read past end of file! Error."<<endl;
	else cout <<"Read past end of file failed! Correct."<<endl;
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
	testBuffer (Buff, "fixfile.dat");
}

void testLength ()
{
	cout << "\nTesting LengthTextBuffer"<<endl;
	LengthFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "lenfile.dat");
}

void testDelim ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	DelimFieldBuffer::SetDefaultDelim ('|');
	DelimFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "delfile.dat");
}

int main(int argc, char ** argv)
{
	InitPerson();
	testFixedField ();
	testLength ();
	testDelim ();
}
