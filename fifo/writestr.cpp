// writestr.cpp
// write a stream of persons, using fstream.h 
#include <fstream.h>
#include <string.h>
#include "readper.cpp"
ostream & operator << (ostream & stream, Person & p)
{ // insert fields into file
	stream << p.LastName << p.FirstName << p.Address
		<< p.City << p.State << p.ZipCode;
	return stream;
}

int main (){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ofstream stream (filename, ios::out);
	if (stream.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		cin >> p; // read fields of person
		if (strlen(p.LastName)==0) break;
		// write person to output stream
		stream << p; // write fields of person
	}
	return 1;
}

