#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

#include <stdbool.h>

const unsigned int START_NUMBER_CHAR = 48;
const unsigned int COUNT_NUMBER_CHAR = 10;
const unsigned int START_SYMBOL_CHAR = 65;
const unsigned int COUNT_SYMBOL_CHAR = 26;
const unsigned int START_SMALL_SYMBOL_CHAR = 97;
const unsigned int COUNT_SMALL_SYMBOL_CHAR = 26;

int get_char_position(char el);

int return_and_error();
int return_and_error_tuple_1(void *ptr);
int return_and_error_tuple_2(void *ptr1, void *ptr2);

long get_decimal(const unsigned int notation, char* string_elements, int n)
{
    long number = 0;
    int power = 0, el = 0;

    for(int i = n - 1; i >= 0; i--)
    {
        el = get_char_position(string_elements[i]);
        if(el >= notation)
        {
            return -1;
        }
        number += el * pow(notation, power);
        ++power;
    }
    return number;
}

void to_notation(long decimal_number, const unsigned int notation, char* digits, char* out)
{
    static int i = 0, n;
    if (decimal_number) {
        ++i;
        to_notation(decimal_number / notation, notation, digits, out);
        out[n - i--] = digits[decimal_number % notation];
    }
    else if(i == 0)
    {
        out[i++] = '0';
        out[n = i] = '\0';
    }
    else

        out[n = i] = '\0';

}

int init_digits(char* const digits)
{
    if(!digits)

        return 1;

    char *ptr = digits;

    for(int i = START_NUMBER_CHAR; i < START_NUMBER_CHAR + COUNT_NUMBER_CHAR; i++)
    {
        *ptr = i;
        ptr++;
    }

    for(int i = START_SMALL_SYMBOL_CHAR; i <  START_SMALL_SYMBOL_CHAR + COUNT_SYMBOL_CHAR; i++)
    {
        *ptr = i;
        ptr++;
    }

    return 0;
}

int get_char_position(char el)
{
    const unsigned int ELEMENTS_IN_DIGIT = 0;
    const unsigned int ELEMENTS_IN_SYMBOL = 10;

    if(el >= START_NUMBER_CHAR && el < START_NUMBER_CHAR + COUNT_NUMBER_CHAR)

        return el - START_NUMBER_CHAR + ELEMENTS_IN_DIGIT;

    else if(el >= START_SYMBOL_CHAR && el < START_SYMBOL_CHAR + COUNT_SYMBOL_CHAR)

        return el - START_SYMBOL_CHAR + ELEMENTS_IN_SYMBOL;

    else if(el >= START_SMALL_SYMBOL_CHAR && el < START_SMALL_SYMBOL_CHAR + COUNT_SMALL_SYMBOL_CHAR)

        return el - START_SMALL_SYMBOL_CHAR + ELEMENTS_IN_SYMBOL;

    else

        return -1;
}

bool check_normal_notation(int n)
{
    if(n >= 2 && n <= 36)
        return true;

    return false;
}

int main()
{
    const unsigned int COUNT_NUMBER_FOR_ALL_NOTATIONS = 36;
    const unsigned int BUFFER_SIZE = 256;

    int notation_from, notation_to;
    char *buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
    
    if(!buffer)
    
        return return_and_error();
        
    int err = 0;

    char* digits = (char*) malloc(COUNT_NUMBER_FOR_ALL_NOTATIONS * sizeof(char));
    
    err = init_digits(digits);
    if(err)

        return return_and_error_tuple_1(buffer);

    err = scanf("%d %d", &notation_from, &notation_to);
    if((err != 2))
        return return_and_error_tuple_2(buffer, digits);

    if((!check_normal_notation(notation_from)) || (!check_normal_notation(notation_to)))
        return return_and_error_tuple_2(buffer, digits);

    err = scanf("%s", buffer);
    if(err != 1 || (!feof(stdin) && getc(stdin) != 10))

      return return_and_error_tuple_2(buffer, digits);

    int length_of_number = strlen(buffer);
    long decimal = get_decimal(notation_from, buffer, length_of_number);
    if(decimal < 0)
        return return_and_error_tuple_2(buffer, digits);

    memset(buffer, 0, BUFFER_SIZE);
    to_notation(decimal, notation_to, digits, buffer);

    if(buffer)
        printf("%s", buffer);
    else
        printf("%s", "[error]");

    free(buffer);
    free(digits);
    return 0;
}

int return_and_error()
{
    printf("[error]");
    return 0;
}

int return_and_error_tuple_1(void *ptr)
{
    free(ptr);

    printf("[error]");
    return 0;
}

int return_and_error_tuple_2(void *ptr1, void *ptr2)
{
    free(ptr1);
    free(ptr2);

    printf("[error]");
    return 0;
}
