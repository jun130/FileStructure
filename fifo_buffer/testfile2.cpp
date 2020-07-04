#include <fstream.h>
#include <iomanip.h>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "person.h"
#include "buffile.h"

Person JohnAmes;
Person AlanMason;
Person GARiccardi;
Person Padded;

template <class IOB>
void testBuffer (IOB & Buff, char * myfile)
{
	Person person;
	int result;
	int recaddr1, recaddr2, recaddr3, recaddr4;

	// Test writing
	//Buff . Print (cout);
	BufferFile TestOut (Buff);
	result = TestOut . Create (myfile,ios::in|ios::out);
	cout << "create file "<<result<<endl;
	if (!result)
	{
		cout << "Unable to create file "<<myfile<<endl;
		result = TestOut . Open (myfile, ios::in|ios::out);
		if (!result)
		{
			cout << "Unable to open file "<<myfile<<endl;
			return;
		}
	}
	JohnAmes . Pack (Buff);
	//Buff . Print (cout);
	recaddr1 = TestOut . Write ();
	cout << "write at "<<recaddr1<<endl;
	AlanMason. Pack (Buff);
	//Buff . Print (cout);
	recaddr2 = TestOut . Write ();
	cout << "write at "<<recaddr2<<endl;
	GARiccardi . Pack (Buff);
	recaddr3 = TestOut . Write ();
	cout << "write at "<<recaddr3<<endl;
	GARiccardi.Pack (Buff);
	recaddr4 = TestOut . Write ();
	cout << "write at "<<recaddr4<<endl;
	TestOut . Close ();

	// test reading
	BufferFile TestIn (Buff);
	TestIn . Open (myfile, ios::in);
	//result = TestIn . ReadHeader ();
	//cout <<"read header "<<result<<endl;
	TestIn . Read (recaddr3);
	person . Unpack (Buff);
	person . Print (cout, "First record:");
	TestIn . Read (recaddr2);
	person . Unpack (Buff);
	person . Print (cout, "Second record:");
	TestIn . Read (recaddr1);
	person . Unpack (Buff);
	person . Print (cout, "Third record");
	TestIn . Read (recaddr4);
	person . Unpack (Buff);
	person . Print (cout, "Fourth record");
	result = TestIn . Read (recaddr4*2);
	if (result!= -1) cout<<"Read past end of file! Error."<<endl;
	else cout <<"Read past end of file failed! Correct."<<endl;
}

void InitPerson()
{
	cout << "Initializing 3 Persons"<<endl;
	strcpy (JohnAmes.LastName, "Ames");
	strcpy (JohnAmes.FirstName, "John");
	strcpy (JohnAmes.Address, "123 Maple");
	strcpy (JohnAmes.City, "Stillwater");
	strcpy (JohnAmes.State, "OK");
	strcpy (JohnAmes.ZipCode, "74075");
	JohnAmes . Print (cout);
	strcpy (AlanMason.LastName, "Mason");
	strcpy (AlanMason.FirstName, "Alan");
	strcpy (AlanMason.Address, "90 Eastgate");
	strcpy (AlanMason.City, "Ada");
	strcpy (AlanMason.State, "OK");
	strcpy (AlanMason.ZipCode, "74820");
	AlanMason . Print (cout);
	strcpy (GARiccardi.LastName, "Riccardi");
	strcpy (GARiccardi.FirstName, "Gregory");
	strcpy (GARiccardi.Address, "2006 W Randolph");
	strcpy (GARiccardi.City, "Tallahassee");
	strcpy (GARiccardi.State, "FL");
	strcpy (GARiccardi.ZipCode, "32312");
	GARiccardi . Print (cout);
	strcpy (Padded.LastName, "Riccardi  ");
	strcpy (Padded.FirstName, "Gregory   ");
	strcpy (Padded.Address, "2006 W Randolph");
	strcpy (Padded.City, "Tallahassee    ");
	strcpy (Padded.State, "FL");
	strcpy (Padded.ZipCode, "32312    ");
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
