#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>

void
my_mergesort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

#endif
