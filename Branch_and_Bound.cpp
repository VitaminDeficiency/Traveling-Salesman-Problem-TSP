#include <stdio.h>
#include <string.h>
#define sz 10
#define _fileName "DuLieuVao.txt"

typedef struct
{
    float Do_Dai;
    int Da_Di_qua;
    int x, y;
}doanDuong;

void _readFile(doanDuong a[][sz], int *n)
{
    int i, j;
    FILE *f;
    f = fopen(_fileName,"r");
    if (f==NULL)
    {
        printf("File Loi!");
        return;
    }
    fscanf(f,"%d",n);       // Ma trận vuông
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
        {
            fscanf(f,"%f",&a[i][j].Do_Dai);
            a[i][j].x = i;
            a[i][j].y = j;
            a[i][j].Da_Di_qua = 0;
        }
    fclose(f);
}
int main()
{
    int n;
    doanDuong a[sz][sz];
    _readFile(a, &n);
    printf("%.2f ",a[2][3].Do_Dai);
}