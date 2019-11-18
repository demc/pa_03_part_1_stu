#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memlib.h"
#define ALIGNMENT 8
#define MIN_BLOCK_SIZE 24

/**
 *HEAP STATE
 */
char *heap_begin;
char *heap_end;

/**
 *PRIVATE HELPER FUNCTIONS
 */

/**
 *Given a size and whether the block is allocated, returns the encoded header.
 */
size_t make_header(size_t size, size_t alloc)
{
    return size | alloc;
}

/**
 *Given a pointer to a header/footer, returns true if the block is allocated.
 */
size_t is_allocated(void *header_ptr)
{
    return (*((size_t *) header_ptr)) & 0x1;
}

/**
 *Given a pointer to a header/footer, returns the TOTAL size of the block.
 */
size_t get_size(void *header_ptr)
{
    return (*((size_t *) header_ptr)) & ~0x7;
}

/**
 *Given a pointer to a header/footer, returns the data storage size in the block. 
 */
size_t get_capacity(void *header_ptr)
{
    long size = get_size(header_ptr);

    // Subtract space for header and footer.
    return size - sizeof(size_t) * 2;
}

/**
 *Given a pointer to a header, return the data storage pointer within a block.
 */
void *get_data_addr(void *header_ptr)
{
    // data resides at base addr + header size
    return header_ptr + sizeof(size_t);
}

/**
 *Given a number, returns the closest number divisibly by 8.
 *Blocks (header + footer + data) must be 8 byte aligned.
 */
size_t closest_block_size(size_t numbytes)
{
    while (numbytes % ALIGNMENT != 0)
    {
        numbytes += 1;
    }

    return numbytes;
}

/**
 *Prints the last three digits of an address.
 *Useful for keeping tests simple.
 */
void print_short_address(void *ptr)
{
    unsigned long short_ptr = (unsigned long) ptr;
    short_ptr &= 0xFFF;
    printf("0x%03lx", short_ptr);
}

/**
 *Given a header, block size, and allocated, writes both a header and footer
 *into the block. Uses the block size to determine where the header is located.
 */
void block_write_hf(char *header_ptr, size_t block_size, size_t alloc)
{
    // Write header
    size_t *block_header = (size_t *) header_ptr;
    *block_header = make_header(block_size, alloc);

    // Write footer
    size_t *block_footer = (size_t *)(header_ptr + block_size - sizeof(size_t));
    *block_footer = make_header(block_size, alloc);
}

/**
 *Splits the provided block if possible given the number of bytes needed.
 *Returns the block size post split. 
 *If the block is not split, returns the original size. 
 *Assume that request_size includes space for the header and footer already!
 */
size_t block_split(char *header_ptr, size_t request_size)
{
    size_t size = get_size(header_ptr);
    size_t diff = size - request_size;

    // TODO: implement split
    
    // If the block is not able to be split.
    return size;
}

/**
 *Coalesces blocks before and after the given block.
 *Returns a pointer to the new block.
 *Will free any block given to this function.
 */
void block_coalesce(void *ptr)
{
    // TODO: implement coalesce
}

/**
 *Headers and footers are implemented as integers.
 */
void cis20_init()
{
    // Intialize memory library.
    mem_init();
    
    // TODO: intialize first heap block
    // Allocate first free list item.
    // Request 16 bytes (8 header + 8 data + 8 footer).
    // Must be 8 byte aligned.

    // Remember: low => high
    heap_begin = mem_heap_lo();
    heap_end = mem_heap_hi();

    printf("Initializing heap...\n");
    printf("BEGIN: ");
    print_short_address(heap_begin);
    printf(", END: ");
    print_short_address(heap_end);
    printf(", SIZE: %lu\n\n", mem_heapsize());
}

void cis20_deinit()
{
    // Deinit memory library.
    mem_deinit();
}

void *cis20_alloc(size_t numbytes)
{
    // TODO: convert pseudocode
    return NULL;
}

void cis20_free(void *data_ptr)
{
    // TODO: convert pseudocode
}

void cis20_traverse_heap()
{
    char *current_header = heap_begin;

    printf("- Heap State - size: %lu bytes --------------------\n", mem_heapsize());
    printf("---------------------------------------------------\n");

    while (current_header < heap_end)
    {
        int size = get_size(current_header);
        int alloc = is_allocated(current_header);
        long data_size = size - sizeof(size_t) * 2;
        char data[data_size + 1];
        memcpy(data, current_header + sizeof(size_t), data_size);
        data[data_size] = '\0';

        print_short_address(current_header);
        printf("\t size: %d  data size: %ld  alloc: %d\n", size, data_size, alloc);

        printf("\t hdr: 0x%x ftr: 0x%x\n", *current_header, *(current_header + data_size + sizeof(size_t)));
        printf("\t data: %s ", data);

        // If the block is unallocated, notify.
        if (alloc == 0)
        {
            printf("(junk)");
        }

        printf("\n");
        printf("---------------------------------------------------\n");

        if (size == 0)
        {
            break;
        }

        current_header += size;
    }

    printf("\n");
}