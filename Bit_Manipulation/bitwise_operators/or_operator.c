/*****************************************************************************
 * Bitwise OR Operator (|) - Example
 * 
 * Demonstrates the bitwise OR operator with practical examples.
 * 
 * Compile: gcc or_operator.c -o or_operator
 * Run: ./or_operator
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
    printf("              BITWISE OR OPERATOR (|)\n");
    printf("================================================================\n\n");

    // Truth Table
    printf("Truth Table:\n");
    printf("  A | B | A | B\n");
    printf("  ---+---+------\n");
    printf("  0 | 0 |  0\n");
    printf("  0 | 1 |  1\n");
    printf("  1 | 0 |  1\n");
    printf("  1 | 1 |  1\n\n");

    // Basic Example
    uint32_t a = 5;   // 0101
    uint32_t b = 3;   // 0011
    uint32_t c = a | b; // 0111 = 7

    printf("Example:\n");
    printf("  a = %u (0b", a);
    printBinary(a, 8);
    printf(")\n");
    printf("  b = %u (0b", b);
    printBinary(b, 8);
    printf(")\n");
    printf("  a | b = %u (0b", c);
    printBinary(c, 8);
    printf(")\n\n");

    // Practical Use: Combining flags
    printf("Practical Use - Combining Flags:\n");
    #define FLAG_READ    (1 << 0)
    #define FLAG_WRITE   (1 << 1)
    #define FLAG_EXECUTE (1 << 2)

    uint32_t permissions = FLAG_READ | FLAG_WRITE;
    printf("  FLAG_READ = %u (0b", FLAG_READ);
    printBinary(FLAG_READ, 8);
    printf(")\n");
    printf("  FLAG_WRITE = %u (0b", FLAG_WRITE);
    printBinary(FLAG_WRITE, 8);
    printf(")\n");
    printf("  permissions = %u (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n\n");

    // Set a bit
    uint32_t num = 0b1000;
    uint32_t bitToSet = 1;
    uint32_t result = num | (1 << bitToSet);
    printf("Setting bit %d in %u (0b", bitToSet, num);
    printBinary(num, 8);
    printf(") = %u (0b", result);
    printBinary(result, 8);
    printf(")\n\n");

    // Combine multiple values
    printf("Combining values:\n");
    uint8_t r = 0x12, g = 0x34, b = 0x56;
    uint32_t combined = (r << 16) | (g << 8) | b;
    printf("  R: 0x%02X, G: 0x%02X, B: 0x%02X\n", r, g, b);
    printf("  Combined: 0x%06X\n\n", combined);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
