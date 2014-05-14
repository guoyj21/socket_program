/*
 * client.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<stdio.h>
#include<stdlib.h>

#include "../common/error.h"
#include "../common/network.h"

int main() {
	int clientSocket = openSocket();

	bindSocket(clientSocket, 0);

	setNonBlock(clientSocket);

//	connectSocket(clientSocket, 11000, "127.0.0.1");
	connectNonBlockSocket(clientSocket, 11000, "127.0.0.1");

	printf("Send message to Server\n");
	while (1) {
		int result = sendMessageNonBlock(clientSocket, "I am client @@@@@@@@@@@\n");
		if (result > 0) {
			break;
		}
	}

	char* buffer = malloc(512);
	while (1) {
		int result = receiveMessageNonBlock(clientSocket, buffer, 512);
		if (result > 0) {
			printf("****** %d\n", result);
			break;
		}
	}

	int i = 0;
	printf("%s\n", buffer);

	return 0;
}

