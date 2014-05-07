/*
 * error.c
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#include<stdlib.h>
#include<stdio.h>

#include "error.h"

void errorMessage(const char *pTag, const char *pMessage) {
	fprintf(stderr, ERROR_MESSAGE_FORMAT, pTag, pMessage);
	fflush(stderr);
}

void fatalError(const char *pMessage, int pExitCode) {
	errorMessage(ERROR_MESSAGE_FATAL_ERROR, pMessage);
	perror(ERROR_MESSAGE_FATAL_ERROR " ");
	exit(pExitCode);
}

void error(const char *pMessage) {
	errorMessage(ERROR_MESSAGE_ERROR, pMessage);
}

void warning(const char *pMessage) {
	errorMessage(ERROR_MESSAGE_WARNING, pMessage);
}
