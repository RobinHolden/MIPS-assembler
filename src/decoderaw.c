#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "instfmts.h"
#include "regs.h"
#include "struct.h"
#include "util.h"

static void getopn(Rawinst *rawinst, Inst *inst);
static void getargs(Rawinst *rawinst, Inst *inst);
static int immval(char *rawarg, int *immvalp);
static int regval(char *rawarg, int *regvalp);
static int targval(char *rawarg, int *targvalp);

/*
 * Returns 0 on success, 1 if op isn't recognized
 */
void
decoderaw(Rawinst *rawinst, Inst *inst)
{
    getopn(rawinst, inst);
	getargs(rawinst, inst);
	return;
}

/*
 * If op is recognized, returns EOF if end of line was found, 0 if not.
 * If op isn't recognized, returns 1.
*/ 
static void
getopn(Rawinst *rawinst, Inst *inst)
{
    int i;

    for (i = 0; rawinst->op[i] != '\0'; ++i){
        rawinst->op[i] = toupper(rawinst->op[i]);
    }
	for (inst->opn = 0; inst->opn < NUMBER_OPS; ++(inst->opn)){
		if (!strcmp(rawinst->op, instfmts[inst->opn].op))
			return;
	}
	error("Syntax error in assembly file: Operator %s not recognized\n", rawinst->op);
}
static void
getargs(Rawinst *rawinst, Inst *inst)
{
    int i;
    int r;

    for (i = 0; i < MAX_NUM_ARGS; ++i){
        switch(instfmts[inst->opn].args[i]) {
        case VOID:
            if (rawinst->args[i] != NULL)
                error("Syntax error in assembly file: Expected %d arguments for instruction %s, found at least %d\n", i, rawinst->op, i + 1);
            inst->args[i] = 0;
            break;
        case RD:
        case RS:
        case RT:
        case SA:
            if ((r = regval(rawinst->args[i], inst->args + i)) == 1)
                error("Syntax error in assembly file: Expected argument %d of instruction %s, found no argument\n", i + 1, rawinst->op);
            if (r == -1)
                error("Syntax error in assembly file: Expected register value for argument %d of instruction %s\n", i + 1, rawinst->op);
            printf("Register value: %d\n", inst->args[i]);
            break;
        case IMM:
            if ((r = immval(rawinst->args[i], inst->args + i)) == 1)
		error("Syntax error in assembly file: Out of bounds immediate value as argument %d of instruction %d\n", i + 1, rawinst->op);
	    if (r == -1)
		error("Syntax error in assembly file: Non immediate value as argument %d of instruction %d\n", i + 1, rawinst->op);
            printf("Immediate value: %d\n", inst->args[i]);
            break;
        case TARGET:
            if ((r = targval(rawinst->args[i], inst->args + i)) == 1)
		error("Syntax error in assembly file: Out of bounds target value as argument %d of instruction %d\n", i + 1, rawinst->op);
	    if (r == -1)
		error("Syntax error in assembly file: Non target value as argument %d of instruction %d\n", i + 1, rawinst->op);
            printf("Target value: %d\n", inst->args[i]);
            break;
        }
    }
    return;
}

static int
immval(char *rawarg, int *immvalp)
{
    long n;
    char *p;

    n = strtol(rawarg, &p, 0);
    if (*p != '\0')
        return -1;
    if (n < -32768 || n > 32767)
        return 1;
    *immvalp = (int)n;
    return 0;
}

static int
regval(char *rawarg, int *regvalp)
{
    int i;

    if (rawarg == NULL)
        return -1;
    if (rawarg[0] != '$')
        return 1;
    if (isdigit(rawarg[1])){
        *regvalp = (int)strtol(rawarg + 1, NULL, 10);
        if (*regvalp < 0 || *regvalp >= NUM_REGS)
            return 1;
    }
    else{
        for (i = 0; rawarg[i] != '\0'; ++i){
            rawarg[i] = tolower(rawarg[i]);
        }
        for (i = 0; i < NUM_REGS && strcmp(rawarg + 1, regs[i].mnem); ++i){
            ;
        }
        if (i == NUM_REGS)
            return 1;
        *regvalp = i;
    }
    return 0;
}

static int
targval(char *rawarg, int *targvalp)
{
    long n;
    char *p;
    
    n = strtol(rawarg, &p, 0);
    if (*p != '\0')
        return -1;
    if (n < 0 || n > 67108863)
        return 1;
    *targvalp = (int)n;
    return 0;
}

