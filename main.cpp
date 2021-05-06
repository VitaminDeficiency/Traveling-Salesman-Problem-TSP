#include <stdio.h>
#include "_heapSort.h"

int main()
{
    int i;
    float a[9] = {3, 4, 100, 12, 10, 5, 9};
    _heapSort(a, 7);
    for (i = 0; i < 7; i++)
        printf("%.2f  ", a[i]);
}