#include <stdio.h>
int xuat(int g[][3]){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
            printf("%d ",g[i][j]);
}
int main(){
    int g[][3] = { { 20, 25, 30 },
                   { 45, 30, 10 } };
    printf("%d ",xuat(g));
}