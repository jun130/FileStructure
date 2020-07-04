// direct.cpp

#include "direct.h"
#include "hash.h"
#include "tindbuff.h"
#include <strstream.h>
#include <string.h>

const int MaxKeySize = 12;

Directory::Directory (int maxBucketKeys)
{
	Depth = 0; // depth of directory
	NumCells = 1; // number of entries, = 2**Depth
	BucketAddr = new int [NumCells]; // array of bucket addresses

	MaxBucketKeys = maxBucketKeys;
	DirectoryBuffer = new LengthFieldBuffer; // default size
	DirectoryFile = new BufferFile(*DirectoryBuffer);
	CurrentBucket = new Bucket (*this, MaxBucketKeys);
	theBucketBuffer = new BucketBuffer (MaxKeySize, MaxBucketKeys);
	BucketFile = new BufferFile (*theBucketBuffer);
	PrintBucket = new Bucket (*this, MaxBucketKeys);
}

Directory::~Directory ()
{
	Close();
}

void makeNames(char * name, char *& dirName, char *& bktName)
{
	ostrstream directoryName;
	directoryName<<name<<".dir"<<ends;
	dirName = strdup(directoryName.str());
	ostrstream bucketName;
	bucketName <<name<<".bkt"<<ends;
	bktName = strdup(bucketName.str());
}

int Directory::Open (char * name)
{
	int result;
	char * directoryName, * bucketName;
	makeNames(name, directoryName, bucketName);
	result = DirectoryFile->Open(directoryName, ios::in|ios::out);
	if (!result) return 0;
	result = DirectoryFile->Read();
	if (result==-1) return 0;
	result = Unpack();
	if (!result==-1) return 0;
	result = BucketFile->Open(bucketName,ios::in|ios::out);
	return result;
}

int Directory::Create (char * name)
{
	// create the two files, clear the directory, create a single bucket
	// and add it to the directory and the bucket file
	int result;
	char * directoryName, * bucketName;
	makeNames(name, directoryName, bucketName);
	result = DirectoryFile->Create(directoryName, ios::in|ios::out);
	if (!result) return 0;
	result = BucketFile->Create(bucketName,ios::in|ios::out);
	if (!result) return 0;
	// store the empty CurrentBucket in the BucketFile and add to Directory
	BucketAddr[0] = StoreBucket (CurrentBucket);
	return result;
}

int Directory::Close ()
{// write the directory and close. error occurs on buffer overflow
	int result;
	result = Pack();
	if (result==-1) return 0;
	DirectoryFile -> Rewind();
	result = DirectoryFile->Write();
	if (result==-1) return 0;
	return DirectoryFile->Close() && BucketFile->Close();
}

int Directory::Insert (char * key, int recAddr)
{
	int found = Search (key);
	if (found == -1) return CurrentBucket->Insert(key, recAddr);
	return 0;// key already in directory
}

int Directory::Remove (char * key)
{// remove the key and return its RecAddr
	int bucketAddr = Find(key);
	LoadBucket (CurrentBucket, bucketAddr);
	return CurrentBucket -> Remove (key);
}

int Directory::Search (char * key) 
{// return RecAddr for key, also put current bucket into variable
	int bucketAddr = Find(key);
	LoadBucket (CurrentBucket, bucketAddr);
	return CurrentBucket->Search(key);
}

int Directory::DoubleSize () 
// double the size of the directory
{
	int newSize = 2 * NumCells;
	int * newBucketAddr = new int[newSize];
	for (int i = 0; i < NumCells; i++)
	{
		newBucketAddr[2*i] = BucketAddr[i];
		newBucketAddr[2*i+1] = BucketAddr[i];
	}
	delete BucketAddr;
	BucketAddr = newBucketAddr;
	Depth ++;
	NumCells = newSize;
	return 1;
}

int Directory::Collapse ()
{// if collapse is possible, reduce size by half
	if (Depth == 0) return 0; // only 1 bucket
	// look for buddies that are different, if found return 
	for (int i = 0; i < NumCells; i += 2)
		if (BucketAddr[i] != BucketAddr[i+1]) return 0;
	int newSize = NumCells / 2;
	int * newAddrs = new int [newSize];
	for (int j = 0; j < newSize; j++)
		newAddrs[j] = BucketAddr[j*2];
	delete BucketAddr;
	BucketAddr = newAddrs;
	Depth --;
	NumCells = newSize;
	return 1;
}

int Directory::InsertBucket (int bucketAddr, int first, int last)
{// change cells to refer to this bucket
	for (int i = first; i <= last; i++)
		BucketAddr[i] = bucketAddr;
	return 1;
}

int Directory::RemoveBucket (int bucketIndex, int bucketDepth)
{// implementation left as exercise
	// set all cells for this bucket to its buddy bucket
	int fillBits = Depth-bucketDepth; // number of bits to fill
	int buddyIndex = bucketIndex ^ (1<<(fillBits-1)); // flip low bit
	int newBucketAddr = BucketAddr[buddyIndex];
	int lowIndex = bucketIndex >> fillBits << fillBits; // zero low bits
	int highIndex = lowIndex + (1<<fillBits) - 1; // set low bits to 1
	for (int i = lowIndex; i <= highIndex; i++)
		BucketAddr[i] = newBucketAddr;
	return 0;
}

int Directory::Find (char * key) 
// return BucketAddr for key
{
	return BucketAddr[MakeAddress (key, Depth)];
}

int Directory::Pack ()  const
{// pack the buffer and return the number of bytes packed
	int result, packsize;
	DirectoryBuffer -> Clear();
	packsize = DirectoryBuffer -> Pack (&Depth, sizeof(int));
	if (packsize == -1) return -1;
	for (int i = 0; i<NumCells; i++)
	{
		result = DirectoryBuffer -> Pack (&BucketAddr[i], sizeof(int));
		if (result == -1) return -1;
		packsize += result;
	}
	return packsize;
}

int Directory::Unpack ()
{
	int result;
	result = DirectoryBuffer -> Unpack (&Depth, sizeof(int));
	if (result == -1) return -1;
	NumCells = 1 << Depth;
	if (BucketAddr != 0) delete BucketAddr;
	BucketAddr = new int[NumCells];
	for (int i = 0; i<NumCells; i++)
	{
		result = DirectoryBuffer -> Unpack (&BucketAddr[i], sizeof(int));
		if (result == -1) return -1;
	}
	return 0;
}

int Directory::StoreBucket (Bucket * bucket)
{// update or append the bucket to the bucket file
	int result;
	result = theBucketBuffer -> Pack (* bucket);
	if (result == -1) return -1;
	int addr = bucket->BucketAddr;
	if (addr != 0) return BucketFile->Write (addr);
	addr = BucketFile -> Append ();
	bucket -> BucketAddr = addr;
	return addr;
}

int Directory::LoadBucket(Bucket * bucket, int bucketAddr)
{// read bucket from file, and set BucketAddr field
	int result;
	result = BucketFile -> Read (bucketAddr);
	if (result == -1) return 0;
	result = theBucketBuffer -> Unpack (*bucket);
	if (result == -1) return 0;
	bucket->BucketAddr = bucketAddr;
	return 1;
}

ostream & Directory::Print (ostream & stream)
{
	stream <<"Directory Depth "<<Depth<<" size "<<NumCells<<endl;
	for (int i = 0; i<NumCells; i++)
	{
		stream <<"bucket "<<BucketAddr[i]<<" addr "<<(void *) i<<endl;
		LoadBucket (PrintBucket, BucketAddr[i]);
		PrintBucket->Print(stream);
	}
	stream <<"end directory"<<endl;
	return stream;
}
