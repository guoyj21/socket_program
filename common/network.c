/*
 * network.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<strings.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<netdb.h>

#include "error.h"
#include "network.h"

int openSocket() {
	int result;

	result = socket(AF_INET, SOCK_STREAM, 0);

	if (result < 0) {
		FATAL_ERROR("Create socket error!");
	}

	return result;
}

void bindSocket(int pSocketFd, int pPort) {
	struct sockaddr_in address;
	int size;

	size = sizeof(address);
	bzero((char *) &address, size);

	address.sin_family = AF_INET;
	address.sin_port = htons(pPort);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(pSocketFd, (struct sockaddr *) &address, size) < 0) {
		FATAL_ERROR("binding socket error!");
	}
}

void connectSocket(int pSocketFd, int pPort, const char *pHost) {
	struct sockaddr_in address;
	struct hostent* server;

	server = gethostbyname(pHost);
	if (server == NULL) {
		FATAL_ERROR("Can not identify Server host");
	}

	bzero((char *) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = pPort;

	bcopy((char *) server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length);

	if (connect(pSocketFd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		FATAL_ERROR("Could not connect to server.");
	}
}

int getConnection(int pSocketFd) {
	struct sockaddr_in address;
	socklen_t size;
	int socketFd;

	size = sizeof(address);
	socketFd = accept(pSocketFd, (struct sockaddr *) &address, &size);

	if (socketFd < 0) {
		FATAL_ERROR("Could not accept connection.");
	}

	return socketFd;
}

void sendMessage(int pSocketFd, const char* pMessage) {
	int size = strlen(pMessage) + 1;
	int result = write(pSocketFd, pMessage, size);

	if (result < 0) {
		FATAL_ERROR("Writing data to socket error!");
	}
}

int receiveMessage(int pSocketFd, char *pBuffer, int pSize) {
	bzero(pBuffer, pSize);
	int result = read(pSocketFd, pBuffer, pSize - 1);

	if (result < 0) {
		FATAL_ERROR("Could not read data from socket!");
	}

	return result;
}

