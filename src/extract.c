#include <stdio.h>

#include "util.h"

static int endofinst(int c, FILE *rfp);
static int skipcomm(FILE *rfp);

/*
 * Returns:
 * > 0 on success
 * > 1 if line should be ignored
 * > EOF if EOF was reached
*/
int
extract(FILE *rfp, char **rawinst)
{
    int c;
    int i, l;
    int r;

    l = 0;

    /* Ignore leading whitespace */
    while (((c = fgetc(rfp)) == ' ' || c == '\t')
                        && c != '\n'
                        && c != '#'
                        && c != EOF){
        ;
    }

    if ((r = endofinst(c, rfp)))
        return r;
    ++l;
    
    /* Get line length*/
    while ((c = fgetc(rfp)) != '\n' && c != '#' && c != EOF){
        ++l;
    }
    *rawinst = emalloc((l + 1) * sizeof(char));
    fseek(rfp, -(l + 1), SEEK_CUR);

    /* Extract raw instruction */
    for (i = 0; (c = fgetc(rfp)) != EOF && i < l; ++i){
        (*rawinst)[i] = c;
    }
    (*rawinst)[i] = '\0';
    
    if ((r = endofinst(c, rfp)) == EOF)
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
endofinst(int c, FILE *rfp)
{
    switch(c) {
    case '#':
        return skipcomm(rfp);
    case '\n':
        return 1;
    case EOF:
        return EOF;
    }
    return 0;
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
