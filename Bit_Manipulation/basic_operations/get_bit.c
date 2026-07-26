/*****************************************************************************
 * Get Bit Value - Example
 * 
 * Demonstrates how to get the value of a specific bit in a number.
 * 
 * Compile: gcc get_bit.c -o get_bit
 * Run: ./get_bit
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>

// Macro to get nth bit value (0 or 1)
#define GET_BIT(num, n) (((num) >> (n)) & 1)

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
    printf("              GET BIT VALUE\n");
    printf("================================================================\n\n");

    uint32_t num = 0b11001010; // 202 in decimal
    
    printf("Number: %u (0b", num);
    printBinary(num, 8);
    printf(")\n\n");

    printf("Getting each bit value (0-7):\n");
    for (int i = 0; i < 8; i++) {
        int bitValue = GET_BIT(num, i);
        printf("  Bit %d: %d\n", i, bitValue);
    }
    printf("\n");

    // Get and store bits in an array
    printf("Storing all bits in an array:\n");
    int bits[8];
    for (int i = 0; i < 8; i++) {
        bits[i] = GET_BIT(num, i);
    }
    printf("  Bits: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", bits[i]);
    }
    printf("\n\n");

    // Practical example: Extract RGB components
    printf("Practical Example - Extracting RGB Components:\n");
    uint32_t color = 0xFF8000; // Orange: R=255, G=128, B=0
    
    // Extract R (bits 16-23)
    uint8_t r = (color >> 16) & 0xFF;
    // Extract G (bits 8-15)
    uint8_t g = (color >> 8) & 0xFF;
    // Extract B (bits 0-7)
    uint8_t b = color & 0xFF;
    
    printf("  Color: 0x%06X\n", color);
    printf("  Red: %u (bits 16-23)\n", r);
    printf("  Green: %u (bits 8-15)\n", g);
    printf("  Blue: %u (bits 0-7)\n\n", b);

    // Extract specific bit ranges
    printf("Extracting bit ranges:\n");
    uint32_t data = 0x12345678;
    uint8_t byte0 = (data >> 0) & 0xFF;
    uint8_t byte1 = (data >> 8) & 0xFF;
    uint8_t byte2 = (data >> 16) & 0xFF;
    uint8_t byte3 = (data >> 24) & 0xFF;
    
    printf("  0x%08X:\n", data);
    printf("    Byte 0 (bits 0-7): 0x%02X\n", byte0);
    printf("    Byte 1 (bits 8-15): 0x%02X\n", byte1);
    printf("    Byte 2 (bits 16-23): 0x%02X\n", byte2);
    printf("    Byte 3 (bits 24-31): 0x%02X\n\n", byte3);

    // Count how many bits are set
    printf("Count set bits by checking each bit:\n");
    uint32_t testNum = 0b11010110;
    int count = 0;
    printf("  Number: %u (0b", testNum);
    printBinary(testNum, 8);
    printf(")\n  Set bits: ");
    
    for (int i = 0; i < 8; i++) {
        if (GET_BIT(testNum, i)) {
            count++;
            printf("bit%d ", i);
        }
    }
    printf("\n  Total: %d set bits\n\n", count);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
