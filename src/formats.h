#ifndef _FORMATS_H
#define _FORMATS_H

#include "defines.h"

typedef struct instfmt {
	int type;
    char *op;
    int opval;
    int args[MAX_NUMBER_ARGS];
}Instfmt;

static const Instfmt instfmts[NUMBER_OPS] = {
	{ RTYPE,	"ADD",	0x20,	{ RD,   	RS,		RT   } },
	{ ITYPE,	"ADDI",	0x08,	{ RT,   	RS,		IMM  } },
	{ RTYPE,	"AND",	0x24,	{ RD,   	RS,		RT   } },
	{ ITYPE,	"BEQ", 	0x04,	{ RS,   	RT,		IMM  } },
	{ ITYPE,	"BGTZ",	0x07,	{ RS,  		IMM,	VOID } },
	{ ITYPE,	"BLEZ",	0x06,	{ RS,		IMM,	VOID } },
	{ ITYPE,	"BNE",	0x05,	{ RS,		RT,		IMM  } },
	{ RTYPE,	"DIV",	0x1A,	{ RS,		RT,		VOID } },
	{ JTYPE,	"J",	0x02,	{ TARGET,	VOID,	VOID } },
	{ JTYPE,	"JAL",	0x03,	{ TARGET,	VOID,	VOID } },
	{ RTYPE,	"JR",	0x08,	{ RS,		VOID,	VOID } },
	{ ITYPE,	"LUI",	0x0F,	{ RT,		IMM,	VOID } },
	{ ITYPE,	"LW",	0x23,	{ RT,		IMM,	RS	 } },
	{ RTYPE,	"MFHI",	0x10,	{ RD,		VOID,	VOID } },
	{ RTYPE,	"MFLO",	0x12,	{ RD,		VOID,	VOID } },
	{ RTYPE,	"MULT",	0x18,	{ RS,		RT,		VOID } },
	{ RTYPE,	"OR",	0x25,	{ RD,		RS,		RT   } },
	{ RTYPE,	"ROTR",	0x02,	{ RD,		RT,		SA   } },
	{ RTYPE,	"SLL",	0x00,	{ RD,		RT,		SA	 } },
	{ RTYPE,	"SLT",	0x2A,	{ RD,		RS,		RT   } },
	{ RTYPE,	"SRL",	0x02,	{ RD,		RT,		SA   } },
	{ RTYPE,	"SUB",	0x22,	{ RD,		RS,		RT   } },
	{ ITYPE,	"SW",	0x2B,	{ RT,		IMM,	RS   } },
	{ RTYPE,	"XOR",	0x26,	{ RD,		RS,		RT   } }
};

#endif