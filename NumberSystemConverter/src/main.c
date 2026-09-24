#include "converter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256
#define OUTPUT_SIZE 65

static void print_menu(void)
{
    printf("\n");
    printf("Number System Converter\n");
    printf("=======================\n");
    printf("1. Binary\n");
    printf("2. Octal\n");
    printf("3. Decimal\n");
    printf("4. Hexadecimal\n");
    printf("5. Exit\n");
}

static int read_choice(const char *prompt)
{
    char input[INPUT_SIZE];
    char *end;
    long choice;

    printf("%s", prompt);

    if (fgets(input, sizeof(input), stdin) == NULL)
        return -1;

    choice = strtol(input, &end, 10);

    if (end == input)
        return -1;

    return (int)choice;
}

static void remove_newline(char *str)
{
    size_t length = strlen(str);

    if (length > 0 && str[length - 1] == '\n')
        str[length - 1] = '\0';
}

int main(void)
{
    char input[INPUT_SIZE];
    char output[OUTPUT_SIZE];

    while (1)
    {
        print_menu();

        int input_choice = read_choice("\nSelect input system: ");

        if (input_choice == 5)
        {
            printf("Goodbye!\n");
            break;
        }

        int input_base = get_base(input_choice);

        if (input_base == 0)
        {
            printf("Invalid input system.\n");
            continue;
        }

        printf("Enter number: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput error.\n");
            break;
        }

        remove_newline(input);

        unsigned long long value;

        if (!parse_number(input, input_base, &value))
        {
            printf("Invalid %d-base number.\n", input_base);
            continue;
        }

        int output_choice = read_choice(
            "\nSelect output system (1-4): "
        );

        if (output_choice < 1 || output_choice > 4)
        {
            printf("Invalid output system.\n");
            continue;
        }

        int output_base = get_base(output_choice);

        if (!format_number(
                value,
                output_base,
                output,
                sizeof(output)))
        {
            printf("Conversion failed.\n");
            continue;
        }

        printf("\nResult: %s\n", output);
    }

    return EXIT_SUCCESS;
}