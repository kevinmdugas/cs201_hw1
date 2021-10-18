CFLAGS = -Wall -std=c11 -pedantic -O0
hw1: hw1_main.o hw1_func.o
	gcc $(CFLAGS) hw1_main.o hw1_func.o -o hw1

hw1_main.o: hw1_main.c
	gcc -c hw1_main.c -o hw1_main.o

hw1_func.o: hw1_func.c
	gcc -c hw1_func.c -o hw1_func.o

clean:
	rm -f *.o hw1
