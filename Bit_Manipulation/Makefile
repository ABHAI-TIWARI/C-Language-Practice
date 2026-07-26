# Makefile for Bit Manipulation Tutorial
# 
# Each C file is a standalone program that can be compiled and run independently.
# 
# Usage:
#   make all      - Compile all programs
#   make clean    - Remove all compiled programs
#   make run      - Compile and run all programs
#   make list     - List all available targets
#   make <target> - Compile and run specific program
#
# Direct compilation:
#   gcc bitwise_operators/and_operator.c -o and_operator
#   ./and_operator

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# Get all C files recursively
SRCS := $(shell find . -name "*.c" -type f)
TARGETS := $(patsubst %.c,%,$(notdir $(SRCS)))

all: compile-all

compile-all: compile-bitwise-operators compile-basic-operations compile-common-techniques compile-practical-examples compile-interview-questions

# Compile all in a subdirectory
compile-bitwise-operators:
	$(CC) $(CFLAGS) -o and_operator bitwise_operators/and_operator.c
	$(CC) $(CFLAGS) -o or_operator bitwise_operators/or_operator.c
	$(CC) $(CFLAGS) -o xor_operator bitwise_operators/xor_operator.c
	$(CC) $(CFLAGS) -o not_operator bitwise_operators/not_operator.c
	$(CC) $(CFLAGS) -o left_shift bitwise_operators/left_shift.c
	$(CC) $(CFLAGS) -o right_shift bitwise_operators/right_shift.c

compile-basic-operations:
	$(CC) $(CFLAGS) -o check_bit basic_operations/check_bit.c
	$(CC) $(CFLAGS) -o set_bit basic_operations/set_bit.c
	$(CC) $(CFLAGS) -o clear_bit basic_operations/clear_bit.c
	$(CC) $(CFLAGS) -o toggle_bit basic_operations/toggle_bit.c
	$(CC) $(CFLAGS) -o get_bit basic_operations/get_bit.c

compile-common-techniques:
	$(CC) $(CFLAGS) -o count_set_bits common_techniques/count_set_bits.c
	$(CC) $(CFLAGS) -o is_power_of_two common_techniques/is_power_of_two.c

compile-practical-examples:
	$(CC) $(CFLAGS) -o flags_management practical_examples/flags_management.c
	$(CC) $(CFLAGS) -o bit_packing practical_examples/bit_packing.c

compile-interview-questions:
	$(CC) $(CFLAGS) -o swap_bits interview_questions/swap_bits.c
	$(CC) $(CFLAGS) -o find_two_unique interview_questions/find_two_unique.c

clean:
	rm -f and_operator or_operator xor_operator not_operator left_shift right_shift
	rm -f check_bit set_bit clear_bit toggle_bit get_bit
	rm -f count_set_bits is_power_of_two
	rm -f flags_management bit_packing
	rm -f swap_bits find_two_unique

run: compile-all
	@echo "Running all bit manipulation programs..."
	@./and_operator
	@./or_operator
	@./xor_operator
	@./not_operator
	@./left_shift
	@./right_shift
	@./check_bit
	@./set_bit
	@./clear_bit
	@./toggle_bit
	@./get_bit
	@./count_set_bits
	@./is_power_of_two
	@./flags_management
	@./bit_packing
	@./swap_bits
	@./find_two_unique

# Run by category
run-bitwise-operators: compile-bitwise-operators
	@./and_operator
	@./or_operator
	@./xor_operator
	@./not_operator
	@./left_shift
	@./right_shift

run-basic-operations: compile-basic-operations
	@./check_bit
	@./set_bit
	@./clear_bit
	@./toggle_bit
	@./get_bit

run-common-techniques: compile-common-techniques
	@./count_set_bits
	@./is_power_of_two

run-practical-examples: compile-practical-examples
	@./flags_management
	@./bit_packing

run-interview-questions: compile-interview-questions
	@./swap_bits
	@./find_two_unique

# List all targets
list:
	@echo "Available make targets:"
	@echo "  make all              - Compile all programs"
	@echo "  make clean            - Remove all compiled programs"
	@echo "  make run              - Compile and run all programs"
	@echo "  make list             - Show this help"
	@echo ""
	@echo "  make compile-bitwise-operators    - Compile bitwise operator examples"
	@echo "  make compile-basic-operations     - Compile basic operation examples"
	@echo "  make compile-common-techniques    - Compile common technique examples"
	@echo "  make compile-practical-examples   - Compile practical examples"
	@echo "  make compile-interview-questions   - Compile interview question examples"
	@echo ""
	@echo "  make run-bitwise-operators    - Run all bitwise operator examples"
	@echo "  make run-basic-operations     - Run all basic operation examples"
	@echo "  make run-common-techniques    - Run all common technique examples"
	@echo "  make run-practical-examples   - Run all practical examples"
	@echo "  make run-interview-questions   - Run all interview question examples"

.PHONY: all clean run compile-all compile-bitwise-operators compile-basic-operations compile-common-techniques compile-practical-examples compile-interview-questions run-bitwise-operators run-basic-operations run-common-techniques run-practical-examples run-interview-questions list
