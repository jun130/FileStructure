// heapsort.cpp
#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif


class Heap
{public:
	Heap(int maxElements);
	int Insert (char * newKey);
	char * Remove();
	ostream & Print (ostream &);
protected:
	int MaxElements;
	char ** HeapArray; // use element 1 as first element
	int NumElements;
	void Exchange(int i, int j);
	int Compare (int i, int j);
};

Heap::Heap(int maxElements)
{
	MaxElements = maxElements;
	HeapArray = new char* [MaxElements+1];
	NumElements = 0;
}

int Heap::Insert(char * newKey)
{
	if (NumElements == MaxElements) return FALSE;
	NumElements++; // add the new key at the last position
	HeapArray[NumElements] = newKey;
	// re-order the heap
	int k = NumElements;
	int parent;
	while (k > 1) // k has a parent
	{
		parent = k / 2;
		if (Compare(k, parent) >= 0)
			// HeapArray[k] is in the right place
			break;
		// else exchange k and parent
		Exchange(k, parent);
		k = parent; 
	}
	return TRUE;
}

ostream & Heap::Print (ostream & stream)
{
	int i;
	for (i = 1; i <= MaxElements; i++)
		stream <<setw(3)<<i;
	stream<<endl;
	for (i=1; i <= NumElements; i++)
		stream <<setw(3)<<HeapArray[i];
	stream<<endl;
	return stream;
}

void Heap::Exchange(int i, int j)
{
	char * temp = HeapArray[i];
	HeapArray[i] = HeapArray[j];
	HeapArray[j] = temp;
}

char * Heap::Remove()
{
	// put the smallest value into 'val' for use in return
	char * val = HeapArray[1];

	// put largest value into root
	HeapArray[1] = HeapArray[NumElements]; 
	// decrease the number of elements
	NumElements--;

	// reorder the heap by exchanging and moving down
	int k = 1; // node of heap that contains the largest value
	int newK; // node to exchange with largest value
	while (2*k <= NumElements)// k has at least one child
	{	// set newK to the index of smallest child of k
		if (Compare(2*k, 2*k+1)<0) newK = 2*k;
		else newK = 2*k+1;
		// done if k and newK are in order
		if (Compare(k, newK) < 0) break; //in order
		Exchange(k, newK); // k and newK out of order
		k = newK; // continue down the tree
	}
	return val;
}

int Heap::Compare (int i, int j) 
{// return -1 if j is not an element of the heap
 // 		or if HeapArray[i]<HeapArray[j]
	if (j > NumElements) return -1; 
	else return strcmp(HeapArray[i],HeapArray[j]);
}

void main()
{
	int i;
	char * stuff []={"F","D","C","G","H","I","B","E","A"};
	Heap heap(9);
	for (i = 0; i<9; i++)
	{
		heap.Insert (stuff[i]);
		heap.Print(cout);
	}
	for (i = 0; i<9; i++)
	{
		cout <<heap.Remove()<<endl;
		heap.Print(cout);
	}
	cout<<endl;
}
