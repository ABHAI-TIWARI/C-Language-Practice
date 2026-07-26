/*****************************************************************************
 * Set a Bit - Example
 * 
 * Demonstrates how to set a specific bit in a number.
 * 
 * Compile: gcc set_bit.c -o set_bit
 * Run: ./set_bit
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>

// Macro to set nth bit
#define SET_BIT(num, n) ((num) | (1U << (n)))

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
    printf("              SET A BIT\n");
    printf("================================================================\n\n");

    uint32_t num = 0b10100000; // 160 in decimal
    
    printf("Original number: %u (0b", num);
    printBinary(num, 8);
    printf(")\n\n");

    printf("Setting different bits:\n");
    for (int i = 0; i < 8; i++) {
        uint32_t result = SET_BIT(num, i);
        printf("  Set bit %d: %u (0b", i, result);
        printBinary(result, 8);
        printf(")\n");
    }
    printf("\n");

    // Set bit 3
    uint32_t modified = SET_BIT(num, 3);
    printf("Setting bit 3: %u (0b", modified);
    printBinary(modified, 8);
    printf(")\n\n");

    // Alternative: Using OR directly
    printf("Alternative using OR directly:\n");
    uint32_t direct = num | (1 << 3);
    printf("  num | (1 << 3) = %u (0b", direct);
    printBinary(direct, 8);
    printf(")\n\n");

    // Practical example: Add a permission
    printf("Practical Example - Adding Permissions:\n");
    #define PERM_READ    (1 << 0)
    #define PERM_WRITE   (1 << 1)
    #define PERM_EXECUTE (1 << 2)

    uint32_t permissions = 0; // No permissions
    printf("  Initial: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = SET_BIT(permissions, 0); // Add read
    printf("  +READ: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = SET_BIT(permissions, 1); // Add write
    printf("  +WRITE: 0b");
    printBinary(permissions, 8);
    printf("\n");
    
    permissions = SET_BIT(permissions, 2); // Add execute
    printf("  +EXECUTE: 0b");
    printBinary(permissions, 8);
    printf("\n\n");

    // Set multiple bits
    printf("Setting multiple bits at once:\n");
    uint32_t value = 0;
    uint32_t bitsToSet = 0b10101010; // Bits 1, 3, 5, 7
    value |= bitsToSet;
    printf("  Set bits 1,3,5,7: %u (0b", value);
    printBinary(value, 8);
    printf(")\n\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
