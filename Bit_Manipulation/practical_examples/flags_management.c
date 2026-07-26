/*****************************************************************************
 * Flags Management - Example
 * 
 * Demonstrates how to use bit manipulation for managing multiple boolean flags
 * in a single integer variable.
 * 
 * Compile: gcc flags_management.c -o flags_management
 * Run: ./flags_management
 *****************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Helper function to print binary representation
void printBinary(uint32_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

// Define file permissions flags
#define PERM_READ    (1 << 0)  // 0001
#define PERM_WRITE   (1 << 1)  // 0010
#define PERM_EXECUTE (1 << 2)  // 0100
#define PERM_DELETE  (1 << 3)  // 1000

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              FLAGS MANAGEMENT\n");
    printf("================================================================\n\n");

    uint32_t permissions = 0;
    
    printf("Initial permissions: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n\n");

    // Set flags
    printf("Setting permissions:\n");
    permissions |= PERM_READ;
    printf("  +READ: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n");
    
    permissions |= PERM_WRITE;
    printf("  +WRITE: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n");
    
    permissions |= PERM_EXECUTE;
    printf("  +EXECUTE: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n\n");

    // Check flags
    printf("Checking permissions:\n");
    printf("  Has READ: %s\n", (permissions & PERM_READ) ? "YES" : "NO");
    printf("  Has WRITE: %s\n", (permissions & PERM_WRITE) ? "YES" : "NO");
    printf("  Has EXECUTE: %s\n", (permissions & PERM_EXECUTE) ? "YES" : "NO");
    printf("  Has DELETE: %s\n\n", (permissions & PERM_DELETE) ? "YES" : "NO");

    // Remove a flag
    printf("Removing WRITE permission:\n");
    permissions &= ~PERM_WRITE;
    printf("  Permissions: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n\n");

    // Toggle a flag
    printf("Toggling DELETE permission:\n");
    permissions ^= PERM_DELETE;
    printf("  After toggle: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n");
    permissions ^= PERM_DELETE;
    printf("  After toggle again: 0x%08X (0b", permissions);
    printBinary(permissions, 8);
    printf(")\n\n");

    // Check all required flags
    printf("Checking if all required flags are set:\n");
    uint32_t required = PERM_READ | PERM_EXECUTE;
    bool allSet = (permissions & required) == required;
    printf("  Required: READ and EXECUTE\n");
    printf("  Result: %s\n\n", allSet ? "ALL SET" : "NOT ALL SET");

    // Check if any flag is set
    printf("Checking if any of READ or WRITE are set:\n");
    uint32_t anyFlags = PERM_READ | PERM_WRITE;
    bool anySet = (permissions & anyFlags) != 0;
    printf("  Check: READ or WRITE\n");
    printf("  Result: %s\n\n", anySet ? "AT LEAST ONE IS SET" : "NONE SET");

    // Practical example: Device status flags
    printf("Practical Example - Device Status Flags:\n");
    #define DEVICE_POWER_ON   (1 << 0)
    #define DEVICE_READY      (1 << 1)
    #define DEVICE_ERROR       (1 << 2)
    #define DEVICE_BUSY        (1 << 3)
    #define DEVICE_CONNECTED   (1 << 4)

    uint32_t deviceStatus = DEVICE_POWER_ON | DEVICE_READY | DEVICE_CONNECTED;
    
    printf("  Status: 0x%08X (0b", deviceStatus);
    printBinary(deviceStatus, 8);
    printf(")\n");
    printf("  Power: %s\n", (deviceStatus & DEVICE_POWER_ON) ? "ON" : "OFF");
    printf("  Ready: %s\n", (deviceStatus & DEVICE_READY) ? "YES" : "NO");
    printf("  Error: %s\n", (deviceStatus & DEVICE_ERROR) ? "YES" : "NO");
    printf("  Busy: %s\n", (deviceStatus & DEVICE_BUSY) ? "YES" : "NO");
    printf("  Connected: %s\n\n", (deviceStatus & DEVICE_CONNECTED) ? "YES" : "NO");

    // Check device state
    printf("Device state checks:\n");
    if ((deviceStatus & DEVICE_POWER_ON) && (deviceStatus & DEVICE_READY)) {
        printf("  Device is powered on and ready\n");
    }
    if (deviceStatus & DEVICE_ERROR) {
        printf("  Device has an error!\n");
    }
    if ((deviceStatus & DEVICE_POWER_ON) && !(deviceStatus & DEVICE_CONNECTED)) {
        printf("  Device is powered but not connected\n");
    }
    printf("\n");

    // Multiple flags operations
    printf("Multiple flag operations:\n");
    uint32_t allFlags = DEVICE_POWER_ON | DEVICE_READY | DEVICE_ERROR | DEVICE_BUSY | DEVICE_CONNECTED;
    uint32_t activeFlags = DEVICE_POWER_ON | DEVICE_READY | DEVICE_CONNECTED;
    
    printf("  All possible flags: 0x%08X\n", allFlags);
    printf("  Active flags: 0x%08X\n", activeFlags);
    printf("  Inactive flags: 0x%08X\n", allFlags & ~activeFlags);
    printf("  Common flags: 0x%08X\n", allFlags & activeFlags);
    printf("\n");

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
