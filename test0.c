/**
 * Test 0
 * 
 * This tests that the heap can be created and destroyed.
 */
#include <stdio.h>
#include "alloc.h"

int main()
{
    printf("~~ Heap Allocator Test 0 ~~\n\n");
    
    // Initialize library.
    cis20_init();
    
    // Deinitialize library.
    cis20_deinit();
}