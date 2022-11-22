#ifndef _DECODE_H
#define _DECODE_H

#define MAX_NUMBER_ARGS 3
#define MAX_OP_SIZE 7
#define NUMBER_OPS 26
#define NUMBER_REGS 32

typedef struct operator{
	char *opstr;
	int opn;
	int opl;
} operator;
typedef struct arguments{
	char **argArr;
	int nargs;
} arguments;

enum{
	ADD,
	ADDI,
	AND,
	BEQ,
	BGTZ,
	BLEZ,
	BNE,
	DIV,
	J,
	JAL,
	JR,
	LUI,
	LW,
	MFHI,
	MFLO,
	MULT,
	NOP,
	SYSCALL,
	OR,
	ROTR,
	SLL,
	SLT,
	SRL,
	SUB,
	SW,
	XOR
};
const char *ops[NUMBER_OPS] = {
	"ADD",
	"ADDI",
	"AND",
	"BEQ",
	"BGTZ",
	"BLEZ",
	"BNE",
	"DIV",
	"J",
	"JAL",
	"JR",
	"LUI",
	"LW",
	"MFHI",
	"MFLO",
	"MULT",
	"NOP",
	"OR",
	"ROTR",
	"SLL",
	"SLT",
	"SRL",
	"SUB",
	"SW",
	"SYSCALL",
	"XOR"
};
int opvals[NUMBER_OPS] =
{
	32,		/* ADD */
	8 << 26,	/* ADDI */
	36,		/* AND */
	4 << 26,	/* BEQ */
	7 << 26,	/* BGTZ */
	6 << 26,	/* BLEZ */
	5 << 26,	/* BNE */
	26,		/* DIV */
	2 << 26,	/* J */
	3 << 26,	/* JAL */
	8,		/* JR */
	15 << 26,	/* LUI */
	35 << 26,	/* LW */
	16,		/* MFHI */
	18,		/* MFLO */
	24,		/* MULT */
	0,		/* NOP */
	37,		/* OR */
	2,		/* ROTR */
	0,		/* SLL */
	42,		/* SLT */
	2,		/* SRL */
	34,		/* SUB */
	43 << 26,	/* SW */
	12,		/* SYSCALL */
	38		/* XOR */
};
const char *mnems[NUMBER_REGS] =
{
	"zero",
	"at",
	"v0",
	"v1",
	"a0",
	"a1",
	"a2",
	"a3",
	"t0",
	"t1",
	"t2",
	"t3",
	"t4",
	"t5",
	"t6",
	"t7",
	"s0",
	"s1",
	"s2",
	"s3",
	"s4",
	"s5",
	"s6",
	"s7",
	"t8",
	"t9",
	"k0",
	"k1",
	"gp",
	"sp",
	"fp",
	"ra"
};
int decode(const char *instr, int *hex);

#endif
