#include <stdio.h>

#define sz 10
#define _fileName "DuLieu.txt"

int n;                  // Số lượng thành phố
int m;                  // Số lượng các cạnh
int maxE = 1000;
int maxC = 100 * maxE;
int MaTran[sz][sz];
int X[sz];   // store all possible ways
int BestWay[sz]; // store best way
int T[sz];   // store cost from x[0] to X[i]
int Visited[sz];    // Visited[i] = True if not visit i
int BestConfig = maxC;  // best cost

void _readFile(int *n, int *m)
{
    int i, j;
    FILE *f;
    f = fopen(_fileName,"r");
    if (f==NULL)
    {
        printf("File Loi!");
        return;
    }
    fscanf(f,"%d%d",n,m);
    for (i = 0; i < *n; i++) for (j = 0; j < *n; j++) fscanf(f,"%d",&MaTran[i][j]);
    fclose(f);
}

void _initialize()
{
    for (int i = 0; i < n; i ++)
    {
        Visited[i] = true;
        BestWay[i] = 0;
        X[i] = 0;
        T[i] = 0;
    }
    Visited[0] = false;    // start from vertice 0
    BestConfig = maxC;
}

void _attemp(int i)
{
    for (int j = 1; j < n; j ++)
    {
        if (Visited[j])
        {
            X[i] = j;
            T[i] = T[i - 1] + MaTran[X[i - 1]][j];
            if (T[i] < BestConfig)
            {
                if (i < n - 1)
                {
                    Visited[j] = false;
                    _attemp(i + 1);
                    Visited[j] = true;
                } else
                {
                    if (T[i] + MaTran[X[i]][0] < BestConfig)
                    {
                        for (int k = 0; k < n; k ++)
                        {
                            BestWay[k] = X[k];
                        }
                        BestConfig = T[i] + MaTran[X[i]][0];
                    }
                }
            }
        }
    }
}

void _print()
{
    printf("Thu tu cac thanh pho: ");
    for (int i = 0; i < n; i ++)
    {
        printf(" %d ->", BestWay[i] + 1);
    }
    printf(" 1 \n");
    printf("Tong do dai: %d", BestConfig);
}

int main()
{
    _readFile(&n, &m);
    _initialize();
    _attemp(1);
    _print();
}