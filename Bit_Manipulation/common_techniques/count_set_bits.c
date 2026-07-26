/*****************************************************************************
 * Count Set Bits (Population Count) - Example
 * 
 * Demonstrates multiple methods to count the number of set bits in a number.
 * 
 * Compile: gcc count_set_bits.c -o count_set_bits
 * Run: ./count_set_bits
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

// Method 1: Iterative Approach
int countSetBitsIterative(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Method 2: Brian Kernighan's Algorithm
int countSetBitsBrianKernighan(uint32_t n) {
    int count = 0;
    while (n) {
        n = n & (n - 1); // Clears the least significant set bit
        count++;
    }
    return count;
}

// Method 3: Using GCC built-in
int countSetBitsBuiltin(uint32_t n) {
    return __builtin_popcount(n);
}

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              COUNT SET BITS (Population Count)\n");
    printf("================================================================\n\n");

    uint32_t testNumbers[] = {0, 1, 5, 0xF, 0xFF, 0xFFFF, 0xFFFFFFFF, 0b10101010, 0b11001100};
    
    printf("Testing with various numbers:\n\n");
    
    for (int i = 0; i < sizeof(testNumbers)/sizeof(testNumbers[0]); i++) {
        uint32_t n = testNumbers[i];
        int count1 = countSetBitsIterative(n);
        int count2 = countSetBitsBrianKernighan(n);
        int count3 = countSetBitsBuiltin(n);
        
        printf("Number: %10u (0x%08X, 0b", n, n);
        printBinary(n, 8);
        printf(")\n");
        printf("  Iterative:           %2d bits\n", count1);
        printf("  Brian Kernighan:    %2d bits\n", count2);
        printf("  Built-in (__builtin_popcount): %2d bits\n", count3);
        
        if (count1 == count2 && count2 == count3) {
            printf("  Result: ALL METHODS AGREE\n");
        } else {
            printf("  Result: ERROR - Methods disagree!\n");
        }
        printf("\n");
    }

    // Performance comparison note
    printf("Performance Notes:\n");
    printf("  Iterative:        O(bits) - checks all bits\n");
    printf("  Brian Kernighan: O(set bits) - only loops for set bits\n");
    printf("  Built-in:         O(1) - single CPU instruction (POPCNT)\n\n");

    // Practical use: Count set bits in a buffer
    printf("Practical Use - Count set bits in a buffer:\n");
    uint8_t buffer[] = {0x0F, 0xF0, 0x55, 0xAA, 0xFF};
    int totalBits = 0;
    
    for (int i = 0; i < sizeof(buffer)/sizeof(buffer[0]); i++) {
        int bits = __builtin_popcount(buffer[i]);
        totalBits += bits;
        printf("  buffer[%d] = 0x%02X: %d bits\n", i, buffer[i], bits);
    }
    printf("  Total set bits: %d\n\n", totalBits);

    // Check if a number has exactly one bit set (is power of two)
    printf("Check if number is power of two (has exactly one bit set):\n");
    uint32_t powers[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    uint32_t nonPowers[] = {0, 3, 5, 6, 7, 9, 10, 15, 255};
    
    printf("  Powers of two: ");
    for (int i = 0; i < sizeof(powers)/sizeof(powers[0]); i++) {
        int bits = countSetBitsBuiltin(powers[i]);
        printf("%d(%d) ", powers[i], bits);
    }
    printf("\n  Non-powers:    ");
    for (int i = 0; i < sizeof(nonPowers)/sizeof(nonPowers[0]); i++) {
        int bits = countSetBitsBuiltin(nonPowers[i]);
        printf("%d(%d) ", nonPowers[i], bits);
    }
    printf("\n\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
