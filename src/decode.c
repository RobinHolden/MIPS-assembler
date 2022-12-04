#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "formats.h"
#include "util.h"

static int getop(char **rawinst, int *opn);
static int getargs(char *rawinst, char *args[]);

/*
 * Returns 0 on success, 1 if op isn't recognized
 */
Inst
decode(char *rawinst)
{
	char *p;
	int n;
	Inst inst = {
		NULL,
		-1,
		{NULL, NULL, NULL}
	};
	
	/* Get label, if exists */
	if ((p = strchr(rawinst, ':')) != NULL){
		rawinst[p - rawinst] = '\0';
		inst.label = emalloc((p - rawinst + 1) * sizeof(char));
		strcpy(inst.label, rawinst);
		rawinst += p - rawinst + 1;
	}

	/* If op was recognized and potential args*/
	if ((n = getop(&rawinst, &inst.opn)) != EOF)
		getargs(rawinst, inst.args);
	return inst;
}

/*
 * If op is recognized, returns EOF if end of line was found, 0 if not.
 * If op isn't recognized, returns 1.
*/ 
static int
getop(char **rawinst, int *opn)
{
	char opstr[MAX_OP_SIZE + 1];
	int i;

	/* Find first character of op */
	while (**rawinst == ' ' || **rawinst == '\t'){
		(*rawinst)++;
	}
	if (**rawinst == '\0')
		return EOF;
	/* Fill in opstr */
	for (i = 0; (*rawinst)[i] != ' '
			 && (*rawinst)[i] != '\t'
			 && (*rawinst)[i] != '\0'
			 && i < MAX_OP_SIZE; ++i){
		opstr[i] = (*rawinst)[i];
	}
	opstr[i] = '\0';

	/* Find opstr in list of ops ----- A faire en dichotomique */
	for (*opn = 0; *opn < NUMBER_OPS; ++(*opn)){
		if (!strcmp(opstr, instfmts[*opn].op)){
			if ((*rawinst)[i] == '\0')
				return EOF;
			*rawinst += i;
			return 0;
		}
	}
	fprintf(stderr, "Error : Operator %s not recognized\n", opstr);
	exit(1);
}

/* Returns 0. */
static int
getargs(char *rawinst, char *args[])
{
	int i, l, n;

	n = 0;
	
	while (n < MAX_NUMBER_ARGS){
		i = l = 0;
		
		/* Find start of arg in rawinst */
		while ((*rawinst == ' ' || *rawinst == '\t') && *rawinst != '\0'){
			++rawinst;
		}
		if (*rawinst == '\0')
			return 0;
		while (*rawinst != ','
			&& *rawinst != ' '
			&& *rawinst != '\t'
			&& *rawinst != '\0'){ /* Determine arg length */
			++l;
			++rawinst;
		}
		if (l == 0) /* If end of inst */
			return 0;
		args[n] = emalloc((l + 1) * sizeof(char));
		rawinst -= l;
		while (i < l){ /* Save argArr[n] */
			args[n][i] = *rawinst;
			++rawinst;
			++i;
		}
		args[n][i] = '\0';

		/* Go to next comma or end of inst */
		while (*rawinst != ',' && *rawinst != '\0'){
			++rawinst;
		}
		if (*rawinst == '\0')
			return 0;
		++rawinst;
		++n;
	}
	return 0;
}
