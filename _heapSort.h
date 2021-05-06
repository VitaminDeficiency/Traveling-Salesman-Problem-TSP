#include <stdio.h>
void swap(float *a, float *b)
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(float *a, int n, int i)
{
    int largest = i; // Khoi tao root
    int l = 2*i + 1; // left
    int r = 2*i + 2; // right
    if (l < n && *(a+l) > *(a+largest))
        largest = l;
    if (r < n && *(a+r) > *(a+largest))
        largest = r;
    if (largest != i)
    {
        swap(a+i, a+largest);
        heapify(a, n, largest);
    }
}
void _heapSort(float *a, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i=n-1; i>0; i--)
    {
        swap(a, (a+i));
        heapify(a, i, 0);
    }
}