/*****************************************************************************
 * Find Two Non-Repeating Numbers - Example
 * 
 * Given an array where all numbers repeat twice except two,
 * find the two unique numbers using bit manipulation.
 * 
 * Compile: gcc find_two_unique.c -o find_two_unique
 * Run: ./find_two_unique
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

// Function to find the two unique numbers
void findTwoUnique(int arr[], int n, int *x, int *y) {
    // Step 1: XOR all elements
    // This gives us x ^ y (since all other elements cancel out)
    int xor_all = 0;
    for (int i = 0; i < n; i++) {
        xor_all ^= arr[i];
    }
    printf("  XOR of all elements: %d (0b", xor_all);
    printBinary(xor_all, 8);
    printf(")\n");

    // Step 2: Find any set bit in xor_all
    // This bit is different between x and y
    int set_bit = xor_all & -xor_all;
    printf("  Rightmost set bit: %d (0b", set_bit);
    printBinary(set_bit, 8);
    printf(")\n");

    // Step 3: Divide elements into two groups based on this bit
    // One group will have x, the other will have y
    *x = 0, *y = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] & set_bit) {
            *x ^= arr[i];
        } else {
            *y ^= arr[i];
        }
    }
}

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              FIND TWO NON-REPEATING NUMBERS\n");
    printf("================================================================\n\n");

    printf("Problem: Given an array where all numbers repeat twice except two,\n");
    printf("find the two unique numbers.\n\n");

    // Example 1
    printf("Example 1:\n");
    int arr1[] = {2, 4, 6, 8, 10, 2, 4, 8, 10, 12};
    int x1, y1;
    
    printf("  Array: ");
    for (int i = 0; i < sizeof(arr1)/sizeof(arr1[0]); i++) {
        printf("%d%s", arr1[i], i < sizeof(arr1)/sizeof(arr1[0])-1 ? ", " : "\n");
    }
    
    findTwoUnique(arr1, sizeof(arr1)/sizeof(arr1[0]), &x1, &y1);
    printf("  Two unique numbers: %d and %d\n\n", x1, y1);

    // Example 2
    printf("Example 2:\n");
    int arr2[] = {5, 3, 5, 2, 3, 7, 2, 8, 8};
    int x2, y2;
    
    printf("  Array: ");
    for (int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++) {
        printf("%d%s", arr2[i], i < sizeof(arr2)/sizeof(arr2[0])-1 ? ", " : "\n");
    }
    
    findTwoUnique(arr2, sizeof(arr2)/sizeof(arr2[0]), &x2, &y2);
    printf("  Two unique numbers: %d and %d\n\n", x2, y2);

    // Example 3 with larger numbers
    printf("Example 3 (larger numbers):\n");
    int arr3[] = {100, 200, 100, 300, 200, 400, 300, 500};
    int x3, y3;
    
    printf("  Array: ");
    for (int i = 0; i < sizeof(arr3)/sizeof(arr3[0]); i++) {
        printf("%d%s", arr3[i], i < sizeof(arr3)/sizeof(arr3[0])-1 ? ", " : "\n");
    }
    
    findTwoUnique(arr3, sizeof(arr3)/sizeof(arr3[0]), &x3, &y3);
    printf("  Two unique numbers: %d and %d\n\n", x3, y3);

    // Explanation
    printf("Explanation:\n");
    printf("  1. XOR all elements: duplicate elements cancel out (a^a=0)\n");
    printf("     Result: x ^ y\n");
    printf("  2. Find any set bit in x^y (this bit differs between x and y)\n");
    printf("  3. Partition array: one group has this bit set, other doesn't\n");
    printf("  4. XOR each group separately: duplicates cancel, leaving x and y\n\n");

    // Verify the solution
    printf("Verification:\n");
    printf("  For Example 1: ");
    int count1 = 0, count2 = 0;
    for (int i = 0; i < sizeof(arr1)/sizeof(arr1[0]); i++) {
        if (arr1[i] == x1) count1++;
        if (arr1[i] == y1) count2++;
    }
    printf("%d appears %d time(s), %d appears %d time(s)\n", x1, count1, y1, count2);
    printf("  Result: %s\n\n", (count1 == 1 && count2 == 1) ? "CORRECT" : "ERROR");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
