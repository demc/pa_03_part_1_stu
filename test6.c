/**
 * Test 6
 *  
 * Try to free all the blocks in the order of
 * head block then tail block, one by one.
 * 
 * Then try 3 splits.
 */
#include <stdio.h>
#include <string.h>
#include "alloc.h"

int main()
{
  printf("~~ Heap Allocator Test 6 ~~\n\n");
  
  cis20_init();
  
  // Create 5 small blocks.
  void *p0 = cis20_alloc(8);
  void *p1 = cis20_alloc(10);
  void *p2 = cis20_alloc(20);
  void *p3 = cis20_alloc(37);
  void *p4 = cis20_alloc(12);
  void *p5 = cis20_alloc(8);
  void *p6 = cis20_alloc(27);
  
  strcpy(p0, "first");
  strcpy(p1, "second");
  strcpy(p2, "third");
  strcpy(p3, "fourth");
  strcpy(p4, "fifth");
  strcpy(p5, "sixth");
  strcpy(p6, "seventh");
  
  cis20_traverse_heap();
  
  // Check coalescing backward.
  cis20_free(p0);
  cis20_free(p6);
  cis20_free(p1);
  cis20_free(p5);
  cis20_free(p2);
  cis20_free(p4);
  cis20_free(p3);

  cis20_traverse_heap();
  
  void *p7 = cis20_alloc(10);
  strcpy(p7, "split 1");
  cis20_traverse_heap();
  
  void *p8 = cis20_alloc(20);
  strcpy(p8, "split 2");
  cis20_traverse_heap();
  
  void *p9 = cis20_alloc(40);
  strcpy(p9, "split 3");
  cis20_traverse_heap();
  
  cis20_deinit();
}


