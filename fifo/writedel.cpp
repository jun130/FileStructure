// writedel.cpp
// write a stream of persons, using fstream.h 
#include <fstream.h>
#include <string.h>
#include "readper.cpp"

ostream & operator << (ostream & stream, Person & p)
{ // insert fields into file
	stream << p.LastName <<'|'<< p.FirstName <<'|'
		<< p.Address << '|' << p.City << '|'
		<< p.State <<'|' << p.ZipCode << '|';
	return stream;
}

int main (){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ofstream file (filename, ios::out);
	if (file.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		cin >> p;
		if (strlen(p.LastName)==0) break;
		// write person to file
		file << p;
	}
}
