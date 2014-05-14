/*
 * server.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/socket.h>
#include<arpa/inet.h>

#include "../common/error.h"
#include "../common/network.h"

int main() {

	/****************************************************************
	 * init server socket
	 ****************************************************************/

	printf("First step, create the socket\n");
	int serverSocket = openSocket();
	printf("The server socket FD is %d\n", serverSocket);

	printf("Set Nonblock socket mode.");
	setNonBlock(serverSocket);

	printf("Second step, bind socket\n");
	bindSocket(serverSocket, 11000);

	printf("Third step, listen socket\n");
	listenSocket(serverSocket);

	printf("Forth step, begin to accept connection\n");
	char* buffer = malloc(512);
	while (1) {
		struct sockaddr_in address;
		socklen_t size;

		size = sizeof(address);

		printf("Begin accept connection\n");
		int socketFd = accept(serverSocket, (struct sockaddr *) &address,
				&size);

		if (socketFd < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				printf("No connection arrive, sleep and try again\n");
				usleep(1000000);
				continue;
			}

			FATAL_ERROR("Accept connection error\n");

		}

		setNonBlock(socketFd);

		/****************************************************************
		 * Read data from client
		 ****************************************************************/

		char* buffer = malloc(512);
		while (1) {
			int result = receiveMessageNonBlock(socketFd, buffer, 512);

			/**
			 * client disconnect
			 */
			if (result > 0) {
				printf("Server  receive ################## %d\n", result);

				int i = 0;
				for (; i < result; i++) {
					printf("%c", buffer[i]);
				}

				break;
			}
		}

		/****************************************************************
		 * Send data to client
		 ****************************************************************/

		int result = sendMessageNonBlock(socketFd, "Hello, welcome @@@@@@@");
		printf("Server send ##### : %d\n", result);

	}

	return 0;
}
