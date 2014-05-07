/*
 * error.h
 *
 *  Created on: May 6, 2014
 *      Author: yingjie
 */

#ifndef ERROR_H_
#define ERROR_H_

#include<stdlib.h>

#define ERROR_MESSAGE_FORMAT			"%s : %s\n"
#define ERROR_MESSAGE_FATAL_ERROR		"FATAL ERROR"
#define ERROR_MESSAGE_ERROR				"ERROR"
#define ERROR_MESSAGE_WARNING			"WARNING"

#define ERROR_STRINGIFY(pM) #pM
#define ERROR_TOSTRING(pM) ERROR_STRINGIFY(pM)

#ifdef _DEBUG
#define ERROR_MESSAGE(pM) (pM " : " __FILE__ " (" ERROR_TOSTRING(__LINE__) ")")
#else
#define ERROR_MESSAGE(pM) (pM)
#endif

#define FATAL_ERROR(pMessage) 	fatalError(ERROR_MESSAGE(pMessage), EXIT_FAILURE)
#define ERROR(pMessage) 		error(ERROR_MESSAGE(pMessage))
#define WARNING(pMessage)		warning(ERROR_MESSAGE(pMessage))

void fatalError(const char *pMessage, int pExitCode);
void error(const char *pMessage);
void warning(const char *pMessage);

#endif /* ERROR_H_ */
