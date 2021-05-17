#include <stdio.h>
#include <stdlib.h>

#define _fileName "DuLieu.txt"
#define _fileName2 "GreedyGrapth.txt"
#define size 20

typedef struct
{
	int Quang_Duong;
	int front, rear;
	bool Chua_Di_Qua;
} Way;

void _readFile(Way MaTran[][size], int *n, int *m)
{
	int i,j;
	FILE *f;
	f=fopen(_fileName,"r");
	if (f==NULL)
	{
		printf("File loi!");
		return;
	}
	fscanf(f,"%d%d",n,m);
	for(i=0; i < *n; i++)
	{
		for(j=0; j < *m; j++)
		{
			fscanf(f,"%d", &MaTran[i][j].Quang_Duong);
			MaTran[i][j].front=i;
			MaTran[i][j].rear =j;
			MaTran[i][j].Chua_Di_Qua = false;
		}
	}
	fclose(f);
}

Way _findEdgeMin(Way MaTran[][size], int n, int i, int *rear)	// Tìm cạnh tiếp theo nhỏ nhất
{
	Way edge;
	float min = 10000;
	for(int j=0; j<n; j++)
	{
		if ((i!=j) && (!MaTran[i][j].Chua_Di_Qua) && (MaTran[i][j].Quang_Duong < min))	// Chưa được đi qua và tìm kiếm cạnh tiếp theo nhỏ nhất
		{
		    min = MaTran[i][j].Quang_Duong;		// Coi biến min là giá trị nhỏ nhất tạm thời cho mỗi vòng lặp
		    edge = MaTran[i][j];				// Đồng thời lưu lại cạnh này vào biến edge
			MaTran[i][j].Chua_Di_Qua = true;	// AB đánh dấu đã đi qua 
		    MaTran[j][i].Chua_Di_Qua = true;	// BA như AB do ma trận vuông
			*rear = j;
		}
	}
	return edge;	// Kết thúc quá trình tìm kiếm ta xuất cạnh bé nhất vừa tìm được
}

int _createWay(Way PA[], int k, int rear)	// Tạo chu trình đường
{
	int t;
	for (t=0; t<k; t++) if(rear == PA[t].front) return 1;
	return 0;
}

void _greedy(Way MaTran[][size], int n, int front, Way PA[])
{
	Way edge;
	int rear, frontDot = front, k = 0;				// Giữ lại điểm đầu	
	while(k < n-1){
		edge = _findEdgeMin(MaTran,n,front,&rear);	// Cạnh bé nhất được tìm từ nút đang xét
		if(!_createWay(PA, k, rear))				// Nếu _createWay == 0 thì ...
		{
			PA[k] = edge;
			front = rear;
			k++;
		} else
		{
			front=PA[k-1].rear;
		}
		PA[n-1]=MaTran[rear][frontDot];		// Nối rear với front
	}
}

void _print(Way PA[], int n)
{
	int i, tong = 0;
	printf("Thu tu cac thanh pho: ");
	for(i = 0; i<=n; i++)
	{
		tong += PA[i].Quang_Duong;
		printf("%c", PA[i].front+65);
		if (i!=n) printf(" -> ");
		
	}
	printf("\nTong do dai quang duong: %d\n\n", tong);
}

void _printMatrix(Way MaTran[][size],int n)
{
	int i, j;
	printf("Ma tran:\n");
	for(i=0;i<n;i++)
	{
		printf("\t");
		for(j=0;j<n;j++) printf("%d ", MaTran[i][j].Quang_Duong);
		printf("\n");
	}
}

void _printFile(Way PA[], int *n)
{

    int i;
    FILE *f;
    f = fopen(_fileName2,"w");
    for (i = 0; i < *n; i++) fprintf(f,"%c  %c  %d\n", PA[i].front+65, PA[i].rear+65, PA[i].Quang_Duong);
    fclose(f);
}

int main()
{
	system("cls");
	Way MaTran[size][size];
	int n,m;
	_readFile(MaTran,&n,&m);
	_printMatrix(MaTran,n);
	Way PA[n];
	char x;
	printf("Nhap diem xuat phat (a,b,c,...):  ");
	scanf("%c",&x);
	if (x >= 97) x-=32;         // Chữ thường sang chữ hoa
	_greedy(MaTran, n,x-65,PA); // Đổi kí tự thành số
	_print(PA,n);
	_printFile(PA,&n);
	return 0;
}