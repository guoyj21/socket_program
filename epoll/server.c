/*
 * server.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h>
#include <sys/epoll.h>
#include<arpa/inet.h>

#include<errno.h>

#include "../common/error.h"
#include "../common/network.h"

int main() {
	printf("**********************\n");
	struct epoll_event event, events[10];
	int epollFd, numOfFd;
	int i = 0, fd, connSocket;

	struct sockaddr_in remote;
	int addrlen;

	char* RECV_BUFFER = malloc(512);
	char* SEND_BUFFER = malloc(512);

	int serverSocket = openSocket();

	setNonBlock(serverSocket);

	bindSocket(serverSocket, 11000);

	listenSocket(serverSocket);
	epollFd = epoll_create(10);

	if (epollFd == -1) {
		FATAL_ERROR("Create epoll failed");
	}

	event.events = EPOLLIN;
	event.data.fd = serverSocket;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &event) == -1) {
		FATAL_ERROR("Register EPOLL Event failed");
	}

	printf("----   start epoll wait   ----\n");
	while (1) {
		numOfFd = epoll_wait(epollFd, events, 10, -1);

		if (numOfFd == -1) {
			FATAL_ERROR("EPOLL wait failed");
		}

		for (i = 0; i < numOfFd; i++) {
			fd = events[i].data.fd;
			if (fd == serverSocket) {
				printf("-------- I am listen socket -------\n");
				while ((connSocket = accept(serverSocket, (struct sockaddr *) &remote, (size_t *) &addrlen) > 0)) {

					setNonBlock(connSocket);

					event.events = EPOLLIN | EPOLLET;
					event.data.fd = connSocket;

					if (epoll_ctl(epollFd, EPOLL_CTL_ADD, connSocket, &event) == -1) {
						FATAL_ERROR("Register event on connection socket failed.");
					}
				}

				if (connSocket == -1) {
					printf("connection status %d\n", errno);
					if (errno != EAGAIN && errno != EINTR) {
						FATAL_ERROR("Accept connection failed.");
					}
				}
				continue;
			}

			if (events[i].events & EPOLLIN) {
				printf("-------------- EPOLLIN event --------------\n");
				int n = 0, nread = 0;
				while ((nread = read(fd, RECV_BUFFER + n, 512 - 1)) > 0) {
					n += nread;
					printf("read read read\n");
				}

				printf("##### Server received: %s\n", RECV_BUFFER);

				if (nread == -1 && errno != EAGAIN) {
					printf("Read Data failed, error code is %d\n", errno);
				}

				event.events = EPOLLOUT | EPOLLET;
				event.data.fd = fd;

				if (epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &event) == -1) {
					FATAL_ERROR("Register EPOLLOUT event failed.");
				}
			}

			if (events[i].events & EPOLLOUT) {
				printf("-------------  EPOLLOUT event ------------\n");
				int left = 0, nwrite = 0;
				int dataSize;
				sprintf(SEND_BUFFER, "Hello , what are you doing now ?");
				dataSize = strlen(SEND_BUFFER);
				while (left > 0) {
					nwrite = write(fd, SEND_BUFFER + dataSize - left, left);
					if (nwrite < left) {
						if (nwrite == -1) {
							if (errno != EAGAIN) {
								printf("Send data failed, error code is %d\n",
								errno);
							}
						}
//						break;
					}
					left -= nwrite;
				}

				event.events = EPOLLET;
				event.data.fd = fd;

				if (epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &event) == -1) {
					FATAL_ERROR("delete event");
				}

				close(fd);
			}
		}

	}

	return 0;
}
