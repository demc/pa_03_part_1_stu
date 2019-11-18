/**
 * Test 1 
 *
 * This is a sanity check for the heap allocator.
 * 10 strings a allocated to the heap and printed.
 */
#include <stdio.h>
#include <string.h>
#include "alloc.h"

int main()
{
  printf("~~ Heap Allocator Test 1 ~~\n\n");

  cis20_init();

  // Store 10 tiny strings onto the heap
  for (int i = 0; i < 10; i++)
  {
    void *ptr = cis20_alloc(8);
    if (ptr != NULL)
    {
      sprintf(ptr, "test %d", i); 
    }
  }

  cis20_traverse_heap();

  cis20_deinit();
}

