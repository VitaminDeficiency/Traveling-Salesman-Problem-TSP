#include <stdio.h>

int matrix[25][25], visited_cities[10], limit, cost = 0;
 
int tsp(int c)
{
    int count, nearest_city = 999;  // Tìm min nên cho trước +vô cực
    int minimum = 999, temp;
    for(count = 0; count < limit; count++)
    {
        if((matrix[c][count] != 0) && (visited_cities[count] == 0))
        {
            if(matrix[c][count] < minimum)
            {
                minimum = matrix[count][0] + matrix[c][count];
            }
            temp = matrix[c][count];
            nearest_city = count;
        }
    }
    if(minimum != 999)
    {
        cost = cost + temp;
    }
    return nearest_city;
}
 
void minimum_cost(int city)
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
    scanf("%d", &limit);
    printf("\nNhap do dai cac canh");
    for(i = 0; i < limit; i++)
    {
        printf("\nNut %d:\n",i + 1);
        for(j = 0; j < limit; j++)
        {
            printf("  Nhap do dai thu %d:\t", j + 1);
            scanf("%d", &matrix[i][j]);
        }
    visited_cities[i] = 0;
    }
    printf("\nMatrix cua quang duong\n");
    for(i = 0; i < limit; i++)
    {
        printf("\n");
        for(j = 0; j < limit; j++)
        {
            printf("%d ", matrix[i][j]);
        }
    }
    printf("\n\nThu tu thanh pho:\t");
    minimum_cost(0);
    printf("\n\nTong quang duong ngan nhat: \t");
    printf("%d\n", cost);
}