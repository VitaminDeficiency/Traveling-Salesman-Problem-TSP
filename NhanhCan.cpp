#include <stdio.h>
#include <stdlib.h>

#define _fileName "DuLieu.txt"
#define _fileName2 "B&BGraph.txt"
#define size 10

int N;
int M;
int MIN = 1000;

int MaTran[size][size];
int bestProcess[size];
int bestWay = MIN;
bool visited[size];

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
    for (i = 0; i < *m; i++) for (j = 0; j < *n; j++) fscanf(f,"%d",&MaTran[i][j]);
    fclose(f);
}

void _update(int tempProcess[])
{
	for (int i=0; i<M; i++)
		bestProcess[i] = tempProcess[i];
	bestProcess[M] = tempProcess[0];
}

int _findMin1(int i)
{
	int min = MIN;
	for (int k=0; k < M; k++)
		if (MaTran[i][k]<min && i != k)
			min = MaTran[i][k];
	return min;
}

int _findMin2(int i)
{
	int first = MIN, second = MIN;
	for (int j = 0; j < M; j++)
	{
		if (i == j)
			continue;

		if (MaTran[i][j] <= first)
		{
			second = first;
			first = MaTran[i][j];
		}
		else if (MaTran[i][j] <= second && MaTran[i][j] != first)
			second = MaTran[i][j];
	}
	return second;
}

void _comeBack(int currWay, int city, int tempProcess[])
{
	if (MaTran[tempProcess[city-1]][tempProcess[0]] != 0)
	{
		float tempWay = currWay + MaTran[tempProcess[city-1]][tempProcess[0]];
		if (tempWay < bestWay)
		{
			_update(tempProcess);
			bestWay = tempWay;
		}
	}
	return;
}

void _tsp(float W, int currWay, int city, int tempProcess[])
{
	if (city == N) _comeBack(currWay, city, tempProcess);
	for (int i = 0; i < N; i++)
	{
		if (MaTran[tempProcess[city-1]][i] != 0 && visited[i] == false)
		{
			float temp = W;
			currWay += MaTran[tempProcess[city-1]][i];

			if (city == 1) W -= ((_findMin1(tempProcess[city-1]) + _findMin1(i))/2);
			else W -= ((_findMin2(tempProcess[city-1]) + _findMin1(i))/2);

			if (W + currWay < bestWay)
			{
				tempProcess[city] = i;
				visited[i] = true;

				_tsp(W, currWay, city+1, tempProcess);
			}
			currWay -= MaTran[tempProcess[city-1]][i];
			W = temp;
			
			for (int a = 0; a < N; a++) visited[a] = false;
			for (int j = 0; j <= city-1; j++) visited[tempProcess[j]] = true;
		}
	}
}

void _khoiTao(int x)
{
	int tempProcess[M];
	float Can_Duoi = 0;
	visited[0] = false;

	for (int i = 0; i < N; i++) Can_Duoi += (_findMin1(i) + _findMin2(i));
    Can_Duoi = Can_Duoi/2;

	visited[x] = true;
	tempProcess[0] = x;

	_tsp(Can_Duoi, 0, 1, tempProcess);
}

void _printMaTran()
{
    printf("Ma tran:\n");
    for (int i = 0; i < N; i++)
    {
        printf("\t");
        for (int j = 0; j < N; j++)
            printf("%d ",MaTran[i][j]);
        printf("\n");
    }
}

void _print()
{
    printf("Thu tu cac thanh pho: ");
    for (int i = 0; i <= N; i ++)
    {
        printf("%c", bestProcess[i]+65);
		if (i!=N) printf(" -> ");
    }
    printf("\nTong do dai quang duong: %d\n\n", bestWay);
}

void _printFile(int *n, int *m)
{
    int i, j;
    FILE *f;
    f = fopen(_fileName2,"w");
    for (i = 0; i < *n; i++) fprintf(f,"%c  %c  %d\n",bestProcess[i]+65, bestProcess[i+1]+65, MaTran[bestProcess[i]][bestProcess[i+1]]);
    fclose(f);
}

int main()
{
	system("cls");
	char x;
	_readFile(&N,&M);
	_printMaTran();
	printf("Nhap diem xuat phat (a,b,c,...):  ");
	scanf("%c",&x);
	if(x>=97) x-=32;
	_khoiTao(x-65);
	_print();
    _printFile(&N,&M);
	system("pause");
}
