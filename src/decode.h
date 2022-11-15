#ifndef _DECODE_H
#define _DECODE_H

#define MAX_NUMBER_ARGS 3
#define MAX_OP_SIZE 7 
#define NUMBER_OPS 26
enum {ADD, ADDI, AND, BEQ, BGTZ, BLEZ, BNE, DIV, J, JAL, JR, LUI, LW, MFHI, MFLO, MULT, NOP, SYSCALL, OR, ROTR, SLL, SLT, SRL, SUB, SW, XOR};

int decode(const char *instr, int *hex);

#endif
