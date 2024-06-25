#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEMORY_SIZE 1024

static uint8_t memory[MEMORY_SIZE];

typedef struct {
    size_t size;
    uint8_t *ptr;
} mem_block;

mem_block *allocated_blocks = NULL;

void initialize_allocator() {
    allocated_blocks = NULL;
}

void *my_malloc(size_t size) {
    mem_block *new_block = NULL;
    uint8_t *alloc_ptr = memory;
    size_t remaining_size = MEMORY_SIZE;

    while (alloc_ptr < memory + MEMORY_SIZE) {
        if (*(alloc_ptr) == 0) {
            size_t block_size = *((size_t *)(alloc_ptr + 1));
            if (block_size >= size + sizeof(size_t)) {
                new_block = (mem_block *)alloc_ptr;
                new_block->size = size;
                new_block->ptr = alloc_ptr + sizeof(size_t);
                *((size_t *)(alloc_ptr + 1)) = size;

                *alloc_ptr = 1;

                remaining_size = block_size - size - sizeof(size_t);

                if (remaining_size > sizeof(size_t)) {
                    mem_block *next_block = (mem_block *)(alloc_ptr + sizeof(size_t) + size);
                    next_block->size = remaining_size - sizeof(size_t);
                    next_block->ptr = alloc_ptr + sizeof(size_t) + size + sizeof(size_t);
                    *((size_t *)(alloc_ptr + 1 + sizeof(size_t) + size)) = remaining_size - sizeof(size_t);
                }
                break;
            }
        }
        alloc_ptr += sizeof(size_t) + *((size_t *)(alloc_ptr + 1));
    }
    return new_block ? new_block->ptr : NULL;
}

void my_free(void *ptr) {
    if (ptr == NULL) return;

    uint8_t *alloc_ptr = (uint8_t *)ptr - sizeof(size_t);
    *alloc_ptr = 0;
}

void print_allocated_blocks() {
    mem_block *current = allocated_blocks;
    printf("Allocated Blocks:\n");
    while (current != NULL) {
        printf("Address: %p, Size: %lu\n", current->ptr, current->size);
        current = (mem_block *)current->ptr;
    }
    printf("\n");
}

int main() {
    initialize_allocator();

    int *ptr1 = (int *)my_malloc(sizeof(int));
    print_allocated_blocks();

    my_free(ptr1);
    print_allocated_blocks();

    return 0;
}
