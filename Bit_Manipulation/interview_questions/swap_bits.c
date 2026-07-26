/*****************************************************************************
 * Swap Two Numbers Without Temporary Variable - Example
 * 
 * Demonstrates how to swap two numbers using XOR without a temporary variable.
 * 
 * Compile: gcc swap_bits.c -o swap_bits
 * Run: ./swap_bits
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>

// Helper function to print binary representation
void printBinary(uint32_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

// Swap using XOR
void swapWithXOR(int *a, int *b) {
    if (a != b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

// Swap using arithmetic
void swapWithArithmetic(int *a, int *b) {
    if (a != b) {
        *a = *a + *b;
        *b = *a - *b;
        *a = *a - *b;
    }
}

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              SWAP TWO NUMBERS WITHOUT TEMPORARY VARIABLE\n");
    printf("================================================================\n\n");

    printf("Note: This is a common interview question.\n");
    printf("In practice, using a temporary variable is preferred for clarity.\n\n");

    // Method 1: Using XOR
    printf("Method 1: Using XOR\n");
    int a = 5, b = 10;
    printf("  Before: a = %d, b = %d\n", a, b);
    swapWithXOR(&a, &b);
    printf("  After:  a = %d, b = %d\n\n", a, b);

    // Method 2: Using arithmetic
    printf("Method 2: Using Addition/Subtraction\n");
    a = 20, b = 30;
    printf("  Before: a = %d, b = %d\n", a, b);
    swapWithArithmetic(&a, &b);
    printf("  After:  a = %d, b = %d\n\n", a, b);

    // Method 3: Using standard temporary variable (recommended)
    printf("Method 3: Using Temporary Variable (Recommended)\n");
    a = 100, b = 200;
    printf("  Before: a = %d, b = %d\n", a, b);
    int temp = a;
    a = b;
    b = temp;
    printf("  After:  a = %d, b = %d\n\n", a, b);

    // Warning about XOR method
    printf("WARNING about XOR method:\n");
    printf("  If pointers alias (point to same location), the value becomes zero!\n");
    a = 5;
    swapWithXOR(&a, &a); // Same location
    printf("  After swapWithXOR(&a, &a): a = %d (should be 5, but is 0!)\n\n", a);

    // Safe version
    printf("Safe XOR swap with check:\n");
    void safeSwapWithXOR(int *x, int *y) {
        if (x != y) {
            *x = *x ^ *y;
            *y = *x ^ *y;
            *x = *x ^ *y;
        }
    }
    
    a = 7, b = 14;
    printf("  Before: a = %d, b = %d\n", a, b);
    safeSwapWithXOR(&a, &a); // Same location
    printf("  After safeSwapWithXOR(&a, &a): a = %d (unchanged)\n", a);
    safeSwapWithXOR(&a, &b);
    printf("  After safeSwapWithXOR(&a, &b): a = %d, b = %d\n\n", a, b);

    // Bit-level demonstration
    printf("Bit-level demonstration:\n");
    uint32_t x = 0b0101; // 5
    uint32_t y = 0b0011; // 3
    printf("  x = %u (0b", x);
    printBinary(x, 8);
    printf(")\n");
    printf("  y = %u (0b", y);
    printBinary(y, 8);
    printf(")\n");
    
    printf("  Step 1: x = x ^ y\n");
    x = x ^ y;
    printf("    x = %u (0b", x);
    printBinary(x, 8);
    printf(")\n");
    
    printf("  Step 2: y = x ^ y\n");
    y = x ^ y;
    printf("    y = %u (0b", y);
    printBinary(y, 8);
    printf(")\n");
    
    printf("  Step 3: x = x ^ y\n");
    x = x ^ y;
    printf("    x = %u (0b", x);
    printBinary(x, 8);
    printf(")\n");
    printf("  Result: x = %u, y = %u (swapped!)\n\n", x, y);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
