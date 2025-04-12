server: server.o
	gcc -o server server.o

server.o: server.c server.h
	gcc -c server.o server.c

clean:
	rm *.o

run: 
	./server