#include <stdio.h>
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
	
	rfp = efopen(fin, "r");
	hexfp = efopen(fhex, "w");
	fstatefp = efopen(ffstate, "w");

	/*
	n = decode(instr, &hex);
	fprintf(fp, "08%x\n", n);
	*/

	fclose(rfp);
	fclose(hexfp);
	fclose(fstatefp);
	
	return 0;
}

