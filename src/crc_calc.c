#inlcude "crc_calc.h"

// CRC8-CCITT polynomial in hexadecimal form: 0x07
#define CRC8_POLYNOMIAL 0x07

// CRC lookup table
uint8_t crc_table[256];

// Function to initialize the CRC lookup table
void init_crc_table() {
    uint8_t remainder;

    for (int dividend = 0; dividend < 256; ++dividend) {
        remainder = dividend;

        for (uint8_t bit = 0; bit < 8; ++bit) {
            if (remainder & 0x80) {
                remainder = (remainder << 1) ^ CRC8_POLYNOMIAL;
            } else {
                remainder <<= 1;
            }
        }

        crc_table[dividend] = remainder;
    }
}

// Function to calculate CRC8-CCITT for a given data buffer using the CRC lookup table
uint8_t calculate_crc8_ccitt_with_table(const uint8_t *data, uint8_t length)
{
    uint8_t crc = 0x00;

    for (int i = 0; i < length; ++i) {
        crc = crc_table[crc ^ data[i]];
    }

    return crc;
}

/*
//Example of usage
int main() {
    uint8_t data[] = {0x10, 0x3E, 0x22};
    uint8_t length = sizeof(data) / sizeof(data[0]);
    uint8_t given_crc = 0x63;

    init_crc_table();
    uint8_t computed_crc = calculate_crc8_ccitt_with_table(data, length);
    
    if (computed_crc == given_crc) {
        printf("CRC is correct. 0x%02X\n", given_crc);
    } else {
        printf("CRC is incorrect. Expected: 0x%02X, Computed: 0x%02X\n", given_crc, computed_crc);
    }

    return 0;
}
*/