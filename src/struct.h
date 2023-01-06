#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "const.h"

typedef struct instfmt {
	int type;
    char *op;
    int opval;
    int args[MAX_NUM_ARGS];
} Instfmt;
typedef struct rawinst {
	char op[MAX_OP_SIZE + 1];
	char *args[MAX_NUM_ARGS];
} Rawinst;
typedef struct inst {
	int opn;
	int args[MAX_NUM_ARGS];
} Inst;

typedef struct reg {
	char *mnem;
	int val;
} Reg;

#endif