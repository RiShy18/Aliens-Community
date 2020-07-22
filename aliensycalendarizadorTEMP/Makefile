list_driver: liblist
	gcc -Wall -Wextra llist.o main.c -o llist_driver lib/llist.a -lm -lpthread 

liblist:
		gcc -c src/llist.c
		ar rv lib/llist.a llist.o
		ranlib lib/llist.a