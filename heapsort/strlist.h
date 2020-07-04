// strlist.h
#ifndef STRLIST_H
#define STRLIST_H

#include "coseq.h"
#include "strclass.h"
#include <fstream.h>

class StringListProcess: public CosequentialProcess<String&>
// Class to process lists that are files of strings, one per line
{public:
	StringListProcess (int NumberOfLists); // constructor

	// Basic list processing methods
	int InitializeList (int ListNumber, char * ListName);
	int InitializeOutput (char * OutputListName);
	int NextItemInList (int ListNumber); //get next item from this list
	String& Item (int ListNumber); // return current item from this list
	int ProcessItem (int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing
protected:
	ifstream * Lists; // array of list files
	String * Items; // array of current Item from each list
	ofstream OutputList;
	static const char * LowValue;
	static const char * HighValue;
};

const int MaxItemLength = 100; // maximum length of an item

#endif
