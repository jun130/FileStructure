#include <fstream.h>
#include <string.h>
#include "coseq.h"

// strlist.cpp
#include "strlist.h"

const char * StringListProcess::LowValue = "";
const char * StringListProcess::HighValue = "\xff";

StringListProcess::StringListProcess (int numberOfLists)
: CosequentialProcess<String&>(numberOfLists), OutputList()
{
	Lists = new ifstream[NumberOfLists+1];
	Items = new String[NumberOfLists+1];
}

int StringListProcess::InitializeList (int ListNumber, char * ListName)
{
	Lists[ListNumber] . open(ListName);
	Items[ListNumber] = LowValue;
	return 1;
}

int StringListProcess::InitializeOutput (char * OutputListName)
{	
	OutputList.open(OutputListName);
	return 1;
}

int StringListProcess::NextItemInList (int ListNumber)
//get next item from this list
{
	char ThisItem[MaxItemLength];
	String PreviousItem = Items[ListNumber];
	Lists[ListNumber].getline(ThisItem, MaxItemLength+1); // get line from file
	// test for errors and termination
	if (!Lists[ListNumber].good()) // end of file
	{	Items[ListNumber]=HighValue; return 0;}
	if (strlen(ThisItem)==0) // no string
	{	Items[ListNumber]=LowValue; return 0;}
	if (strcmp(ThisItem, (char*)PreviousItem) < 0)
	{
		cerr << "Items out of order: current "<<ThisItem
			<< " previous "<<(char*)PreviousItem<<endl;
		Items[ListNumber]=HighValue; return 0;
	}
	// this is a new item, store it
	Items[ListNumber]=ThisItem;//store this Item as current item
	return 1;
}

String& StringListProcess::Item (int ListNumber)
// return current item from this list
{	return Items[ListNumber];}

int StringListProcess::ProcessItem (int ListNumber)
// process the item in this list
// output a line containing the item
{	
	OutputList << Items[ListNumber] <<endl;
	return 1;
}

int StringListProcess::FinishUp()
{
	for (int i = 1; i <= NumberOfLists; i++)
		Lists[i].close();
	OutputList.close();
	return 1;
}
