#ifndef _SHIFTS_H
#define _SHIFTS_H

#include "const.h"

const int shifts[NUM_INST_TYPES][NUM_ELMTS] = {
	[RTYPE] = { [RS] = 21,		[RT] = 16,	[RD] = 11, [SA] = 6, [OPCODE] = 0 },
	[ITYPE] = { [OPCODE] = 26,	[RS] = 21,	[RT] = 16, [IMM] = 0 },
	[JTYPE] = { [OPCODE] = 26,	[TARGET] = 0 }
};

#endif
