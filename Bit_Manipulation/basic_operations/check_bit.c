/*****************************************************************************
 * Check if a Bit is Set - Example
 * 
 * Demonstrates how to check if a specific bit is set in a number.
 * 
 * Compile: gcc check_bit.c -o check_bit
 * Run: ./check_bit
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Macro to check if nth bit is set
#define IS_BIT_SET(num, n) (((num) >> (n)) & 1)

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
    printf("              CHECK IF A BIT IS SET\n");
    printf("================================================================\n\n");

    uint32_t num = 0b10101100; // 172 in decimal
    
    printf("Number: %u (0b", num);
    printBinary(num, 8);
    printf(")\n\n");

    printf("Checking each bit (0-7):\n");
    for (int i = 0; i < 8; i++) {
        if (IS_BIT_SET(num, i)) {
            printf("  Bit %d: SET (1)\n", i);
        } else {
            printf("  Bit %d: NOT SET (0)\n", i);
        }
    }
    printf("\n");

    // Alternative implementation as a function
    printf("Using a function:\n");
    bool isBitSet(uint32_t num, int n) {
        return (num >> n) & 1;
    }

    printf("  Bit 3: %s\n", isBitSet(num, 3) ? "SET" : "NOT SET");
    printf("  Bit 5: %s\n", isBitSet(num, 5) ? "SET" : "NOT SET");
    printf("  Bit 0: %s\n\n", isBitSet(num, 0) ? "SET" : "NOT SET");

    // Practical example: Check multiple flags
    printf("Practical Example - Checking Flags:\n");
    #define FLAG_A (1 << 0)
    #define FLAG_B (1 << 2)
    #define FLAG_C (1 << 4)
    #define FLAG_D (1 << 7)

    uint32_t flags = FLAG_A | FLAG_C | FLAG_D;
    printf("  Flags = 0b");
    printBinary(flags, 8);
    printf("\n");
    printf("  FLAG_A: %s\n", (flags & FLAG_A) ? "SET" : "NOT SET");
    printf("  FLAG_B: %s\n", (flags & FLAG_B) ? "SET" : "NOT SET");
    printf("  FLAG_C: %s\n", (flags & FLAG_C) ? "SET" : "NOT SET");
    printf("  FLAG_D: %s\n\n", (flags & FLAG_D) ? "SET" : "NOT SET");

    // Check if any of multiple flags are set
    printf("Check if ANY of FLAG_A or FLAG_B are set:\n");
    uint32_t checkFlags = FLAG_A | FLAG_B;
    if (flags & checkFlags) {
        printf("  YES, at least one is set\n\n");
    } else {
        printf("  NO, none are set\n\n");
    }

    // Check if ALL of multiple flags are set
    printf("Check if ALL of FLAG_A and FLAG_C are set:\n");
    checkFlags = FLAG_A | FLAG_C;
    if ((flags & checkFlags) == checkFlags) {
        printf("  YES, all are set\n\n");
    } else {
        printf("  NO, not all are set\n\n");
    }

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
