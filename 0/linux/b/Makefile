all: mycat
mycat: mycat.c
	gcc -c mycat.c mylib.c
	ld /usr/local/lib/crt0.o mycat.o mylib.o -o mycat
clean:
	rm mycat