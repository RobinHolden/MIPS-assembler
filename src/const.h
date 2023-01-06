#ifndef _CONST_H_
#define _CONST_H_

#define MAX_NUM_ARGS 3
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
enum regs {
	zero,
    at,
	v0,
	v1,
	a0,
	a1,
	a2,
	a3,
	t0,
	t1,
	t2,
	t3,
	t4,
	t5,
	t6,
	t7,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	t8,
	t9,
	k0,
	k1,
	gp,
	sp,
	fp,
	ra,
    NUM_REGS
};

#endif