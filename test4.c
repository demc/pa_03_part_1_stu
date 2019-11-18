/**
 * Test 4
 *
 * Tests that blocks are coalesced forward when necessary.
 */
#include <stdio.h>
#include <string.h>
#include "alloc.h"

int main()
{
  printf("~~ Heap Allocator Test 4 ~~\n\n");
  
  cis20_init();
  
  // Create 5 small blocks.
  void *p0 = cis20_alloc(8);
  void *p1 = cis20_alloc(8);
  void *p2 = cis20_alloc(8);
  void *p3 = cis20_alloc(8);
  void *p4 = cis20_alloc(8);
  
  strcpy(p0, "first");
  strcpy(p1, "second");
  strcpy(p2, "third");
  strcpy(p3, "fourth");
  strcpy(p4, "fifth");
  
  cis20_traverse_heap();
  
  // Check coalescing forward.
  cis20_free(p4);
  cis20_free(p3);
  cis20_traverse_heap();
  
  cis20_deinit();
}


