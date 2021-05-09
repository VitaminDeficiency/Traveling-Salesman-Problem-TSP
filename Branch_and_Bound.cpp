#include <stdio.h>
#include <string.h>
#define sz 10
#define _fileName "DuLieu.txt"

int MaTran[sz][sz];
int Da_Di_qua[sz];
int DoDai = 0;
int x[100];
int n;

void _readFile(int *n)
{
    int i, j;
    FILE *f;
    f = fopen(_fileName,"r");
    if (f==NULL)
    {
        printf("File Loi!");
        return;
    }
    fscanf(f,"%d",n);
    for (i = 0; i < *n; i++){
        for (j = 0; j < *n; j++) fscanf(f,"%d",&MaTran[i][j]);
        Da_Di_qua[i] = 0;
    }
    fclose(f);
}

int tsp(int c)
{
    int i, nearest_city = 999, minimum = 999;
    if (DoDai + nearest_city*(n-i+1) >= minimum) return;
    for (int j = 1; j<n; j++)
    {
        if (Da_Di_qua[j])
        {
            x[i] = j;
            Da_Di_qua[j] = 0;
            DoDai += MaTran[x[i-1]][j];
            if (i==n) if (DoDai+MaTran[x[n]][x[1]]<minimum) nearest_city = DoDai+MaTran[x[n]][x[1]]; else tsp(i+1);
            DoDai -= MaTran[x[i-1]][j];
            Da_Di_qua[j] = 1;
        }
    }
}

int main()
{
    int n;
    _readFile(&n);
    printf("\n\nThu tu thanh pho:\t");
    tsp(2);
    printf("\n\nTong quang duong ngan nhat: \t");
    printf("%d\n",DoDai);
}