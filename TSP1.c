#include <stdio.h>

int matrix[25][25],         // Kiểu mảng 2 chiều ứng với matrix của các nút (hàng) và độ dài (cột)
    visited_cities[10],     // Đã đi qua
    n,                      // Số lượng thành phố
    cost = 0;               // Tổng độ dài quãng đường

int tsp(int c)
{
    int i, nearest_city = 999;  // Tìm min nên cho trước +vô cực
    int minimum = 999, temp;
    for(i = 0; i < n; i++)
    {
        if(matrix[c][i] && !visited_cities[i])  // Xét Matrix !=0 và Visited ==0
        {
            if(matrix[c][i] < minimum) minimum = matrix[i][0] + matrix[c][i];
            temp = matrix[c][i];
            nearest_city = i;
        }
    }
    if(minimum != 999)
    {
        cost = cost + temp;
    }
    return nearest_city;
}

void minimum_cost(int city) // Tìm kiếm quãng đường ngắn nhất
{
    int nearest_city;
    visited_cities[city] = 1;
    printf("%d ", city + 1);
    nearest_city = tsp(city);
    if(nearest_city == 999)
    {
        nearest_city = 0;
        printf("%d", nearest_city + 1);
        cost = cost + matrix[city][nearest_city];
        return;
    }
    minimum_cost(nearest_city);
}

int main()
{ 
    int i, j;
    printf("Nhap vao tong so nut:\t");
    scanf("%d", &n);
    printf("\nNhap do dai cac canh");
    for(i = 0; i < n; i++)
    {
        printf("\nNut %d:\n",i + 1);
        for(j = 0; j < n; j++)
        {
            printf("  Nhap do dai thu %d:\t", j + 1);
            scanf("%d", &matrix[i][j]);
        }
    visited_cities[i] = 0;
    }
    printf("\nMatrix cua quang duong cac nut\n");
    for(i = 0; i < n; i++)
    {
        printf("\n");
        for(j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
    }
    printf("\n\nThu tu thanh pho:\t");
    minimum_cost(0);
    printf("\n\nTong quang duong ngan nhat: \t");
    printf("%d\n", cost);
}