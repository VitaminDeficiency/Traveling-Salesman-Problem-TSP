#include<stdio.h>
#define size 30

typedef struct{
	float do_dai;
	int dau, cuoi;
	int da_dung;
}canh;


void read_file(char file_name[], canh a[][size], int *n){
	int tam, i,j;
	FILE *f;
	f=fopen(file_name,"r");
	if (f==NULL){
		printf("Mo file co loi !!!");
		return;
	}
	fscanf(f,"%d",n); //doc so dinh cua do thi n
	
	for(i=0; i<*n; i++) fscanf(f,"%d",&tam); //doc dong chi so Cot
	
	for(i=0; i<*n; i++){
		fscanf(f,"%d",&tam); //Doc chi so dong
		for(j=0; j<*n; j++){
			fscanf(f,"%f", &a[i][j].do_dai);
			a[i][j].dau=i;
			a[i][j].cuoi=j;
			a[i][j].da_dung=0;
			
		}
	}
	fclose(f);
}



void in_ma_tran(canh a[][size],int n){
	int i, j;
	printf("Ma tran TRONG SO cua do thi\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) printf(" %c%c=%8.2f",a[i][j].dau+65, a[i][j].cuoi+65, a[i][j].do_dai);
		printf("\n");
	}
}

canh tim_canh_nho_nhat(canh a[][size], int n, int i, int *cuoi){
	canh ca;
	int j;
	float do_dai_nn=3.40282e+38;
	for(j=0; j<n; j++){
			if ((i!=j)&&(!a[i][j].da_dung  )&& (a[i][j].do_dai<do_dai_nn)){
			   do_dai_nn = a[i][j].do_dai;
			   ca=a[i][j];
			   a[i][j].da_dung=1;
			   a[j][i].da_dung=1;
			   *cuoi=j;
			}
	}
	return ca;
}

int tao_chu_trinh(canh PA[],int k, int cuoi){
	int t;
	for (t=0; t<k; t++)
		if(cuoi==PA[t].dau) return 1;
	return 0;
}


void greedy(canh a[][size], int n, int dau, canh PA[]){
	canh ca;
	int cuoi, diem_dau=dau, k=0;
	while(k<n-1){
		ca=tim_canh_nho_nhat(a,n,dau, &cuoi);
		if(!tao_chu_trinh(PA,k, cuoi)) {
			PA[k]=ca;
			dau= cuoi;
			k++;
		}
		else {
			dau=PA[k-1].cuoi;
		}
		
		PA[n-1]=a[cuoi][diem_dau]; //Noi diem cuoi voi diem dau
	}
}


void in_PA(canh PA[], int n){
	int i;
	float sum=0.0;
	printf("\nPHUONG AN TIM DUOC:\n");
	for(i=0; i<n; i++){
		sum+=PA[i].do_dai;
		printf("Canh %c%c= %8.2f\n", PA[i].dau+65, PA[i].cuoi+65, PA[i].do_dai);
	}
	printf("Tong do dai cac canh cua chu trinh =%8.2f\n", sum);
}


int main(){
	canh a[size][size];
	int n;
	read_file("Dulich.txt",a,&n);
	in_ma_tran(a,n);
	canh PA[n];
	char tpxp='a';
	printf("Nhap diem xuat phat (a,b,c,...):  ");
	scanf("%c", &tpxp);
	if (tpxp>=97) tpxp-=32; //Doi chu thuong thanh chu hoa
	greedy(a, n,tpxp-65,PA); //Doi ki tu thanh so
	in_PA(PA,n);
	return 0;
}

