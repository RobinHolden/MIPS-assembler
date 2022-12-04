#ifndef _DEFINES_H
#define _DEFINES_H

#define MAX_NUMBER_ARGS 3
#define NUMBER_REGS 31

#define MAX_OP_SIZE 4

#define VOID -1

enum types {
	RTYPE,
	ITYPE,
	JTYPE,
	NUM_INST_TYPES
};
enum elmts {
	FUNC,
	IMM,
    OPCODE,
    RD,
    RS,
    RT,
    SA,
    TARGET,
	NUM_ELMTS
};
enum ops {
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
	OR,
	ROTR,
	SLL,
	SLT,
	SRL,
	SUB,
	SW,
	XOR,
	NUMBER_OPS
};

#endif