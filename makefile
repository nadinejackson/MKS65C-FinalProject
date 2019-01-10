all: client server

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

server: basic_server.o pipe_networking.o game.o
	gcc -o server basic_server.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -c client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c
game.o: game.c
	gcc -c game.c
clean:
	rm *.o
	rm server
	rm client
