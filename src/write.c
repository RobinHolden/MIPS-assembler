#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "defines.h"
#include "formats.h"
#include "write.h"
#include "writeutils.h"

static int targetval(char *arg, int *targetp);
static int immval(char *arg, int *immp);
static int regval(char *arg);

int
write(Inst inst, FILE *hexfp)
{
    int i, n, hex;

    n = hex = 0;

    for (i = 0; i < MAX_NUMBER_ARGS; ++i){
        switch(instfmts[inst.opn].args[i]) {
        case VOID:
            n = 0;
            break;
        case RD:
        case RS:
        case RT:
        case SA:
            if ((n = regval(inst.args[i])) == -1){
                fprintf(stderr, "Error: Unknown register: %s\n", inst.args[i]);
                exit(1);
            }
            printf("Register value: %d\n", n);
            break;
        case IMM:
            if (immval(inst.args[i], &n) == -1){
                fprintf(stderr, "Error: Unsupported immediate value: %s\n", inst.args[i]);
                exit(1);
            }
            printf("Immediate value: %d\n", n);
            break;
        case TARGET:
            if (targetval(inst.args[i], &n) == -1){
                fprintf(stderr, "Error: Unsupported target value: %s\n", inst.args[i]);
                exit(1);
            }
            printf("Target value: %d\n", n);
            break;
        }
        hex += n << shifts[ instfmts[inst.opn].type ] [ instfmts[inst.opn].args[i] ];
    }
    if (inst.opn == ROTR)
        hex += 1 << 21;
    hex += instfmts[inst.opn].opval << shifts[ instfmts[inst.opn].type ][OPCODE];

    fprintf(hexfp, "%08x\n", hex);
    return 0;
}

static int
regval(char *arg)
{
    int i, n;

    i = 0;

    if (arg[0] != '$')
        return -1;
    if (isdigit(arg[1])){
        n = (int)strtol(arg + 1, NULL, 10);
        if (n < 0 || n >= NUMBER_REGS){
            return -1;
        }
    }
    else{
        while (i < NUMBER_REGS && strcmp(arg + 1, mnems[i])){
            ++i;
        }
        if (i == NUMBER_REGS)
            return -1;
        n = i;
    }

    return n;
}

static int
immval(char *arg, int *immp)
{
    long n;
    char *p;

    n = strtol(arg, &p, 0);
    if (*p != '\0')
        return -1;
    if (n < -32768 || n > 32767)
        return -1;
    *immp = (int)n;
    return 0;
}

static int
targetval(char *arg, int *targetp)
{
    long n;
    char *p;
    
    n = strtol(arg, &p, 0);
    if (*p != '\0')
        return -1;
    if (n < 0 || n > 67108863)
        return -1;
    *targetp = (int)n;
    return 0;
}

