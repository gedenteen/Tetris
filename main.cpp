#include "functions.h"
#include "classes.h"
#include <time.h>

int main() {
	srand(time(0));
	//--- графическое окно ----------------------------------------//
	int x1, y1, dif, x2, y2, i, u;
	x1 = y1 = dif = 40;
	y2 = y1 + 18 * dif;
	x2 = x1 + 10 * dif;
	//x1, y1, x2, y2 - координаты пол€ дл€ игры
	int xmax=x2+dif*12, ymax=y2+dif;
	initwindow(xmax, ymax);
	//--- создание игрового пол€ ----------------------------------//
	Restart:
	setfillstyle ( 1, 7 ); // стиль, цвет
	bar (x1, y1, x2, y2);
	setcolor(0);
	int x, y, flag = 1, resul;
	for (i=0, x=x1; i<10; i++, x+=dif) {
		moveto(x, y1);
		lineto(x, y2);
	}
	for (i=0, y=y1; i<20; i++, y+=dif) {
		moveto(x1, y);
		lineto(x2, y);
	}
	//--- друга€ информаци€ ---------------------------------------//
	setcolor(2);
	settextstyle(0, 0, 3); //увеличение размера текста в три раза
	outtextxy ( x2+dif, y2-240, "”правление:");
	outtextxy ( x2+dif, y2-200, "W - вверх");
	outtextxy ( x2+dif, y2-160, "A - влево");
	outtextxy ( x2+dif, y2-120, "S - вниз");
	outtextxy ( x2+dif, y2-80, "D - вправо");
	outtextxy ( x2+dif, y2-40, "Enter - рестарт");
	outtextxy ( x2+dif, y1, "—чет: ");
	outtextxy ( x2+200, y1, 0); //перегрузка функции в functions.cpp
	//--- массив фигур дл€ избежани€ плохого рандома --------------//
	int f_max = 7, f_i = 0, f_arr[f_max];
	rand_array(f_max, f_arr);
	figure *pfigure;
	int key, score = 0;
	while (flag) { //flag == 1, пока игра не закончена
		switch (f_arr[f_i]) {
			case 0:
				pfigure = new Z_figure(dif);
				break;
			case 1:
				pfigure = new T_figure(dif);
				break;
			case 2:
				pfigure = new O_figure(dif);
				break;
			case 3:
				pfigure = new I_figure(dif);
				break;
			case 4:
				pfigure = new S_figure(dif);
				break;
			case 5:
				pfigure = new J_figure(dif);
				break;
			case 6:
				pfigure = new L_figure(dif);
				break;
			default:
				break;
		}
		f_i++;
		if (f_i == f_max) { //если все фигуры задействованы
			f_i = 0;
			rand_array(f_max, f_arr);
		}
		pfigure->draw();
		for (i=0; i<1000; i++) {
			delay(5);
			if ( kbhit() ) {
				key = getch();
				pfigure->clear();
				if (key == 75 || key == 97) //влево
					resul = pfigure->change_xy(-1, 0);
				if (key == 77 || key == 100) //вправо
					resul = pfigure->change_xy(1, 0);
				if (key == 80 || key == 115) //вниз
					resul = pfigure->change_xy(0, 1);
				if (key == 72 || key == 119) //вверх
					pfigure->change_posn();
				pfigure->draw();
			}
			if (i % 40 == 0) {
				pfigure->clear();
				resul = pfigure->change_xy(0, 1);
				pfigure->draw();
			}
			if (resul == 2) { //если фигура упала
				i = 1000;
				delete pfigure;
			}
			//проверка на завершение игры
			if (i>40 and check_cell(5, 0, dif) != 7) {
				flag = 0;
				setcolor(4);
				settextstyle(0, 0, 5);
				outtextxy ( x2+dif, y1+50, "Game over");
				key = getch();
				if (key == 13) { //если enter, то рестарт
					setfillstyle ( 1, 0 ); //закрашивание надписи
					bar (x2+dif, y1, x2+500, y1+200);
					goto Restart;
				}
			}
		}
		//проверка на заполненные линии
		for (i=0; i<20; i++) {
			y = (i + 1) * dif + 1;
			for (u=0, resul=0; u<10; u++) {
				x = (u + 1) * dif + 1;
				if (getpixel(x, y) != 7)
					resul++;
				else break;
			}
			if (resul == 10) { //если лини€ заполнена
				move_lines(i, dif);
				outtextxy ( x2+200, y1, ++score);
			}
		}
	}
	getch();
	return 0;
}
