/* bsearch example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort, bsearch, NULL */

void *
bsearch_less (const void *key, const void *base, size_t nmemb, size_t size,
	 int (*compar) (const void *, const void *))
{
  int l, u, idx;
  const void *p;
  int comparison;

  l = 0;
  u = nmemb - 1;
  while (l <= u)
  {
      idx = (l + u) / 2;
      p = (void *) (((const char *) base) + (idx * size));
      comparison = (*compar) (key, p);
      if (comparison < 0)
         u = idx - 1;
      else if (comparison > 0)
         l = idx + 1;
      else
         return (idx == 0) ? NULL : (void *) (((const char *) p) - size);
  }

  return (u < 0) ? NULL : (void *) (((const char *) base) + (u * size));
}

void *
bsearch_more(const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar) (const void *, const void *))
{
  int l, u, idx;
  const void *p;
  int comparison;

  l = 0;
  u = nmemb - 1;
  while (l <= u)
  {
      idx = (l + u) / 2;
      p = (void *) (((const char *) base) + (idx * size));
      comparison = (*compar) (key, p);
      if (comparison < 0)
         u = idx - 1;
      else if (comparison > 0)
         l = idx + 1;
      else
         return (idx == u) ? NULL : (void *) (((const char *) p) + size);
  }

  return (l > nmemb - 1) ? NULL : (void *) (((const char *) base) + (l * size));
}


int compareints (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

//int values[] = { 50, 20, 60, 40, 10, 30 };
int values[] = { 50, 20, 60, 30, 10, 30 };

void test_bsearch_less(int key)
{
  int* pItem = (int*) bsearch_less (&key, values, 6, sizeof (int), compareints);
  if (pItem!=NULL)
    printf ("%d is nearest less than %d int the array.\n",*pItem, key);
  else
    printf ("no key is less than %d in the array.\n",key);
}

void test_bsearch(int key)
{
  int* pItem = (int*) bsearch (&key, values, 6, sizeof (int), compareints);
  if (pItem!=NULL)
    printf ("%d is in the array.\n",*pItem);
  else
    printf ("%d is not in the array.\n",key);

}

void test_bsearch_more(int key)
{
  int* pItem = (int*) bsearch_more(&key, values, 6, sizeof (int), compareints);
  if (pItem!=NULL)
    printf ("%d is nearest more than %d int the array.\n",*pItem, key);
  else
    printf ("no key is more than %d in the array.\n",key);
}

void print_values(int* base, size_t nmemb)
{
  printf("values: ");
  for (size_t i = 0; i < nmemb; ++i)
  {
    printf("%d ", *(base+i));
  }
  printf("\n");
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    printf("usage: ./bsearch_example num\n");
    return -1;
  }

  int key = atoi(argv[1]);
  qsort (values, 6, sizeof (int), compareints);
  
  print_values(values,6);  

  test_bsearch(key); 
  test_bsearch_less(key); 
  test_bsearch_more(key); 
  return 0;
}

