#ifndef _MNEMS_H
#define _MNEMS_H

#include "defines.h"
#include "decode.h"

const char *mnems[NUMBER_REGS] = {
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
const int shifts[NUM_INST_TYPES][NUM_ELMTS] = {
	[RTYPE] = { [RS] = 21,		[RT] = 16,	[RD] = 11, [SA] = 6, [OPCODE] = 0 },
	[ITYPE] = { [OPCODE] = 26,	[RS] = 21,	[RT] = 16, [IMM] = 0 },
	[JTYPE] = { [OPCODE] = 26,	[TARGET] = 0 }
};

#endif