//testind.cc
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recordng.h"
#include "indfile.h"
#include <iostream.h>

// make an indexed file from a recording file
int IndexRecordingFile (char * myfile, 
	TextIndexedFile<Recording> & indexFile)
{
	Recording rec; int recaddr, result;
	DelimFieldBuffer Buffer; // create a buffer
	BufferFile RecFile(Buffer); 
	result = RecFile . Open (myfile,ios::in);
	if (!result)
	{
		cout << "Unable to open file "<<myfile<<endl;
		return 0;
	}
	while (1) // loop until the read fails
	{
		recaddr = RecFile . Read (); // read next record
		if (recaddr < 0) break;
		rec. Unpack (Buffer);
		indexFile . Append(rec);
	}
	Recording rec1;
	result = indexFile.Read ("LON2312", rec1);
	cout <<"Found record: "<<rec;
}


int main (int argv, char ** argc)
{// first argument is the file name for the data file
	int result;
	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Recording> IndFile (Buffer, 12, 10);
	result = IndFile . Create ("indfile");
	if (!result) 
	{
		cout<<"Unable to create indfile "<<result<<endl;
		return 0;
	}	
	IndexRecordingFile (argc[1], IndFile);
	IndFile.Close();
}

