// direct.h

#ifndef DIRECT_H
#define DIRECT_H

#include "bucket.h"
#include "recfile.h"
#include "buffile.h"
#include "length.h"
#include "tindbuff.h"

class Directory 
{public:
	Directory (int maxBucketKeys = -1);
	~Directory ();
	int Open (char * name);
	int Create (char * name);
	int Close ();
	int Insert (char * key, int recAddr);
	int Remove (char * key);
	int Search (char * key); // return RecAddr for key
	ostream & Print (ostream & stream);
protected:
	int Depth; // depth of directory
	int NumCells; // number of entries, = 2**Depth
	int * BucketAddr; // array of bucket addresses
	
	// protected methods
	int DoubleSize (); // double the size of the directory
	int Collapse (); // collapse, halve the size
	int InsertBucket (int bucketAddr, int first, int last);
	int RemoveBucket (int bucketIndex, int depth);// remove bucket from directory
	int Find (char * key); // return BucketAddr for key
	int StoreBucket (Bucket * bucket);// update or append bucket in file
	int LoadBucket (Bucket * bucket, int bucketAddr);// load bucket from file

	// methods to support Remove

	// members to support directory and bucket files
	int MaxBucketKeys;
	BufferFile * DirectoryFile;
	LengthFieldBuffer * DirectoryBuffer;
	Bucket * CurrentBucket;// object to hold one bucket
	BucketBuffer * theBucketBuffer;// buffer for buckets
	BufferFile * BucketFile;
	int Pack () const;
	int Unpack ();
	Bucket * PrintBucket;// object to hold one bucket


	friend class Bucket;
};

#endif
