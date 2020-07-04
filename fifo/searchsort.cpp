class KeyType
{public:
	int operator == (KeyType &); // equality operator
	int operator < (KeyType &); // less than operator
};

class RecType {public: KeyType Key();};

class FixedRecordFile
{public:
	int NumRecs();
	int Create (char * fileName);
	int ReadByRRN (RecType & record, int RRN);
	int Append (RecType & record);
};

int BinarySearch 
	(FixedRecordFile & file, RecType & obj, KeyType & key)
// binary search for key
// if key found, obj contains corresponding record, 1 returned
// if key not found, 0 returned
{
	int low = 0; int high = file.NumRecs()-1;
	while (low <= high)
	{
		int guess = (high - low) / 2;
		file.ReadByRRN (obj, guess);
		if (obj.Key() == key) return 1; // record found
		if (obj.Key() < key) high = guess - 1;// search before guess
		else low = guess + 1;// search after guess
	}
	return 0; // loop ended without finding key
}

class KeyRRN 
// contains a pair (key, RRN)
{public:
	KeyType key; int RRN; 
	KeyRRN();
	KeyRRN (KeyType key, int RRN);
};

int Sort (KeyRRN [], int numKeys); // sort array by key

int KeySort (FixedRecordFile& inFile, char * outFileName)
{
	RecType obj;
	KeyRRN * Keys = new KeyRRN [inFile.NumRecs()];
	// read file and load Keys
	for (int i = 0; i < inFile.NumRecs(); i++)
	{
		inFile.ReadByRRN (obj, i);
		Keys [i] = KeyRRN(obj.Key(),i);
	}
	Sort (Keys, inFile.NumRecs());// sort Keys 
	FixedRecordFile outFile;// file to hold records in key order
	outFile . Create (outFileName);// create a new file
	// write new file in order
	for (int j = 0; j < inFile.NumRecs(); j++)
	{
		inFile.ReadByRRN (obj, Keys[j].RRN);
		outFile . Append (obj);
	}
	return 1;
}
	