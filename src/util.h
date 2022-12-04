#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>

#define MAX(a,b) (a>b?a:b)

void *emalloc(size_t size);
FILE *efopen(const char *pathname, const char *mode);

#endif