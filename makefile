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

#MODULE_NAME = nonblock_socket
MODULE_NAME = epoll
#MODULE_NAME=block_socket


COMMON_SOURCES = $(wildcard ./common/*.c)
OBJS = $(COMMON_SOURCES:.c=.o)


./$(MODULE_NAME)/client: $(OBJS) ./$(MODULE_NAME)/client.o
	$(CC) -o $@ $^
	@echo "client"

./$(MODULE_NAME)/server: $(OBJS) ./$(MODULE_NAME)/server.o
	$(CC) -o $@ $^
	@echo "server"

%.o: %.c
	$(CC) -g -Wall -c $< -o $@

.PHONY: all
all: ./$(MODULE_NAME)/client ./$(MODULE_NAME)/server
	@echo "build..."


.PHONY: clean
clean:
	rm ./common/*.o ./$(MODULE_NAME)/client ./$(MODULE_NAME)/server ./$(MODULE_NAME)/*.o ./$(MODULE_NAME)/*.o
	@echo "clean....."
