##########################################################################################
#
# writen by Yingjie Guo
#
##########################################################################################

IDIR = ./
CC = gcc
CFLAGS = -std=c99 -Wall -I$(IDIR)
LIBS = 
ODIR = ./
LDIR = ./


SOURCES = $(wildcard ./common/*.c)
OBJS = $(SOURCES:.c=.o)


./block_socket/client: $(OBJS) ./block_socket/client.o
	$(CC) -o $@ $^
	@echo "client"

./block_socket/server: $(OBJS) ./block_socket/server.o
	$(CC) -o $@ $^
	@echo "server"

%.o: %.c
	$(CC) -g -Wall -c $< -o $@



.PHONY: all
all: ./block_socket/client ./block_socket/server
	@echo "build..."


.PHONY: clean
clean:
	rm ./block_socket/*.o ./block_socket/client ./block_socket/server
	@echo "clean....."
