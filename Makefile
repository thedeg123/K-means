all: example_k-means
example_k-means: example_k-means.c k-means.o
	gcc k-means.o example_k-means.c -o example_k-means -g
k-means.o: k-means.c k-means.h
	gcc k-means.c -c
clean:
	rm example_k-means k-means.o
	rm -rf example_k-means.dSYM
