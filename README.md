# Simple Memory Allocator in C

This project implements a basic memory allocator in C, which manages a fixed-size memory block and provides functions for memory allocation (`my_malloc`), memory deallocation (`my_free`), and a utility function to print allocated blocks (`print_allocated_blocks`).

## Files

* **allocator.c**: Contains the implementation of the memory allocator functions.
* **allocator.h**: Header file declaring the memory allocator functions and structures.

## Compilation

To compile the program, use a C compiler compatible with your system (e.g., GCC for Unix-like systems or MinGW for Windows):

``gcc -o allocator allocator.c``

## Usage

### Initialization

Before using the memory allocator, initialize it using `initialize_allocator()` function. This function sets up internal structures needed for memory management.

```c
initialize_allocator();
```
## Memory Allocation

Allocate memory using `my_malloc(size_t size)` function. It returns a pointer to the allocated memory block or `NULL` if allocation fails.

```c
int *ptr = (int *)my_malloc(sizeof(int));
if (ptr == NULL) {
    // Handle allocation failure
} else {
    // Use the allocated memory
    *ptr = 10;
}
```
## Memory Deallocation

Free allocated memory using `my_free(void *ptr)` function. Pass the pointer returned by `my_malloc()` to release the allocated memory.

```c
my_free(ptr);
```

## Printing Allocated Blocks

For debugging purposes, use `print_allocated_blocks()` function to print the list of currently allocated memory blocks.

```c
print_allocated_blocks();
```
## Notes

- This is a basic implementation for educational purposes and may not be suitable for production environments.
- Error handling is minimal in this example. Consider adding more robust error checking and handling in a real-world application.
- The memory allocator manages a fixed-size memory block (`MEMORY_SIZE`), which can be adjusted as needed for specific requirements.
