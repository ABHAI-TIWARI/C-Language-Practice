# C Memory Layout - Hands-On Practical Tutorial

This file provides a **practical, hands-on tutorial** on C memory layout. It complements the theoretical tutorial (`memory_layout.c`) with actual code you can run, modify, and experiment with.

## Files

- `memory_hands_on.c` - Hands-on tutorial with 8 practical sections
- `memory_layout.c` - Theoretical tutorial (see README.md)
- `README.md` - Complete memory layout theory

## Quick Start

```bash
# Navigate to memory_layout directory
cd /workspaces/C-Language-Practice/memory_layout

# Compile the hands-on tutorial
gcc memory_hands_on.c -o memory_hands_on

# Run it
./memory_hands_on

# Check segment sizes
size memory_hands_on
```

## Tutorial Structure

This hands-on tutorial is divided into **8 parts**, each demonstrating practical aspects of C memory layout:

### Part 1: Size of All Data Types

Shows the size of every C data type on your system:
- Basic types (char, int, long, etc.)
- Floating point types (float, double, long double)
- Pointer types
- Derived types (arrays, structs, unions, function pointers)
- Type limits (MIN/MAX values)

**Expected Output:**
```
 sizeof(int)            =  4 bytes
 sizeof(long)           =  8 bytes
 sizeof(float)          =  4 bytes
 sizeof(double)         =  8 bytes
 sizeof(char*)          =  8 bytes
 sizeof(int[1024])      = 4096 bytes
```

**Key Insight:** Data type sizes vary by system architecture (32-bit vs 64-bit).

### Part 2: Increasing .DATA Segment

Demonstrates how initialized global variables increase the `.data` segment:

**Code in file:**
```c
// These go to .data segment
int data_int1 = 100;
int data_int2 = 200;
float data_float = 3.14f;
int data_large_array[100] = {0};  // Even with = {0}, this is .data
```

**Verification:**
```bash
# Before modification
size memory_hands_on

# After adding more initialized globals, recompile and check again
size memory_hands_on
```

**Key Insight:** The `.data` segment stores all **initialized** global and static variables. Note that `= {0}` initialization still puts arrays in `.data`, not `.bss`.

### Part 3: Increasing .BSS Segment

Demonstrates how uninitialized and zero-initialized global variables increase the `.bss` segment:

**Code in file:**
```c
// These go to .bss segment
int bss_int1;                     // Uninitialized
int bss_zero_int = 0;            // Zero-initialized
static int bss_static;           // Uninitialized static
int bss_large_array[1000];       // Uninitialized array
char bss_char_array[10000];     // Uninitialized array
```

**Verification:**
```bash
size memory_hands_on
# Look at the .bss column
```

**Key Insight:** The `.bss` segment stores **uninitialized** and **zero-initialized** global/static variables. The OS zeros out `.bss` at program startup, so the executable doesn't need to store the zeros.

### Part 4: WITH Heap Allocation

Demonstrates dynamic memory allocation using `malloc()`:

**Code:**
```c
int *heap_int = (int *)malloc(sizeof(int));
*heap_int = 42;

int *heap_array = (int *)malloc(100 * sizeof(int));
// Use heap_array...

free(heap_int);
free(heap_array);
```

**Key Operations:**
- `malloc()` - Allocate uninitialized memory
- `calloc()` - Allocate zero-initialized memory
- `realloc()` - Resize allocated memory
- `free()` - Release memory

**Key Insight:** Heap memory is **not** part of the executable file. It's allocated at runtime from the system's available memory.

### Part 5: WITHOUT Heap Allocation

Shows memory usage when only using stack, `.data`, and `.bss`:

**Characteristics:**
- All memory determined at **compile time**
- No dynamic allocation
- No `malloc()`/`free()` calls
- Fixed memory footprint

**Key Insight:** Programs without heap allocation have **predictable** memory usage and **no memory leaks**.

### Part 6: Changing Stack Size

Demonstrates stack memory usage and how to test stack limits:

**Stack Allocation Examples:**
```c
// 1MB on stack
void large_stack_allocation(int size_mb) {
    volatile char buffer[size_mb * 1024 * 1024];
    // Use buffer...
}

// Recursive stack growth
void recursive_stack_test(int depth) {
    char local_buffer[1024]; // 1KB per call
    if (depth < 10) {
        recursive_stack_test(depth + 1);
    }
}
```

**Key Insight:** Stack grows **downward** (toward lower addresses). Each function call creates a **stack frame** containing local variables, parameters, and return address.

**Testing Stack Limits:**
```bash
# Check current stack size limit
ulimit -s

# Temporarily increase stack size (Linux)
ulimit -s 32768  # 32MB

# Run program with modified stack
./memory_hands_on
```

**Note:** Stack overflow occurs when stack exceeds its limit (typically 8MB on Linux).

### Part 7: Comparing Segment Sizes

Shows how to check and calculate segment sizes:

**Using `size` command:**
```bash
gcc memory_hands_on.c -o memory_hands_on
size memory_hands_on
```

**Typical Output:**
```
   text    data     bss     dec     hex filename
  16289     680   14496   31465   7ae9 memory_hands_on
```

**Interpretation:**
- **text**: Code + read-only data (16289 bytes)
- **data**: Initialized globals (680 bytes)
- **bss**: Uninitialized globals (14496 bytes)
- **dec**: Total size in decimal
- **hex**: Total size in hexadecimal

**Approximate Calculations:**
The program calculates approximate sizes of `.data` and `.bss` segments based on the global variables defined.

### Part 8: Hands-On Exercises

Practical exercises to deepen your understanding:

#### Exercise 1: Grow .DATA Segment
```c
// Add to global scope (outside any function)
int huge_data[1000000] = {1};  // 1 million ints, initialized to 1

// Recompile and check size
gcc memory_hands_on.c -o memory_hands_on
size memory_hands_on
// Observe .data size increase
```

#### Exercise 2: Grow .BSS Segment
```c
// Add to global scope
int huge_bss[1000000];  // 1 million ints, uninitialized

// Recompile and check size
gcc memory_hands_on.c -o memory_hands_on
size memory_hands_on
// Observe .bss size increase
```

#### Exercise 3: Large Heap Allocation
```c
// In demonstrate_with_heap() function
int *big_alloc = (int *)malloc(10 * 1024 * 1024);  // 10MB
if (big_alloc) {
    // Use the memory
    memset(big_alloc, 0, 10 * 1024 * 1024);
    printf("Allocated 10MB on heap\n");
    free(big_alloc);
}

// Check memory usage while running
# In another terminal:
top -p $(pgrep -f memory_hands_on)
```

#### Exercise 4: Cause Stack Overflow
```c
// Method 1: Infinite recursion (will crash)
void infinite_recursion() {
    infinite_recursion();
}

// Method 2: Large stack allocation (will crash)
void stack_overflow() {
    volatile char huge[100 * 1024 * 1024]; // 100MB on stack
    huge[0] = 1;
}

// Call either function and observe stack overflow
```

#### Exercise 5: Detect Memory Leaks
```c
// In demonstrate_with_heap(), comment out all free() calls
// int *heap_int = (int *)malloc(sizeof(int));
// *heap_int = 42;
// // free(heap_int);  // COMMENT THIS OUT

// Recompile and run with Valgrind
gcc memory_hands_on.c -o memory_hands_on
valgrind --leak-check=full --show-leak-kinds=all ./memory_hands_on

// Observe memory leak reports
```

#### Exercise 6: calloc vs malloc
```c
// Replace malloc with calloc
int *arr_malloc = (int *)malloc(10 * sizeof(int));
// Values are uninitialized

int *arr_calloc = (int *)calloc(10, sizeof(int));
// Values are all zero

// Verify
for (int i = 0; i < 10; i++) {
    printf("arr_malloc[%d] = %d\n", i, arr_malloc[i]);  // Garbage
    printf("arr_calloc[%d] = %d\n", i, arr_calloc[i]);  // 0
}

free(arr_malloc);
free(arr_calloc);
```

#### Exercise 7: Change Stack Size
```bash
# Check current stack size limit
ulimit -s

# Increase to 32MB
ulimit -s 32768

# Now try running with larger stack allocations
./memory_hands_on

# Or set unlimited (be careful!)
ulimit -s unlimited
```

## Practical Commands

### Checking Executable Size
```bash
size <executable>      # Show text, data, bss sizes
```

### Checking Memory Usage
```bash
# During execution
ps aux | grep memory_hands_on

# Real-time monitoring
top -p $(pgrep -f memory_hands_on)

# Detailed memory info
pmap $(pgrep -f memory_hands_on)
```

### Memory Error Detection
```bash
# Install Valgrind
sudo apt-get install valgrind

# Basic leak check
valgrind ./memory_hands_on

# Full leak check
valgrind --leak-check=full --show-leak-kinds=all ./memory_hands_on

# Track origins of uninitialized values
valgrind --track-origins=yes ./memory_hands_on
```

### Modifying Stack Size
```bash
# Check current limit
ulimit -s

# Set new limit (in KB)
ulimit -s 16384  # 16MB

# Set unlimited (be careful!)
ulimit -s unlimited
```

### On Windows (MinGW/Cygwin)
```bash
# Set stack size during compilation (bytes)
gcc -Wl,--stack,8388608 memory_hands_on.c -o memory_hands_on
# 8388608 = 8MB
```

## Common Questions

### Q: Why does `int arr[100] = {0};` go to .data instead of .bss?
A: Because it's explicitly initialized (to zero). The C standard treats any explicit initialization, even to zero, as belonging to `.data`. Only completely uninitialized variables go to `.bss`. However, some compilers may optimize this and put it in `.bss` anyway.

### Q: How can I see the actual memory addresses of my variables?
A: Run the program - it prints addresses. Or use a debugger:
```bash
gdb ./memory_hands_on
(gdb) break main
(gdb) run
(gdb) print &data_int1
```

### Q: What happens if I don't free heap memory?
A: The memory is **leaked** - your program loses the pointer to it, but the memory remains allocated until the program terminates. In long-running programs, this causes memory exhaustion.

### Q: Can I run out of heap memory?
A: Yes. If you keep allocating without freeing, you'll eventually exhaust available memory. The OS will return NULL from malloc(), or the program may be terminated.

### Q: Can I run out of stack memory?
A: Yes. This is called a **stack overflow**. It typically happens with deep recursion or very large stack allocations. The program will crash with a segmentation fault.

### Q: How do I know which segment a variable belongs to?
A: 
- Local variables → **Stack**
- Function parameters → **Stack**
- Global initialized variables → **.data**
- Global uninitialized variables → **.bss**
- Dynamically allocated memory → **Heap**
- String literals → **.rodata** (read-only data)
- Function code → **.text**

### Q: Why is .bss more efficient than .data?
A: The `.bss` segment doesn't require storage in the executable file on disk. The OS simply reserves the space and zeros it at program startup. The `.data` segment must store all the initialized values in the executable file.

## Real-World Examples

### Example 1: Web Server
```c
// Global configuration (stored in .data)
config_t server_config = {
    .port = 8080,
    .max_connections = 1000,
    .timeout = 30
};

// Connection pool (stored in .bss - zero-initialized)
connection_t connections[MAX_CONNECTIONS];

int main() {
    // Request buffer (allocated on heap)
    char *request = malloc(MAX_REQUEST_SIZE);
    
    // Process buffer (on stack)
    char process_buffer[4096];
    
    // ...
}
```

### Example 2: Image Processing
```c
// Image data (heap - large, dynamic)
pixel_t *image = malloc(width * height * sizeof(pixel_t));

// Processing kernel (stack - small, fixed)
float kernel[3][3] = {
    {-1, -1, -1},
    {-1,  8, -1},
    {-1, -1, -1}
};

// Statistics (data - global, initialized)
int processed_images = 0;
```

### Example 3: Embedded System
```c
// Hardware registers (volatile, at fixed addresses)
volatile uint32_t *GPIO_A = (uint32_t *)0x40000000;

// Configuration (const, in .rodata or .text)
const pin_config_t pins[] = {...};

// Buffer (static, in .bss)
static uint8_t rx_buffer[256];

void main() {
    // Local variables (stack)
    uint8_t temp;
    int i;
    
    // No heap allocation (not available on many embedded systems)
}
```

## Memory Optimization Tips

### 1. Use Stack for Small, Short-Lived Data
```c
// Good: Small buffer on stack
char buffer[1024];

// Bad: Large buffer on stack (may cause overflow)
char buffer[10 * 1024 * 1024]; // 10MB - use heap instead
```

### 2. Use .bss for Large Zero-Initialized Data
```c
// Good: Uninitialized or zero-initialized
int large_array[1000000];  // Goes to .bss

// Also good: Explicit zero initialization
int zero_array[1000000] = {0};  // May go to .bss depending on compiler
```

### 3. Minimize .data Segment
```c
// Bad: Large initialized array
int lookup_table[10000] = {1, 2, 3, ..., 10000};

// Better: Use const (may go to .rodata which can be shared)
const int lookup_table[10000] = {1, 2, 3, ..., 10000};

// Best: Load from file at runtime
int *lookup_table = load_lookup_table("table.dat");
```

### 4. Heap Best Practices
```c
// Always check for NULL
int *ptr = malloc(size);
if (!ptr) {
    // Handle allocation failure
}

// Free in reverse order of allocation
free(child_struct);
free(parent_struct);

// Set to NULL after free
free(ptr);
ptr = NULL;

// Use calloc for zero-initialized memory
int *arr = calloc(count, sizeof(int));
```

### 5. Avoid Memory Fragmentation
```c
// Bad: Many small allocations
for (int i = 0; i < 1000; i++) {
    small_struct_t *s = malloc(sizeof(small_struct_t));
}

// Better: Allocate one large block
small_struct_t *array = malloc(1000 * sizeof(small_struct_t));

// Best: Use a memory pool/arena allocator
memory_pool_t pool = pool_create(1000, sizeof(small_struct_t));
```

## Summary Table

| Aspect | Text | Data | BSS | Heap | Stack |
|--------|------|------|-----|------|-------|
| **Contents** | Code, RO data | Init globals | Uninit globals | Dynamic | Locals |
| **Initialization** | Compile time | Compile time | Runtime (0) | Runtime | Runtime |
| **Size** | Fixed | Fixed | Fixed | Dynamic | Dynamic |
| **Lifetime** | Program | Program | Program | Until free | Function |
| **Growth** | N/A | N/A | N/A | Up | Down |
| **Speed** | Fast | Fast | Fast | Medium | Very Fast |
| **Management** | OS | OS | OS | Programmer | Compiler |
| **In Executable** | Yes | Yes | No | No | No |
| **Read/Write** | Read-only | Read-write | Read-write | Read-write | Read-write |

## Resources

- [man:size](https://man7.org/linux/man-pages/man1/size.1.html) - Check segment sizes
- [man:pmap](https://man7.org/linux/man-pages/man1/pmap.1.html) - Memory map of process
- [Valgrind Documentation](https://valgrind.org/docs/manual/quick-start.html)
- [GDB Debugger](https://www.gnu.org/software/gdb/) - Memory inspection
- [C Memory Management - GeeksforGeeks](https://www.geeksforgeeks.org/memory-management-in-c/)
