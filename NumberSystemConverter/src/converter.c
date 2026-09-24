#include "converter.h"

#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

static int char_to_value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}

bool parse_number(const char *str, int base, unsigned long long *value)
{
    unsigned long long result = 0;

    if (str == NULL || value == NULL)
        return false;

    if (base != 2 && base != 8 && base != 10 && base != 16)
        return false;

    if (*str == '\0')
        return false;

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        int digit = char_to_value(str[i]);

        if (digit < 0 || digit >= base)
            return false;

        /*
         * Check for overflow before:
         *
         * result = result * base + digit
         */
        if (result > (ULLONG_MAX - (unsigned long long)digit) /
                         (unsigned long long)base)
        {
            return false;
        }

        result = result * (unsigned long long)base +
                 (unsigned long long)digit;
    }

    *value = result;
    return true;
}

bool format_number(unsigned long long value,
                   int base,
                   char *buffer,
                   unsigned long buffer_size)
{
    const char digits[] = "0123456789ABCDEF";
    char temp[65];
    size_t index = 0;
    size_t output_length;

    if (buffer == NULL || buffer_size == 0)
        return false;

    if (base != 2 && base != 8 && base != 10 && base != 16)
        return false;

    /*
     * Special case for zero.
     */
    if (value == 0)
    {
        if (buffer_size < 2)
            return false;

        buffer[0] = '0';
        buffer[1] = '\0';

        return true;
    }

    /*
     * Build the number backwards.
     */
    while (value > 0)
    {
        temp[index++] = digits[value % base];
        value /= base;
    }

    output_length = index;

    if (output_length + 1 > buffer_size)
        return false;

    /*
     * Reverse the result into the output buffer.
     */
    for (size_t i = 0; i < output_length; i++)
    {
        buffer[i] = temp[output_length - i - 1];
    }

    buffer[output_length] = '\0';

    return true;
}

int get_base(int choice)
{
    switch (choice)
    {
        case 1:
            return 2;

        case 2:
            return 8;

        case 3:
            return 10;

        case 4:
            return 16;

        default:
            return 0;
    }
}