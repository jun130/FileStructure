// person.cpp
#include <iostream.h>
#include <string.h>
#include "person.h"

istream & operator >> (istream & stream, Person & p)
{ // read fields from input
	cout<<"Enter last name, or <cr> to end: "<<flush;
	stream.getline (p.LastName, 30);
	if (strlen(p.LastName)==0) return stream;
	cout<<"Enter first name: "<<flush; stream.getline(p.FirstName,30);
	cout<<"Enter address: "<<flush; stream.getline(p.Address,30);
	cout<<"Enter city: "<<flush; stream.getline(p.City, 30);
	cout<<"Enter state: "<<flush; stream.getline(p.State,15);
	cout<<"Enter zip code: "<<flush; stream.getline(p.ZipCode,10);
	return stream;
}
