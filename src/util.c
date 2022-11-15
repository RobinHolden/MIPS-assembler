#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void *emalloc(size_t size)
{
	void *p = NULL;

	if ((p = malloc(size)) == NULL){
		perror("malloc");
        exit(1);
    }
	return p;
}


FILE *efopen(const char *pathname, const char *mode)
{
    FILE *fp;

    if ((fp = fopen(pathname, mode)) == NULL){
        perror("fopen");
        exit(1);
    }
    return fp;
}