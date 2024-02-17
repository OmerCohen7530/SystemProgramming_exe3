CC = gcc
AR = ar
CFLAGS =-Wall -g
AFLAGS =-rcs

.PHONY: all clean

all: StrList

StrList: Main.o libStrList.a
	$(CC) $(CFLAGS) -o StrList Main.o libStrList.a

libStrList.a: StrList.o
	$(AR) $(AFLAGS) libStrList.a StrList.o

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c StrList.c

Main.o: Main.c StrList.h
	$(CC) $(CFLAGS) -c Main.c


clean:
	rm -f *.o *.a StrList