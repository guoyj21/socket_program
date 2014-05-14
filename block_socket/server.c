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

extern int openSocket();


int main() {
	printf("First step, create the socket\n");
	int serverSocket = openSocket();
	printf("The server socket FD is %d\n", serverSocket);

	printf("Second step, bind socket\n");
	bindSocket(serverSocket);

	printf("Third step, listen socket\n");
	listenSocket(serverSocket);

	printf("Forth step, begin to accept connection\n");
	char* buffer = malloc(512);
	while(true) {
		int clientSocket = acceptSocket(serverSocket);
		receiveMessage(clientSocket, buffer, 512);
		sendMessage(clietSocket, "Hi boy, welcome");
	}


	return 0;
}
