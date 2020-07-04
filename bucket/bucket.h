// bucket.h

#ifndef BUCKET_H
#define BUCKET_H

#include "bucket.h"
#include "iobuffer.h"
#include "textind.h"
#include "tindbuff.h"
#include <iostream.h>

class Directory; // forward reference
class BucketBuffer; // forward reference

const int defaultMaxKeys = 100;

class Bucket: public TextIndex
{protected:
	// there are no public members, 
	// access to Bucket members is only through class Directory
	Bucket (Directory & dir, int maxKeys = defaultMaxKeys); // constructor
	int Insert (char * key, int recAddr);
	int Remove (char * key);
	Bucket * Split ();// split the bucket and redistribute the keys
	int NewRange (int & newStart, int & newEnd);
		// calculate the range of a new (split) bucket
	int Redistribute (Bucket & newBucket); // redistribute keys
	int FindBuddy ();// find the bucket that is the buddy of this 
	int TryCombine (); // attempt to combine buckets
	int Combine (Bucket * buddy, int buddyIndex); // combine two buckets
	int Depth; 
		// number of bits used 'in common' 
		// by the keys in this bucket
	Directory & Dir; // directory that contains the bucket
	int BucketAddr; // address of file
	ostream & Print (ostream &);
	friend class Directory;
	friend class BucketBuffer;
};

class BucketBuffer: public TextIndexBuffer
{public:
	BucketBuffer (int keySize, int maxKeys);
	int Pack (const Bucket & bucket);
	int Unpack (Bucket & bucket);
};

#endif
