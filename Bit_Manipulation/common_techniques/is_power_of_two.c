/*****************************************************************************
 * Check if a Number is a Power of Two - Example
 * 
 * Demonstrates how to check if a number is a power of two using bit manipulation.
 * 
 * Compile: gcc is_power_of_two.c -o is_power_of_two
 * Run: ./is_power_of_two
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Helper function to print binary representation
void printBinary(uint32_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

// Method 1: Using bitwise AND
bool isPowerOfTwo(uint32_t n) {
    if (n == 0) return false;
    return (n & (n - 1)) == 0;
}

// Method 2: Count set bits
bool isPowerOfTwoCount(uint32_t n) {
    if (n == 0) return false;
    int count = 0;
    while (n) {
        count++;
        n &= (n - 1);
    }
    return count == 1;
}

// Method 3: Using built-in
bool isPowerOfTwoBuiltin(uint32_t n) {
    if (n == 0) return false;
    return __builtin_popcount(n) == 1;
}

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              CHECK IF NUMBER IS POWER OF TWO\n");
    printf("================================================================\n\n");

    printf("Explanation:\n");
    printf("  A number is a power of two if it has exactly ONE bit set.\n");
    printf("  For example: 1 (1), 2 (10), 4 (100), 8 (1000), 16 (10000), etc.\n");
    printf("  Subtracting 1 from such a number flips all bits after the set bit.\n");
    printf("  So n & (n-1) will be zero if n is a power of two.\n\n");

    uint32_t testNumbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 31, 32, 33, 63, 64, 100};
    
    printf("Testing numbers 0-100:\n");
    for (int i = 0; i < sizeof(testNumbers)/sizeof(testNumbers[0]); i++) {
        uint32_t n = testNumbers[i];
        bool result1 = isPowerOfTwo(n);
        bool result2 = isPowerOfTwoCount(n);
        bool result3 = isPowerOfTwoBuiltin(n);
        
        printf("  %3u (0b", n);
        printBinary(n, 8);
        printf("): %s", result1 ? "YES" : "NO");
        
        if (result1 == result2 && result2 == result3) {
            printf(" (all methods agree)\n");
        } else {
            printf(" (ERROR: methods disagree!)\n");
        }
    }
    printf("\n");

    // Find all powers of two up to a limit
    printf("All powers of two up to 1000:\n");
    for (uint32_t i = 1; i <= 1000; i <<= 1) {
        printf("  %u (0b", i);
        printBinary(i, 10);
        printf(")\n");
    }
    printf("\n");

    // Practical use: Find next power of two
    printf("Practical Use - Find next power of two:\n");
    uint32_t numbers[] = {10, 15, 16, 17, 31, 32, 100, 1023, 1024};
    for (int i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
        uint32_t n = numbers[i];
        uint32_t next = 1;
        if (n > 1) {
            n--;
            n |= n >> 1;
            n |= n >> 2;
            n |= n >> 4;
            n |= n >> 8;
            n |= n >> 16;
            next = n + 1;
        }
        printf("  Next power of two >= %u: %u\n", numbers[i], next);
    }
    printf("\n");

    // Application: Memory allocation
    printf("Application - Memory Allocation:\n");
    printf("  When allocating memory, the size is often rounded up to the next\n");
    printf("  power of two for alignment purposes.\n");
    uint32_t sizes[] = {128, 256, 512, 1024, 2048};
    printf("  Common memory allocation sizes:\n");
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        printf("    %u bytes\n", sizes[i]);
    }
    printf("\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
