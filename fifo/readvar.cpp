// readvar.cpp
// write a stream of persons, using fstream.h 
#include <fstream.h>
#include <strstream.h>
#include <string.h>
#include "writeper.cpp"

istream & operator >> (istream & stream, Person & p)
{ // read fields from stream
	char delim;
	stream.getline(p.LastName, 30,'|');
	if (strlen(p.LastName)==0) return stream; 
	stream.getline(p.FirstName,30,'|');
	stream.getline(p.Address,30,'|');
	stream.getline(p.City, 30,'|');
	stream.getline(p.State,15,'|');
	stream.getline(p.ZipCode,10,'|');
	return stream;
}

int ReadVariablePerson (istream & stream, Person & p)
{ // read a variable sized record from stream and store it in p
  // if read fails, set p.LastName to empty string and return 0
	short length;
	stream . read ((char *)&length, sizeof(length));
	if (stream . fail()){p.LastName[0]=0; return 0;}
	char * buffer = new char[length+1];
	stream . read (buffer, length);
	buffer [length] = 0; // terminate buffer with null
	istrstream strbuff (buffer);
	strbuff >> p;
	return 1;
}
int main (){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ifstream stream (filename, ios::in);
	if (stream.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		ReadVariablePerson (stream, p);
		if (strlen(p.LastName)==0) break;
		// write person to file
		cout << p;
	}
}
