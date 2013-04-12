all:
	gcc -g -c mergesort.c
	gcc -g -c quicksort.c
	gcc -g -o test test.c mergesort.o quicksort.o
clean:
	rm -rf test *.o
