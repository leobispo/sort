#include "mergesort.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct queue_element {
  void *element;
  struct queue_element *next;
};

struct queue {
  struct queue_element *head;
  struct queue_element *tail;
};

static void
copyfunc(char *a, char *b, int copytype)
{
  if (copytype <= 1)
    (*(long *) a) = (long) b;
  else
    (*(char *) a) = (long) b;
}

static bool
queue_enqueue(struct queue *q, void *element)
{
  if (!q || !element)
    return false;

  struct queue_element *el = (struct queue_element *) malloc(sizeof(struct queue_element));
  memset(el, 0, sizeof(struct queue_element));
  el->element = element;

  if (!q->head)
    q->head = q->tail = el;
  else {
    q->tail->next = el;
    q->tail       = el;
  }

  return true;
}

static void *
queue_dequeue(struct queue *q)
{
  if (!q || !q->head)
    return NULL;

  void *element = q->head->element;

  struct queue_element *next = q->head->next;
  free(q->head);
  q->head = next;

  return element;
}


static void
merge(void *base, size_t width, int (*compar)(const void *, const void *), size_t left_begin, size_t left_end,
  size_t right_begin, size_t right_end, int copytype)
{
  struct queue right = { 0 };
  struct queue left  = { 0 };

  size_t i;
  for (i = left_begin; i < left_end; ++i)
    queue_enqueue(&left, (void *) *(long *) ((char *) base + (i  * width)));

  for (i = right_begin; i < right_end; ++i)
    queue_enqueue(&right, (void *) *(long *) ((char *) base + (i  * width)));


  void *left_ptr  = queue_dequeue(&left);
  void *right_ptr = queue_dequeue(&right);
  for (i = left_begin; i < right_end; ++i) {
    if (!left_ptr || !right_ptr)
      break;

    if (compar(&left_ptr, &right_ptr) < 0) {
      copyfunc(((char *) base + (i  * width)), (char *) left_ptr, copytype);
      left_ptr = queue_dequeue(&left);
    }
    else {
      copyfunc(((char *) base + (i  * width)), (char *) right_ptr, copytype);
      right_ptr = queue_dequeue(&right);
    }
  }

  while (left_ptr) {
    copyfunc(((char *) base + (i++  * width)), (char *) left_ptr, copytype);
    left_ptr = queue_dequeue(&left);
  }

  while (right_ptr) {
    copyfunc(((char *) base + (i++  * width)), (char *) right_ptr, copytype);
    right_ptr = queue_dequeue(&right);
  }
}

void
my_mergesort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
  ///////////////////////////
  // TOP DOWN
  //
  //      {5 4 2 8 7 3}
  //   {5 4 2}     {8 7 3}
  //  {5 4}  {2}  {8 7}  {3}
  // {5} {4} {2} {8} {7} {3}
  //   4 5    2    7 8    3
  //    2 4 5       3 7 8
  //       2 3 4 5 7 8
  //
  ///////////////////////////
  // BOTTOM UP
  //
  //    {5 4 2 8 7 3 1}
  // {4 5} {2 8} {3 7} {1}
  //  {2 4 5 8}   {1 3 7}
  //    {1 2 3 4 5 7 8}
  //
  ///////////////////////////

  int copytype = ((char *) base - (char *)0) % sizeof(long) || width % sizeof(long) ? 2 : width == sizeof(long) ? 0 : 1;

  if (nel < 2)
    return;

  size_t step = 1;

  while (step < nel) {
    size_t left   = 0;
    size_t right  = step;
    while (right + step <= nel) {
      merge(base, width, compar, left, left + step, right, right + step, copytype);
      left  = right + step;
      right = left  + step; 
    }

    if (right < nel)
      merge(base, width, compar, left, left + step, right, nel - 1, copytype);
 
    step *= 2;
  }
}
