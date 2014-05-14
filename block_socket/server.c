/*
 * server.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<stdio.h>
#include<stdlib.h>

#include "../common/error.h"
#include "../common/network.h"

int main() {
	printf("First step, create the socket\n");
	int serverSocket = openSocket();
	printf("The server socket FD is %d\n", serverSocket);

	printf("Second step, bind socket\n");
	bindSocket(serverSocket, 11000);

	printf("Third step, listen socket\n");
	listenSocket(serverSocket);

	printf("Forth step, begin to accept connection\n");
	char* buffer = malloc(512);
	while (1) {
		printf("Begin accept connection\n");
		int clientSocket = getConnection(serverSocket);
		printf("Connection arrive\n");
		receiveMessage(clientSocket, buffer, 512);
		printf("%s\n", buffer);
		sendMessage(clientSocket, "Hi boy, welcome\n");
	}

	return 0;
}
