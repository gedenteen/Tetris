#include <graphics.h>

int check_cell(int x, int y, int dif) {
	int pixel_x = (x + 1) * dif + 1;
	int pixel_y = (y + 1) * dif + 1;
	return getpixel(pixel_x, pixel_y);
}
void rand_array(int n, int arr[]) {
	int i, u, temp;
	for (i=0; i<n; i++) {
		arr[i] = i;
	}
	for (i=0; i<n; i++) {
		u = rand() % n;
		temp = arr[i];
		arr[i] = arr[u];
		arr[u] = temp;
	}
}
void move_lines(int main_y, int dif) {
	int x, y, pixel_x, pixel_y, color_top;
	for (y=main_y; y>0; y--) {
		pixel_y = (y + 1) * dif + 1;
		for (x=0; x<10; x++) {
			pixel_x = (x + 1) * dif + 1;
			color_top = getpixel(pixel_x, pixel_y - dif);
			setfillstyle(1, color_top);
			floodfill (pixel_x, pixel_y, 0); //заливка до черного цвета
		}
	}
	pixel_y = dif + 1;
	for (x=0; x<10; x++) { //самая верхняя строка
		setfillstyle(1, 7); //закрашивается в серый
		pixel_x = (x + 1) * dif + 1;
		floodfill (pixel_x, pixel_y, 0);
	}
}
void outtextxy(int x, int y, int val) { //вывод int числа
   char buf[20];
   snprintf(buf, sizeof(buf), "%d", val); //printf в массив buf
   outtextxy(x, y, buf);
}
