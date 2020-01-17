all: hencode hdecode

hencode: hencode.o heap.o
	g++ -o hencode hencode.o heap.o

hencode.o: hencode.cc heap.h
	g++ -c hencode.cc

heap.o: heap.cc heap.h
	g++ -c heap.cc

hdecode: hdecode.o
	g++ -o hdecode hdecode.o

hdecode.o: hdecode.cc
	g++ -c hdecode.cc

clean:
	rm -f *.o hencode hdecode
