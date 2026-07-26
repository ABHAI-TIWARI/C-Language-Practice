/*****************************************************************************
 * Bit Packing - Example
 * 
 * Demonstrates how to pack multiple small values into a single integer
 * for efficient data storage.
 * 
 * Compile: gcc bit_packing.c -o bit_packing
 * Run: ./bit_packing
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

// RGB color packing (8 bits each for R, G, B)
typedef uint32_t Color;

Color packRGB(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}

void unpackRGB(Color c, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = (c >> 16) & 0xFF;
    *g = (c >> 8) & 0xFF;
    *b = c & 0xFF;
}

// RGBA color packing (with alpha/transparency)
typedef uint32_t ColorRGBA;

ColorRGBA packRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

void unpackRGBA(ColorRGBA c, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a) {
    *r = (c >> 24) & 0xFF;
    *g = (c >> 16) & 0xFF;
    *b = (c >> 8) & 0xFF;
    *a = c & 0xFF;
}

int main() {
    printf("\n");
    printf("================================================================\n");
    printf("              BIT PACKING\n");
    printf("================================================================\n\n");

    // RGB Color Packing
    printf("RGB Color Packing (24-bit):\n");
    uint8_t r = 255, g = 128, b = 0;
    Color color = packRGB(r, g, b);
    printf("  Packed: R=%u, G=%u, B=%u -> 0x%06X\n", r, g, b, color);
    
    uint8_t r2, g2, b2;
    unpackRGB(color, &r2, &g2, &b2);
    printf("  Unpacked: R=%u, G=%u, B=%u\n\n", r2, g2, b2);

    // RGBA Color Packing
    printf("RGBA Color Packing (32-bit with alpha):\n");
    r = 128, g = 64, b = 32;
    uint8_t a = 200; // Semi-transparent
    ColorRGBA rgba = packRGBA(r, g, b, a);
    printf("  Packed: R=%u, G=%u, B=%u, A=%u -> 0x%08X\n", r, g, b, a, rgba);
    
    uint8_t r3, g3, b3, a3;
    unpackRGBA(rgba, &r3, &g3, &b3, &a3);
    printf("  Unpacked: R=%u, G=%u, B=%u, A=%u\n\n", r3, g3, b3, a3);

    // Packing multiple small values
    printf("Packing 8 values of 4 bits each into 32 bits:\n");
    uint32_t packed = 0;
    uint8_t values[8] = {5, 10, 3, 7, 12, 1, 9, 4};
    
    // Pack
    for (int i = 0; i < 8; i++) {
        packed |= (values[i] & 0x0F) << (i * 4);
    }
    printf("  Original values: ");
    for (int i = 0; i < 8; i++) {
        printf("%2u ", values[i]);
    }
    printf("\n");
    printf("  Packed: 0x%08X\n", packed);
    
    // Unpack
    printf("  Unpacked values: ");
    for (int i = 0; i < 8; i++) {
        uint8_t val = (packed >> (i * 4)) & 0x0F;
        printf("%2u ", val);
    }
    printf("\n\n");

    // Sensor data packing
    printf("Sensor Data Packing:\n");
    printf("  Packing temperature (10 bits), humidity (7 bits), pressure (8 bits),\n");
    printf("  light (4 bits), and status (3 bits) into 32 bits:\n\n");
    
    // Simulated sensor data
    uint32_t temperature = 750;   // 75.0 degrees (scaled by 10), 10 bits
    uint32_t humidity = 65;      // 65%%, 7 bits
    uint32_t pressure = 101;     // 101 kPa, 8 bits
    uint32_t light = 12;         // Light level 0-15, 4 bits
    uint32_t status = 2;         // Status code 0-7, 3 bits
    
    // Pack into 32 bits
    uint32_t sensorData = ((temperature & 0x3FF) << 20) | \
                         ((humidity & 0x7F) << 13) | \
                         ((pressure & 0xFF) << 5) | \
                         ((light & 0x0F) << 1) | \
                         (status & 0x07);
    
    printf("  Packed sensor data: 0x%08X\n", sensorData);
    
    // Unpack
    uint32_t tempOut = (sensorData >> 20) & 0x3FF;
    uint32_t humOut = (sensorData >> 13) & 0x7F;
    uint32_t presOut = (sensorData >> 5) & 0xFF;
    uint32_t lightOut = (sensorData >> 1) & 0x0F;
    uint32_t statOut = sensorData & 0x07;
    
    printf("  Unpacked:\n");
    printf("    Temperature: %u (scaled by 10)\n", tempOut);
    printf("    Humidity: %u%%\n", humOut);
    printf("    Pressure: %u kPa\n", presOut);
    printf("    Light: %u\n", lightOut);
    printf("    Status: %u\n\n", statOut);

    // Memory efficiency comparison
    printf("Memory Efficiency:\n");
    printf("  Without packing (5 separate uint32_t): %zu bytes\n", 5 * sizeof(uint32_t));
    printf("  With packing (1 uint32_t): %zu bytes\n", sizeof(uint32_t));
    printf("  Savings: %.1f%%\n\n", 100.0 * (1.0 - 1.0/5.0));

    // Pack four 8-bit values into 32-bit
    printf("Packing four 8-bit values into 32-bit:\n");
    uint8_t a1 = 0x12, b1 = 0x34, c1 = 0x56, d1 = 0x78;
    uint32_t packed32 = (a1 << 24) | (b1 << 16) | (c1 << 8) | d1;
    printf("  Packed: 0x%02X, 0x%02X, 0x%02X, 0x%02X -> 0x%08X\n", a1, b1, c1, d1, packed32);
    
    uint8_t a2 = (packed32 >> 24) & 0xFF;
    uint8_t b2 = (packed32 >> 16) & 0xFF;
    uint8_t c2 = (packed32 >> 8) & 0xFF;
    uint8_t d2 = packed32 & 0xFF;
    printf("  Unpacked: 0x%02X, 0x%02X, 0x%02X, 0x%02X\n\n", a2, b2, c2, d2);

    printf("================================================================\n");
    printf("                         END\n");
    printf("================================================================\n\n");

    return 0;
}
