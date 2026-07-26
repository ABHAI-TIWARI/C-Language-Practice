/*****************************************************************************
 * Toggle a Bit - Example
 * 
 * Demonstrates how to toggle (flip) a specific bit in a number.
 * 
 * Compile: gcc toggle_bit.c -o toggle_bit
 * Run: ./toggle_bit
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>

// Macro to toggle nth bit
#define TOGGLE_BIT(num, n) ((num) ^ (1U << (n)))

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
    printf("              TOGGLE A BIT\n");
    printf("================================================================\n\n");

    uint32_t num = 0b10101010; // 170 in decimal
    
    printf("Original number: %u (0b", num);
    printBinary(num, 8);
    printf(")\n\n");

    printf("Toggling bit 3 multiple times:\n");
    uint32_t current = num;
    for (int i = 0; i < 5; i++) {
        printf("  Toggle %d: %u (0b", i + 1, current);
        printBinary(current, 8);
        printf(")\n");
        current = TOGGLE_BIT(current, 3);
    }
    printf("\n");

    // Toggle all bits one by one
    printf("Toggling all bits (0-7) sequentially:\n");
    current = num;
    printf("  Start: %u (0b", current);
    printBinary(current, 8);
    printf(")\n");
    for (int i = 0; i < 8; i++) {
        current = TOGGLE_BIT(current, i);
        printf("  After bit %d: %u (0b", i, current);
        printBinary(current, 8);
        printf(")\n");
    }
    printf("\n");

    // Alternative: Using XOR
    printf("Alternative using XOR:\n");
    current = num;
    current = current ^ (1 << 2);
    printf("  num ^ (1 << 2) = %u (0b", current);
    printBinary(current, 8);
    printf(")\n\n");

    // Practical example: Toggle LED states
    printf("Practical Example - Toggling LED States:\n");
    #define LED_1 (1 << 0)
    #define LED_2 (1 << 1)
    #define LED_3 (1 << 2)
    #define LED_4 (1 << 3)

    uint32_t ledStates = LED_1 | LED_3; // LED 1 and 3 are ON
    printf("  Initial: 0b");
    printBinary(ledStates, 8);
    printf(" (LED 1 and 3 ON)\n");
    
    ledStates = TOGGLE_BIT(ledStates, 0); // Toggle LED 1
    printf("  Toggle LED 1: 0b");
    printBinary(ledStates, 8);
    printf("\n");
    
    ledStates = TOGGLE_BIT(ledStates, 2); // Toggle LED 3
    printf("  Toggle LED 3: 0b");
    printBinary(ledStates, 8);
    printf("\n");
    
    ledStates = TOGGLE_BIT(ledStates, 1); // Toggle LED 2
    printf("  Toggle LED 2: 0b");
    printBinary(ledStates, 8);
    printf("\n\n");

    // Toggle all bits in a byte
    printf("Toggle all bits in 0xAA (10101010):\n");
    uint8_t byte = 0xAA;
    byte = ~byte; // Toggle all bits
    printf("  Result: 0x%02X (0b", byte);
    printBinary(byte, 8);
    printf(")\n\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
