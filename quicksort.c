#include "quicksort.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define swapcode(TYPE, parmi, parmj, n) { \
  long i = (n) / sizeof (TYPE);           \
  TYPE *pi = (TYPE *) (parmi);            \
  TYPE *pj = (TYPE *) (parmj);            \
  do {                                    \
    TYPE t = *pi;                         \
    *pi++ = *pj;                          \
    *pj++ = t;                            \
  } while (--i > 0);                      \
}

#define SWAPINIT(a, es) swaptype = ((char *) a - (char *)0) % sizeof(long) || \
  es % sizeof(long) ? 2 : es == sizeof(long) ? 0 : 1;

#define swap(a, b, es, swaptype) \
  if (swaptype == 0) {           \
    long t = *(long *)(a);       \
    *(long *)(a) = *(long *)(b); \
    *(long *)(b) = t;            \
  }                              \
  else                           \
    swapfunc(a, b, es, swaptype)

static void
swapfunc(char *a, char *b, int n, int swaptype)
{
  if(swaptype <= 1) 
    swapcode(long, a, b, n)
  else
    swapcode(char, a, b, n)
}

struct stack {
  int idx_begin;
  int idx_end;

  struct stack *next;
};

static void
stack_push(struct stack **top, int idx_begin, int idx_end)
{
  if (!top)
    return;

  struct stack *tmp = (struct stack *) malloc(sizeof(struct stack));
  memset(tmp, 0, sizeof(struct stack));

  tmp->idx_begin  = idx_begin;
  tmp->idx_end    = idx_end;

  if (!*top)
    *top = tmp;
  else {
    tmp->next = *top;
    *top      = tmp;
  }
}

static bool
stack_pop(struct stack **top, int *idx_begin, int *idx_end)
{
  if (!top || !*top || !idx_begin || !idx_end)
    return false;

  *idx_begin = (*top)->idx_begin;
  *idx_end   = (*top)->idx_end;

  struct stack *tmp = *top;
  *top = tmp->next;

  free(tmp);

  return true;
}

void
my_quicksort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
  srand(time(NULL));

  if (!width || !base || !compar)
    return;

  struct stack *st = NULL;
  stack_push(&st, 0, nel - 1);

  int idx_begin;
  int idx_end;

  int swaptype;
  SWAPINIT(base, width);

  while (st) {
    stack_pop(&st, &idx_begin, &idx_end);
    if (idx_end <= idx_begin)
      continue;

    size_t pivot = (idx_begin + (rand() % (idx_end - idx_begin + 1)));

    swap(((char *) base + (idx_begin * width)), (char *) base + (pivot * width), width, swaptype);

    void *key = (void *) ((char *) base + (idx_begin * width));

    int left  = idx_begin;
    int right = idx_end;

    while (left <= right) {
      while (compar((void *) ((char *) base + (left  * width)), key) < 0) ++left;
      while (compar((void *) ((char *) base + (right * width)), key) > 0) --right;
      if (left <= right) {
        swap(((char *) base + (left * width)), (char *) base + (right * width), width, swaptype);
        ++left;
        --right;
      }
    }

    stack_push(&st, idx_begin, right);
    stack_push(&st, left, idx_end);
  }
}
