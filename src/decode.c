#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "util.h"

/*
 * Returns 0 on success, -1 if op isn't recognized, -2 if wrong number of args,
 * <arg_number> if an arg isn't recognized (starting from 1).
 */
int
decode(const char *instr, int *hex) /* Needs finishing off (don't forget to free) */
{
	operator op;
	arguments args;
	
	if (!parseop(instr, &op))
		return -1;
	getargs(instr + op.opl, &args);

	/* Sum op value to *hex --- Needs finishing off */
	*hex = 0;
	switch(op.opn){
	case ADD: /* FALLTHROUGH */
	case AND:
	case OR:
	case SLT:
	case SUB:
	case XOR:
		break;
	case ADDI:
		break;
	case BEQ: /* FALLTHROUGH */
	case BNE:
		break;
	case BGTZ: /* FALLTHROUGH */
	case BLEZ:
		break;
	case DIV: /* FALLTHROUGH */
	case MULT:
		break;
	case J: /* FALLTHROUGH */
	case JAL:
		break;
	case JR:
		break;
	case LUI:
		break;
	case LW: /* FALLTHROUGH */
	case SW:
		break;
	case MFHI: /* FALLTHROUGH */
	case MFLO:
		break;
	case NOP:
		break;
	case ROTR: /* FALLTHROUGH */
	case SLL:
	case SRL:
		break;
	case SYSCALL:
		break;
	default: /* NOTREACHED */
		return 1; 
	}
	return 0;
}

/* Returns 0 if op is recognized, 1 if not. */
static int
getop(const char *instr, operator *opp)
{
	extern const char *ops[];
	int i;

	/* Find opstr in instr and save opl */
	opp->opstr = emalloc((MAX_OP_SIZE + 1) * sizeof(char));
	for (i = 0; instr[i] != '\t'
			 && instr[i] != ' '
			 && instr[i] != '\0'
			 && instr[i] != '\v'; ++i){
		if (i == MAX_OP_SIZE)
			return 1;
		opp->opstr[i] = instr[i];
	}
	opp->opstr[i] = '\0';
	opp->opl = i;

	/* Find opstr in ops[] and save opn ----- A faire en dichotomique */
	for (opp->opn = 0; opp->opn < NUMBER_OPS; ++(opp->opn)){
		if (!strcmp(opp->opstr, ops[opp->opn]))
			return 0;
	}
	return 1;
}

/* Returns 0. */
static int
getargs(const char *instrwoop, arguments *args)
{
	int i, j, l;

	i = j = l = 0;
	
	args->argArr = emalloc(MAX_NUMBER_ARGS * sizeof(char *));
	while (j < MAX_NUMBER_ARGS){ /* Initialize argArr[*] to NULL */
		args->argArr[j] = NULL;
		++j;
	}
	j = 0;
	while (args->nargs < MAX_NUMBER_ARGS){
		while (instrwoop[i] == '\t'
			|| instrwoop[i] == ' '
			|| instrwoop[i] == '\v'){ /* Find start of arg in instrwoop */
			++i;
		}
		while (instrwoop[i] != '\t'
			&& instrwoop[i] != ' '
			&& instrwoop[i] != '\v'
			&& instrwoop[i] != '\0'){ /* Determine arg length */
			++i;
			++l;
		}
		if (l == 0) /* If end of instr */
			return 0;
		args->argArr[args->nargs] = emalloc((l + 1) * sizeof(char));
		i -= l;
		while (j < l){ /* Save argArr[n] */
			args->argArr[args->nargs][j] = instrwoop[i];
			++i;
			++j;
		}
		args->argArr[args->nargs][j] = '\0';
		++(args->nargs);
		j = l = 0;
	}
	return 0;
}
