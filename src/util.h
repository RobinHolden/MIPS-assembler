#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

#define MAX(a,b) (a>b?a:b)

void *emalloc(size_t size);
FILE *efopen(const char *pathname, const char *mode);
void error(const char *fmt, ...);

#endif