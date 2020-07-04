//makerec.cc
#include "buffile.h"
#include "recordng.h"
#include "delim.h"
#include <iostream.h>
#include "recfile.h"

// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class RecordingFile
//    the file "record2.dat" is created using class RecordFile<Recording>

void main()
{
	int recaddr;
	DelimFieldBuffer Buffer;
	BufferFile RecordingFile (Buffer);
	RecordingFile . Create ("record.dat", ios::out);
	RecordFile<Recording> Rec2file (Buffer);
	Rec2file . Create ("record2.dat", ios::out);
	Recording * R[10];
	R[0] = new Recording ("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording ("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");	
	R[2] = new Recording ("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording ("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording ("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording ("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording ("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording ("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording ("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording ("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	for (int i= 0; i<10; i++)
	{
		R[i] -> Pack (Buffer);
		recaddr = RecordingFile . Write ();
		cout <<"Recording R["<<i<<"] at recaddr "<<recaddr<<endl;
		recaddr = Rec2file . Write (*R[i]);
		cout <<"Recordin2 R["<<i<<"] at recaddr "<<recaddr<<endl;
		delete R[i];
	} 
}


