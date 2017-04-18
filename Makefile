INC_DIR := includes
CFLAGS  += -Wall -g -O0 -I$(INC_DIR)
LDFLAGS +=

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

packet-sniffer: main.o sockets.o loop.o
	gcc $(LDFLAGS) main.o sockets.o loop.o -o $@

clean:
	rm packet-sniffer *.o