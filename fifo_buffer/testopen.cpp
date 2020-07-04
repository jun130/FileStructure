#include <fstream.h>
#include <iomanip.h>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "person.h"
#include "buffile.h"

Person JohnAmes;
Person AlanMason;
Person GARiccardi;
Person Padded;

void testFixedField ()
{
	cout <<"Testing Fixed Field Buffer"<<endl;
	FixedFieldBuffer Buff (6);
	Person :: InitBuffer (Buff);
	BufferFile Buffile (Buff);
	int result = Buffile . Open ("fixfile.dat", ios::out|ios::in);
	cout <<"test open result "<<result<<endl;
}

int main(int argc, char ** argv)
{
	testFixedField ();
}
