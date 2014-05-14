/*
 * network.h
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#ifndef NETWORK_H_
#define NETWORK_H_

int openSocket();
void bindSocket(int pSocketFd, int pPort);
void listenSocket(int pSocketFd);
void setNonBlock(int pSocketFd);
void connectSocket(int pSocketFd, int pPort, const char *pHost);
int getConnection(int pSocketFd);


void connectNonBlockSocket(int pSocketFd, int pPort, const char *pHost);
int receiveMessageNonBlock(int pSocketFd, char *pBuffer, int pSize);
int sendMessageNonBlock(int pSocketFd, const char* pMessage);

void sendMessage(int pSocketFd, const char* pMessage);
int receiveMessage(int pSocketFd, char *pBuffer, int pSize);

#endif /* NETWORK_H_ */
