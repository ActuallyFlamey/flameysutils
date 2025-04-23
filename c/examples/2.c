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
    int array[4];
    va_list range;

    arghelper(&range, 6, 43);

    vcarrinput("for example %d or %d: ", "Give me element number %d, ", "%d", array, sizeof(int), 0, 3, true, "\nInvalid value. Try again.\n", is_in_range, range, 6, 43);

    va_end(range);

    printf("\n");

    printarr(array, "%d", 0, 3);

    return 0;
}
