#include <stdio.h>
#include <stdlib.h>

#define _fileName "DuLieu.txt"
#define _fileName2 "B&BGrapth.txt"
#define size 10

int N;
int M;
int MIN = 1000;

int MaTran[size][size];
int Chu_Trinh_Tot_Nhat[size];
int Quang_Duong_Tot_Nhat = MIN;       // Khởi tạo nên cho nó là một số vô cùng lớn
bool Da_Di_Qua[size];                 // Đánh dấu ghé qua hay chưa (true nếu chưa ghé qua)

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

// Copy giải pháp tạm thời vào biến tốt nhất hiện thành
void _update(int Chu_Trinh_Tam_Thoi[])
{
	for (int i=0; i<M; i++)
		Chu_Trinh_Tot_Nhat[i] = Chu_Trinh_Tam_Thoi[i];
	Chu_Trinh_Tot_Nhat[M] = Chu_Trinh_Tam_Thoi[0];
}

// Hàm tìm quãng đường ngắn nhất
// Tìm cột nhỏ nhất ở hàng i
int _firstMin(int i)
{
	int min = MIN;
	for (int k=0; k < M; k++)
		if (MaTran[i][k]<min && i != k)
			min = MaTran[i][k];
	return min;
}

// Hàm tìm quãng đường ngắn thứ 2
// Tìm cột nhỏ thứ 2 tại hàng i
int _secondMin(int i)
{
	int first = MIN, second = MIN;
	for (int j = 0; j < M; j++)
	{
		if (i == j)
			continue;   // Lệnh continue giống như break nhưng thay vì kết thúc vòng lặp thì lại chạy vòng lặp tiếp theo

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

void _tsp(float Can_Duoi, int Doan_Duong, int level, int Chu_Trinh_Tam_Thoi[])
{
	// Khi ta đi hết các thành phố
	if (level == N)
	{
		// Kiểm tra xem có phải là thành phố cuối cùng không
		// Trở về nút xuất phát
		if (MaTran[Chu_Trinh_Tam_Thoi[level-1]][Chu_Trinh_Tam_Thoi[0]] != 0)
		{
			// Quang_Duong_Tam_Thoi chứa độ dài đường đi vừa qua
			int Quang_Duong_Tam_Thoi = Doan_Duong + MaTran[Chu_Trinh_Tam_Thoi[level-1]][Chu_Trinh_Tam_Thoi[0]];

			// Cập nhật kết quả (Quang_Duong_Tot_Nhat) nếu kết quả hiện tại tốt hơn
			if (Quang_Duong_Tam_Thoi < Quang_Duong_Tot_Nhat)
			{
				_update(Chu_Trinh_Tam_Thoi);
				Quang_Duong_Tot_Nhat = Quang_Duong_Tam_Thoi;
			}
		}
		return; // Backtrack
	}

	// Khi chưa đi hết các thành phố ta đệ quy xây dựng cây (Phân nhánh)
	for (int i = 0; i < N; i++)
	{
		// Xem xét thành phố tiếp theo nếu nó không giống nhau và chưa được đi qua
		if (MaTran[Chu_Trinh_Tam_Thoi[level-1]][i] != 0 && Da_Di_Qua[i] == false)
		{
			float temp = Can_Duoi;
			Doan_Duong += MaTran[Chu_Trinh_Tam_Thoi[level-1]][i];
			
			// Cận dưới = Cạn dưới cũ - ((chi phí cạnh tối thiểu second là 1 + chi phí cạnh first tối thiểu là 2) / 2) + chi phí cạnh 1-2) + giá trị đườg đi tại 2 nút
			if (level == 1) Can_Duoi -= ((_firstMin(Chu_Trinh_Tam_Thoi[level-1]) + _firstMin(i))/2);
			else Can_Duoi -= ((_secondMin(Chu_Trinh_Tam_Thoi[level-1]) + _firstMin(i))/2);
			
			// (Can_Duoi + Doan_Duong) là cận dưới của một nút con mà ta đã đến
			// Nếu cận dưới hiện tại < Quang_Duong_Tot_Nhat, chúng ta cần khám phá thêm nút
			if (Can_Duoi + Doan_Duong < Quang_Duong_Tot_Nhat)
			{
				Chu_Trinh_Tam_Thoi[level] = i;	// Đặt thành phố i vào hướng đến của level
				Da_Di_Qua[i] = true;			// Đánh dấu đã đi qua 
				printf("level: %d\n", level);
				printf("CD: %.2f\n", Can_Duoi + Doan_Duong);
				// Khám phá thêm nút (Đệ quy)
				_tsp(Can_Duoi, Doan_Duong, level+1, Chu_Trinh_Tam_Thoi);
			}

			// Ngược lại, sau khi cắt tỉa thì trả lại Doan_Duong và Can_Duoi về ban đầu
			Doan_Duong -= MaTran[Chu_Trinh_Tam_Thoi[level-1]][i];
			Can_Duoi = temp;

			// Đồng thời hoàn lại nút đã truy cập
			for (int a = 0; a < N; a++) Da_Di_Qua[a] = false;
			for (int j=0; j<=level-1; j++) Da_Di_Qua[Chu_Trinh_Tam_Thoi[j]] = true;
		}
	}
}

// Hàm chọn đường đi ngắn nhất lý tưởng
void _khoiTao(int x)
{
	int Chu_Trinh_Tam_Thoi[M];
	float Can_Duoi = 0;

	Chu_Trinh_Tam_Thoi[0] = -1;
	Da_Di_Qua[0] = false;

	// Tạo cận nút gốc
	for (int i = 0; i < N; i++)
		Can_Duoi += (_firstMin(i) + _secondMin(i));
    Can_Duoi = Can_Duoi/2;

	// Thành phố bắt đầu
	if (x) Da_Di_Qua[x-1] = true;
	else Da_Di_Qua[x] = true;
	Chu_Trinh_Tam_Thoi[0] = x;

	// Gọi đến tsp, cho Doan_Duong = 0 và thành phố 1
	_tsp(Can_Duoi, 0, 1, Chu_Trinh_Tam_Thoi);
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
        printf("%c", Chu_Trinh_Tot_Nhat[i]+65);
		if (i!=N) printf(" -> ");
    }
    printf("\nTong do dai quang duong: %d\n", Quang_Duong_Tot_Nhat);
}

void _printFile(int *n, int *m)
{
    int i, j;
    FILE *f;
    f = fopen(_fileName2,"w");
    for (i = 0; i < *n; i++) fprintf(f,"%c  %c  %d\n",Chu_Trinh_Tot_Nhat[i]+65, Chu_Trinh_Tot_Nhat[i+1]+65, MaTran[Chu_Trinh_Tot_Nhat[i]][Chu_Trinh_Tot_Nhat[i+1]]);
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
	_khoiTao(x-65); // Chữ cái thành số
	_print();
    _printFile(&N,&M);
	system("pause");
}
