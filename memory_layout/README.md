# C Memory Layout Tutorial

This directory contains a comprehensive tutorial on **C Program Memory Layout**. Understanding how memory is organized in a C program is fundamental to writing efficient, bug-free code.

## Files

- `memory_layout.c` - Main tutorial code with executable examples
- `README.md` - This documentation file

## Memory Segments Overview

A C program's memory is divided into **five main segments**:

```
+------------------+   Higher Addresses
|  Environment &   |   +------------------+
|   Arguments      |   |      Stack        |
+------------------+   |  (Grows Down)      |
|      Stack        |   +------------------+
|  (Grows Down)      |   |       Heap        |
+------------------+   |   (Grows Up)       |
|       Heap        |   +------------------+
|   (Grows Up)       |   |       BSS         |
+------------------+   +------------------+
|       BSS         |   |      Data         |
| (Uninitialized)   |   +------------------+
+------------------+   |      Text         |
|      Data         |   |  (Code + RO Data) |
| (Initialized)     |   +------------------+
+------------------+   Lower Addresses
|      Text         |
| (Code + RO Data) |
+------------------+
```

| Segment | Description | Typical Contents | Size | Lifespan |
|---------|-------------|------------------|------|----------|
| **Text** | Read-only | Machine instructions, string literals, const variables | Fixed | Program execution |
| **Data** | Read-write | Initialized global variables, initialized static variables | Fixed | Program execution |
| **BSS** | Read-write | Uninitialized global variables, uninitialized static variables | Fixed | Program execution |
| **Heap** | Read-write | Dynamically allocated memory (malloc, calloc, realloc) | Dynamic | Until freed |
| **Stack** | Read-write | Local variables, function parameters, return addresses | Dynamic | Function scope |

## Tutorial Content

### 1. **Text Segment (Code Segment)**

**Characteristics:**
- Contains the **executable machine instructions** of the program
- **Read-only** - prevents accidental modification of program code
- Typically the **lowest address** in memory
- Shared among processes running the same program

**Contents:**
- Compiled machine code (function bodies)
- Read-only data (string literals: `"hello"`)
- Constant variables (`const int x = 10;`)

**Example:**
```c
const int MAX = 100;  // Stored in Text segment
char *str = "Hello";   // "Hello" is in Text segment
```

### 2. **Data Segment**

**Characteristics:**
- Contains **initialized global and static variables**
- **Read-write** memory
- Size is **determined at compile time**
- Further divided into:
  - Initialized data segment
  - Read-only data segment

**Contents:**
- Global variables with initial values
- Static variables with initial values

**Example:**
```c
int global_var = 42;        // Data segment
static int static_var = 10; // Data segment
float pi = 3.14159;        // Data segment
```

### 3. **BSS Segment (Block Started by Symbol)**

**Characteristics:**
- Contains **uninitialized global and static variables**
- **Read-write** memory
- Stands for "Block Started by Symbol"
- OS initializes all to **zero** at program start
- Size is **determined at compile time**

**Contents:**
- Global variables without explicit initialization
- Static variables without explicit initialization
- Variables explicitly initialized to zero

**Example:**
```c
int global_uninit;          // BSS segment (initialized to 0)
static int static_uninit;   // BSS segment (initialized to 0)
long array[1000];           // BSS segment (all zeros)
```

**Note:** The difference between Data and BSS is that Data contains initialized values from the executable file, while BSS is just a reserved space that the OS zeros out.

### 4. **Heap Segment**

**Characteristics:**
- **Dynamically allocated** memory
- **Read-write** memory
- Grows **upward** (toward higher addresses)
- Managed by programmer using `malloc()`, `calloc()`, `realloc()`, `free()`
- Slower allocation/deallocation than stack
- Can lead to **memory fragmentation**

**Memory Allocation Functions:**

#### `malloc()` - Memory Allocation
```c
void *malloc(size_t size);
// Allocates 'size' bytes of uninitialized memory
// Returns NULL on failure
int *ptr = (int *)malloc(10 * sizeof(int));
```

#### `calloc()` - Contiguous Allocation
```c
void *calloc(size_t num, size_t size);
// Allocates memory for 'num' objects of 'size' bytes each
// Initializes all bytes to zero
// Returns NULL on failure
int *ptr = (int *)calloc(10, sizeof(int));  // All zeros
```

#### `realloc()` - Reallocation
```c
void *realloc(void *ptr, size_t new_size);
// Resizes previously allocated memory
// Copies old data to new location if necessary
// Returns NULL on failure (original memory still valid)
ptr = (int *)realloc(ptr, 20 * sizeof(int));
```

#### `free()` - Deallocation
```c
void free(void *ptr);
// Releases memory allocated by malloc/calloc/realloc
// Does NOT set pointer to NULL (must do manually)
free(ptr);
ptr = NULL;  // Good practice
```

**Example:**
```c
int *arr = (int *)malloc(100 * sizeof(int));
if (arr == NULL) {
    // Handle allocation failure
}
// Use the memory...
free(arr);
arr = NULL;  // Prevent dangling pointer
```

### 5. **Stack Segment**

**Characteristics:**
- **Automatically managed** by compiler
- **Read-write** memory
- Grows **downward** (toward lower addresses)
- **Very fast** allocation/deallocation
- Uses **LIFO** (Last In, First Out) principle
- Limited size (typically **few MB**, OS-dependent)
- Exceeding limit causes **stack overflow**

**Contents:**
- Local variables
- Function parameters
- Return addresses
- Function call frames

**Stack Frame:**
Each function call creates a stack frame containing:
1. Function parameters
2. Local variables
3. Return address
4. Saved registers
5. Previous frame pointer

**Example:**
```c
void func(int a, int b) {
    int local = a + b;      // On stack
    char buffer[100];      // On stack
    // ...
}  // All stack memory automatically freed when function returns
```

## Key Differences: Stack vs Heap

| Feature | Stack | Heap |
|---------|-------|------|
| **Management** | Automatic (compiler) | Manual (programmer) |
| **Speed** | Very fast | Slower |
| **Size** | Limited (few MB) | Limited by available memory |
| **Allocation** | Function calls | `malloc()`, `calloc()`, `realloc()` |
| **Deallocation** | Automatic | `free()` |
| **Direction** | Grows down | Grows up |
| **Fragmentation** | None | Possible |
| **Access** | LIFO | Random |
| **Usage** | Local variables, function calls | Dynamic data structures |

## Common Memory Errors

### 1. **Segmentation Fault**

**Cause:** Accessing memory that the program doesn't have permission to access.

**Examples:**
```c
int *ptr = NULL;
*ptr = 5;  // SEGFAULT: Dereferencing NULL pointer

int *arr = malloc(10 * sizeof(int));
arr[10] = 5;  // SEGFAULT: Buffer overflow

int local;
int *ptr = &local;
*ptr = 5;  // OK
free(ptr);  // SEGFAULT: Freeing non-heap memory
```

### 2. **Memory Leak**

**Cause:** Allocating memory but never freeing it, causing the program to consume more and more memory.

**Example:**
```c
void leak() {
    int *ptr = malloc(100 * sizeof(int));
    // Forgot to free(ptr);
    // Memory is leaked each time leak() is called
}
```

**Detection:** Use tools like **Valgrind** (`valgrind --leak-check=full ./program`)

### 3. **Dangling Pointer**

**Cause:** Using a pointer after the memory it points to has been freed.

**Example:**
```c
int *ptr = malloc(sizeof(int));
*ptr = 100;
free(ptr);
// ptr is now a dangling pointer
*ptr = 200;  // UNDEFINED BEHAVIOR
```

**Prevention:** Set pointers to `NULL` after freeing:
```c
free(ptr);
ptr = NULL;  // Now dereferencing will cause a segfault (easier to debug)
```

### 4. **Double Free**

**Cause:** Calling `free()` on the same pointer twice.

**Example:**
```c
int *ptr = malloc(sizeof(int));
free(ptr);
free(ptr);  // UNDEFINED BEHAVIOR - Double free
```

**Prevention:** Set pointer to `NULL` after freeing:
```c
free(ptr);
ptr = NULL;
free(ptr);  // Safe - free(NULL) does nothing
```

### 5. **Buffer Overflow**

**Cause:** Writing more data than allocated to a buffer.

**Example:**
```c
int arr[5];
arr[5] = 10;  // Buffer overflow - writing to index 5 (valid: 0-4)

char buffer[10];
strcpy(buffer, "This string is too long");  // Buffer overflow
```

**Prevention:** Always check buffer sizes, use safer functions like `strncpy()` instead of `strcpy()`.

### 6. **Stack Overflow**

**Cause:** Exhausting the stack space, typically through deep recursion or large stack allocations.

**Example:**
```c
void infinite_recursion() {
    infinite_recursion();  // Stack overflow
}

void large_stack_allocation() {
    int huge_array[1000000];  // Might cause stack overflow
}
```

**Prevention:** Use iteration instead of deep recursion, allocate large arrays on the heap.

## Memory Layout in a Complete Program

```c
#include <stdio.h>
#include <stdlib.h>

int global_init = 10;            // Data segment
int global_uninit;               // BSS segment
const int GLOBAL_CONST = 20;     // Text segment

void func() {
    int local = 30;               // Stack
    static int static_local = 40; // Data segment (initialized)
    static int static_uninit;     // BSS segment
    
    int *heap_ptr = malloc(sizeof(int)); // Heap
    *heap_ptr = 50;
}

int main() {
    int a = 1;                    // Stack
    char *str = "Hello";           // "Hello" in Text, str on Stack
    
    func();
    
    free(heap_ptr);  // Important!
    return 0;
}
```

## Compilation and Execution

To compile and run the tutorial:

```bash
# Navigate to the memory_layout directory
cd /workspaces/C-Language-Practice/memory_layout

# Compile the code
gcc memory_layout.c -o memory_layout_tutorial

# Run the executable
./memory_layout_tutorial

# Or compile and run in one step
gcc memory_layout.c -o memory_layout_tutorial && ./memory_layout_tutorial
```

## Using Valgrind for Memory Analysis

[Valgrind](https://valgrind.org/) is a powerful tool for detecting memory errors:

```bash
# Install Valgrind (Ubuntu/Debian)
sudo apt-get install valgrind

# Run with memory leak detection
valgrind --leak-check=full --show-leak-kinds=all ./memory_layout_tutorial

# Run with detailed memory tracking
valgrind --track-origins=yes ./memory_layout_tutorial
```

**Valgrind Output Interpretation:**
- `definitely lost`: Memory allocated but never freed
- `indirectly lost`: Memory lost due to other lost blocks
- `possibly lost`: Memory may be lost (pointer to middle of block)
- `still reachable`: Memory not freed but still accessible
- `suppressed`: Errors intentionally suppressed

## Best Practices

1. **Always check for NULL** after memory allocation
   ```c
   int *ptr = malloc(size);
   if (ptr == NULL) {
       // Handle error
   }
   ```

2. **Always free what you allocate**
   ```c
   for (int i = 0; i < n; i++) {
       arr[i] = malloc(size);
   }
   // Don't forget to free each element
   for (int i = 0; i < n; i++) {
       free(arr[i]);
   }
   free(arr);
   ```

3. **Set pointers to NULL after freeing**
   ```c
   free(ptr);
   ptr = NULL;
   ```

4. **Use `calloc()` for zero-initialized memory**
   ```c
   int *arr = calloc(n, sizeof(int));  // All zeros
   ```

5. **Avoid memory leaks in long-running programs**
   - Check for leaks regularly
   - Use tools like Valgrind
   - Implement proper cleanup functions

6. **Limit recursion depth**
   - Use iteration for deep recursion
   - Set reasonable limits on recursive calls

7. **Validate array indices**
   ```c
   if (index >= 0 && index < size) {
       arr[index] = value;
   }
   ```

8. **Use const for read-only data**
   ```c
   const int MAX_SIZE = 100;
   ```

## Advanced Topics

### Memory Alignment

- Some data types require specific memory alignment
- Use `alignof()` operator (C11) or compiler attributes
- Misalignment can cause performance penalties or crashes

### Memory-Mapped Files

- `mmap()` system call maps files directly to memory
- Efficient for large file I/O
- File contents appear as a byte array in memory

### Custom Memory Allocators

- Implement your own `malloc()` and `free()` for specific needs
- Useful for embedded systems, real-time systems
- Can optimize for specific allocation patterns

### Arena Allocation

- Allocate many objects and free them all at once
- More efficient than individual allocations
- Reduces fragmentation

### Reference Counting

- Track how many references exist to allocated memory
- Automatically free when reference count reaches zero
- Used in garbage collection systems

## Useful System Calls

| Function | Description |
|----------|-------------|
| `sbrk()` | Change data segment size |
| `brk()` | Set data segment end |
| `mmap()` | Memory-mapped files |
| `munmap()` | Unmap memory |
| `mprotect()` | Change memory protection |

## Resources

### Online Tutorials
- [C Memory Management - GeeksforGeeks](https://www.geeksforgeeks.org/memory-management-in-c/)
- [Memory Layout of C Programs - GeeksforGeeks](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
- [C Memory Management - TutorialsPoint](https://www.tutorialspoint.com/cprogramming/c_memory_management.htm)

### Books
- **The C Programming Language** by Kernighan & Ritchie (K&R) - Chapter 5 (Pointers and Arrays), Chapter 6 (Structures)
- **C Programming Absolute Beginner's Guide** by Perry & Miller
- **Expert C Programming** by Peter van der Linden

### Tools
- [Valgrind](https://valgrind.org/) - Memory error detector
- [AddressSanitizer (ASan)](https://github.com/google/sanitizers) - Fast memory error detector
- [GDB](https://www.gnu.org/software/gdb/) - GNU Debugger for memory inspection
- [strace](https://strace.io/) - Trace system calls (including memory-related ones)

### Manual Pages
```bash
man malloc
man free
man calloc
man realloc
man sbrk
man brk
man mmap
```

## Summary

Understanding C memory layout is crucial for:

1. **Writing efficient programs** - Knowing where data resides helps optimize memory usage
2. **Avoiding bugs** - Most C bugs are memory-related (segfaults, leaks, corruption)
3. **Debugging** - Understanding memory layout helps diagnose issues
4. **System programming** - Essential for OS development, embedded systems
5. **Performance optimization** - Proper memory management improves performance

The five memory segments (Text, Data, BSS, Heap, Stack) each serve specific purposes, and understanding their characteristics and limitations will make you a better C programmer.
