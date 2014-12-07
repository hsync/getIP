getIP:	main.o
	gcc -o getIP main.o

main.o:	main.c
	gcc -c -std=gnu99 main.c
