#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void
*emalloc(size_t size)
{
	void *p = NULL;

	if ((p = malloc(size)) == NULL){
		perror("malloc");
        exit(1);
    }
	return p;
}
FILE
*efopen(const char *pathname, const char *mode)
{
    FILE *fp;

    if ((fp = fopen(pathname, mode)) == NULL){
        perror("fopen");
        exit(1);
    }
    return fp;
}
void
error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(1);
}