// coseq.h
#ifndef COSEQ_H
#define COSEQ_H

template <class ItemType>
class CosequentialProcess
// base class for cosequential processing
{public:
	CosequentialProcess(int numberOfLists);

	// The following methods provide basic list processing
	// These must be defined in subclasses
	virtual int InitializeList (int ListNumber, char * ListName)=0;
	virtual int InitializeOutput (char * OutputListName)=0;
	virtual int NextItemInList (int ListNumber)=0; 
		//advance to next item in this list
	virtual ItemType Item (int ListNumber) = 0; 
		// return current item from this list
	virtual int ProcessItem (int ListNumber)=0; // process the item in this list
	virtual int FinishUp()=0; // complete the processing

	// General list processing methods
	virtual int Match2Lists (char * List1Name, char * List2Name, char * OutputListName);
		// 2-way sequential matching algorithm
	virtual int Merge2Lists (char * List1Name, char * List2Name, char * OutputListName);
		// 2-way sequential merging algorithm
protected:
	int NumberOfLists; // number of lists to be processed
};

template <class ItemType>
CosequentialProcess<ItemType>::CosequentialProcess(int numberOfLists)
{	NumberOfLists = numberOfLists;}

template <class ItemType>
int CosequentialProcess<ItemType>::Match2Lists
	(char * List1Name, char * List2Name, char * OutputListName)
{
	int MoreItems;// true if items remain in lists
	InitializeList (1, List1Name);
	InitializeList (2, List2Name);
	InitializeOutput(OutputListName);
	MoreItems = NextItemInList(1) && NextItemInList(2);
	while (MoreItems){
		if (Item(1) < Item(2))
			MoreItems = NextItemInList(1);
		else if (Item(1) == Item(2)) // Item1 == Item2
		{
			ProcessItem (1); // match found
			MoreItems = NextItemInList(1) && NextItemInList(2);
		}
		else // Item(1) > Item(2)
			MoreItems = NextItemInList(2);
	}
	FinishUp();
	return 1;
}

template <class ItemType>
int CosequentialProcess<ItemType>::Merge2Lists
	(char * List1Name, char * List2Name, char * OutputListName)
{
	int MoreItems1, MoreItems2; // true if more items in list
	InitializeList (1, List1Name);
	InitializeList (2, List2Name);
	InitializeOutput (OutputListName);
	MoreItems1 = NextItemInList(1);
	MoreItems2 = NextItemInList(2);

	while (MoreItems1 || MoreItems2){// if either file has more
		if (Item(1) < Item(2))
		{// list 1 has next item to be processed
			ProcessItem (1); 
			MoreItems1 = NextItemInList(1);
		}
		else if (Item(1) == Item(2))
		{// lists have the same item, process from list 1
			ProcessItem (1);
			MoreItems1 = NextItemInList(1);
			MoreItems2 = NextItemInList(2);
		}
		else // Item(1) > Item(2)
		{// list 2 has next item to be processed
			ProcessItem (2);
			MoreItems2 = NextItemInList(2);
		}
	}
	FinishUp();
	return 1;
}

#endif


