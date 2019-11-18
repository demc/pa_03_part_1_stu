/** 
 * Test 2 
 *
 * Tests that oddly shaped size requests are placed in regular size blocks.
 * Strings and placed into the requested space, one string is freed.
 */
#include <stdio.h>
#include <string.h>
#include "alloc.h"

int main()
{
  printf("~~ Heap Allocator Test 2 ~~\n\n");

  cis20_init();

  void *p0 = cis20_alloc(11);
  void *p1 = cis20_alloc(5);
  void *p2 = cis20_alloc(19);

  strcpy(p0, "p0");
  strcpy(p1, "p1");
  strcpy(p2, "p2");

  cis20_traverse_heap();
  cis20_free(p1);
  cis20_traverse_heap();

  cis20_deinit();
}


