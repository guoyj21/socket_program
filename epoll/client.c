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

	connectSocket(clientSocket, 11000, "127.0.0.1");

	sendMessage(clientSocket, "I am client***************\n");
	char* buffer = malloc(512);
	receiveMessage(clientSocket, buffer, 512);

	int i = 0;
	printf("%s\n", buffer);

	return 0;
}

