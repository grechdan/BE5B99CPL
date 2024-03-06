all:

	gcc -Wall -o my_string.o -c my_string.c
	gcc -Wall main.c my_string.o -o main
	valgrind ./main

clean:

	rm main -f
	rm my_string -f
	rm my_string.o -f
