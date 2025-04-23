#include <stdio.h>
#include <stdlib.h>
#include <flameysutils.h>

int main()
{
    int end = 99;
    int array[end + 1];

    randints(array, 0, end, 0, 1000);

    printf("The array: ");
    printarr(array, "%d", 0, end);

    shuffle(array, 0, end);

    printf("\nShuffled: ");
    printarr(array, "%d", 0, end);

    qsort(array, 0, end, ascending);

    printf("\nSorted: ");
    printarr(array, "%d", 0, end);

    printf("\nAverage: %.3Lf\nMedian: %d\nSorted: %s\n", average(array, 0, end), med(array, 0, end), (is_sorted(array, 0, end, ascending) ? "Yes" : "No"));

    return 0;
}
