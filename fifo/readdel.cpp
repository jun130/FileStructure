// readdel.cpp
// read a stream of persons with delimited fields
#include <fstream.h>
#include <string.h>
#include "writeper.cpp"
istream & operator >> (istream & stream, Person & p)
{ // read fields from file
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
void main (){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ifstream file (filename, ios::in);
	if (file.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		file >> p;
		if (strlen(p.LastName)==0) break;
		// write person to file
		cout << p;
	}
}
