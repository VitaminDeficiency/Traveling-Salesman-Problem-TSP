#include<stdio.h>

#define _fileName "DuLieu.txt"
#define _fileName2 "GreedyGrapth.txt"
#define size 30

typedef struct{
	int Quang_Duong;
	int front, rear;
	bool Chua_Di_Qua;
}Way;

void _readFile(Way MaTran[][size], int *n, int *m){
	int i,j;
	FILE *f;
	f=fopen(_fileName,"r");
	if (f==NULL){
		printf("File loi!");
		return;
	}
	fscanf(f,"%d%d",n,m);
	for(i=0; i<*n; i++){
		for(j=0; j<*n; j++){
			fscanf(f,"%d", &MaTran[i][j].Quang_Duong);
			MaTran[i][j].front=i;
			MaTran[i][j].rear =j;
			MaTran[i][j].Chua_Di_Qua = false;
		}
	}
	fclose(f);
}


Way tim_canh_nho_nhat(Way MaTran[][size], int n, int i, int *rear){
	Way ca;
	int j;
	float do_dai_nn=3.40282e+38;
	for(j=0; j<n; j++){
			if ((i!=j)&&(!MaTran[i][j].Chua_Di_Qua  ) && (MaTran[i][j].Quang_Duong<do_dai_nn)){
			   do_dai_nn = MaTran[i][j].Quang_Duong;
			   ca=MaTran[i][j];
			   MaTran[i][j].Chua_Di_Qua = true;	// AB
			   MaTran[j][i].Chua_Di_Qua = true;	// BA
			   *rear=j;
			}
	}
	return ca;
}

int tao_chu_trinh(Way PA[],int k, int rear){
	int t;
	for (t=0; t<k; t++)
		if(rear==PA[t].front) return 1;
	return 0;
}

void _greedy(Way MaTran[][size], int n, int front, Way PA[]){
	Way ca;
	int rear, diem_dau=front, k=0;
	while(k<n-1){
		ca = tim_canh_nho_nhat(MaTran,n,front, &rear);
		if(!tao_chu_trinh(PA,k, rear)) {
			PA[k]=ca;
			front= rear;
			k++;
		}
		else {
			front=PA[k-1].rear;
		}
		
		PA[n-1]=MaTran[rear][diem_dau]; //Noi diem rear voi diem front
	}
}

void _print(Way PA[], int n){
	int i, sum = 0;
	printf("Thu tu cac thanh pho: ");
	for(i=0; i<n; i++){
		sum += PA[i].Quang_Duong;
		printf("%c -> ", PA[i].front+65);
		if (i == n-1) printf ("%c",PA[i].rear+65);
	}
	printf("\nTong do dai quang duong: %d\n", sum);
}


void _printMatrix(Way MaTran[][size],int n){
	int i, j;
	printf("Ma tran:\n");
	for(i=0;i<n;i++){
		printf("\t");
		for(j=0;j<n;j++) printf("%d ", MaTran[i][j].Quang_Duong);
		printf("\n");
	}
}

void _printFile(Way PA[], int *n)
{

    int i, j, sum;
    FILE *f;
    f = fopen(_fileName2,"w");
    for (i = 0; i < *n; i++) fprintf(f,"%c  %c  %d\n",PA[i].front+65,PA[i].rear+65,PA[i].Quang_Duong);
    fclose(f);
}

int main(){
	Way MaTran[size][size];
	int n,m;
	_readFile(MaTran,&n,&m);
	_printMatrix(MaTran,n);
	Way PA[n];
	char tpxp='a';
	printf("Nhap diem xuat phat (a,b,c,...):  ");
	scanf("%c",&tpxp);
	if (tpxp >= 97) tpxp -= 32; //Doi chu thuong thanh chu hoa
	_greedy(MaTran, n,tpxp-65,PA); //Doi ki tu thanh so
	_print(PA,n);
	_printFile(PA,&n);
	return 0;
}