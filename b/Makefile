all: mysh mycat
mysh: mysh.c
	gcc -c mysh.c mylib.c
	ld /usr/local/lib/crt0.o mysh.o mylib.o -o mysh
mycat: mycat.c
	gcc -c mycat.c mylib.c
	ld /usr/local/lib/crt0.o mycat.o mylib.o -o mycat
clean:
	rm mysh
	rm mycat