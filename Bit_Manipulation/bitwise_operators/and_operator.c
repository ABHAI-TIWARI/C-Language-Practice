/*****************************************************************************
 * Bitwise AND Operator (&) - Example
 * 
 * Demonstrates the bitwise AND operator with practical examples.
 * 
 * Compile: gcc and_operator.c -o and_operator
 * Run: ./and_operator
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
    printf("              BITWISE AND OPERATOR (&)\n");
    printf("================================================================\n\n");

    // Truth Table
    printf("Truth Table:\n");
    printf("  A | B | A & B\n");
    printf("  ---+---+------\n");
    printf("  0 | 0 |  0\n");
    printf("  0 | 1 |  0\n");
    printf("  1 | 0 |  0\n");
    printf("  1 | 1 |  1\n\n");

    // Basic Example
    uint32_t a = 5;   // 0101
    uint32_t b = 3;   // 0011
    uint32_t c = a & b; // 0001 = 1

    printf("Example:\n");
    printf("  a = %u (0b", a);
    printBinary(a, 8);
    printf(")\n");
    printf("  b = %u (0b", b);
    printBinary(b, 8);
    printf(")\n");
    printf("  a & b = %u (0b", c);
    printBinary(c, 8);
    printf(")\n\n");

    // Practical Use: Masking
    printf("Practical Use - Masking:\n");
    uint32_t number = 0xABCD1234;
    uint32_t mask = 0x0000FFFF;
    uint32_t lowerByte = number & mask;

    printf("  number = 0x%08X\n", number);
    printf("  mask = 0x%08X\n", mask);
    printf("  lower 16 bits = 0x%04X\n\n", lowerByte);

    // Check if a bit is set
    uint32_t flags = 0b1010;
    uint32_t bitToCheck = 2; // Check bit 2 (0-indexed)
    if (flags & (1 << bitToCheck)) {
        printf("Bit %d is SET in flags (0x%04X)\n", bitToCheck, flags);
    } else {
        printf("Bit %d is NOT SET in flags (0x%04X)\n", bitToCheck, flags);
    }
    printf("\n");

    // Extract specific bits
    printf("Extracting bits 4-7 from 0x12345678:\n");
    uint32_t data = 0x12345678;
    uint32_t extracted = (data >> 4) & 0x0F; // Extract bits 4-7
    printf("  data = 0x%08X\n", data);
    printf("  bits 4-7 = 0x%02X\n\n", extracted);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
