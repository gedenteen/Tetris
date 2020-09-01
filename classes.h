#ifndef CLASSES_H
#define CLASSES_H

#include <stdio.h>
#include <graphics.h>

class cell {
private:
	int x, y, color; 
	cell() : x(0), y(0), color(7) {}
	cell (int x, int y, int c=7) { //параметр по умолчанию
		this->x = x;
		this->y = y;
		color = c;
	}	
	void draw(int dif) {
		int pixel_y, pixel_x;
		pixel_y = dif + y * dif + 1; //+1 для перемещения пера внуть клетки
		pixel_x = dif + x * dif + 1; //
		setfillstyle(1, color);
		floodfill (pixel_x, pixel_y, 0); //заливка до черного цвета
	}
	void clear(int dif) {
		int pixel_y, pixel_x;
		pixel_y = dif + y * dif + 1; //+1 для перемещения пера внуть клетки
		pixel_x = dif + x * dif + 1; //
		setfillstyle(1, 7); //серый цвет
		floodfill (pixel_x, pixel_y, 0); //заливка до черного цвета
	}	
	void change_xy(int dx, int dy) {
		x += dx;
		y += dy;
	}
	friend class figure;
	friend class T_figure;
	friend class Z_figure;
	friend class O_figure;
	friend class I_figure;
	friend class S_figure;
	friend class J_figure;
	friend class L_figure;
};

class figure {
private:
	static const int n = 4;
	virtual void position1() = 0;
	virtual void position2() = 0;
	virtual void position3() = 0;
	virtual void position4() = 0;
protected:	
	cell cell_arr[n];
	int posn_now, dif;
public:	
	change_posn() {
		switch (posn_now) {
			case 1:
				position2();
				break;
			case 2:
				position3();
				break;
			case 3:
				position4();
				break;	
			case 4:
				position1();
				break;	
			default:
				printf("\n error in switch \n");	
		}
	}
	void draw() {
		for (int i=0; i<n; i++)
			cell_arr[i].draw(dif);
	}
	void clear() {
		for (int i=0; i<n; i++)
			cell_arr[i].clear(dif);
	}
	int change_xy(int dx, int dy) {
		int i, resul;
		if (dx != 0) {
			for (i=0; i<n; i++) {
				resul = check_cell(cell_arr[i].x + dx, cell_arr[i].y, dif);
				if (resul != 7)
					return 1;
			}
		} else
		if (dy != 0) { 
			for (i=0; i<n; i++) {
				resul = check_cell(cell_arr[i].x, cell_arr[i].y + dy, dif);
				if (resul != 7)
					return 2;
			}	
		}
		for (int i=0; i<n; i++) {
			cell_arr[i].change_xy(dx, dy);
		}
		return 0;	
	}
	~figure() {
		//printf("destructor \n");
	}
};
class T_figure : public figure {
public:
	T_figure(int dif) {
		cell_arr[0] = cell(5, 0, 5);
		cell_arr[1] = cell(4, 0, 5);
		cell_arr[2] = cell(6, 0, 5);
		cell_arr[3] = cell(5, 1, 5);
		posn_now = 1;
		this->dif = dif;
	}
	~T_figure() {}
private:	
	void position1() { 
		if (check_cell(cell_arr[1].x-1, cell_arr[1].y-1, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(-1, -1);
			cell_arr[2].change_xy(1, 1);
			cell_arr[3].change_xy(-1, 1);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x+1, cell_arr[1].y-1, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(1, -1);
			cell_arr[2].change_xy(-1, 1);
			cell_arr[3].change_xy(-1, -1);
			posn_now = 2;
		}
	}
	void position3() {
		if (check_cell(cell_arr[1].x+1, cell_arr[1].y+1, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(1, 1);
			cell_arr[2].change_xy(-1, -1);
			cell_arr[3].change_xy(1, -1);
			posn_now = 3;
		}
	}
	void position4() {
		if (check_cell(cell_arr[1].x-1, cell_arr[1].y+1, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(-1, 1);
			cell_arr[2].change_xy(1, -1);
			cell_arr[3].change_xy(1, 1);
			posn_now = 4;
		}
	}
};
class Z_figure : public figure {
public:
	Z_figure(int dif) {
		cell_arr[0] = cell(5, 1, 4);
		cell_arr[1] = cell(4, 0, 4);
		cell_arr[2] = cell(5, 0, 4);
		cell_arr[3] = cell(6, 1, 4);
		posn_now = 1;
		this->dif = dif;
	}
	~Z_figure() {}
private:
	void position1() { 
		if (check_cell(cell_arr[1].x, cell_arr[1].y-2, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(0, -2);
			cell_arr[2].change_xy(1, -1);
			cell_arr[3].change_xy(1, 1);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x+2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(2, 0);
			cell_arr[2].change_xy(1, 1);
			cell_arr[3].change_xy(-1, 1);
			posn_now = 2;
		}
	}
	void position3() {
		if (check_cell(cell_arr[1].x, cell_arr[1].y+2, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(0, 2);
			cell_arr[2].change_xy(-1, 1);
			cell_arr[3].change_xy(-1, -1);
			posn_now = 3;
		}
	}
	void position4() {
		if (check_cell(cell_arr[1].x-2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(-2, 0);
			cell_arr[2].change_xy(-1, -1);
			cell_arr[3].change_xy(1, -1);
			posn_now = 4;
		}
	}
};
class O_figure : public figure {
public:
	O_figure(int dif) {
		cell_arr[0] = cell(5, 0, 14);
		cell_arr[1] = cell(6, 0, 14);
		cell_arr[2] = cell(5, 1, 14);
		cell_arr[3] = cell(6, 1, 14);
		posn_now = 1;
		this->dif = dif;
	}
	~O_figure() {}
private:
	void position1() {}
	void position2() {}
	void position3() {}
	void position4() {}
};
class I_figure : public figure {
public:
	I_figure(int dif) {
		cell_arr[0] = cell(5, 0, 1);
		cell_arr[1] = cell(4, 0, 1);
		cell_arr[2] = cell(6, 0, 1);
		cell_arr[3] = cell(7, 0, 1);
		posn_now = 1;
		this->dif = dif;
	}
	~I_figure() {}
private:
	void position1() { 
		if (check_cell(cell_arr[1].x-1, cell_arr[1].y+1, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+2, cell_arr[3].y-2, dif) == 7) {
			cell_arr[1].change_xy(-1, 1);
			cell_arr[2].change_xy(1, -1);
			cell_arr[3].change_xy(2, -2);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x+1, cell_arr[1].y-1, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-2, cell_arr[3].y+2, dif) == 7) {
			cell_arr[1].change_xy(1, -1);
			cell_arr[2].change_xy(-1, 1);
			cell_arr[3].change_xy(-2, 2);
			posn_now = 2;
		}
	}
	void position3() {
		position1();
	}
	void position4() {}
};
class S_figure : public figure {
public:
	S_figure(int dif) {
		cell_arr[0] = cell(5, 1, 2);
		cell_arr[1] = cell(4, 1, 2);
		cell_arr[2] = cell(5, 0, 2);
		cell_arr[3] = cell(6, 0, 2);
		posn_now = 1;
		this->dif = dif;
	}
	~S_figure() {}
private:
	void position1() { 
		if (check_cell(cell_arr[1].x-1, cell_arr[1].y+1, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x, cell_arr[3].y-2, dif) == 7) {
			cell_arr[1].change_xy(-1, 1);
			cell_arr[2].change_xy(-1, -1);
			cell_arr[3].change_xy(0, -2);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x+1, cell_arr[1].y-1, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x, cell_arr[3].y+2, dif) == 7) {
			cell_arr[1].change_xy(1, -1);
			cell_arr[2].change_xy(1, 1);
			cell_arr[3].change_xy(0, 2);
			posn_now = 2;
		}
	}
	void position3() {
		position1();
	}
	void position4() {}
};
class J_figure : public figure {
public:
	J_figure(int dif) {
		cell_arr[0] = cell(6, 1, 6);
		cell_arr[1] = cell(5, 0, 6);
		cell_arr[2] = cell(5, 1, 6);
		cell_arr[3] = cell(7, 1, 6);
		posn_now = 1;
		this->dif = dif;
	}
	~J_figure() {}
private:
	void position1() { 
		if (check_cell(cell_arr[1].x, cell_arr[1].y-2, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(0, -2);
			cell_arr[2].change_xy(-1, -1);
			cell_arr[3].change_xy(1, 1);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x+2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(2, 0);
			cell_arr[2].change_xy(1, -1);
			cell_arr[3].change_xy(-1, 1);
			posn_now = 2;
		}
	}
	void position3() {
		if (check_cell(cell_arr[1].x, cell_arr[1].y+2, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(0, 2);
			cell_arr[2].change_xy(1, 1);
			cell_arr[3].change_xy(-1, -1);
			posn_now = 3;
		}
	}
	void position4() {
		if (check_cell(cell_arr[1].x-2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(-2, 0);
			cell_arr[2].change_xy(-1, 1);
			cell_arr[3].change_xy(1, -1);
			posn_now = 4;
		}
	}
};
class L_figure : public figure {
public:
	L_figure(int dif) {
		cell_arr[0] = cell(4, 1, 9);
		cell_arr[1] = cell(5, 0, 9);
		cell_arr[2] = cell(5, 1, 9);
		cell_arr[3] = cell(3, 1, 9);
		posn_now = 1;
		this->dif = dif;
	}
	~L_figure() {}
private:
	void position1() { 
		if (check_cell(cell_arr[1].x+2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(2, 0);
			cell_arr[2].change_xy(1, 1);
			cell_arr[3].change_xy(-1, -1);
			posn_now = 1;
		}
	}
	void position2() {
		if (check_cell(cell_arr[1].x, cell_arr[1].y+2, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y+1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y-1, dif) == 7) {
			cell_arr[1].change_xy(0, 2);
			cell_arr[2].change_xy(-1, 1);
			cell_arr[3].change_xy(1, -1);
			posn_now = 2;
		}
	}
	void position3() {
		if (check_cell(cell_arr[1].x-2, cell_arr[1].y, dif) == 7)
		if (check_cell(cell_arr[2].x-1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x+1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(-2, 0);
			cell_arr[2].change_xy(-1, -1);
			cell_arr[3].change_xy(1, 1);
			posn_now = 3;
		}
	}
	void position4() {
		if (check_cell(cell_arr[1].x, cell_arr[1].y-2, dif) == 7)
		if (check_cell(cell_arr[2].x+1, cell_arr[2].y-1, dif) == 7)
		if (check_cell(cell_arr[3].x-1, cell_arr[3].y+1, dif) == 7) {
			cell_arr[1].change_xy(0, -2);
			cell_arr[2].change_xy(1, -1);
			cell_arr[3].change_xy(-1, 1);
			posn_now = 4;
		}
	}
};

#endif
