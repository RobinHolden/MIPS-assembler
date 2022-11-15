#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>

void *emalloc(size_t size);
FILE *efopen(const char *pathname, const char *mode);

#endif