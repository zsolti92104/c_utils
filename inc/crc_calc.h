extern uint8_t crc_table[256];

void init_crc_table();
uint8_t calculate_crc8_ccitt_with_table(const uint8_t *data, uint8_t length);