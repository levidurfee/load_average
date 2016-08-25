all: clean load
clean:
	rm -Rf load
load:
	gcc -O3 -lcurl -o load load.c