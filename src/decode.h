#ifndef _DECODE_H
#define _DECODE_H

#include "defines.h"

typedef struct inst {
	char *label;
	int opn;
	char *args[MAX_NUMBER_ARGS];
}Inst;

Inst decode(char *rawinst);

#endif