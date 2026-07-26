/*****************************************************************************
 * Right Shift Operator (>>) - Example
 * 
 * Demonstrates the right shift operator with practical examples.
 * 
 * Compile: gcc right_shift.c -o right_shift
 * Run: ./right_shift
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
    printf("              RIGHT SHIFT OPERATOR (>>)\n");
    printf("================================================================\n\n");

    printf("Right shift shifts bits to the right.\n");
    printf("For unsigned: fills with zeros on the left.\n");
    printf("For signed: implementation-defined (usually sign-extended)\n\n");

    // Basic Example
    uint32_t a = 20;  // 010100
    int shift = 2;
    uint32_t b = a >> shift; // 000101 = 5

    printf("Example (unsigned):\n");
    printf("  a = %u (0b", a);
    printBinary(a, 8);
    printf(")\n");
    printf("  a >> %d = %u (0b", shift, b);
    printBinary(b, 8);
    printf(")\n");
    printf("  %u / 2^%d = %u\n\n", a, shift, b);

    // Multiple shifts
    printf("Multiple shifts:\n");
    for (int i = 0; i <= 4; i++) {
        printf("  %u >> %d = %u (0b", a, i, a >> i);
        printBinary(a >> i, 8);
        printf(")\n");
    }
    printf("\n");

    // Signed right shift behavior
    printf("Signed vs Unsigned Right Shift:\n");
    int32_t negative = -8; // In two's complement
    printf("  -8 in hex: 0x%08X\n", negative);
    printf("  -8 >> 1 = %d (0x%08X)\n", negative >> 1, negative >> 1);
    printf("  Note: Sign bit is extended on signed right shift\n\n");

    // Extracting bits
    printf("Practical Use - Extracting Bits:\n");
    uint32_t number = 0xABCD1234;
    uint8_t byte0 = (number >> 0) & 0xFF;
    uint8_t byte1 = (number >> 8) & 0xFF;
    uint8_t byte2 = (number >> 16) & 0xFF;
    uint8_t byte3 = (number >> 24) & 0xFF;
    printf("  number = 0x%08X\n", number);
    printf("  Byte 0 (LSB): 0x%02X\n", byte0);
    printf("  Byte 1: 0x%02X\n", byte1);
    printf("  Byte 2: 0x%02X\n", byte2);
    printf("  Byte 3 (MSB): 0x%02X\n\n", byte3);

    // Divide by powers of two
    printf("Dividing by powers of two:\n");
    uint32_t num = 200;
    for (int i = 1; i <= 5; i++) {
        uint32_t result = num >> i;
        printf("  %u / 2^%d = %u (using >> %d)\n", num, i, result, i);
    }
    printf("\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
