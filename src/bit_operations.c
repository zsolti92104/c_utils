void print_bits(uint8_t num)
{
    printf("\n0b");
    uint8_t bit;
    for(int i = 0; i < 8; i++)
    {
        bit = ((num << i) & 0x80) > 0 ? 1 : 0;
        printf("%d", bit);
    }
}