/*****************************************************************************
 * Bitwise NOT Operator (~) - Example
 * 
 * Demonstrates the bitwise NOT operator with practical examples.
 * 
 * Compile: gcc not_operator.c -o not_operator
 * Run: ./not_operator
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
    printf("              BITWISE NOT OPERATOR (~)\n");
    printf("================================================================\n\n");

    // Truth Table
    printf("Truth Table:\n");
    printf("  A | ~A\n");
    printf("  ---+----\n");
    printf("  0 |  1\n");
    printf("  1 |  0\n\n");

    // Basic Example (32-bit)
    uint32_t a = 5;   // 00000101
    uint32_t b = ~a;  // 11111010

    printf("Example (32-bit):\n");
    printf("  a = %u (0x%08X)\n", a, a);
    printf("  ~a = %u (0x%08X)\n\n", b, b);

    // 8-bit example for clarity
    printf("Example (8-bit for clarity):\n");
    uint8_t a8 = 5;  // 00000101
    uint8_t b8 = ~a8; // 11111010 = 250
    printf("  a = %u (0b", a8);
    printBinary(a8, 8);
    printf(")\n");
    printf("  ~a = %u (0b", b8);
    printBinary(b8, 8);
    printf(")\n\n");

    // Practical Use: Inverting a bitmask
    printf("Practical Use - Inverting Bitmask:\n");
    uint32_t mask = 0x0000FFFF;
    uint32_t inverted = ~mask;
    printf("  Original mask: 0x%08X\n", mask);
    printf("  Inverted mask: 0x%08X\n\n", inverted);

    // Clear a bit using NOT
    printf("Clear a bit using NOT:\n");
    uint32_t num = 0b1111;
    uint32_t bitToClear = 2;
    uint32_t result = num & ~(1 << bitToClear);
    printf("  Original: %u (0b", num);
    printBinary(num, 8);
    printf(")\n");
    printf("  Clear bit %d: %u (0b", bitToClear, result);
    printBinary(result, 8);
    printf(")\n\n");

    // Two's complement: -x = ~x + 1
    printf("Two's complement relationship:\n");
    int32_t x = 5;
    int32_t neg_x = ~x + 1;
    printf("  x = %d\n", x);
    printf("  -x = %d\n", -x);
    printf("  ~x + 1 = %d\n\n", neg_x);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
