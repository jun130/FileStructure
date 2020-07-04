// writevar.cpp
// write a stream of variable sized records
//    for person objects, using fstream.h 
#include <fstream.h>
#include <strstream.h>
#include "readper.cpp"
ostream & operator << (ostream & stream, Person & p)
{ // insert fields into file
	stream << p.LastName <<'|'<< p.FirstName <<'|'
		<< p.Address << '|' << p.City << '|'
		<< p.State <<'|' << p.ZipCode << '|';
	return stream;
}
int WriteVariablePerson (ostream & stream, Person & p)
{ // write a variable sized record from p into a stream
	ostrstream strbuff; // output string stream
	strbuff << p << ends; // use << to fill strbuff
	short length = strbuff.pcount()-1;
	stream . write ((char *)&length, sizeof(length));
	stream . write (strbuff.str(), length);
	if (stream . fail()) return 0;
	return 1;
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
		// read fields of person
		cin >> p;
		if (strlen(p.LastName)==0) break;
		// write person to file
		WriteVariablePerson(stream, p);
	}
}
