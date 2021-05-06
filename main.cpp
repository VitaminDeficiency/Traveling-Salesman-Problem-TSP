#include <stdio.h>
#include <malloc.h>
#include "_heapSort.h"

typedef struct DoanDuong
{
    char Ten_Duong[2];
    int Do_Dai_Doan_Duong;
};
DoanDuong _readFile(){
    FILE *f;
    DoanDuong *DD;
    f = fopen("DuLieuVao.txt","r");
    DD = (DoanDuong*)malloc(sizeof(DoanDuong));
}
int main()
{

}