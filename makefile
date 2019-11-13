install: main.o gameplay.o printers.o queue.o
	gcc main.o gameplay.o printers.o queue.o -o space-impacter

main.o:
	gcc -c main.c

gameplay.o:
	gcc -c code/gameplay.c

printers.o:
	gcc -c code/printers.c

queue.o:
	gcc -c code/queue.c

clean:
	rm -f *.o space-impacter
