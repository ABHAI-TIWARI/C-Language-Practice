/*****************************************************************************
 * C Language Tutorial: Memory Layout
 * 
 * This file demonstrates the memory layout of a C program, covering:
 * - Text/Code Segment
 * - Data Segment (Initialized Data)
 * - BSS Segment (Uninitialized Data)
 * - Heap Segment
 * - Stack Segment
 * - Memory allocation functions (malloc, calloc, realloc, free)
 * - Common memory errors (segmentation fault, memory leak, dangling pointer)
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* =========================================================================
 * GLOBAL VARIABLES - Reside in Data Segment or BSS Segment
 * ========================================================================= */

// Initialized global variables -> Data Segment
int global_init = 42;
float global_float = 3.14;
char global_char = 'A';

// Uninitialized global variables -> BSS Segment
int global_uninit;
static int static_uninit;
long global_long;

// Constant variables -> Typically in Text Segment (read-only)
const int CONST_VALUE = 100;

/* =========================================================================
 * FUNCTION TO DEMONSTRATE STACK MEMORY
 * ========================================================================= */

// Recursive function to demonstrate stack growth
void recursive_function(int depth) {
    char stack_array[100];  // Allocated on stack
    int i;
    
    // Fill array with pattern
    for (i = 0; i < 100; i++) {
        stack_array[i] = depth + i;
    }
    
    printf("Recursion depth: %d, stack_array[0] = %d, address: %p\n", 
           depth, stack_array[0], (void *)stack_array);
    
    if (depth > 0) {
        recursive_function(depth - 1);
    }
}

/* =========================================================================
 * FUNCTION TO DEMONSTRATE HEAP MEMORY
 * ========================================================================= */

void demonstrate_heap() {
    int *ptr1, *ptr2, *ptr3;
    int i;
    
    printf("\n--- Heap Memory Allocation ---\n\n");
    
    // malloc: Allocate memory, uninitialized
    printf("1. malloc() - Allocates uninitialized memory\n");
    ptr1 = (int *)malloc(5 * sizeof(int));
    if (ptr1 == NULL) {
        printf("   Memory allocation failed!\n");
        return;
    }
    printf("   Allocated 5 integers at address: %p\n", (void *)ptr1);
    
    // Initialize allocated memory
    for (i = 0; i < 5; i++) {
        ptr1[i] = i * 10;
    }
    printf("   Values: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", ptr1[i]);
    }
    printf("\n");
    
    // calloc: Allocate and zero-initialize memory
    printf("\n2. calloc() - Allocates and initializes to zero\n");
    ptr2 = (int *)calloc(5, sizeof(int));
    if (ptr2 == NULL) {
        printf("   Memory allocation failed!\n");
        free(ptr1);
        return;
    }
    printf("   Allocated 5 integers at address: %p\n", (void *)ptr2);
    printf("   Values: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", ptr2[i]);
    }
    printf("\n");
    
    // realloc: Resize previously allocated memory
    printf("\n3. realloc() - Resizes allocated memory\n");
    printf("   Original ptr1: %p with 5 elements\n", (void *)ptr1);
    ptr3 = (int *)realloc(ptr1, 10 * sizeof(int));
    if (ptr3 == NULL) {
        printf("   Reallocation failed!\n");
        free(ptr1);
        free(ptr2);
        return;
    }
    printf("   New address: %p with 10 elements\n", (void *)ptr3);
    
    // Initialize new elements
    for (i = 5; i < 10; i++) {
        ptr3[i] = i * 10;
    }
    printf("   Values: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", ptr3[i]);
    }
    printf("\n");
    
    // free: Release allocated memory
    printf("\n4. free() - Releases allocated memory\n");
    free(ptr3);
    free(ptr2);
    printf("   Memory freed successfully\n");
}

/* =========================================================================
 * FUNCTION TO DEMONSTRATE MEMORY SEGMENTS
 * ========================================================================= */

void demonstrate_segments() {
    // Local variables -> Stack Segment
    int local_var = 100;
    char local_char = 'B';
    
    // Dynamically allocated -> Heap Segment
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 200;
    
    printf("\n--- Memory Segments ---\n\n");
    
    printf("1. TEXT SEGMENT (Code):\n");
    printf("   Contains: Executable instructions, read-only data\n");
    printf("   Example: This function's machine code\n");
    printf("   Address of CONST_VALUE: %p, Value: %d\n", 
           (void *)&CONST_VALUE, CONST_VALUE);
    
    printf("\n2. DATA SEGMENT (Initialized Global/Static):\n");
    printf("   Contains: Initialized global and static variables\n");
    printf("   Address of global_init: %p, Value: %d\n", 
           (void *)&global_init, global_init);
    printf("   Address of global_float: %p, Value: %.2f\n", 
           (void *)&global_float, global_float);
    printf("   Address of global_char: %p, Value: %c\n", 
           (void *)&global_char, global_char);
    
    printf("\n3. BSS SEGMENT (Uninitialized Global/Static):\n");
    printf("   Contains: Uninitialized global and static variables\n");
    printf("   Address of global_uninit: %p, Value: %d\n", 
           (void *)&global_uninit, global_uninit);
    printf("   Address of static_uninit: %p, Value: %d\n", 
           (void *)&static_uninit, static_uninit);
    printf("   Address of global_long: %p, Value: %ld\n", 
           (void *)&global_long, global_long);
    
    printf("\n4. HEAP SEGMENT (Dynamic Allocation):\n");
    printf("   Contains: Dynamically allocated memory\n");
    printf("   Address of heap_var: %p, Value: %d\n", 
           (void *)heap_var, *heap_var);
    
    printf("\n5. STACK SEGMENT (Local Variables):\n");
    printf("   Contains: Local variables, function parameters, return addresses\n");
    printf("   Address of local_var: %p, Value: %d\n", 
           (void *)&local_var, local_var);
    printf("   Address of local_char: %p, Value: %c\n", 
           (void *)&local_char, local_char);
    
    free(heap_var);
}

/* =========================================================================
 * FUNCTION TO DEMONSTRATE MEMORY ERRORS
 * ========================================================================= */

void demonstrate_memory_errors() {
    printf("\n--- Common Memory Errors ---\n\n");
    
    // 1. Segmentation Fault - Accessing invalid memory
    printf("1. SEGMENTATION FAULT\n");
    printf("   Cause: Accessing memory that doesn't belong to the program\n");
    printf("   Example: Dereferencing a NULL or invalid pointer\n");
    printf("   Note: This would crash the program, so we only explain it\n\n");
    
    // 2. Memory Leak - Not freeing allocated memory
    printf("2. MEMORY LEAK\n");
    printf("   Cause: Allocating memory but never freeing it\n");
    printf("   Example:\n");
    int *leak_ptr = (int *)malloc(10 * sizeof(int));
    printf("      Allocated memory at: %p\n", (void *)leak_ptr);
    printf("      If we don't call free(), this memory is leaked\n");
    printf("      The program loses the pointer to this memory\n");
    // Note: We're NOT freeing leak_ptr here to demonstrate the concept
    // In real code, ALWAYS free allocated memory
    
    // 3. Dangling Pointer - Using pointer after free
    printf("\n3. DANGLING POINTER\n");
    printf("   Cause: Using a pointer after the memory it points to is freed\n");
    printf("   Example:\n");
    int *dangling_ptr = (int *)malloc(sizeof(int));
    *dangling_ptr = 100;
    printf("      Allocated memory at: %p, Value: %d\n", 
           (void *)dangling_ptr, *dangling_ptr);
    free(dangling_ptr);
    printf("      Freed the memory\n");
    printf("      WARNING: Accessing *dangling_ptr now is undefined behavior!\n");
    // We set to NULL to prevent accidental use
    dangling_ptr = NULL;
    
    // 4. Double Free - Freeing memory twice
    printf("\n4. DOUBLE FREE\n");
    printf("   Cause: Calling free() on the same pointer twice\n");
    printf("   Example:\n");
    int *double_free_ptr = (int *)malloc(sizeof(int));
    printf("      Allocated memory at: %p\n", (void *)double_free_ptr);
    free(double_free_ptr);
    printf("      Freed the memory once\n");
    printf("      WARNING: Freeing again would cause undefined behavior!\n");
    // Setting to NULL after free prevents double free
    double_free_ptr = NULL;
    
    // 5. Buffer Overflow - Writing beyond allocated memory
    printf("\n5. BUFFER OVERFLOW\n");
    printf("   Cause: Writing more data than allocated\n");
    printf("   Example:\n");
    int *buffer = (int *)malloc(5 * sizeof(int));
    printf("      Allocated array of 5 integers at: %p\n", (void *)buffer);
    printf("      Valid indices: 0 to 4\n");
    printf("      Writing to buffer[5] would be a buffer overflow!\n");
    free(buffer);
}

/* =========================================================================
 * FUNCTION TO SHOW MEMORY LAYOUT VISUALIZATION
 * ========================================================================= */

void visualize_memory_layout() {
    printf("\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |             C PROGRAM MEMORY LAYOUT              |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                                                  |\n");
    printf("  |  Higher Addresses        Lower Addresses         |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |             ARGUMENTS & ENVIRONMENT               |\n");
    printf("  |--------------------------------------------------|\n");
    printf("  |                                                  |\n");
    printf("  |                   STACK                          |\n");
    printf("  |     (Grows Downward)                            |\n");
    printf("  |  - Local variables                              |\n");
    printf("  |  - Function parameters                          |\n");
    printf("  |  - Return addresses                             |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                                                  |\n");
    printf("  |                   HEAP                           |\n");
    printf("  |     (Grows Upward)                              |\n");
    printf("  |  - malloc(), calloc(), realloc()                 |\n");
    printf("  |  - Dynamic memory allocation                    |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                  BSS                             |\n");
    printf("  |  - Uninitialized global variables               |\n");
    printf("  |  - Zero-initialized by OS                       |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                 DATA                             |\n");
    printf("  |  - Initialized global variables                 |\n");
    printf("  |  - Initialized static variables                 |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                 TEXT                             |\n");
    printf("  |  - Executable instructions                       |\n");
    printf("  |  - Read-only data (string literals, const)       |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  |                                                  |\n");
    printf("  |  Lower Addresses        Higher Addresses         |\n");
    printf("  |                                                  |\n");
    printf("  +--------------------------------------------------+\n");
    printf("\n");
}

/* =========================================================================
 * MAIN FUNCTION
 * ========================================================================= */

int main() {
    printf("\n====================================================\n");
    printf("     C MEMORY LAYOUT TUTORIAL\n");
    printf("====================================================\n");
    
    // Display memory layout visualization
    visualize_memory_layout();
    
    // Demonstrate different memory segments
    demonstrate_segments();
    
    // Demonstrate stack memory
    printf("\n--- Stack Memory ---\n\n");
    printf("Demonstrating stack growth with recursion:\n");
    recursive_function(3);
    
    // Demonstrate heap memory
    demonstrate_heap();
    
    // Demonstrate memory errors
    demonstrate_memory_errors();
    
    printf("\n====================================================\n");
    printf("     KEY TAKEAWAYS:\n");
    printf("====================================================\n");
    printf("  1. TEXT segment: Contains program code (read-only)\n");
    printf("  2. DATA segment: Initialized global/static variables\n");
    printf("  3. BSS segment:  Uninitialized global/static variables\n");
    printf("  4. HEAP segment:  Dynamically allocated memory\n");
    printf("  5. STACK segment: Local variables and function calls\n");
    printf("\n");
    printf("  - Stack grows DOWNWARD (toward lower addresses)\n");
    printf("  - Heap grows UPWARD (toward higher addresses)\n");
    printf("  - Always free() what you malloc()\n");
    printf("  - Check for NULL after malloc()\n");
    printf("  - Set pointers to NULL after free()\n");
    printf("\n====================================================\n\n");
    
    return 0;
}
