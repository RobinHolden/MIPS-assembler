#include <stdio.h>

#include "decoderaw.h"
#include "extract.h"
#include "write.h"

#include "struct.h"
#include "util.h"


int
interMode()
{
	return 0;
}


int
stepMode(const char *fin)
{
	FILE *rfp;

	rfp = efopen(fin, "r");
	fclose(rfp);
	
	return 0;
}


int
autoMode(const char *fin, const char *fhex, const char *ffstate)
{
	FILE *rfp, *hexfp, *fstatefp;
	int ignore;
	Rawinst rawinst;
	Inst inst;

	rfp = efopen(fin, "r");
	hexfp = efopen(fhex, "w");
	fstatefp = efopen(ffstate, "w");

	while ((ignore = extract(rfp, &rawinst)) != EOF){
		if (!ignore){
			decoderaw(&rawinst, &inst);
			write(&inst, hexfp); // TODO
		}
	}

	fclose(rfp);
	fclose(hexfp);
	fclose(fstatefp);
	
	return 0;
}

