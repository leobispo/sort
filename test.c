#include "quicksort.h"
#include "mergesort.h"

static
int compare_int(const void *a, const void *b)
{
  return *((const int *) a) - *((const int *) b);
}

static
int compare_long(const void *a, const void *b)
{
  return *((const long *) a) - *((const long *) b);
}

static
int compare_str(const void *s1, const void *s2)
{
  char **a = (char **) s1;
  char **b = (char **) s2;

  return strcasecmp(*a, *b);
}


int main(int argc, char **argv)
{
  int merge_arr[] = { 5, 2, 7, 10, 15, 3, 20, 4, 8, 9, 12, 11, 22 };

  my_mergesort(merge_arr, (sizeof(merge_arr) / sizeof(int)), sizeof(int), compare_int);

  size_t i;
  for (i = 0; i < (sizeof(merge_arr) / sizeof(int)); ++i)
    printf("%u ", merge_arr[i]);

  printf("\n");

  char *merge_arr1[] = { "lmn", "abc", "def", "bcd", "opq" };

  my_quicksort(merge_arr1, (sizeof(merge_arr1) / sizeof(char *)), sizeof(char *), compare_str);

  for (i = 0; i < (sizeof(merge_arr1) / sizeof(char *)); ++i)
    printf("%s ", merge_arr1[i]);

  printf("\n");

  return 0;
}
