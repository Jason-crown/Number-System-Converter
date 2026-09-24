#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdbool.h>

/*
 * Convert a string in the specified base to an unsigned integer.
 *
 * Returns true on success and stores the result in *value.
 * Returns false if the input contains invalid characters or overflows.
 */
bool parse_number(const char *str, int base, unsigned long long *value);

/*
 * Convert an unsigned integer to a string in the specified base.
 *
 * The resulting string is stored in buffer.
 */
bool format_number(unsigned long long value,
                   int base,
                   char *buffer,
                   unsigned long buffer_size);

/*
 * Return the numeric base associated with a menu choice.
 */
int get_base(int choice);

#endif