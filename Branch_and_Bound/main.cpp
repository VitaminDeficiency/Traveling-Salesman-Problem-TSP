#include <stdio.h>

#define sz 10
#define _fileName "DuLieu.txt"

int n;                  // Số lượng thành phố
int m;                  // Số lượng các cạnh
int maxE = 1000;
int maxC = 1000;
int MaTran[sz][sz];     // Ma trận cấp sz
int BestWay[sz];        // Thứ tự quãng đường tốt nhất
int X[sz];              // store all possible ways
int T[sz];              // store cost from x[0] to X[i]
int BestConfig;         // Lưu trữ cách tốt nhất tạm thời
bool Visited[sz];       // Visited[i] = True khi chưa ghé thăm thành phố i

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

void _khoiTao()
{
    for (int i = 0; i < n; i ++)
    {
        Visited[i] = true;
        BestWay[i] = 0;
        X[i] = 0;
        T[i] = 0;
    }
    Visited[0] = false; // start from vertice 0
    BestConfig = maxC;
}

void _tsp(int i)
{
    for (int j = 1; j < n; j ++)
    {
        if (Visited[j]) // Kiểm tra xem thành phố thứ j đã ghé qua chưa
        {
            X[i] = j;
            T[i] = T[i - 1] + MaTran[X[i - 1]][j];
            if (T[i] < BestConfig)
            {
                if (i < n - 1)
                {
                    Visited[j] = false; // Đánh dấu đã ghé qua
                    _tsp(i + 1);        // Phân nhánh
                    Visited[j] = true;
                } else
                {
                    if (T[i] + MaTran[X[i]][0] < BestConfig)
                    {
                        for (int k = 0; k < n; k ++)
                        {
                            BestWay[k] = X[k];                  // Thứ tự quãng đường tốt nhất tạm thời
                        }
                        BestConfig = T[i] + MaTran[X[i]][0];    // Đã tìm được giá trị tốt nhất tạm thời
                    }
                }
            }
            //printf("T "); for (int a = 0; a < n; a++)  printf("%d  ",T[a]);
        }
    }
}

void _printMaTran()
{
    printf("Ma tran bieu dien:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\t");
        for (int j = 0; j < n; j++)
            printf("%d ",MaTran[i][j]);
        printf("\n");
    }
}

void _print()
{
    printf("Thu tu cac thanh pho: ");
    for (int i = 0; i < n; i ++)
    {
        printf(" %c ->", BestWay[i] + 65);
    }
    printf(" %c\n", BestWay[0] + 65);
    printf("Tong do dai: %d", BestConfig);
}

int main()
{
    _readFile(&n, &m);
    _printMaTran();
    _khoiTao();
    _tsp(1);
    _print();
}