INC_DIR := includes
CFLAGS  += -Wall -g -Og -I$(INC_DIR)
LDFLAGS +=

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

packet-sniffer: main.o sockets.o loop.o
	gcc $(LDFLAGS) $< -o $@

clean:
	rm packet-sniffer *.o