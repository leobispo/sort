#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>

void
my_quicksort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

#endif
