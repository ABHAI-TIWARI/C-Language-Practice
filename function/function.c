/*****************************************************************************
 * C Language Tutorial: Functions
 * 
 * This file demonstrates various aspects of functions in C:
 * - Function declaration and definition
 * - Function parameters and return values
 * - Function prototypes
 * - Pass by value vs pass by reference
 * - Recursion
 * - Variable scope in functions
 *****************************************************************************/

#include <stdio.h>

/* =========================================================================
 * 1. BASIC FUNCTION STRUCTURE
 *    Syntax: return_type function_name(parameters) { body }
 * ========================================================================= */

// Function declaration (prototype)
int add(int a, int b);

// Function definition
int add(int a, int b) {
    return a + b;
}

/* =========================================================================
 * 2. FUNCTION WITH NO PARAMETERS AND NO RETURN VALUE
 * ========================================================================= */

void greet() {
    printf("Hello, World!\n");
}

/* =========================================================================
 * 3. FUNCTION WITH PARAMETERS
 * ========================================================================= */

// Function that takes parameters and returns a value
float calculate_area(float radius) {
    const float PI = 3.14159;
    return PI * radius * radius;
}

/* =========================================================================
 * 4. FUNCTION WITH MULTIPLE PARAMETERS
 * ========================================================================= */

int calculate_volume(int length, int width, int height) {
    return length * width * height;
}

/* =========================================================================
 * 5. PASS BY VALUE vs PASS BY REFERENCE
 * ========================================================================= */

// Pass by value - modifies a copy, original remains unchanged
void increment_by_value(int num) {
    num = num + 1;
    printf("Inside increment_by_value: num = %d\n", num);
}

// Pass by reference - modifies the original variable
void increment_by_reference(int *num_ptr) {
    *num_ptr = *num_ptr + 1;
    printf("Inside increment_by_reference: num = %d\n", *num_ptr);
}

/* =========================================================================
 * 6. RECURSION
 *    A function that calls itself
 * ========================================================================= */

// Factorial using recursion: n! = n * (n-1)!
unsigned long long factorial(int n) {
    // Base case
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// Fibonacci sequence using recursion
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* =========================================================================
 * 7. FUNCTION WITH ARRAY PARAMETERS
 * ========================================================================= */

// Find sum of array elements
int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Find maximum element in array
int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* =========================================================================
 * 8. FUNCTION RETURNING MULTIPLE VALUES (using pointers)
 * ========================================================================= */

void calculate_sum_and_product(int a, int b, int *sum, int *product) {
    *sum = a + b;
    *product = a * b;
}

/* =========================================================================
 * 9. VARIABLE SCOPE IN FUNCTIONS
 * ========================================================================= */

int global_var = 100;  // Global variable - accessible everywhere

void demonstrate_scope() {
    int local_var = 50;  // Local variable - only accessible in this function
    
    printf("Inside demonstrate_scope:\n");
    printf("  global_var = %d\n", global_var);
    printf("  local_var = %d\n", local_var);
    
    // Modifying global variable
    global_var = 200;
    
    // Block scope
    if (1) {
        int block_var = 25;
        printf("  Inside block: block_var = %d\n", block_var);
    }
    // block_var is not accessible here
}

/* =========================================================================
 * 10. STATIC VARIABLES IN FUNCTIONS
 *     Retains its value between function calls
 * ========================================================================= */

int counter() {
    static int count = 0;  // Static variable - initialized only once
    count++;
    return count;
}

/* =========================================================================
 * 11. INLINE FUNCTIONS (suggested to compiler)
 * ========================================================================= */

static inline int square(int x) {
    return x * x;
}

/* =========================================================================
 * MAIN FUNCTION - Entry point of the program
 * ========================================================================= */

int main() {
    printf("\n========== C FUNCTIONS TUTORIAL ==========\n\n");
    
    /* --- 1. Basic Function --- */
    printf("1. BASIC FUNCTION:\n");
    int result = add(5, 3);
    printf("   add(5, 3) = %d\n\n", result);
    
    /* --- 2. Function with no parameters --- */
    printf("2. FUNCTION WITH NO PARAMETERS:\n");
    greet();
    printf("\n");
    
    /* --- 3. Function with parameters --- */
    printf("3. FUNCTION WITH PARAMETERS:\n");
    float radius = 5.0;
    float area = calculate_area(radius);
    printf("   Area of circle with radius %.2f = %.2f\n\n", radius, area);
    
    /* --- 4. Function with multiple parameters --- */
    printf("4. FUNCTION WITH MULTIPLE PARAMETERS:\n");
    int vol = calculate_volume(10, 5, 2);
    printf("   Volume of box (10x5x2) = %d\n\n", vol);
    
    /* --- 5. Pass by Value vs Pass by Reference --- */
    printf("5. PASS BY VALUE vs PASS BY REFERENCE:\n");
    int num = 10;
    printf("   Before: num = %d\n", num);
    
    increment_by_value(num);
    printf("   After increment_by_value: num = %d (unchanged)\n", num);
    
    increment_by_reference(&num);
    printf("   After increment_by_reference: num = %d (changed)\n\n", num);
    
    /* --- 6. Recursion --- */
    printf("6. RECURSION:\n");
    printf("   factorial(5) = %llu\n", factorial(5));
    printf("   fibonacci(10) = %d\n\n", fibonacci(10));
    
    /* --- 7. Functions with Arrays --- */
    printf("7. FUNCTIONS WITH ARRAYS:\n");
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    printf("   Sum of array = %d\n", sum_array(numbers, size));
    printf("   Max of array = %d\n\n", find_max(numbers, size));
    
    /* --- 8. Returning Multiple Values --- */
    printf("8. RETURNING MULTIPLE VALUES:\n");
    int a = 7, b = 8;
    int sum, product;
    calculate_sum_and_product(a, b, &sum, &product);
    printf("   For %d and %d: sum = %d, product = %d\n\n", a, b, sum, product);
    
    /* --- 9. Variable Scope --- */
    printf("9. VARIABLE SCOPE:\n");
    printf("   Before demonstrate_scope: global_var = %d\n", global_var);
    demonstrate_scope();
    printf("   After demonstrate_scope: global_var = %d\n\n", global_var);
    
    /* --- 10. Static Variables --- */
    printf("10. STATIC VARIABLES:\n");
    printf("   counter() called 5 times:\n");
    for (int i = 0; i < 5; i++) {
        printf("   %d ", counter());
    }
    printf("\n\n");
    
    /* --- 11. Inline Functions --- */
    printf("11. INLINE FUNCTIONS:\n");
    printf("   square(5) = %d\n", square(5));
    printf("   square(10) = %d\n\n", square(10));
    
    printf("========== END OF TUTORIAL ==========\n");
    
    return 0;
}