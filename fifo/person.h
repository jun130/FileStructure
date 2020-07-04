// person.h
#ifndef PERSON
#define PERSON

class Person 
{ public:
	// data members
	char LastName [11]; char FirstName [11]; char Address [16];
	char City [16]; char State [3]; char ZipCode [10];
	// method
	Person (); // default constructor
};

Person::Person ()
{//constructor
	LastName[0]=0; FirstName[0]=0; Address[0]=0;
	City[0]=0; State[0]=0; ZipCode[0]=0;
}

#endif