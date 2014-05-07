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
	WARNING("I am warning");
	ERROR("I don't know why ");

	FATAL_ERROR("what are you doing");
	return 0;
}
