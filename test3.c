/**
 * Test 3
 *
 * Tests that blocks are split when necessary.
 */
#include <stdio.h>
#include <string.h>
#include "alloc.h"

int main()
{
  printf("~~ Heap Allocator Test 3 ~~\n\n");

  cis20_init();
  
  // Fill the default first block.
  void *p0 = cis20_alloc(8);

  // Create a large block.
  void *p1 = cis20_alloc(64);

  // Create a small block.
  void *p2 = cis20_alloc(8);

  strcpy(p0, "first");
  strcpy(p1, "second");
  strcpy(p2, "third");
  
  cis20_traverse_heap();
  
  // Free a block to create empty space in the heap.
  cis20_free(p1);

  // Create a small block. Should cause splitting.
  void *p3 = cis20_alloc(8);
  strcpy(p3, "SPLIT!");

  cis20_traverse_heap(); 
  
  // Create another large block. Should fit between blocks.
  void *p4 = cis20_alloc(40);
  strcpy(p4, "THIS SHOULD FIT PERFECTLY!");
  
  cis20_traverse_heap(); 
  
  cis20_deinit();
}

