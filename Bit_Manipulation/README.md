# Bit Manipulation in C - Complete Tutorial

## Table of Contents
1. [Introduction](#introduction)
2. [Bitwise Operators](#bitwise-operators)
3. [Basic Bit Operations](#basic-bit-operations)
4. [Common Bit Manipulation Techniques](#common-bit-manipulation-techniques)
5. [Practical Use Cases](#practical-use-cases)
6. [Interview Questions](#interview-questions)
7. [Practice Problems](#practice-problems)
8. [Resources](#resources)

---

## Introduction

Bit manipulation is the act of algorithmically manipulating individual bits or bit patterns in computer data. It's a fundamental skill in systems programming, embedded systems, and performance-critical applications.

### Why Learn Bit Manipulation?

- **Performance**: Bit operations are extremely fast (single CPU instruction)
- **Memory Efficiency**: Can store more information in less space
- **Hardware Control**: Essential for device drivers and embedded systems
- **Cryptography**: Foundation of many encryption algorithms
- **Interview Success**: Frequently tested in technical interviews

### Bit Representation

In C, all data is stored in binary. Understanding how numbers are represented is crucial:

```c
// Integer representation (32-bit example)
// 5 in binary: 0000...0101 (32 bits)
// -5 in binary (two's complement): 1111...1011 (32 bits)
```

---

## Bitwise Operators

C provides six bitwise operators that work on integer types:

### 1. Bitwise AND (`&`)
Performs AND operation on each bit pair.

```c
int a = 5;    // 0101
int b = 3;    // 0011
int c = a & b; // 0001 (1)
```

**Truth Table:**
| A | B | A & B |
|---|---|------|
| 0 | 0 |  0   |
| 0 | 1 |  0   |
| 1 | 0 |  0   |
| 1 | 1 |  1   |

### 2. Bitwise OR (`|`)
Performs OR operation on each bit pair.

```c
int a = 5;    // 0101
int b = 3;    // 0011
int c = a | b; // 0111 (7)
```

**Truth Table:**
| A | B | A | B |
|---|---|-----|
| 0 | 0 |  0  |
| 0 | 1 |  1  |
| 1 | 0 |  1  |
| 1 | 1 |  1  |

### 3. Bitwise XOR (`^`)
Performs exclusive OR operation.

```c
int a = 5;    // 0101
int b = 3;    // 0011
int c = a ^ b; // 0110 (6)
```

**Truth Table:**
| A | B | A ^ B |
|---|---|------|
| 0 | 0 |  0   |
| 0 | 1 |  1   |
| 1 | 0 |  1   |
| 1 | 1 |  0   |

### 4. Bitwise NOT (`~`)
Inverts all bits (one's complement).

```c
int a = 5;    // 000...0101 (32 bits)
int b = ~a;   // 111...1010 (depends on integer size)
```

### 5. Left Shift (`<<`)
Shifts bits to the left by specified positions, filling with zeros.

```c
int a = 5;    // 0101
int b = a << 2; // 010100 (20) - equivalent to 5 * 4
```

### 6. Right Shift (`>>`)
Shifts bits to the right. For unsigned, fills with zeros. For signed, implementation-defined (usually sign-extended).

```c
int a = 20;   // 010100
int b = a >> 2; // 000101 (5) - equivalent to 20 / 4
```

---

## Basic Bit Operations

### Checking if a Bit is Set

```c
// Check if the nth bit is set in number
#define IS_BIT_SET(num, n) ((num >> n) & 1)

int num = 13; // 1101
if (IS_BIT_SET(num, 2)) {
    printf("Bit 2 is set\n"); // This will print
}
```

### Setting a Bit

```c
// Set the nth bit
#define SET_BIT(num, n) (num | (1 << n))

int num = 5;  // 0101
num = SET_BIT(num, 1); // 0111 (7)
```

### Clearing a Bit

```c
// Clear the nth bit
#define CLEAR_BIT(num, n) (num & ~(1 << n))

int num = 7;  // 0111
num = CLEAR_BIT(num, 1); // 0101 (5)
```

### Toggling a Bit

```c
// Toggle the nth bit
#define TOGGLE_BIT(num, n) (num ^ (1 << n))

int num = 5;  // 0101
num = TOGGLE_BIT(num, 1); // 0111 (7)
num = TOGGLE_BIT(num, 1); // 0101 (5)
```

### Getting the Value of a Bit

```c
// Get value of nth bit (0 or 1)
#define GET_BIT(num, n) (((num) >> (n)) & 1)

int num = 13; // 1101
int bit2 = GET_BIT(num, 2); // 1
int bit1 = GET_BIT(num, 1); // 0
```

---

## Common Bit Manipulation Techniques

### 1. Counting Set Bits (Population Count)

**Method 1: Iterative Approach**
```c
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
```

**Method 2: Brian Kernighan's Algorithm**
```c
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1); // Clears the least significant set bit
        count++;
    }
    return count;
}
```

**Method 3: Using Built-in Function (GCC)**
```c
int count = __builtin_popcount(n); // For unsigned int
int count = __builtin_popcountll(n); // For unsigned long long
```

### 2. Checking if a Number is Power of Two

```c
// A number is power of two if it has exactly one bit set
int isPowerOfTwo(int n) {
    if (n <= 0) return 0;
    return (n & (n - 1)) == 0;
}

// Examples:
// 1 (1)    -> true
// 2 (10)   -> true
// 4 (100)  -> true
// 3 (11)   -> false
// 5 (101)  -> false
```

### 3. Finding the Position of the Least Significant Set Bit

```c
int findLSB(int n) {
    if (n == 0) return -1;
    return __builtin_ctz(n); // Count trailing zeros (GCC)
    
    // Alternative without built-in:
    // int position = 0;
    // while ((n & 1) == 0) {
    //     n >>= 1;
    //     position++;
    // }
    // return position;
}
```

### 4. Finding the Position of the Most Significant Set Bit

```c
int findMSB(int n) {
    if (n == 0) return -1;
    return 31 - __builtin_clz(n); // Count leading zeros (GCC)
    
    // Alternative without built-in:
    // int position = 0;
    // while (n >>= 1) {
    //     position++;
    // }
    // return position;
}
```

### 5. Swapping Two Numbers Without Temporary Variable

```c
void swap(int *a, int *b) {
    if (a != b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

// Usage:
int x = 5, y = 10;
swap(&x, &y); // x=10, y=5
```

**Note:** This method can cause issues if `a` and `b` point to the same location. Always use the safe version with a temporary variable in production code.

### 6. Checking if Two Numbers Have Opposite Signs

```c
int haveOppositeSigns(int a, int b) {
    return (a ^ b) < 0;
}

// Explanation: If signs are opposite, the sign bit will be different
// XOR of sign bits will be 1, making the result negative
```

### 7. Absolute Value Without Branching

```c
int absolute(int n) {
    int mask = n >> (sizeof(int) * 8 - 1);
    return (n + mask) ^ mask;
}

// Explanation:
// For negative numbers, mask = -1 (all bits set)
// For positive numbers, mask = 0
// (n + mask) ^ mask flips the sign
```

### 8. Finding the Maximum of Two Numbers Without Comparison

```c
int max(int a, int b) {
    int diff = a - b;
    int sign = (diff >> 31) & 1; // 0 if a >= b, 1 if a < b
    return a - diff * sign;
}

// Alternative:
int max(int a, int b) {
    return a * ((a >= b)) + b * ((b > a));
}
```

### 9. Checking if a Number is Even or Odd

```c
int isEven(int n) {
    return (n & 1) == 0;
}

int isOdd(int n) {
    return (n & 1) == 1;
}
```

### 10. Multiplying by 2^n

```c
// Multiply by 2^n using left shift
int multiplyByPowerOfTwo(int num, int n) {
    return num << n;
}

// Example: 5 << 3 = 5 * 8 = 40
```

### 11. Dividing by 2^n

```c
// Divide by 2^n using right shift (for unsigned)
unsigned int divideByPowerOfTwo(unsigned int num, int n) {
    return num >> n;
}

// For signed, be careful with sign extension
```

### 12. Checking if nth Bit is Set in a Byte

```c
#define CHECK_BIT(byte, n) ((byte) & (1 << (n)))

unsigned char byte = 0b01011010;
if (CHECK_BIT(byte, 3)) {
    // Bit 3 is set
}
```

---

## Practical Use Cases

### 1. Flag Management

Bit manipulation is perfect for storing multiple boolean flags in a single integer.

```c
// Define flags
#define FLAG_READ    (1 << 0)  // 0001
#define FLAG_WRITE   (1 << 1)  // 0010
#define FLAG_EXECUTE (1 << 2)  // 0100
#define FLAG_DELETE  (1 << 3)  // 1000

// Set flags
int permissions = FLAG_READ | FLAG_WRITE; // 0011

// Check flags
if (permissions & FLAG_READ) {
    printf("Read permission granted\n");
}

// Add a flag
permissions |= FLAG_EXECUTE; // 0111

// Remove a flag
permissions &= ~FLAG_WRITE; // 0101

// Toggle a flag
permissions ^= FLAG_DELETE; // 1101

// Check all flags
if ((permissions & (FLAG_READ | FLAG_WRITE | FLAG_EXECUTE)) == 
    (FLAG_READ | FLAG_WRITE | FLAG_EXECUTE)) {
    printf("All permissions granted\n");
}
```

### 2. Bitmasking for Configuration Options

```c
// Configuration options for a device
#define CONFIG_BAUD_9600   (1 << 0)
#define CONFIG_BAUD_19200  (1 << 1)
#define CONFIG_PARITY_NONE  (1 << 2)
#define CONFIG_PARITY_EVEN  (1 << 3)
#define CONFIG_STOP_1       (1 << 4)
#define CONFIG_STOP_2       (1 << 5)

// Set configuration
int config = CONFIG_BAUD_19200 | CONFIG_PARITY_EVEN | CONFIG_STOP_1;

// Check configuration
if (config & CONFIG_PARITY_EVEN) {
    printf("Parity: Even\n");
}
```

### 3. Efficient Data Storage (Bit Packing)

Store multiple small values in a single integer.

```c
// RGB color stored in 32 bits: 8 bits each for R, G, B, Alpha
typedef unsigned int Color;

Color packRGB(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

void unpackRGB(Color c, unsigned char *r, unsigned char *g, unsigned char *b) {
    *r = (c >> 24) & 0xFF;
    *g = (c >> 16) & 0xFF;
    *b = (c >> 8) & 0xFF;
}

// Usage:
Color color = packRGB(255, 128, 0); // Orange
unsigned char r, g, b;
unpackRGB(color, &r, &g, &b);
```

### 4. Bit Field Structures

C allows you to define structures with bit fields.

```c
struct DeviceStatus {
    unsigned int power: 1;      // 1 bit
    unsigned int ready: 1;      // 1 bit
    unsigned int error: 1;      // 1 bit
    unsigned int mode: 2;       // 2 bits
    unsigned int reserved: 27;  // 27 bits
};

// Usage:
struct DeviceStatus status;
status.power = 1;
status.ready = 1;
status.mode = 2; // 0-3

// Note: Bit fields have implementation-defined behavior
// Check your compiler documentation
```

### 5. CRC (Cyclic Redundancy Check) Calculation

Simple CRC-8 implementation:

```c
unsigned char crc8(unsigned char *data, int length) {
    unsigned char crc = 0xFF;
    unsigned char polynomial = 0x07; // x^8 + x^2 + x + 1
    
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}
```

### 6. Parity Calculation

Check if a byte has even or odd parity (even number of set bits):

```c
int calculateParity(unsigned char byte) {
    int parity = 0;
    while (byte) {
        parity ^= 1;
        byte = byte & (byte - 1); // Clear LSB
    }
    return parity; // 0 = even, 1 = odd
}

// Faster method using XOR
int calculateParityFast(unsigned char byte) {
    byte ^= byte >> 4;
    byte ^= byte >> 2;
    byte ^= byte >> 1;
    return byte & 1;
}
```

### 7. Endianness Detection

```c
// Check if system is little-endian or big-endian
int isLittleEndian() {
    int num = 1;
    char *byte = (char *)&num;
    return *byte == 1;
}

// Usage:
if (isLittleEndian()) {
    printf("Little-endian system\n");
} else {
    printf("Big-endian system\n");
}
```

### 8. Finding the Next Power of Two

```c
unsigned int nextPowerOfTwo(unsigned int n) {
    if (n == 0) return 1;
    
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    
    return n + 1;
}

// Examples:
// nextPowerOfTwo(5)  = 8
// nextPowerOfTwo(16) = 16
// nextPowerOfTwo(17) = 32
```

### 9. Bit Reversal

```c
unsigned char reverseBits(unsigned char byte) {
    unsigned char reversed = 0;
    for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (byte & 1);
        byte >>= 1;
    }
    return reversed;
}

// Faster method using lookup table
unsigned char reverseBitsLookup(unsigned char byte) {
    static const unsigned char lookup[256] = {
        0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
        0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
        // ... rest of the table
    };
    return lookup[byte];
}
```

### 10. Gray Code Conversion

Gray code is a binary numeral system where two successive values differ in only one bit.

```c
// Binary to Gray code
unsigned int binaryToGray(unsigned int num) {
    return num ^ (num >> 1);
}

// Gray code to binary
unsigned int grayToBinary(unsigned int gray) {
    unsigned int mask = gray;
    while (mask != 0) {
        mask >>= 1;
        gray ^= mask;
    }
    return gray;
}
```

---

## Interview Questions

### Easy Level

#### Q1: Count the number of set bits in an integer

**Solution:**
```c
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count++;
        n &= (n - 1);
    }
    return count;
}
```

**Time Complexity:** O(k) where k is the number of set bits

---

#### Q2: Check if a given number is a power of two

**Solution:**
```c
int isPowerOfTwo(int n) {
    if (n <= 0) return 0;
    return (n & (n - 1)) == 0;
}
```

**Explanation:** Numbers that are powers of two have exactly one bit set. Subtracting 1 from such a number flips all the bits after the set bit (including the set bit itself). So, `n & (n-1)` will be zero if `n` is a power of two.

---

#### Q3: Swap two numbers without using a temporary variable

**Solution:**
```c
void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
```

**Note:** This is a common trick question. In practice, using a temporary variable is preferred for clarity and to avoid issues when pointers alias.

---

#### Q4: Find the position of the only set bit in a number that is a power of two

**Solution:**
```c
int findSetBitPos(int n) {
    if (n == 0 || (n & (n - 1)) != 0) return -1; // Not power of two
    
    int pos = 0;
    while (n >>= 1) {
        pos++;
    }
    return pos;
}

// Faster using built-in:
int findSetBitPos(int n) {
    return __builtin_ctz(n);
}
```

---

#### Q5: Turn off the rightmost set bit

**Solution:**
```c
int turnOffRightmostBit(int n) {
    return n & (n - 1);
}

// Example:
// n = 12 (1100)
// n - 1 = 11 (1011)
// n & (n - 1) = 8 (1000)
```

---

### Medium Level

#### Q6: Find the two non-repeating numbers in an array where all other numbers repeat twice

**Solution:**
```c
void findTwoOdd(int arr[], int n, int *x, int *y) {
    int xor_all = 0;
    
    // XOR all elements
    for (int i = 0; i < n; i++) {
        xor_all ^= arr[i];
    }
    
    // Find a set bit in xor_all (any set bit will do)
    int set_bit = xor_all & -xor_all;
    
    // Divide elements into two groups
    *x = 0, *y = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] & set_bit) {
            *x ^= arr[i];
        } else {
            *y ^= arr[i];
        }
    }
}
```

**Explanation:** The XOR of all elements gives us `x ^ y`. We then find any set bit in this result, which must be different between `x` and `y`. We use this bit to partition the array into two groups, each containing one of the unique numbers.

---

#### Q7: Count number of bits to be flipped to convert A to B

**Solution:**
```c
int countBitsFlip(int a, int b) {
    int xor_result = a ^ b;
    return countSetBits(xor_result);
}

// Or directly:
int countBitsFlip(int a, int b) {
    int count = 0;
    int n = a ^ b;
    while (n) {
        count++;
        n &= (n - 1);
    }
    return count;
}
```

---

#### Q8: Find the next higher number with same number of set bits

**Solution:**
```c
int nextHigher(int n) {
    if (n == 0) return 0;
    
    int rightOne = n & -n; // Rightmost set bit
    int nextHigherOneBit = n + rightOne;
    int rightOnesPattern = n ^ nextHigherOneBit;
    rightOnesPattern = (rightOnesPattern) / rightOne;
    rightOnesPattern >>= 2;
    
    return nextHigherOneBit | rightOnesPattern;
}

// Example: 5 (0101) -> 6 (0110)
//          6 (0110) -> 9 (1001)
```

---

#### Q9: Check if all bits can be set by flipping at most one bit

**Solution:**
```c
int isAllBitsSet(int n) {
    // All bits set means number is of form 2^k - 1
    // Check if n+1 is power of two
    if (n == 0) return 1;
    int m = n + 1;
    return (m & (m - 1)) == 0;
}

int canSetWithOneFlip(int n) {
    if (isAllBitsSet(n)) return 1;
    if (isAllBitsSet(n | (n + 1))) return 1;
    return 0;
}
```

---

#### Q10: Rotate bits of a number

**Solution:**
```c
int rotateLeft(int n, int d, int bits) {
    // d = number of positions to rotate
    // bits = total number of bits in the number
    return (n << d) | (n >> (bits - d));
}

int rotateRight(int n, int d, int bits) {
    return (n >> d) | (n << (bits - d));
}

// For 32-bit integers:
int rotateLeft32(int n, int d) {
    return (n << d) | (n >> (32 - d));
}

// Example: rotateLeft32(1, 1) = 0x80000002
```

---

### Hard Level

#### Q11: Find the longest sequence of 1s in binary representation of a number

**Solution:**
```c
int longestSeqOfOnes(int n) {
    int max = 0, current = 0;
    
    while (n) {
        if (n & 1) {
            current++;
            max = (current > max) ? current : max;
        } else {
            current = 0;
        }
        n >>= 1;
    }
    
    return max;
}
```

---

#### Q12: Find the number of trailing zeros in a number

**Solution:**
```c
int countTrailingZeros(int n) {
    if (n == 0) return 32; // or sizeof(int) * 8
    
    int count = 0;
    while ((n & 1) == 0) {
        count++;
        n >>= 1;
    }
    return count;
}

// Using built-in:
int countTrailingZeros(int n) {
    return __builtin_ctz(n);
}
```

---

#### Q13: Calculate the absolute difference between two numbers without subtraction

**Solution:**
```c
int absoluteDifference(int a, int b) {
    // If a >= b, return a - b
    // If a < b, return b - a
    // This is equivalent to |a - b|
    
    int diff = a + (~b + 1); // a - b using two's complement
    int sign = diff >> 31; // -1 if negative, 0 if positive
    
    // (diff + sign) ^ sign handles the absolute value
    return (diff + sign) ^ sign;
}

// Alternative simpler approach:
int absoluteDifference(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}
```

---

#### Q14: Find the minimum of two numbers without comparison

**Solution:**
```c
int min(int a, int b) {
    int diff = a - b;
    int sign = (diff >> 31) & 1; // 0 if a >= b, 1 if a < b
    return b + diff * sign;
}

// Or:
int min(int a, int b) {
    return a + ((b - a) & ((b - a) >> 31));
}
```

---

#### Q15: Implement multiplication of two numbers using bit manipulation

**Solution:**
```c
int multiply(int a, int b) {
    int result = 0;
    
    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1;
        b >>= 1;
    }
    
    return result;
}

// This is the Russian Peasant algorithm
// Example: 5 * 6 = 30
// 5 (101), 6 (110)
// Step 1: b=6 (even) -> a=10, b=3
// Step 2: b=3 (odd) -> result=10, a=20, b=1
// Step 3: b=1 (odd) -> result=30, a=40, b=0
// Result = 30
```

---

#### Q16: Implement division using bit manipulation

**Solution:**
```c
int divide(unsigned int dividend, unsigned int divisor) {
    if (divisor == 0) return INT_MAX; // Division by zero
    
    unsigned int quotient = 0;
    unsigned int temp = 0;
    
    for (int i = 31; i >= 0; i--) {
        if ((temp + (divisor << i)) <= dividend) {
            temp += divisor << i;
            quotient |= (1 << i);
        }
    }
    
    return quotient;
}
```

---

#### Q17: Check if a number is a palindrome in binary representation

**Solution:**
```c
int isBinaryPalindrome(unsigned int n, int bits) {
    int left = bits - 1;
    int right = 0;
    
    while (left > right) {
        // Extract left bit
        int leftBit = (n >> left) & 1;
        // Extract right bit
        int rightBit = (n >> right) & 1;
        
        if (leftBit != rightBit) {
            return 0;
        }
        
        left--;
        right++;
    }
    
    return 1;
}

// Usage:
// isBinaryPalindrome(5, 3) -> 1 (101 is palindrome)
// isBinaryPalindrome(7, 3) -> 1 (111 is palindrome)
// isBinaryPalindrome(6, 3) -> 0 (110 is not palindrome)
```

---

#### Q18: Find the number of times a bit is set at a particular position across all numbers from 1 to n

**Solution:**
```c
int countSetBitsAtPosition(int n, int position) {
    // Calculate the pattern: 2^position
    int pattern = 1 << position;
    
    // Full cycles
    int fullCycles = n / (pattern << 1);
    int count = fullCycles * pattern;
    
    // Remaining numbers
    int remainder = n % (pattern << 1);
    count += (remainder >= pattern) ? (remainder - pattern + 1) : 0;
    
    return count;
}

// Example: countSetBitsAtPosition(10, 0) = 5
// Numbers 1-10: 1,2,3,4,5,6,7,8,9,10
// LSB set in: 1,3,5,7,9 -> 5 times
```

---

#### Q19: Given a number, find the smallest number greater than it with same number of set bits

**Solution:**
```c
int nextNumberWithSameSetBits(int n) {
    if (n == 0) return 0;
    
    int rightOne = n & -n; // Rightmost set bit
    int nextHigherOneBit = n + rightOne;
    int rightOnesPattern = n ^ nextHigherOneBit;
    rightOnesPattern = (rightOnesPattern) / rightOne;
    rightOnesPattern >>= 2;
    
    return nextHigherOneBit | rightOnesPattern;
}
```

---

#### Q20: Count number of integers from 1 to n that have exactly k set bits

**Solution:**
```c
int countNumbersWithKSetBits(int n, int k) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (countSetBits(i) == k) {
            count++;
        }
    }
    return count;
}

// For large n, use combinatorics:
// The answer is sum of C(bits, k) for bits from k to floor(log2(n)) + 1
// But need to handle cases where numbers exceed n
```

---

## Practice Problems

Try these problems to test your understanding:

### Beginner

1. Write a function to check if a number has exactly one bit set.
2. Write a function to check if a number has all bits set.
3. Write a function to return the number of bits required to represent a number in binary.
4. Write a function to check if two numbers differ by exactly one bit.
5. Write a function to find the position of the only unset bit in a number that has all other bits set.

### Intermediate

6. Write a function to find the smallest power of two greater than or equal to a given number.
7. Write a function to count the number of bits that need to be flipped to convert one number to another.
8. Write a function to rotate the bits of a number.
9. Write a function to check if a number is a palindrome in binary representation.
10. Write a function to find the next number with the same number of set bits.

### Advanced

11. Implement a function to multiply two numbers using only bitwise operations and addition.
12. Implement a function to divide two numbers using only bitwise operations and subtraction.
13. Write a function to find the longest sequence of 1s in the binary representation of a number.
14. Write a function to count the number of integers from 1 to n that have exactly k set bits.
15. Write a function to find the two numbers in an array that appear exactly once (all others appear twice) using bitwise operations.

### Real-world Applications

16. Implement a simple checksum calculator for a data buffer.
17. Create a function to pack four 8-bit values into a 32-bit integer.
18. Create a function to unpack a 32-bit integer into four 8-bit values.
19. Implement a function to reverse the bits in a byte.
20. Create a bitmask-based state machine for a simple device controller.

---

## Common Bit Manipulation Tricks

| Operation | Expression | Example |
|-----------|------------|---------|
| Check if nth bit is set | `(num >> n) & 1` | `(5 >> 2) & 1` = 1 |
| Set nth bit | `num \| (1 << n)` | `5 \| (1 << 1)` = 7 |
| Clear nth bit | `num & ~(1 << n)` | `7 & ~(1 << 1)` = 5 |
| Toggle nth bit | `num ^ (1 << n)` | `5 ^ (1 << 1)` = 7 |
| Get lowest set bit | `num & -num` | `12 & -12` = 4 |
| Clear lowest set bit | `num & (num - 1)` | `12 & 11` = 8 |
| Check if power of two | `(n & (n - 1)) == 0` | `(8 & 7) == 0` |
| Count set bits | `__builtin_popcount(n)` | `__builtin_popcount(5)` = 2 |
| Find LSB position | `__builtin_ctz(n)` | `__builtin_ctz(8)` = 3 |
| Find MSB position | `31 - __builtin_clz(n)` | `31 - __builtin_clz(8)` = 3 |

---

## Performance Considerations

1. **Use unsigned types** when possible to avoid sign-extension issues.
2. **Compiler intrinsics** like `__builtin_popcount`, `__builtin_ctz`, etc., are highly optimized.
3. **Portability**: Bit manipulation behavior can be implementation-defined for signed integers.
4. **Endianness**: Be aware of byte order when working with multi-byte values.
5. **Undefined behavior**: Shifting by more than the bit width is undefined.

---

## Common Pitfalls

1. **Shifting signed integers**: Right shift of negative numbers is implementation-defined.
2. **Overflow**: Shifting left can cause overflow if the result doesn't fit in the type.
3. **Undefined behavior**: Shifting by a negative amount or by >= the bit width.
4. **Sign extension**: When casting between signed and unsigned types.
5. **Bit field portability**: Bit field ordering and padding are implementation-defined.

---

## Compiler-Specific Built-ins

### GCC/Clang Built-ins

```c
int __builtin_popcount(unsigned int x);        // Count set bits
int __builtin_popcountll(unsigned long long x); // For 64-bit
int __builtin_parity(unsigned int x);          // Parity (even=0, odd=1)
int __builtin_clz(unsigned int x);             // Count leading zeros
int __builtin_ctz(unsigned int x);             // Count trailing zeros
int __builtin_clzll(unsigned long long x);     // For 64-bit
int __builtin_ctzll(unsigned long long x);     // For 64-bit
```

### MSVC Built-ins

```c
#include <intrin.h>
int __popcnt(unsigned int x);
unsigned char _BitScanForward(unsigned long *index, unsigned long mask);
unsigned char _BitScanReverse(unsigned long *index, unsigned long mask);
```

---

## Resources

### Books
- "Hacker's Delight" by Henry S. Warren, Jr.
- "Bit Twiddling Hacks" by Sean Eron Anderson
- "Computer Systems: A Programmer's Perspective" by Randal E. Bryant and David R. O'Hallaron

### Online Resources
- [Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html)
- [GeeksforGeeks Bit Manipulation](https://www.geeksforgeeks.org/bit-manipulation/)
- [LeetCode Bit Manipulation Problems](https://leetcode.com/tag/bit-manipulation/)

### Practice Platforms
- LeetCode
- HackerRank
- Codeforces
- Codewars

---

## Conclusion

Bit manipulation is a powerful tool in a programmer's toolkit. It allows for:

- **Efficient data representation** (flags, bitmasks)
- **Faster computations** (bitwise operations are single instructions)
- **Memory optimization** (storing more data in less space)
- **Low-level hardware control** (device registers, communication protocols)

Mastering bit manipulation takes practice. Start with the basics, work through the examples, and solve the interview questions. With time and experience, you'll develop an intuitive understanding of how to manipulate individual bits effectively.

**Happy Bit Manipulating!**
