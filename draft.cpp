#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
int main()
{
  int driver=0, mode = 0, maloi; /* driver để chế độ DETECT tự phát hiện kiểu màn hình đang dùng. */
  initgraph(&driver,&mode,"C:/TC/BGI"); /* khởi động đồ hoạ với tệp egavga.bgi ở thư mục c:\tc\bgi. Nếu đặt là “” (xâu rỗng) thì tự tìm tệp này ở thư mục chứa tệp .c hay .cpp của chương trình */
if ((maloi=graphresult())!=0 ) // nếu không khởi động được đồ hoạ thì báo lỗi
{
   printf("khong the khoi dong do hoa \n");
   printf("ma loi : %d \nTran Van Nhuom %s ",maloi, grapherrormsg(maloi) );
   getch();
   exit(1);
}
setbkcolor(WHITE); // đặt màu nền là màu trắng ,có thể là setbkcolor(15)
setcolor(RED); // đặt màu vẽ là màu đỏ, có thể đặt setcolor (4);
line(10,10,100,100); // vẽ một đường thẳng
getch(); // tạm dừng màn hình đợi ấn phím bất kỳ
int bk=getbkcolor() , cl=getcolor(); // lưu giá trị màu nền và màu vẽ
int x=getmaxx(), y=getmaxy(); // lưu toạ độ lớn nhất của kiểu màn hình đang sử dụng
closegraph();
printf("getbkcolor = %d getcolor= %d",bk,cl);
printf("\ngetmaxx = %d getmaxy= %d",x,y);
getch();
return 0;
}