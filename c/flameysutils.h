/**
    * @file flameysutils.h
    * @author Flamey (flamey@hexa.blue)
    * @brief Some useful functions that I use often.
    * @version 0.2.0
    * @date 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

/*
    MISCELLANEOUS UTILITIES
*/

/**
    * @brief Swaps the values of two variables.
    *
    * @param a Pointer to the first variable.
    * @param b Pointer to the second variable.
    * @param size Size of the variables.
*/
void swap(void* a, void* b, size_t size)
{
    void* swapper = malloc(size);

    memcpy(swapper, b, size);
    memcpy(b, a, size);
    memcpy(a, swapper, size);

    free(swapper);
}

/**
    * @brief Fills a `va_list` with the specified variadic arguments.
    *           You are given the responsibility to run `va_end()` on the `va_list` when you've finished using it.
    *
    * @param dest Pointer to the destination `va_list`.
    * @param ... Arguments to put inside the `va_list`.
*/
void arghelper
(
    va_list* dest,
    ...
)
{
    va_list args;
    va_start(args, dest);

    va_copy(*dest, args);

    va_end(args);
}

/*
    INPUT FUNCTIONS
*/

/**
    * @brief Writes a hint towards what the user should insert, then puts the user input inside a variable.
    *           Values from the `va_list` can be written inside the hint.
    *
    *        ### The average user should not use this: use `input()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void vinput
(
    const char* text,
    const char* format,
    void* pointer,
    va_list args
)
{
    vprintf(text, args);
    fflush(stdin);
    scanf(format, pointer);
}

/**
    * @brief Writes a hint towards what the user should insert, then puts the user input inside a variable.
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param ... Values for `text`'s formats.
*/
void input
(
    const char* text,
    const char* format,
    void* pointer,
    ...
)
{
    va_list args;
    va_start(args, pointer);

    vinput(text, format, pointer, args);

    va_end(args);
}

/**
    * @brief Same as `input()`, but checks the input against a condition and retries if it doesn't match.
    *           Values from the `va_list` can be written inside the hint.
    * 
    *        ### The average user should not use this: use `cinput()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test against constants.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void cvinput
(
    const char* text,
    const char* format,
    void* pointer,
    const char* fail,
    bool (*condition)(void*),
    va_list args
)
{
    va_list copy;

    do
    {
        va_copy(copy, args);

        vinput(text, format, pointer, copy);

        if (!(*condition)(pointer))
        {
            printf(fail);
        }
    } while (!(*condition)(pointer));

    va_end(copy);
}

/**
    * @brief Same as `input()`, but checks the input against a condition and retries if it doesn't match.
    * 
    *        Example `condition` function:
    *```c
    *bool is_greater_than_4(void* number)
    *{
    *    return *(int*) number > 4;
    *}
    *```
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test against constants.
    * @param ... Values for `text`'s formats.
*/
void cinput
(
    const char* text,
    const char* format,
    void* pointer,
    const char* fail,
    bool (*condition)(void*),
    ...
)
{
    va_list args;
    va_start(args, condition);

    cvinput(text, format, pointer, fail, condition, args);

    va_end(args);
}

/**
    * @brief Same as `input()`, but checks the input against a condition and retries if it doesn't match.
    *           Values from the `va_list` can be written inside the hint.
    *           The condition function can take in a `va_list` if it needs other arguments.
    * 
    *        ### The average user should not use this: use `vcinput()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test the user's input against.
    * @param condargs `va_list` used by `condition`.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void vcvinput
(
    const char* text,
    const char* format,
    void* pointer,
    const char* fail,
    bool (*condition)(void*, va_list),
    va_list condargs,
    va_list args
)
{
    va_list argscopy, condargscopy;

    do
    {
        va_copy(argscopy, args);
        va_copy(condargscopy, condargs);

        vinput(text, format, pointer, argscopy);
 
        if (!(*condition)(pointer, condargscopy))
        {
            printf(fail);
        }

        va_copy(condargscopy, condargs);
    } while (!(*condition)(pointer, condargscopy));

    va_end(argscopy);
    va_end(condargscopy);
}

/**
    * @brief Same as `input()`, but checks the input against a condition and retries if it doesn't match.
    *           The condition function can take in a `va_list` if it needs other arguments.
    * 
    *        Example `condition` function:
    *```c
    *bool is_in_range(void* number, va_list range)
    *{
    *    int min = va_arg(range, int);
    *    int max = va_arg(range, int);
    *
    *    return *(int*) number >= min && *(int*) number <= max;
    *}
    *```
    * 
    *        You can use the `arghelper()` function from this header to make the `va_list` that you will pass to this function.
    *           Make sure to run `va_end()` on your `va_list` variable after calling this function.
    *
    * @param text Hint to the user about what should be written.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param pointer Variable to store the user's value.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test the user's input against.
    * @param condargs `va_list` used by `condition`.
    * @param ... Values for `text`'s formats.
*/
void vcinput
(
    const char* text,
    const char* format, 
    void* pointer,
    const char* fail,
    bool (*condition)(void*, va_list),
    va_list condargs,
    ...
)
{
    va_list args;
    va_start(args, condargs);

    vcvinput(text, format, pointer, fail, condition, condargs, args);

    va_end(args);
}

/**
    * @brief Writes a hint towards what the user should insert, then puts the user input inside an array, in order.
    *           Values from the `va_list` can be written inside the hint.
    * 
    *        ### The average user should not use this: use `arrinput()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param ordinal Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array The array to be filled with the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void varrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    va_list args
)
{
    va_list copy;

    for (size_t i = start; i <= end; i++)
    {
        va_copy(copy, args);

        if (ordinalBefore)
        {
            printf(ordinal, i + 1);
            vprintf(text, copy);
        }
        else
        {
            vprintf(text, copy);
            printf(ordinal, i + 1);
        }

        fflush(stdin);
        scanf(format, array + (i * size));
    }

    va_end(copy);
}

/**
    * @brief Writes a hint towards what the user should insert, then puts the user input inside an array, in order.
    * 
    * @param text Hint to the user about what should be written.
    * @param ordinal Text to format with the current array index.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array Array to store the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param ... Values for `text`'s formats.
*/
void arrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    ...
)
{
    va_list args;
    va_start(args, ordinalBefore);

    varrinput(text, ordinal, format, array, size, start, end, ordinalBefore, args);

    va_end(args);
}

/**
    * @brief Same as `arrinput()`, but checks the input against a condition and retries if it doesn't match.
    *           Values from the `va_list` can be written inside the hint.
    * 
    *        ### The average user should not use this: use `carrinput()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param ordinal Text to format with the current array index.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array Array to store the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test against constants.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void cvarrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    const char* fail,
    bool (*condition)(void*),
    va_list args
)
{
    va_list copy;

    for (size_t i = 0; i <= end; i++)
    {
        do
        {
            va_copy(copy, args);

            if (ordinalBefore)
            {
                printf(ordinal, i + 1);
                vprintf(text, copy);
            }
            else
            {
                vprintf(text, copy);
                printf(ordinal, i + 1);
            }

            fflush(stdin);
            scanf(format, array + (i * size));

            if (!(*condition)(array + (i * size)))
            {
                printf(fail);
            }
        } while (!(*condition)(array + (i * size)));
    }

    va_end(copy);
}

/**
    * @brief Same as `arrinput()`, but checks the input against a condition and retries if it doesn't match.
    * 
    * @param text Hint to the user about what should be written.
    * @param ordinal Text to format with the current array index.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array Array to store the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test against constants.
    * @param ... Values for `text`'s formats.
*/
void carrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    const char* fail,
    bool (*condition)(void*),
    ...
)
{
    va_list args;
    va_start(args, condition);

    cvarrinput(text, ordinal, format, array, size, start, end, ordinalBefore, fail, condition, args);

    va_end(args);
}

/**
    * @brief Same as `arrinput()`, but checks the input against a condition and retries if it doesn't match.
    *           Values from the `va_list` can be written inside the hint.
    *           The condition function can take in a `va_list` if it needs other arguments.
    * 
    *        ### The average user should not use this: use `vcarrinput()` instead.
    *
    * @param text Hint to the user about what should be written.
    * @param ordinal Text to format with the current array index.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array Array to store the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test the user's input against.
    * @param condargs `va_list` used by `condition`.
    * @param args `va_list` for `vprintf()` used by `text`.
*/
void vcvarrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    const char* fail,
    bool (*condition)(void*, va_list),
    va_list condargs,
    va_list args
)
{
    va_list copy, condargscopy;

    for (size_t i = 0; i <= end; i++)
    {
        do
        {
            va_copy(copy, args);
            va_copy(condargscopy, condargs);

            if (ordinalBefore)
            {
                printf(ordinal, i + 1);
                vprintf(text, copy);
            }
            else
            {
                vprintf(text, copy);
                printf(ordinal, i + 1);
            }

            fflush(stdin);
            scanf(format, array + (i * size));

            if (!(*condition)(array + (i * size), condargscopy))
            {
                printf(fail);
            }

            va_copy(condargscopy, condargs);
        } while (!(*condition)(array + (i * size), condargscopy));
    }

    va_end(copy);
    va_end(condargscopy);
}

/**
    * @brief Same as `carrinput()`, but checks the input against a condition and retries if it doesn't match.
    *           The condition function can take in a `va_list` if it needs other arguments.
    * 
    *        Example `condition` function:
    *```c
    *bool is_in_range(void* number, va_list range)
    *{
    *    int min = va_arg(range, int);
    *    int max = va_arg(range, int);
    *
    *    return *(int*) number >= min && *(int*) number <= max;
    *}
    *```
    * 
    *        You can use the `arghelper()` function from this header to make the `va_list` that you will pass to this function.
    *           Make sure to run `va_end()` on your `va_list` variable after calling this function.
    *
    * @param text Hint to the user about what should be written.
    * @param ordinal Text to format with the current array index.
    * @param format C format specifier that will be passed to `scanf()`'s first argument.
    * @param array Array to store the user's values.
    * @param size Size of each array element.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param ordinalBefore Whether or not to display `ordinal` before or after `text`.
    * @param fail Text to display if the condition is false.
    * @param condition Boolean function to test the user's input against.
    * @param condargs `va_list` used by `condition`.
    * @param ... Values for `text`'s formats.
*/
void vcarrinput
(
    const char* text,
    const char* ordinal,
    const char* format,
    void* array,
    size_t size,
    size_t start,
    size_t end,
    bool ordinalBefore,
    const char* fail,
    bool (*condition)(void*, va_list),
    va_list condargs,
    ...
)
{
    va_list args;
    va_start(args, condargs);

    vcvarrinput(text, ordinal, format, array, size, start, end, ordinalBefore, fail, condition, condargs, args);

    va_end(args);
}

/*
    PRINTING FUNCTIONS
*/

/**
    * @brief Prints an array to the standard input in [0, 1, 2, 3, ...] format.
    * 
    * @param array The array to print.
    * @param format C format specifier for the array elements.
    * @param start The array index to start printing from (`0` to start from the beginning).
    * @param end The array index to stop printing at (array length - 1 to finish at the end).
*/
#define printarr(array, format, start, end) ( \
{ \
    printf("["); \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (i == end) \
        { \
            printf(format, array[i]); \
        } \
        else \
        { \
            printf(format ", ", array[i]); \
        } \
    } \
    \
    printf("]\n"); \
})

/*
    RANDOMIZATION FUNCTIONS
*/

/**
    * @brief Generates a random integer inside a range.
    *
    * @param min The lowest possible number.
    * @param max The highest possible number.
    *
    * @return A random integer between `min` and `max`.
*/
int randint
(
    int min,
    int max
)
{
    return rand() % (max - min + 1) + min;
}

/**
    * @brief Inserts random integers inside an array.
    *
    * @param array The integer array to fill.
    * @param start The array index to start writing from (`0` to start from the beginning).
    * @param end The array index to stop writing at (array length - 1 to finish at the end).
    * @param min The lowest possible number.
    * @param max The highest possible number.
*/
void randints
(
    int array[],
    size_t start,
    size_t end,
    int min,
    int max
)
{
    srand(time(0));

    for (size_t i = start; i <= end; i++)
    {
        array[i] = randint(min, max);
    }
}

/*
    ARRAY UTILITIES
*/

/**
    * @brief Shuffles an array.
    * 
    * @param array The array to shuffle.
    * @param start The array index to start shuffling from (`0` to start from the beginning).
    * @param end The array index to stop shuffling at (array length - 1 to finish at the end).
*/
#define shuffle(array, start, end) ( \
{ \
    srand(time(0)); \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        size_t new_index = randint(start, end); \
        \
        swap(&array[i], &array[new_index], sizeof(array[0])); \
    } \
})

/**
    * @brief Calculates the average of an array's values.
    * 
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The average of all array values. 
*/
#define average(array, start, end) ( \
{ \
    long long sum = 0; \
    long double avg; \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        sum += array[i]; \
    } \
    \
    avg = (long double) sum / (end + 1 - start); \
    \
    avg; \
})

/**
    * @brief Finds the minimum value in an array.
    * 
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The minimum of all array values. 
*/
#define min(array, start, end) ( \
{ \
    typeof(array[0]) minimum = array[start]; \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (array[i] < minimum) minimum = array[i]; \
    } \
    \
    minimum; \
})

/**
    * @brief Finds the maximum value in an array.
    * 
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The maximum of all array values. 
*/
#define max(array, start, end) ( \
{ \
    typeof(array[0]) maximum = array[start]; \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (array[i] > maximum) maximum = array[i]; \
    } \
    \
    maximum; \
})

/**
    * @brief Finds the median value in an array.
    * 
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The median of all array values. 
*/
#define med(array, start, end) ( \
{ \
    typeof(array[0]) medium = array[start]; \
    long double avg = average(array, start, end); \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (abs(array[i] - avg) < abs(medium - avg)) medium = array[i]; \
    } \
    \
    medium; \
})

/**
    * @brief Finds the index of the minimum value in an array.
    *
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The index of the minimum value in `array`. 
*/
#define imin(array, start, end) ( \
{ \
    size_t index = start; \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (array[i] < array[index]) index = i; \
    } \
    \
    index; \
})

/**
    * @brief Finds the index of the maximum value in an array.
    *
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The index of the maximum value in `array`. 
*/
#define imax(array, start, end) ( \
{ \
    size_t index = start; \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (array[i] > array[index]) index = i; \
    } \
    \
    index; \
})

/**
    * @brief Finds the index of the median value in an array.
    *
    * @param array The array to scan.
    * @param start The array index to start scanning from (`0` to start from the beginning).
    * @param end The array index to stop scanning at (array length - 1 to finish at the end).
    *
    * @return The index of the median value in `array`. 
*/
#define imed(array, start, end) ( \
{ \
    size_t index = start; \
    long double avg = average(array, start, end); \
    \
    for (size_t i = start; i <= end; i++) \
    { \
        if (abs(array[i] - avg) < abs(array[index] - avg)) index = i; \
    } \
    \
    index; \
})

/*
    ARRAY SORTING FUNCTIONS
*/

/**
    * @brief Checks if an array is sorted.
    * 
    * @param array The array to check.
    * @param start The array index to start checking from (`0` to start from the beginning).
    * @param end The array index to stop checking at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
    *
    * @return `true` if `array` is sorted, `false` otherwise.
*/
#define is_sorted(array, start, end, compare) ( \
{ \
    bool result = true; \
    \
    for (size_t i = start + 1; i <= end; i++) \
    { \
        if ((*compare)(&array[i - 1], &array[i]) > 0) \
        { \
            result = false; \
        } \
    } \
    \
    result; \
})

/**
    * @brief Sorts an array using the Quick Sort algorithm.
    *           Partitions the array around a pivot element, then recursively sorts the left and right subarrays.
    *           This macro is a wrapper for `stdlib.h`'s `qsort()` function.
    * 
    * @param array The array to sort.
    * @param start The array index to start sorting from (`0` to start from the beginning).
    * @param end The array index to stop sorting at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
*/
#define qsort(array, start, end, compare) qsort(array + start, end + 1 - start, sizeof(array[0]), compare)

/**
    * @brief Sorts an array using the Bubble Sort algorithm.
    *           Checks two items at a time: if they aren't in order, swaps them. Iterates over the array until it is all sorted.
    * 
    * @param array The array to sort.
    * @param start The array index to start sorting from (`0` to start from the beginning).
    * @param end The array index to stop sorting at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
*/
#define bsort(array, start, end, compare) ( \
{ \
    for (size_t i = start; i < end; i++) \
    { \
        for (size_t j = start; j < end - i; j++) \
        { \
            if ((*compare)(&array[j], &array[j + 1]) > 0) \
            { \
                swap(&array[j], &array[j + 1], sizeof(array[0])); \
            } \
        } \
    } \
})

/**
    * @brief Sorts an array using the Gnome Sort algorithm.
    *           Reads through the array. When it finds an unsorted item, it runs through the previously read items to find the place to put it.
    * 
    * @param array The array to sort.
    * @param start The array index to start sorting from (`0` to start from the beginning).
    * @param end The array index to stop sorting at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
*/
#define gsort(array, start, end, compare) ( \
{ \
    for (size_t i = start + 1; i <= end; i++) \
    { \
        if ((*compare)(&array[i - 1], &array[i]) > 0) \
        { \
            for (size_t j = start; j < i; j++) \
            { \
                if (!((*compare)(&array[i], &array[j]) > 0)) \
                { \
                    swap(&array[i], &array[j], sizeof(array[0])); \
                } \
            } \
        } \
    } \
})

/**
    * @brief "Sorts" an array using the Bogosort *joke* algorithm.
    *           Shuffles the list. If it isn't sorted, shuffle again.
    * 
    * @param array The array to sort.
    * @param start The array index to start sorting from (`0` to start from the beginning).
    * @param end The array index to stop sorting at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
*/
#define bogosort(array, start, end, compare) ( \
{ \
    while (!is_sorted(array, start, end, compare)) \
    { \
        shuffle(array, start, end); \
    } \
})

/**
    * @brief "Sorts" an array using the Miracle Sort *joke* algorithm. Do not use this.
    *           Constantly checks if the list has been sorted by a cosmic ray causing a bit flip.
    * 
    * @param array The array to sort.
    * @param start The array index to start sorting from (`0` to start from the beginning).
    * @param end The array index to stop sorting at (array length - 1 to finish at the end).
    * @param compare A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.
*/
#define mrclsort(array, start, end, compare) ( \
{ \
    while (!(is_sorted(array, start, end, compare))) {} \
})

/*
    SORT DIRECTION UTILITIES
*/

/**
    * @brief Comparison function for sorting an array in ascending order.
    * 
    * @param a The first element to compare.
    * @param b The second element to compare.
    * 
    * @return The difference between the two elements.
*/
int ascending
(
    const void* a,
    const void* b
)
{
    return *(typeof(a)*) a - *(typeof(b)*) b;
}

/**
    * @brief Comparison function for sorting an array in descending order.
    * 
    * @param a The first element to compare.
    * @param b The second element to compare.
    * 
    * @return The difference between the two elements.
*/
int descending
(
    const void* a,
    const void* b
)
{
    return *(typeof(b)*) b - *(typeof(a)*) a;
}