#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <flameysutils.h>

bool is_in_range(void* number, va_list range)
{
    int min = va_arg(range, int);
    int max = va_arg(range, int);

    return *(int*) number >= min && *(int*) number <= max;
}

int main()
{
    int test;
    va_list range;

    arghelper(&range, 8, 16);

    vcinput("Look at these cool numbers: %d, %d, %d! Can you give me another? ", "%d", &test, "\nThat's not a cool number.\n", is_in_range, range, 10, 16, 14);

    va_end(range);

    printf("\nYes! %d is so cool!\n", test);

    return 0;
}
