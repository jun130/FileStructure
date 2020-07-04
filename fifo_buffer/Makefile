#name of the directory
DIR = app_f
ROOTDIR = ../..
LIB = libiobuf.a
OBJECTS = iobuffer.o fixlen.o fixfld.o person.o varlen.o \
		delim.o length.o buffile.o
EXECS = test testfile

include $(ROOTDIR)/default.mk

test.o: iobuffer.h fixlen.h fixfld.h person.h varlen.h

testfile.o: iobuffer.h fixlen.h fixfld.h person.h \
	varlen.h buffile.h

fixlen.o: fixlen.h iobuffer.h

fixfld.o: fixlen.h fixfld.h iobuffer.h

varlen.o: varlen.h iobuffer.h

iobuffer.o: iobuffer.h

person.o: person.h iobuffer.h varlen.h fixlen.h fixfld.h \
	delim.h length.h

delim.o: delim.h iobuffer.h varlen.h

length.o: length.h iobuffer.h varlen.h

buffile.o: buffile.h iobuffer.h 

