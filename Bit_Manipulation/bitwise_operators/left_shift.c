/*****************************************************************************
 * Left Shift Operator (<<) - Example
 * 
 * Demonstrates the left shift operator with practical examples.
 * 
 * Compile: gcc left_shift.c -o left_shift
 * Run: ./left_shift
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

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              LEFT SHIFT OPERATOR (<<)\n");
    printf("================================================================\n\n");

    printf("Left shift shifts bits to the left, filling with zeros on the right.\n");
    printf("Equivalent to multiplying by 2^n (for unsigned)\n\n");

    // Basic Example
    uint32_t a = 5;   // 0101
    int shift = 2;
    uint32_t b = a << shift; // 010100 = 20

    printf("Example:\n");
    printf("  a = %u (0b", a);
    printBinary(a, 8);
    printf(")\n");
    printf("  a << %d = %u (0b", shift, b);
    printBinary(b, 8);
    printf(")\n");
    printf("  %u * 2^%d = %u\n\n", a, shift, b);

    // Multiple shifts
    printf("Multiple shifts:\n");
    for (int i = 0; i <= 4; i++) {
        printf("  %u << %d = %u (0b", a, i, a << i);
        printBinary(a << i, 8);
        printf(")\n");
    }
    printf("\n");

    // Practical Use: Creating bitmasks
    printf("Practical Use - Creating Bitmasks:\n");
    for (int i = 0; i < 8; i++) {
        printf("  1 << %d = %u (0b", i, 1 << i);
        printBinary(1 << i, 8);
        printf(")\n");
    }
    printf("\n");

    // Multiply by powers of two
    printf("Multiplying by powers of two:\n");
    uint32_t num = 3;
    for (int i = 0; i <= 5; i++) {
        printf("  %u * 2^%d = %u (using << %d)\n", num, i, num << i, i);
    }
    printf("\n");

    // Warning about overflow
    printf("Warning - Overflow:\n");
    uint8_t smallNum = 128; // 10000000
    uint8_t shifted = smallNum << 1; // Overflow!
    printf("  uint8_t: 128 << 1 = %u (overflow occurred)\n", shifted);
    printf("  Always use appropriate types for shifting!\n\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
