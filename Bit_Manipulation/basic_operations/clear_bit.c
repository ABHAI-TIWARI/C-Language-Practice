/*****************************************************************************
 * Clear a Bit - Example
 * 
 * Demonstrates how to clear (unset) a specific bit in a number.
 * 
 * Compile: gcc clear_bit.c -o clear_bit
 * Run: ./clear_bit
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>

// Macro to clear nth bit
#define CLEAR_BIT(num, n) ((num) & ~(1U << (n)))

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
    printf("              CLEAR A BIT\n");
    printf("================================================================\n\n");

    uint32_t num = 0b11111111; // 255 in decimal
    
    printf("Original number: %u (0b", num);
    printBinary(num, 8);
    printf(")\n\n");

    printf("Clearing different bits:\n");
    for (int i = 0; i < 8; i++) {
        uint32_t result = CLEAR_BIT(num, i);
        printf("  Clear bit %d: %u (0b", i, result);
        printBinary(result, 8);
        printf(")\n");
    }
    printf("\n");

    // Clear bit 3
    uint32_t modified = CLEAR_BIT(num, 3);
    printf("Clearing bit 3: %u (0b", modified);
    printBinary(modified, 8);
    printf(")\n\n");

    // Alternative: Using AND with NOT
    printf("Alternative using AND with NOT:\n");
    uint32_t direct = num & ~(1 << 3);
    printf("  num & ~(1 << 3) = %u (0b", direct);
    printBinary(direct, 8);
    printf(")\n\n");

    // Practical example: Remove a permission
    printf("Practical Example - Removing Permissions:\n");
    #define PERM_READ    (1 << 0)
    #define PERM_WRITE   (1 << 1)
    #define PERM_EXECUTE (1 << 2)

    uint32_t permissions = PERM_READ | PERM_WRITE | PERM_EXECUTE; // All permissions
    printf("  Initial: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = CLEAR_BIT(permissions, 0); // Remove read
    printf("  -READ: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = CLEAR_BIT(permissions, 1); // Remove write
    printf("  -WRITE: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = CLEAR_BIT(permissions, 2); // Remove execute
    printf("  -EXECUTE: 0b");
    printBinary(permissions, 8);
    printf("\n\n");

    // Clear all bits except one
    printf("Clearing all bits except bit 3:\n");
    uint32_t keepBit3 = CLEAR_BIT(CLEAR_BIT(CLEAR_BIT(CLEAR_BIT(
        CLEAR_BIT(CLEAR_BIT(CLEAR_BIT(0xFF, 0), 1), 2), 4), 5), 6), 7);
    printf("  Result: %u (0b", keepBit3);
    printBinary(keepBit3, 8);
    printf(")\n\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
