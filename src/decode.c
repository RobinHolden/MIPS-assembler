#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "decode.h"
#include "util.h"

const char *opArr[NUMBER_OPS] = {"ADD", "ADDI", "AND", "BEQ", "BGTZ", "BLEZ", "BNE", "DIV", "J", "JAL", "JR", "LUI", "LW", "MFHI", "MFLO", "MULT", "NOP", "OR", "ROTR", "SLL", "SLT", "SRL", "SUB", "SW", "SYSCALL", "XOR"};

// Returns 0 on success, -1 if op isn't recognized, -2 if wrong number of args, <arg_number> if an arg isn't recognized (starting from 1).
int
decode(const char *instr, int *hex) // Traiter chaque cas + rajouter free du tableau **args
{
	char **args;
	int opnumber;

	if (parseOp(instr, &opnumber))
		return 1;
	parseArgs(instr, &args);

	// Sum op value to *hex --- A modif
	*hex = 0;
	switch (opnumber){
	case ADD:
		*hex += 32;
		break;
	case ADDI:
		*hex += (8 << 26);
		break;
	case AND:
		*hex += 36;
		break;
	case BEQ:
		*hex += (4 << 26);
		break;
	case BGTZ:
		*hex += (7 << 26);
		break;
	case BLEZ:
		*hex += (6 << 26);
		break;
	case BNE:
		*hex += (5 << 26);
		break;
	case DIV:
		*hex += 26;
		break;
	case J:
		*hex += (2 << 26);
		break;
	case JAL:
		*hex += (3 << 26);
		break;
	case JR:
		*hex += 8;
		break;
	case LUI:
		*hex += (15 << 26);
		break;
	case LW:
		*hex += (35 << 26);
		break;
	case MFHI:
		*hex += 16;
		break;
	case MFLO:
		*hex += 18;
		break;
	case MULT:
		*hex += 24;
		break;
	case NOP:
		return 0; // NO OP
	case OR:
		*hex += 37;
		break;
	case ROTR:
		// ???
		break;
	case SLL:
		break;
	case SLT:
		*hex += 42;
		break;
	case SRL:
		*hex += 2;
		break;
	case SUB:
		*hex += 34;
		break;
	case SW:
		*hex += (43 << 26);
	case SYSCALL:
		*hex += 12;
		break;
	case XOR:
		*hex += 38;
		break;
	default:
		return 1;
	}
	return 0;
}

// Returns 0 on success, 1 if op isn't recognized.
int 
parseOp(const char *instr, int *opnumber)
{
	char *op;
	int i;

	// Find op in instruction
	op = emalloc((MAX_OP_SIZE + 1) * sizeof(char));
	for (i = 0; instr[i] != '\t' && instr[i] != ' ' && instr[i] != '\v' && instr[i] != '#' && instr[i] != '\n' && instr[i] != EOF; ++i){
		if (i == MAX_OP_SIZE){
			free(op);
			return 1;
		}
		op[i] = instr[i];
	}
	op[i] = '\0';

	// Find op in opArr ----- A faire en dichotomique
	for (*opnumber = 0; *opnumber < NUMBER_OPS; ++(*opnumber)){
		if (!strcmp(op, opArr[*opnumber])){
			free(op);
			return 0;
		}
	}
	free(op);
	return 1;
}

// Returns number of arguments.
int 
parseArgs(const char *instr, char ***args)
{
	int i, j, l, n;

	l = 0;
	// Find end of op
	for (i = 0; instr[i] != '\t' && instr[i] != ' ' && instr[i] != '\v'; ++i){
		if (instr[i] == '#' || instr[i] == '\n' || instr[i] == EOF)
			return 0;
	}
	// Treat args
	*args = emalloc(MAX_NUMBER_ARGS * sizeof(char *));
	for (j = 0; j < MAX_NUMBER_ARGS; ++j){ // Initialize args to NULL
		*args[j] = NULL;
	}
	j = 0;
	for (n = 0; n < MAX_NUMBER_ARGS;){
		while (instr[i] == '\t' || instr[i] == ' ' || instr[i] == '\v'){ // Find arg
			++i;
		}
		while (instr[i] != '\t' && instr[i] != ' ' && instr[i] != '\v' && instr[i] != '#' && instr[i] != '\n' && instr[i] != EOF){ // Determine arg length
			++i;
			++l;
		}
		if (l == 0) // Detect if final arg
			return n;
		*args[n] = emalloc((l + 1) * sizeof(char));
		i -= l;
		for (j = 0; j < l; ++j){ // Save arg
			*args[n][j] = instr[i];
			++i;
		}
		*args[n][j] = '\0';
		++n;
		l = 0;
	}

	return 0;
}