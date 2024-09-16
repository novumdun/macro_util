#include "macro_bits_opt.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned int var = 0;
    unsigned long long varl = 0;

    printf("size %d\r\n", sizeof(varl));

    varl = BITS_MASK(0, 31);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK(0, 63);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK(2, 31);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK(2, 63);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK(2, 5);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_MASK_LEN(0, 32);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK_LEN(0, 64);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_MASK_LEN(2, 3);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_UNSET(0x12345678, 0, 3);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_UNSET_LEN(0x12345678, 4, 4);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_UNSET_LEN(0x12345678, 28, 4);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_UNSET_LEN(0x123456789abcdef0, 60, 4);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_SET(0, 0, 31);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_SET(0, 0, 63);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_SET_LEN(0, 0, 64);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_SET_LEN(0x123456789abcdef0, 60, 4);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_SET_LEN(0x123456789abcdef0, 63, 1);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_SET_VAL(0x12345678, 32, 63, 0x9abcdef0);
    // varl = BITS_UNSET((0x12345678), (32), (63));
    // printf("%d %0#16lx\r\n", __LINE__, varl);
    // varl = varl | ((0x9abcdef0UL) << (32));
    printf("%d %0#16lx\r\n", __LINE__, varl);


    varl = BITS_SET_VAL_LEN(0x12345678, 32, 32, 0x9abcdef0);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_SET_VAL_LEN(0x123456789abcdef0, 60, 4, 0xC);
    printf("%d %0#16lx\r\n", __LINE__, varl);

    varl = BITS_GET_VAL(0x123456789abcdef0, 0, 31);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_GET_VAL(0x123456789abcdef0, 32, 63);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_GET_VAL_LEN(0x123456789abcdef0, 32, 32);
    printf("%d %0#16lx\r\n", __LINE__, varl);
    varl = BITS_GET_VAL_LEN(0x123456789abcdef0, 60, 4);
    printf("%d %0#16lx\r\n", __LINE__, varl);

}
