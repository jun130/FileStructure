// strclass.h
#ifndef STRCLASS_H
#define STRCLASS_H

// class string makes a C (null terminated) character array
//   into a regular object, with 

#include <iostream.h>

class String
{
   public:
	String ();
	String (const String&); //copy constructor
	String (const char *); // create from C string
	~String ();
	String & operator = (const String &);
	operator char * ();
	int operator < (const String &) const;
	int operator > (const String &) const;
	int operator <= (const String &) const;
	int operator >= (const String &) const;
	int operator != (const String &) const;
	int operator == (const String &) const;
	char * str () const; // return a copy of the string
   protected:
	char * string;
	unsigned int MaxLength;
   friend ostream & operator << (ostream & stream, String & str);
};

ostream & operator << (ostream & stream, String & str);

inline ostream & operator << (ostream & stream, String & str)
{ stream << str.string; return stream;}

inline int String::operator > (const String& str) const
{ return !(*this <= str);}

inline int String::operator >= (const String& str) const
{ return !(*this < str);}

inline int String::operator != (const String& str) const
{ return !(*this == str);}

#endif