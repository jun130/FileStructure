// bucket.cpp

#include "bucket.h"
#include "direct.h"
#include "hash.h"

Bucket::Bucket (Directory & dir, int maxKeys) // constructor
:TextIndex (maxKeys), Dir (dir)
{
	BucketAddr = 0;
	Depth = 0;
}

int Bucket::Insert (char * key, int recAddr)
{
	if (NumKeys < MaxKeys)
	{
		int result = TextIndex::Insert (key, recAddr);
		Dir.StoreBucket (this);
		return result;
	}
	else
	{
		Split ();
		return Dir.Insert (key, recAddr);
	}
}

int Bucket::Remove (char * key)
{// remove the key, return its RecAddr
	int result = TextIndex::Remove (key);
	if (!result) return 0; // key not in bucket
	TryCombine (); // attempt to combine with buddy
	// make the changes permanent
	Dir.StoreBucket(this);
	return 1;
}

Bucket * Bucket::Split ()
{
	int newStart, newEnd;
	if (Depth == Dir.Depth)// no room to split this bucket
		Dir.DoubleSize();
	Bucket * newBucket = new Bucket (Dir, MaxKeys);
	Dir.StoreBucket (newBucket);
	NewRange (newStart, newEnd);
	Dir.InsertBucket(newBucket->BucketAddr, newStart, newEnd);
	Depth ++;
	newBucket->Depth = Depth;
	Redistribute (*newBucket);
	Dir.StoreBucket (this);
	Dir.StoreBucket (newBucket);
	return newBucket;
}

int Bucket::FindBuddy ()
{// find the directory address of the bucket that is paired with this
	if (Dir.Depth == 0) return -1; // no buddy, empty directory
	// unless bucket depth == directory depth, there is no single
	// bucket to pair with
	if (Depth < Dir.Depth) return -1; 
	int sharedAddress = MakeAddress(Keys[0], Depth); // address of any key
	return sharedAddress ^ 1; // exclusive or with low bit 
}

int Bucket::TryCombine ()
{// called after insert to combine buddies, if possible
	int result;
	int buddyIndex = FindBuddy ();
	if (buddyIndex == -1) return 0;// no combination possible
	// load buddy bucket into memory
	int buddyAddr = Dir.BucketAddr[buddyIndex];
	Bucket * buddyBucket = new Bucket (Dir, MaxKeys);
	Dir . LoadBucket (buddyBucket, buddyAddr);
	// if the sum of the sizes of the buckets is too big, return
	if (NumKeys + buddyBucket->NumKeys > MaxKeys) return 0;
	Combine (buddyBucket, buddyIndex);// collapse the 2 buckets
	result = Dir.Collapse ();
	if (result) TryCombine(); //if collapse, may be able to combine
	return 1;
}

int Bucket::Combine (Bucket * buddy, int buddyIndex)
{// collapse this and buddy into a single bucket
	int result;
	// move keys from buddy to this
	for (int i = 0; i < buddy->NumKeys; i++)
	{// insert the key of the buddy into this
		result = Insert (buddy->Keys[i],buddy->RecAddrs[i]);
		if (!result) return 0;
	}
	Depth --;// reduce the depth of the bucket 
	Dir . RemoveBucket (buddyIndex, Depth);
	return 1;
}

int Bucket::NewRange (int & newStart, int & newEnd)
{// make a range for the new split bucket
	int sharedAddr = MakeAddress(Keys[0], Depth);
	int bitsToFill = Dir.Depth - (Depth + 1);
	newStart = (sharedAddr << 1) | 1;
	newEnd = newStart;
	for (int j = 0; j < bitsToFill; j++)
	{
		newStart = newStart << 1;
		newEnd = (newEnd << 1) | 1;
	}
	return 1;
}

int Bucket::Redistribute (Bucket & newBucket)
{
	// check each key in this bucket
	for (int i = NumKeys - 1; i >= 0; i--)
	{
		int bucketAddr = Dir.Find (Keys[i]); // look up the bucket
		if (bucketAddr != BucketAddr)// key belongs in the new bucket
		{
			newBucket.TextIndex::Insert (Keys[i], RecAddrs[i]);
			TextIndex::Remove (Keys[i]); // delete key from this bucket
		}
	}
	return 1;
}

ostream & Bucket::Print(ostream & stream)
{
	stream <<"Bucket depth: "<<Depth<<endl;
	TextIndex::Print (stream);
	return stream;
}

BucketBuffer::BucketBuffer (int keySize, int maxKeys)
: TextIndexBuffer(keySize,maxKeys,1,sizeof(int))
{
	AddField (sizeof(int));
}

int BucketBuffer::Pack (const Bucket & bucket) 
{
	int result;
	TextIndexBuffer::Pack(bucket);
	if (result == -1) return -1;
	return FixedFieldBuffer::Pack (&bucket.Depth);
}

int BucketBuffer::Unpack (Bucket & bucket)
{
	int result;
	result = TextIndexBuffer::Unpack(bucket);
	if (result == -1) return -1;
	return FixedFieldBuffer::Unpack (&bucket.Depth);
}
