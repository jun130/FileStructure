// deltext.cpp
// Copyright 1997, Gregory A. Riccardi

#include "deltext.h"
#include <string.h>

DelimTextBuffer :: DelimTextBuffer (char delim, int maxBytes)
 // construct with a maximum of maxFields
{	Init (delim, maxBytes);}

void DelimTextBuffer :: Clear ()
// clear fields from buffer
{	NextByte = 0; BufferSize = 0;}

int DelimTextBuffer :: Read (istream & stream)
{
	Clear ();
	stream . read ((char*)&BufferSize, sizeof(BufferSize));
	if (stream.fail()) return FALSE;
	if (BufferSize > MaxBytes) return FALSE; // buffer overflow
	stream . read (Buffer, BufferSize);
	return stream . good ();
}


int DelimTextBuffer :: Write (ostream & stream) const
{
	stream . write ((char*)&BufferSize, sizeof(BufferSize));
	stream . write (Buffer, BufferSize);
	return stream . good ();
}

int DelimTextBuffer :: Pack (const char * str, int size)
// set the value of the next field of the buffer;
// if size = -1 (default) use strlen(str) as Delim of field
{
	short len; // length of string to be packed
	if (size >= 0) len = size;
	else len = strlen (str);
	if (len > strlen(str)) // str is too short!
		return FALSE;
	int start = NextByte; // first character to be packed
	NextByte += len + 1;
	if (NextByte > MaxBytes) return FALSE;
	memcpy (&Buffer[start], str, len);
	Buffer [start+len] = Delim; // add delimeter
	BufferSize = NextByte;
	return TRUE;
}

int DelimTextBuffer :: Unpack (char * str)
// extract the value of the next field of the buffer
{
	int len = -1; // length of packed string
	int start = NextByte; // first character to be unpacked
	for (int i = start; i < BufferSize; i++)
		if (Buffer[i] == Delim) 
			{len = i - start; break;}
	if (len == -1) return FALSE; // delimeter not found
	NextByte += len + 1;
	if (NextByte > BufferSize) return FALSE;
	strncpy (str, &Buffer[start], len);
	str [len] = 0; // zero termination for string 
	return TRUE;
}

void DelimTextBuffer :: Print (ostream & stream) const
{
	stream << "Buffer has max characters "<<MaxBytes<<" and Buffer Size "<<BufferSize<<endl;
}

// Protected members

int DelimTextBuffer :: Init (char delim, int maxBytes)
 // construct with a maximum of maxFields
{
	Delim = delim;
	DelimStr[0] = Delim;
	DelimStr[1] = 0;
	if (maxBytes < 0) maxBytes = 0;
	MaxBytes = maxBytes;
	Buffer = new char[MaxBytes];
	BufferSize = 0;
	return 1;
}


