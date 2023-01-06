#include <stdio.h>

#include "struct.h"
#include "util.h"

static int checkendinst(int c, FILE *rfp);
static int getrawargs(FILE *rfp, char *args[]);
static int getrawop(FILE *rfp, char *s);
static int skipcomm(FILE *rfp);
static int skipwhitespace(FILE *rfp);

/*
 * Returns:
 * > 0 on success
 * > 1 if line should be ignored
 * > EOF if EOF was reached
*/
int
extract(FILE *rfp, Rawinst *rawinst)
{
    int r;
    
    if ((r = skipwhitespace(rfp)))
        return r;
    if (getrawop(rfp, rawinst->op) == EOF)
        return EOF;
    if (getrawargs(rfp, rawinst->args) == EOF)
        return EOF;
    return 0;
}

/* 
 * Returns:
 * 0 if c isn't end of inst
 * 1 if c is '\n' or comment was found and skipped
 * EOF is c is EOF
*/
static int
checkendinst(int c, FILE *rfp)
{
    switch(c) {
    case '#':
        return skipcomm(rfp);
    case '\n':
        fgetc(rfp);
        return 1;
    case EOF:
        return EOF;
    }
    return 0;
}

static int
getrawargs(FILE *rfp, char *args[])
{
	int i, l, n;
    int c;
    int r;

	n = 0;
    
    for (i = 0; i < MAX_NUM_ARGS; ++i){
        args[i] = NULL;
    }
	while (n < MAX_NUM_ARGS){
		l = 0;
        if ((r = skipwhitespace(rfp)))
            return r;
		while ((c = fgetc(rfp)) != ','
			               && c != ' '
                           && c != '\t'
                           && c != '\n'
                           && c != '#'
                           && c != EOF){
			++l;
		}

		args[n] = emalloc((l + 1) * sizeof(char));
		fseek(rfp, -(l + 1), SEEK_CUR);
		for (i = 0; i < l; ++i){
            args[n][i] = fgetc(rfp);
		}
		args[n][i] = '\0';

		/* Go to next comma or end of inst */
        if ((r = skipwhitespace(rfp)))
            return r;
        if ((c = fgetc(rfp)) != ',')
            error("Syntax error in assembly file: Expected ',', found %c\n", c);
		++n;
	}
	return 0;
} 

static int
getrawop(FILE *rfp, char *s)
{
    int i;
    int c;

	for (i = 0; (c = fgetc(rfp)) != ' '
                            && c != '\t'
                            && c != '\n'
                            && c != '#'
                            && c != EOF
                            && i < MAX_OP_SIZE; ++i){
		s[i] = c;
	}
	s[i] = '\0';
    return skipwhitespace(rfp);
}

/* Returns 1 when newline is found, or EOF if found */
static int
skipcomm(FILE *rfp){
    int c;

    while ((c = fgetc(rfp)) != '\n' && c != EOF){
        ;
    }
    return (c == EOF) ? EOF : 1;
}

static int
skipwhitespace(FILE *rfp)
{
    int c;

    while (((c = fgetc(rfp)) == ' ' || c == '\t')
                        && c != '\n'
                        && c != '#'
                        && c != EOF){
        ;
    }
    fseek(rfp, -1, SEEK_CUR);

    return checkendinst(c, rfp);
}
