#include <stdio.h>

#include "decode.h"
#include "extract.h"
#include "util.h"
#include "write.h"

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
	char *rawinst;
	int ignore;
	Inst inst;

	rawinst = NULL;
	rfp = efopen(fin, "r");
	hexfp = efopen(fhex, "w");
	fstatefp = efopen(ffstate, "w");

	while ((ignore = extract(rfp, &rawinst)) != EOF){
		if (!ignore){
			inst = decode(rawinst);
			write(inst, hexfp);
			// Write instruction to hexfp;
		}
	}

	fclose(rfp);
	fclose(hexfp);
	fclose(fstatefp);
	
	return 0;
}

