all: precision concurrent-counter sloppy-counter

precision: precision.c
	gcc -o precision precision.c

concurrent-counter: concurrent-counter.c
	gcc -o concurrent-counter concurrent-counter.c -pthread -g

sloppy-counter: sloppy-counter.c
	gcc -o sloppy-counter sloppy-counter.c -pthread -g
