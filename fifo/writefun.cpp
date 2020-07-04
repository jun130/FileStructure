// writestr.cpp
// write a stream of persons, using fstream.h 
#include <fstream.h>
#include <string.h>
#include "readper.cpp"
const int MaxBufferSize = 200;
int WritePerson (ostream & stream, Person & p)
{	char buffer [MaxBufferSize];
	strcpy(buffer, p.LastName); strcat(buffer,"|");
	strcat(buffer, p.FirstName); strcat(buffer,"|");
	strcat(buffer, p.Address);  strcat(buffer,"|");
	strcat(buffer, p.City);  strcat(buffer,"|");
	strcat(buffer, p.State);  strcat(buffer,"|");
	strcat(buffer, p.ZipCode);  strcat(buffer,"|");
	short length=strlen(buffer); 
	stream.write ((char *)&length, sizeof(length)); // write length
	stream.write (&buffer, length);
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
		// write person to output stream
		WritePerson(stream,p);
	}
}

