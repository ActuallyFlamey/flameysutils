# flameysutils.h

# Index

## Miscellaneous Utilities
- [`swap()`](#void-swap) - Swaps the values of two variables.
- [`arghelper()`](#void-arghelper) - Fills a `va_list` with the specified variadic arguments.
- [`validarrcheck()`](#void-validarrcheck) - Checks if the given array indices are valid.

## Input Functions
- [`vinput()`](#void-vinput)
- [`input()`](#void-input) - Writes a hint towards what the user should insert, then puts the user input inside a variable.
- [`cvinput()`](#void-cvinput)
- [`cinput()`](#void-cinput) - Same as [`input()`](#void-input), but checks the input against a condition and retries if it doesn't match.
- [`vcvinput()`](#void-vcvinput)
- [`vcinput()`](#void-vcinput) - Same as [`cvinput()`](#void-cvinput), but checks the input against a condition and retries if it doesn't match. The condition function can take in a `va_list` if it needs other arguments.
- [`varrinput()`](#void-varrinput)
- [`arrinput()`](#void-arrinput) - Writes a hint towards what the user should insert, then puts the user input inside an array, in order.
- [`cvarrinput()`](#void-cvarrinput)
- [`carrinput()`](#void-carrinput) - Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match.
- [`vcvarrinput()`](#void-vcvarrinput)
- [`vcarrinput()`](#void-vcarrinput) - Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match. The condition function can take in a `va_list` if it needs other arguments.

## Printing Functions
- [`printarr()` macro](#printarr-macro) - Prints an array to the standard input in [0, 1, 2, 3, ...] format.

## Randomization Functions
- [`int randint()`](#int-randint) - Generates a random integer inside a range.
- [`void randints()`](#void-randints) - Inserts random integers inside an array.

## Array Utilities
- [`arrcopy()` macro](#arrcopy-macro) - Copies the values of an array to another array.
- [`shuffle()` macro](#shuffle-macro) - Shuffles an array.
- [`average()` macro](#average-macro) - Calculates the average of an array's values.
- [`min()` macro](#min-macro) - Finds the minimum value in an array.
- [`max()` macro](#max-macro) - Finds the maximum value in an array.
- [`med()` macro](#med-macro) - Finds the median value in an array.
- [`imin()` macro](#imin-macro) - Finds the index of the minimum value in an array.
- [`imax()` macro](#imax-macro) - Finds the index of the maximum value in an array.
- [`imed()` macro](#imed-macro) - Finds the index of the median value in an array.

## Array Sorting Functions
- [`is_sorted()` macro](#is_sorted-macro) - Checks if an array is sorted.
- [`qsort()` macro](#qsort-macro) - Sorts an array using the Quick Sort algorithm.
- [`bsort()` macro](#bsort-macro) - Sorts an array using the Bubble Sort algorithm.
- [`gsort()` macro](#gsort-macro) - Sorts an array using the Gnome Sort algorithm.
- [`bogosort()` macro](#bogosort-macro) - "Sorts" an array using the Bogosort *joke* algorithm. Do not use this.
- [`mrclsort()` macro](#mrclsort-macro) - "Sorts" an array using the Miracle Sort *joke* algorithm. Do not use this.

## Sort Direction Utilities
- [`int ascending()`](#int-ascending) - Comparison function for sorting an array in ascending order.
- [`int descending()`](#int-descending) - Comparison function for sorting an array in descending order.

# Full Documentation

## Miscellaneous Utilities

### `void swap()`

#### Description
Swaps the values of two variables.

#### Parameters
- **`a`:** **`void*`** Pointer to the first variable.
- **`b`:** **`void*`** Pointer to the second variable.
- **`size`:** **`size_t`** Size of the variables.

### `void arghelper()`

#### Description
Fills a `va_list` with the specified variadic arguments.
You are given the responsibility to run `va_end()` on the `va_list` when you've finished using it.

#### Parameters
- **`dest`:** **`va_list*`** Pointer to the destination `va_list`.
- **`...`:** Arguments to put inside the `va_list`.

### `void validarrcheck()`

#### Description
Checks if the given array indices are valid.

#### Parameters
- **`array`:** **`void*`** The array to run checks on.
- **`start`:** **`size_t`** The array index given as the start.
- **`end`:** **`size_t`** The array index given as the end.
- **`funcname`:** **`const char*`** The calling function's name.

## String Utilities

### `void lowercase()`

#### Description
Converts a string to lowercase.

#### Parameters
- **`string`:** **`char*`** The string to modify.
- **`start`:** **`size_t`** The string index to start modifying from (`0` to start from the beginning).
- **`end`:** **`size_t`** The string index to stop modifying at (`strlen(string)` to stop at the end).

### `void uppercase()`

#### Description
Converts a string to uppercase.

#### Parameters
- **`string`:** **`char*`** The string to modify.
- **`start`:** **`size_t`** The string index to start modifying from (`0` to start from the beginning).
- **`end`:** **`size_t`** The string index to stop modifying at (`strlen(string)` to stop at the end).

## Input Functions

### `void vinput()`

#### Description
Writes a hint towards what the user should insert, then puts the user input inside a variable.
Values from the `va_list` can be written inside the hint.

### The average user should not use this: use [`input()`](#void-input) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void input()`

#### Description
Writes a hint towards what the user should insert, then puts the user input inside a variable.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`...`:** Values for `text`'s formats.

### `void cvinput()`

#### Description
Same as [`input()`](#void-input), but checks the input against a condition and retries if it doesn't match.
Values from the `va_list` can be written inside the hint.

### The average user should not use this: use [`cinput()`](#void-cinput) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*)`** Boolean function to test against constants.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void cinput()`

#### Description
Same as [`input()`](#void-input), but checks the input against a condition and retries if it doesn't match.

Example `condition` function:
```c
bool is_greater_than_4(void* number)
{
    return *(int*) number > 4;
}
```

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*)`** Boolean function to test against constants.
- **`...`:** Values for `text`'s formats.

### `void vcvinput()`

#### Description
Same as [`input()`](#void-input), but checks the input against a condition and retries if it doesn't match.
Values from the `va_list` can be written inside the hint.
The condition function can take in a `va_list` if it needs other arguments.

### The average user should not use this: use [`vcinput()`](#void-vcinput) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*, va_list)`** Boolean function to test the user's input against.
- **`condargs`:** **`va_list`** `va_list` used by `condition`.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void vcinput()`

#### Description
Same as [`input()`](#void-input), but checks the input against a condition and retries if it doesn't match.
The condition function can take in a `va_list` if it needs other arguments.

Example `condition` function:
```c
bool is_in_range(void* number, va_list range)
{
    int min = va_arg(range, int);
    int max = va_arg(range, int);

    return *(int*) number >= min && *(int*) number <= max;
}
```

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`pointer`:** **`void*`** Variable to store the user's value.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*, va_list)`** Boolean function to test the user's input against.
- **`condargs`:** **`va_list`** `va_list` used by `condition`.
- **`...`:** Values for `text`'s formats.

### `void varrinput()`

#### Description
Writes a hint towards what the user should insert, then puts the user input inside an array, in order.
Values from the `va_list` can be written inside the hint.

### The average user should not use this: use [`arrinput()`](#void-arrinput) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void arrinput()`

#### Description
Writes a hint towards what the user should insert, then puts the user input inside an array, in order.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`...`:** Values for `text`'s formats.

### `void cvarrinput()`

#### Description
Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match.
Values from the `va_list` can be written inside the hint.

### The average user should not use this: use [`carrinput()`](#void-carrinput) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*)`** Boolean function to test against constants.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void carrinput()`

#### Description
Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*)`** Boolean function to test against constants.
- **`...`:** Values for `text`'s formats.

### `void vcvarrinput()`

#### Description
Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match.
Values from the `va_list` can be written inside the hint.
The condition function can take in a `va_list` if it needs other arguments.

### The average user should not use this: use [`vcarrinput()`](#void-vcarrinput) instead.

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*, va_list)`** Boolean function to test the user's input against.
- **`condargs`:** **`va_list`** `va_list` used by `condition`.
- **`args`:** **`va_list`** `va_list` for `vprintf()` used by `text`.

### `void vcarrinput()`

#### Description
Same as [`arrinput()`](#void-arrinput), but checks the input against a condition and retries if it doesn't match.
The condition function can take in a `va_list` if it needs other arguments.

Example `condition` function:
```c
bool is_in_range(void* number, va_list args)
{
    int min = va_arg(args, int);
    int max = va_arg(args, int);

    return *(int*)number >= min && *(int*)number <= max;
}
```

#### Parameters
- **`text`:** **`const char*`** Hint to the user about what should be written.
- **`ordinal`:** **`const char*`** Format string for the current number in the array (ex.: `"Insert the %dth number: "`).
- **`format`:** **`const char*`** C format specifier that will be passed to `scanf()`'s first argument.
- **`array`:** **`void*`** The array to be filled with the user's values.
- **`size`:** **`size_t`** Size of each array element.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`ordinalBefore`:** **`bool`** Whether or not to display `ordinal` before or after `text`.
- **`fail`:** **`const char*`** Text to display if the condition is false.
- **`condition`:** **`bool (*condition)(void*, va_list)`** Boolean function to test the user's input against.
- **`condargs`:** **`va_list`** `va_list` used by `condition`.
- **`...`:** Values for `text`'s formats.

## Printing Functions

### `printarr()` macro

#### Description
Prints an array to the standard input in [0, 1, 2, 3, ...] format.

#### Parameters
- **`array`:** **`void*`** The array to print.
- **`format`:** **`const char*`** C format specifier for the array elements.
- **`start`:** **`size_t`** The array index to start printing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop printing at (array length - 1 to finish at the end).

## Randomization Functions

### `int randint()`

#### Description
Generates a random integer inside a range.

#### Parameters
- **`min`:** **`int`** The lowest possible number.
- **`max`:** **`int`** The highest possible number.

#### Output
**`int`** A random integer between `min` and `max`.

### `void randints()`

#### Description
Inserts random integers inside an array.

#### Parameters
- **`array`:** **`void*`** The integer array to fill.
- **`start`:** **`size_t`** The array index to start writing from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop writing at (array length - 1 to finish at the end).
- **`min`:** **`int`** The lowest possible number.
- **`max`:** **`int`** The highest possible number.

## Array Utilities

### `arrcopy()` macro

#### Description
Copies the values of an array to another array.

#### Parameters
- **`dest`:** **`void*`** The destination array.
- **`orig`:** **`void*`** The original array.
- **`start`:** **`size_t`** The array index to start copying from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop copying at (array length - 1 to finish at the end).

### `shuffle()` macro

#### Description
Shuffles an array.

#### Parameters
- **`array`:** **`void*`** The array to shuffle.
- **`start`:** **`size_t`** The array index to start shuffling from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop shuffling at (array length - 1 to finish at the end).

### `average()` macro

#### Description
Calculates the average of an array's values.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**`long double`** The average of all array values.

### `min()` macro

#### Description
Finds the minimum value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**type of array elements** The minimum value in the array.

### `max()` macro

#### Description
Finds the maximum value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**type of array elements** The maximum value in the array.

### `med()` macro

#### Description
Finds the median value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**type of array elements** The median of all array values.

### `imin()` macro

#### Description
Finds the index of the minimum value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**`size_t`** The index of the minimum value in `array`.

### `imax()` macro

#### Description
Finds the index of the maximum value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**`size_t`** The index of the maximum value in `array`.

### `imed()` macro

#### Description
Finds the index of the median value in an array.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).

#### Output
**`size_t`** The index of the median value in `array`.

## Array Sorting Functions

### `is_sorted()` macro

#### Description
Checks if an array is sorted.

#### Parameters
- **`array`:** **`void*`** The array to scan.
- **`start`:** **`size_t`** The array index to start scanning from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop scanning at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

#### Output
**`bool`** `true` if the array is sorted, `false` otherwise.

### `qsort()` macro

#### Description
Sorts an array using the Quick Sort algorithm.
           Partitions the array around a pivot element, then recursively sorts the left and right subarrays.
           This macro is a wrapper for `stdlib.h`'s `qsort()` function.

#### Parameters
- **`array`:** **`void*`** The array to sort.
- **`start`:** **`size_t`** The array index to start sorting from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop sorting at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

### `bsort()` macro

#### Description
Sorts an array using the Bubble Sort algorithm.
           Checks two items at a time: if they aren't in order, swaps them. Iterates over the array until it is all sorted.

#### Parameters
- **`array`:** **`void*`** The array to sort.
- **`start`:** **`size_t`** The array index to start sorting from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop sorting at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

### `gsort()` macro

#### Description
Sorts an array using the Gnome Sort algorithm.
           Reads through the array. When it finds an unsorted item, it runs through the previously read items to find the place to put it.

#### Parameters
- **`array`:** **`void*`** The array to sort.
- **`start`:** **`size_t`** The array index to start sorting from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop sorting at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

### `bogosort()` macro

#### Description
"Sorts" an array using the Bogosort *joke* algorithm.
           Shuffles the list. If it isn't sorted, shuffle again.

#### Parameters
- **`array`:** **`void*`** The array to sort.
- **`start`:** **`size_t`** The array index to start sorting from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop sorting at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

### `mrclsort()` macro

#### Description
"Sorts" an array using the Miracle Sort *joke* algorithm. Do not use this.
           Constantly checks if the list has been sorted by a cosmic ray causing a bit flip.

#### Parameters
- **`array`:** **`void*`** The array to sort.
- **`start`:** **`size_t`** The array index to start sorting from (`0` to start from the beginning).
- **`end`:** **`size_t`** The array index to stop sorting at (array length - 1 to finish at the end).
- **`compare`:** A comparison function. This header provides `ascending()` and `descending()`, but you can make your own.

## Sort Direction Utilities

### `int ascending()`

#### Description
Comparison function for sorting an array in ascending order.

#### Parameters
- **`a`:** **`const void*`** The first element to compare.
- **`b`:** **`const void*`** The second element to compare.

#### Output
**`int`** The difference between the two elements.

### `int descending()`

#### Description
Comparison function for sorting an array in descending order.

#### Parameters
- **`a`:** **`const void*`** The first element to compare.
- **`b`:** **`const void*`** The second element to compare.

#### Output
**`int`** The difference between the two elements.