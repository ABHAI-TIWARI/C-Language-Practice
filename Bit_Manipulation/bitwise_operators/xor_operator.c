/*****************************************************************************
 * Bitwise XOR Operator (^) - Example
 * 
 * Demonstrates the bitwise XOR operator with practical examples.
 * 
 * Compile: gcc xor_operator.c -o xor_operator
 * Run: ./xor_operator
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
    printf("              BITWISE XOR OPERATOR (^)\n");
    printf("================================================================\n\n");

    // Truth Table
    printf("Truth Table:\n");
    printf("  A | B | A ^ B\n");
    printf("  ---+---+------\n");
    printf("  0 | 0 |  0\n");
    printf("  0 | 1 |  1\n");
    printf("  1 | 0 |  1\n");
    printf("  1 | 1 |  0\n\n");

    // Basic Example
    uint32_t a = 5;   // 0101
    uint32_t b = 3;   // 0011
    uint32_t c = a ^ b; // 0110 = 6

    printf("Example:\n");
    printf("  a = %u (0b", a);
    printBinary(a, 8);
    printf(")\n");
    printf("  b = %u (0b", b);
    printBinary(b, 8);
    printf(")\n");
    printf("  a ^ b = %u (0b", c);
    printBinary(c, 8);
    printf(")\n\n");

    // Practical Use: Toggling bits
    printf("Practical Use - Toggling Bits:\n");
    uint32_t num = 0b10101010;
    uint32_t bitToToggle = 1;
    uint32_t result = num ^ (1 << bitToToggle);
    printf("  Original: %u (0b", num);
    printBinary(num, 8);
    printf(")\n");
    printf("  Toggle bit %d: %u (0b", bitToToggle, result);
    printBinary(result, 8);
    printf(")\n\n");

    // Check if two numbers differ by exactly one bit
    printf("Check if two numbers differ by exactly one bit:\n");
    uint32_t x = 5; // 0101
    uint32_t y = 7; // 0111
    uint32_t diff = x ^ y;
    if (diff & (diff - 1)) {
        printf("  %u and %u differ by MORE than one bit\n", x, y);
    } else {
        printf("  %u and %u differ by EXACTLY one bit\n", x, y);
    }
    printf("\n");

    // XOR as addition without carry
    printf("XOR as addition without carry:\n");
    printf("  5 + 3 = %d\n", 5 + 3);
    printf("  5 ^ 3 = %d (same as addition without carry)\n", 5 ^ 3);
    printf("  6 + 3 = %d\n", 6 + 3);
    printf("  6 ^ 3 = %d (different due to carry)\n\n", 6 ^ 3);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
