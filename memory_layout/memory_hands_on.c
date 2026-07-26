/*****************************************************************************
 * C Memory Layout - Hands-On Practical Tutorial
 * 
 * This hands-on tutorial demonstrates:
 * - Size of all C data types
 * - Increasing .data segment (initialized globals)
 * - Increasing .bss segment (uninitialized globals)
 * - Heap allocation and deallocation
 * - Stack size modification
 * - Memory segment visualization with sizes
 * - Using size command to verify segments
 * 
 * Compile with: gcc memory_hands_on.c -o memory_hands_on
 * Check segments with: size memory_hands_on
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* =========================================================================
 * PART 1: SIZE OF ALL DATA TYPES
 * ========================================================================= */

void print_data_type_sizes() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 1: SIZE OF ALL C DATA TYPES (in bytes)\n");
    printf("================================================================\n\n");
    
    printf("--- Basic Data Types ---\n");
    printf(" sizeof(char)           = %2zu bytes\n", sizeof(char));
    printf(" sizeof(signed char)   = %2zu bytes\n", sizeof(signed char));
    printf(" sizeof(unsigned char) = %2zu bytes\n", sizeof(unsigned char));
    printf(" sizeof(short)          = %2zu bytes\n", sizeof(short));
    printf(" sizeof(unsigned short) = %2zu bytes\n", sizeof(unsigned short));
    printf(" sizeof(int)            = %2zu bytes\n", sizeof(int));
    printf(" sizeof(unsigned int)   = %2zu bytes\n", sizeof(unsigned int));
    printf(" sizeof(long)           = %2zu bytes\n", sizeof(long));
    printf(" sizeof(unsigned long)  = %2zu bytes\n", sizeof(unsigned long));
    printf(" sizeof(long long)      = %2zu bytes\n", sizeof(long long));
    printf(" sizeof(unsigned long long) = %2zu bytes\n", sizeof(unsigned long long));
    
    printf("\n--- Floating Point Types ---\n");
    printf(" sizeof(float)          = %2zu bytes\n", sizeof(float));
    printf(" sizeof(double)         = %2zu bytes\n", sizeof(double));
    printf(" sizeof(long double)    = %2zu bytes\n", sizeof(long double));
    
    printf("\n--- Pointer Types ---\n");
    printf(" sizeof(char*)          = %2zu bytes\n", sizeof(char*));
    printf(" sizeof(int*)           = %2zu bytes\n", sizeof(int*));
    printf(" sizeof(void*)          = %2zu bytes\n", sizeof(void*));
    printf(" sizeof(float*)         = %2zu bytes\n", sizeof(float*));
    printf(" sizeof(double*)        = %2zu bytes\n", sizeof(double*));
    
    printf("\n--- Boolean Type ---\n");
    printf(" sizeof(_Bool)          = %2zu bytes\n", sizeof(_Bool));
    
    printf("\n--- Limits ---\n");
    printf(" CHAR_BIT               = %d\n", CHAR_BIT);
    printf(" CHAR_MIN               = %d\n", CHAR_MIN);
    printf(" CHAR_MAX               = %d\n", CHAR_MAX);
    printf(" SCHAR_MIN              = %d\n", SCHAR_MIN);
    printf(" SCHAR_MAX              = %d\n", SCHAR_MAX);
    printf(" UCHAR_MAX              = %u\n", UCHAR_MAX);
    printf(" SHRT_MIN               = %d\n", SHRT_MIN);
    printf(" SHRT_MAX               = %d\n", SHRT_MAX);
    printf(" USHRT_MAX              = %u\n", USHRT_MAX);
    printf(" INT_MIN                = %d\n", INT_MIN);
    printf(" INT_MAX                = %d\n", INT_MAX);
    printf(" UINT_MAX               = %u\n", UINT_MAX);
    printf(" LONG_MIN               = %ld\n", LONG_MIN);
    printf(" LONG_MAX               = %ld\n", LONG_MAX);
    printf(" ULONG_MAX              = %lu\n", ULONG_MAX);
    printf(" LLONG_MIN              = %lld\n", LLONG_MIN);
    printf(" LLONG_MAX              = %lld\n", LLONG_MAX);
    printf(" ULLONG_MAX             = %llu\n", ULLONG_MAX);
    
    printf("\n--- Derived Types ---\n");
    
    // Array sizes
    int arr[10];
    printf(" sizeof(int[10])        = %2zu bytes\n", sizeof(arr));
    printf(" sizeof(int[100])       = %2zu bytes\n", sizeof(int[100]));
    printf(" sizeof(int[1024])      = %2zu bytes\n", sizeof(int[1024]));
    
    // Structure sizes
    struct empty_struct {};
    printf(" sizeof(empty struct)   = %2zu bytes\n", sizeof(struct empty_struct));
    
    struct point {
        int x;
        int y;
    };
    printf(" sizeof(struct point)   = %2zu bytes\n", sizeof(struct point));
    
    struct aligned_struct {
        char a;
        int b;
        char c;
    };
    printf(" sizeof(aligned struct) = %2zu bytes\n", sizeof(struct aligned_struct));
    printf("   Note: Padding may be added for alignment\n");
    
    // Union sizes
    union test_union {
        char c;
        int i;
        double d;
    };
    printf(" sizeof(union)          = %2zu bytes (size of largest member)\n", sizeof(union test_union));
    
    // Pointer to array
    int (*ptr_to_arr)[10];
    printf(" sizeof(int (*)[10])     = %2zu bytes\n", sizeof(ptr_to_arr));
    
    // Function pointer
    int (*func_ptr)(int, int);
    printf(" sizeof(function ptr)   = %2zu bytes\n", sizeof(func_ptr));
}

/* =========================================================================
 * PART 2: INCREASING .DATA SEGMENT (Initialized Global Variables)
 * ========================================================================= */

// These variables will be stored in .data segment (initialized)
int data_int1 = 100;
int data_int2 = 200;
int data_int3 = 300;
float data_float = 3.14f;
double data_double = 2.71828;
char data_char = 'X';

// Large initialized array in .data
int data_large_array[100] = {0}; // All zeros - still .data

// String literals go to .rodata (read-only data section)
const char *data_string = "This is in .rodata segment";

// Initialized static variable - also .data
static int data_static = 42;

void demonstrate_data_segment() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 2: INCREASING .DATA SEGMENT\n");
    printf("================================================================\n\n");
    
    printf("The following variables are stored in .data segment:\n\n");
    
    printf(" Global initialized variables:\n");
    printf("   data_int1    = %d, address: %p\n", data_int1, (void *)&data_int1);
    printf("   data_int2    = %d, address: %p\n", data_int2, (void *)&data_int2);
    printf("   data_int3    = %d, address: %p\n", data_int3, (void *)&data_int3);
    printf("   data_float   = %.2f, address: %p\n", data_float, (void *)&data_float);
    printf("   data_double  = %.5f, address: %p\n", data_double, (void *)&data_double);
    printf("   data_char    = %c, address: %p\n", data_char, (void *)&data_char);
    
    printf("\n Initialized array (100 ints):\n");
    printf("   data_large_array[0] = %d, address: %p\n", data_large_array[0], (void *)data_large_array);
    printf("   data_large_array[99] = %d, address: %p\n", data_large_array[99], (void *)&data_large_array[99]);
    printf("   Total size: %zu bytes\n", sizeof(data_large_array));
    
    printf("\n Static initialized variable:\n");
    printf("   data_static = %d, address: %p\n", data_static, (void *)&data_static);
    
    printf("\n String literal (in .rodata):\n");
    printf("   data_string = \"%s\", address: %p\n", data_string, (void *)data_string);
    
    printf("\n To see .data size, run: size memory_hands_on\n");
    printf(" The .data segment contains all initialized non-zero global variables\n");
    printf(" Note: Zero-initialized globals go to .bss, not .data\n");
}

/* =========================================================================
 * PART 3: INCREASING .BSS SEGMENT (Uninitialized Global Variables)
 * ========================================================================= */

// These variables will be stored in .bss segment (uninitialized)
int bss_int1;                  // Uninitialized -> .bss
int bss_int2;                  // Uninitialized -> .bss
static int bss_static;         // Uninitialized static -> .bss
long bss_long;                 // Uninitialized -> .bss

// Zero-initialized variables also go to .bss
int bss_zero_int = 0;          // Zero-initialized -> .bss
static int bss_zero_static = 0; // Zero-initialized static -> .bss

// Large uninitialized array in .bss
int bss_large_array[1000];     // Uninitialized -> .bss
char bss_char_array[10000];   // Uninitialized -> .bss

void demonstrate_bss_segment() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 3: INCREASING .BSS SEGMENT\n");
    printf("================================================================\n\n");
    
    printf("The following variables are stored in .bss segment:\n\n");
    
    printf(" Uninitialized global variables:\n");
    printf("   bss_int1   = %d, address: %p\n", bss_int1, (void *)&bss_int1);
    printf("   bss_int2   = %d, address: %p\n", bss_int2, (void *)&bss_int2);
    printf("   bss_static = %d, address: %p\n", bss_static, (void *)&bss_static);
    printf("   bss_long   = %ld, address: %p\n", bss_long, (void *)&bss_long);
    
    printf("\n Zero-initialized variables (also in .bss):\n");
    printf("   bss_zero_int    = %d, address: %p\n", bss_zero_int, (void *)&bss_zero_int);
    printf("   bss_zero_static = %d, address: %p\n", bss_zero_static, (void *)&bss_zero_static);
    
    printf("\n Large uninitialized arrays:\n");
    printf("   bss_large_array[1000], address: %p, size: %zu bytes\n", 
           (void *)bss_large_array, sizeof(bss_large_array));
    printf("   bss_char_array[10000], address: %p, size: %zu bytes\n", 
           (void *)bss_char_array, sizeof(bss_char_array));
    
    printf("\n Key points:\n");
    printf("   - .bss contains uninitialized AND zero-initialized globals\n");
    printf("   - .bss is more memory-efficient (OS zeros it at startup)\n");
    printf("   - No storage space in the executable file for .bss\n");
    printf("   - To see .bss size, run: size memory_hands_on\n");
}

/* =========================================================================
 * PART 4: HEAP MEMORY - WITH HEAP ALLOCATION
 * ========================================================================= */

void demonstrate_with_heap() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 4: HEAP MEMORY - WITH HEAP ALLOCATION\n");
    printf("================================================================\n\n");
    
    printf("Dynamically allocating memory on the heap...\n\n");
    
    // Allocate different types on heap
    int *heap_int = (int *)malloc(sizeof(int));
    float *heap_float = (float *)malloc(sizeof(float));
    char *heap_char = (char *)malloc(sizeof(char));
    int *heap_array = (int *)malloc(100 * sizeof(int));
    
    *heap_int = 42;
    *heap_float = 3.14f;
    *heap_char = 'H';
    
    for (int i = 0; i < 100; i++) {
        heap_array[i] = i * 10;
    }
    
    printf(" Allocated on heap:\n");
    printf("   int   at %p, value: %d\n", (void *)heap_int, *heap_int);
    printf("   float at %p, value: %.2f\n", (void *)heap_float, *heap_float);
    printf("   char  at %p, value: %c\n", (void *)heap_char, *heap_char);
    printf("   array at %p, size: %zu bytes\n", (void *)heap_array, 100 * sizeof(int));
    
    // Verify values
    printf("\n First 5 elements of heap_array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", heap_array[i]);
    }
    printf("...\n");
    
    printf("\n Allocating more memory...\n");
    int *heap_large = (int *)malloc(10000 * sizeof(int));
    if (heap_large) {
        printf("   Allocated 10000 ints at %p\n", (void *)heap_large);
        free(heap_large);
    }
    
    // Free all allocated memory
    printf("\n Freeing heap memory...\n");
    free(heap_int);
    free(heap_float);
    free(heap_char);
    free(heap_array);
    
    printf("   All heap memory freed\n");
    printf("\n Heap allows dynamic memory allocation at runtime\n");
    printf(" Heap grows upward (toward higher addresses)\n");
}

/* =========================================================================
 * PART 5: HEAP MEMORY - WITHOUT HEAP ALLOCATION
 * ========================================================================= */

void demonstrate_without_heap() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 5: MEMORY USAGE - WITHOUT HEAP ALLOCATION\n");
    printf("================================================================\n\n");
    
    printf("Using only stack, data, and bss segments...\n\n");
    
    // All memory is on stack, data, or bss
    int local_stack_var = 100;
    char local_stack_char = 'S';
    
    printf(" Stack variables:\n");
    printf("   local_stack_var = %d, address: %p\n", local_stack_var, (void *)&local_stack_var);
    printf("   local_stack_char = %c, address: %p\n", local_stack_char, (void *)&local_stack_char);
    
    printf("\n Global variables (from .data and .bss):\n");
    printf("   data_int1 = %d, address: %p (.data)\n", data_int1, (void *)&data_int1);
    printf("   bss_int1 = %d, address: %p (.bss)\n", bss_int1, (void *)&bss_int1);
    
    printf("\n Accessing global arrays:\n");
    printf("   data_large_array[50] = %d, address: %p\n", data_large_array[50], (void *)&data_large_array[50]);
    printf("   bss_large_array[500] = %d, address: %p\n", bss_large_array[500], (void *)&bss_large_array[500]);
    
    printf("\n No dynamic allocation - program uses fixed memory layout\n");
    printf(" All memory determined at compile time\n");
    printf(" No risk of memory leaks or fragmentation\n");
}

/* =========================================================================
 * PART 6: CHANGING STACK SIZE
 * ========================================================================= */

// Function with large stack allocation
void large_stack_allocation(int size_mb) {
    // Allocate approximately size_mb megabytes on stack
    volatile char buffer[size_mb * 1024 * 1024];
    
    // Use the buffer to prevent optimization
    for (int i = 0; i < size_mb * 1024 * 1024; i++) {
        buffer[i] = i % 256;
    }
    
    printf(" Allocated %d MB on stack at address: %p\n", size_mb, (void *)buffer);
    printf(" First byte: %d, Last byte: %d\n", buffer[0], buffer[size_mb * 1024 * 1024 - 1]);
}

// Recursive function to demonstrate stack growth
int recursive_depth = 0;
void recursive_stack_test(int depth) {
    char local_buffer[1024]; // 1KB per call
    
    // Fill buffer
    for (int i = 0; i < 1024; i++) {
        local_buffer[i] = depth % 256;
    }
    
    recursive_depth++;
    printf("  Recursion depth: %d, stack address: %p\n", depth, (void *)local_buffer);
    
    if (depth < 5) {
        recursive_stack_test(depth + 1);
    }
}

void demonstrate_stack_size() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 6: CHANGING AND TESTING STACK SIZE\n");
    printf("================================================================\n\n");
    
    printf("Stack segment contains:\n");
    printf("  - Local variables\n");
    printf("  - Function parameters\n");
    printf("  - Return addresses\n");
    printf("  - Saved registers\n\n");
    
    printf("--- Testing Stack Growth with Recursion ---\n");
    recursive_depth = 0;
    recursive_stack_test(1);
    printf("  Maximum recursion depth reached: %d\n", recursive_depth);
    
    printf("\n--- Testing Large Stack Allocation ---\n");
    printf("WARNING: Large allocations may cause stack overflow!\n\n");
    
    // Try allocating 1MB on stack
    printf("Attempting 1MB stack allocation:\n");
    large_stack_allocation(1);
    
    // Note: On many systems, default stack size is 8MB
    // Allocating more will cause stack overflow
    // Uncomment at your own risk:
    // printf("Attempting 10MB stack allocation:\n");
    // large_stack_allocation(10); // This will likely crash!
    
    printf("\n Stack grows DOWNWARD (toward lower addresses)\n");
    printf(" Each function call creates a stack frame\n");
    printf(" Stack size is limited (typically 8MB on Linux)\n");
}

/* =========================================================================
 * PART 7: COMPARING SEGMENT SIZES
 * ========================================================================= */

void demonstrate_segment_sizes() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 7: COMPARING MEMORY SEGMENT SIZES\n");
    printf("================================================================\n\n");
    
    printf("To see actual segment sizes, compile and run:\n");
    printf("  gcc memory_hands_on.c -o memory_hands_on\n");
    printf("  size memory_hands_on\n\n");
    
    printf("Typical output:\n");
    printf("  text    data     bss     dec     hex filename\n");
    printf("  %d      %d       %d      %d      %x   memory_hands_on\n",
           100, 200, 300, 600, 600);
    printf("\n Where:\n");
    printf("  text = .text segment (code + read-only data)\n");
    printf("  data = .data segment (initialized globals)\n");
    printf("  bss  = .bss segment (uninitialized globals)\n");
    printf("  dec  = total in decimal\n");
    printf("  hex  = total in hexadecimal\n\n");
    
    printf("In this program:\n");
    printf("  .data contains: initialized global variables\n");
    printf("  .bss contains: uninitialized + zero-initialized globals\n");
    printf("  .text contains: all functions + string literals\n");
    printf("  heap: dynamic allocations (not in executable file)\n");
    printf("  stack: runtime allocations (not in executable file)\n");
    
    printf("\n--- Calculating Approximate Sizes ---\n\n");
    
    // Calculate approximate .data size
    size_t data_size = sizeof(data_int1) + sizeof(data_int2) + sizeof(data_int3) +
                       sizeof(data_float) + sizeof(data_double) + sizeof(data_char) +
                       sizeof(data_large_array) + sizeof(data_static) + sizeof(data_string);
    printf("Approximate .data segment usage: %zu bytes\n", data_size);
    
    // Calculate approximate .bss size
    size_t bss_size = sizeof(bss_int1) + sizeof(bss_int2) + sizeof(bss_static) +
                      sizeof(bss_long) + sizeof(bss_zero_int) + sizeof(bss_zero_static) +
                      sizeof(bss_large_array) + sizeof(bss_char_array);
    printf("Approximate .bss segment usage:  %zu bytes\n", bss_size);
    
    printf("\nNote: These are approximations. Actual sizes may vary due to\n");
    printf("      alignment, padding, and compiler optimizations.\n");
}

/* =========================================================================
 * PART 8: HANDS-ON EXERCISES
 * ========================================================================= */

void hands_on_exercises() {
    printf("\n");
    printf("================================================================\n");
    printf(" PART 8: HANDS-ON EXERCISES\n");
    printf("================================================================\n\n");
    
    printf("Exercise 1: Create a large global array\n");
    printf("  - Add: int huge_data[1000000] = {1}; to global scope\n");
    printf("  - Recompile and check .data size with 'size' command\n");
    printf("  - Observe how .data size increases\n\n");
    
    printf("Exercise 2: Create a large uninitialized global array\n");
    printf("  - Add: int huge_bss[1000000]; to global scope\n");
    printf("  - Recompile and check .bss size with 'size' command\n");
    printf("  - Observe how .bss size increases\n\n");
    
    printf("Exercise 3: Allocate memory on heap\n");
    printf("  - Modify demonstrate_with_heap() to allocate 10MB\n");
    printf("  - Use: malloc(10 * 1024 * 1024)\n");
    printf("  - Check memory usage with 'top' or 'htop' while running\n\n");
    
    printf("Exercise 4: Test stack overflow\n");
    printf("  - Create a recursive function without base case\n");
    printf("  - Or allocate a very large array on stack (100MB)\n");
    printf("  - Observe the stack overflow error\n\n");
    
    printf("Exercise 5: Memory leak detection\n");
    printf("  - Remove all free() calls in demonstrate_with_heap()\n");
    printf("  - Run with Valgrind: valgrind --leak-check=full ./memory_hands_on\n");
    printf("  - Observe memory leak reports\n\n");
    
    printf("Exercise 6: Use calloc vs malloc\n");
    printf("  - Replace malloc with calloc in heap examples\n");
    printf("  - Check if memory is zero-initialized\n");
    printf("  - Use: int *arr = calloc(10, sizeof(int));\n\n");
    
    printf("Exercise 7: Change stack size\n");
    printf("  - On Linux: ulimit -s unlimited (temporarily)\n");
    printf("  - Or: ulimit -s <size_in_kb>\n");
    printf("  - Try allocating more on stack\n");
    printf("  - On Windows: Linker option /STACK:\n\n");
}

/* =========================================================================
 * MAIN FUNCTION
 * ========================================================================= */

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("        C MEMORY LAYOUT - HANDS-ON TUTORIAL\n");
    printf("================================================================\n");
    
    // Part 1: Data type sizes
    print_data_type_sizes();
    
    // Part 2: .data segment
    demonstrate_data_segment();
    
    // Part 3: .bss segment
    demonstrate_bss_segment();
    
    // Part 4: With heap
    demonstrate_with_heap();
    
    // Part 5: Without heap
    demonstrate_without_heap();
    
    // Part 6: Stack size
    demonstrate_stack_size();
    
    // Part 7: Segment sizes
    demonstrate_segment_sizes();
    
    // Part 8: Exercises
    hands_on_exercises();
    
    printf("\n");
    printf("================================================================\n");
    printf("                    END OF TUTORIAL\n");
    printf("================================================================\n\n");
    
    printf("NEXT STEPS:\n");
    printf("  1. Run: size memory_hands_on\n");
    printf("  2. Try the hands-on exercises\n");
    printf("  3. Use Valgrind to check for memory issues\n");
    printf("  4. Experiment with different allocation sizes\n");
    printf("  5. Try to cause and fix memory errors\n\n");
    
    return 0;
}
