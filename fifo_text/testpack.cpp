// test.cc
// Copyright 1997, Gregory A. Riccardi

#include <fstream.h>
#include <iomanip.h>
#include "fixtext.h"
#include "lentext.h"
#include "deltext.h"
#include "person.h"

void testFixText ()
{
	int result;
	Person person;
	
	FixedTextBuffer Buff (6);
	Person :: InitBuffer (Buff);
	strcpy (person.LastName, "Darling");
	strcpy (person.FirstName, "Pandora");
	strcpy (person.Address, "4112 Center St.");
	strcpy (person.City, "Tallahassee");
	strcpy (person.State, "FL");
	strcpy (person.ZipCode, "32306");
	person . Print (cout);
	person . Pack (Buff);
	Buff . Print (cout);
	ofstream TestOut ("fixtext.dat",ios::out);
	Buff . Write (TestOut);
	strcpy (person.FirstName, "Dave");
	person.Print (cout);
	person.Pack (Buff);
	Buff . Write (TestOut);
	TestOut . close ();
	ifstream TestIn ("fixtext.dat");
	FixedTextBuffer InBuff (6);
	Person :: InitBuffer (InBuff);
	Buff . Read (TestIn);
	person . Unpack (Buff);
	person . Print (cout);
}

void testLenText ()
{
	cout << "\nTesting LengthTextBuffer"<<endl;
	Person person;
	LengthTextBuffer Buff;
	Person :: InitBuffer (Buff);
	strcpy (person.LastName, "Darling");
	strcpy (person.FirstName, "Pandora");
	strcpy (person.Address, "4112 Center St.");
	strcpy (person.City, "Tallahassee");
	strcpy (person.State, "FL");
	strcpy (person.ZipCode, "32306");
	person . Print (cout);
	Buff . Print (cout);
	cout <<"pack person "<<person . Pack (Buff)<<endl;
	Buff . Print (cout);
	ofstream TestOut ("lentext.dat",ios::out);
	Buff . Write (TestOut);
	strcpy (person.FirstName, "Dave");
	person.Print (cout);
	person.Pack (Buff);
	Buff . Write (TestOut);
	TestOut . close ();
	ifstream TestIn ("lentext.dat");
	LengthTextBuffer InBuff;
	Person :: InitBuffer (InBuff);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
}

void testDelText ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	Person person;
	DelimTextBuffer Buff;
	Person :: InitBuffer (Buff);
	strcpy (person.LastName, "Darling");
	strcpy (person.FirstName, "Pandora");
	strcpy (person.Address, "4112 Center St.");
	strcpy (person.City, "Tallahassee");
	strcpy (person.State, "FL");
	strcpy (person.ZipCode, "32306");
	person . Print (cout);
	Buff . Print (cout);
	cout <<"pack person "<<person . Pack (Buff)<<endl;
	Buff . Print (cout);
	ofstream TestOut ("deltext.dat",ios::out);
	Buff . Write (TestOut);
	strcpy (person.FirstName, "Dave");
	person.Print (cout);
	person.Pack (Buff);
	Buff . Write (TestOut);
	TestOut . close ();
	ifstream TestIn ("deltext.dat");
	DelimTextBuffer InBuff;
	Person :: InitBuffer (InBuff);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
	cout <<"read "<<Buff . Read (TestIn)<<endl;
	cout <<"unpack "<<person . Unpack (Buff)<<endl;
	person . Print (cout);
}

int main(int argc, char ** argv)
{
	testFixText ();
	testLenText ();
	testDelText ();
}
