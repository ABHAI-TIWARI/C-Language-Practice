#include <stdio.h>

// Step 1: define the opeartions

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}
int mul(int a, int b) {
    return a * b;
}
int div(int a, int b) {
    return a / b;
}

// Step 2: Lokup table - struct holding op char + function pointer

typedef struct {
    char op;
    int (*fn)(int, int);
} operation_t;

operation_t optable[] = {
    {'+', add},
    {'-', sub},
    {'*', mul},
    {'/', div},
};

// step 3: calculatior dispatcher via table lookup

int calculate(char op, int a, int b) {
    for (int i = 0; i < sizeof(optable) / sizeof(operation_t); i++) {
        if (optable[i].op == op) {
            return optable[i].fn(a, b);
        }
    }
    printf("Error: unknown operator '%c'\n", op);
    return 0; // default case
}

int main() {
    printf("3 + 4 = %d\n", calculate('+', 3, 4));
    printf("10 - 5 = %d\n", calculate('-', 10, 5));
    printf("6 * 7 = %d\n", calculate('*', 6, 7));
    printf("20 / 10 = %d\n", calculate('/', 20,10));

    return 0;
}