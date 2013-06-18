all:
	cc -g -o fun fun-test.c fun.c
	cc -o sorttest sorttest.c mergesort.o quicksort.o heapsort.o arraycheck.c
	cc -o recovery recovery.c mergesort.o quicksort.o heapsort.o arraycheck.c
	cc -lpthread -o nversion nversion.c mergesort.o quicksort.o heapsort.o arraycheck.c
