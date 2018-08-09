CC=g++
LIBS=
CFLAGS=$(LIBS) -std=c++11 -I"include/"
SRCDIR=ComMake/

output:
	$(CC) $(SRCDIR)LinkedList.cpp $(SRCDIR)LinkedLista.cpp $(SRCDIR)HashTable.cpp $(SRCDIR)bd.cpp -o $@ $(CFLAGS)
			
.PHONY: all output


all: output	

.DEFAULT_GOAL:=all


