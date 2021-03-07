CC := clang
CFLAGS := -g

all: server client

clean:
	rm -rf server client

server: server.c socket.h
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

