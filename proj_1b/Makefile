all: mycp
	
mycp: mycopy.o
	gcc -g mycopy.o -o mycp

mycp.o: mycopy.c
	gcc -g -c mycopy.c

clean:
	\rm *.o mycp
	
