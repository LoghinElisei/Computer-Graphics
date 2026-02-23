#pragma once

#define WIN32
#include <iostream>
#include <FL/FL.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#define PI 3.141592

class Exemplul1 : public Fl_Window
{
	int xc, yc; // centrul ferestrei
	float x[4], y[4]; // coordonatele varfurilor unui patrat
	int N; // nr de patrate

public:
	Exemplul1(int w = 512, int h = 512, int x = 200, int y = 200, const char* title = "SPG")
		: Fl_Window(x, y, w, h, title)
	{
		xc = this->w() / 2;
		yc = this->h() / 2;
		N = 10;
		init_obiect(100, 80);
	}

	void init_obiect(int raza, int latura)
	{
		// functie ce calculeaza coordonatele varfurilor in pozitia initiala
		float half = latura / 2.0;
		x[0] = xc + raza - half;
		y[0] = yc - half;
		x[1] = xc + raza + half;
		y[1] = yc - half;
		x[2] = xc + raza + half;
		y[2] = yc + half;
		x[3] = xc + raza - half;
		y[3] = yc + half;
	}

	void desen()
	{
		// deseneaza un patrat cu varfurile (x[0] y[0]), (x[1] y[1]), etc.
		for (int i = 0; i < 3; i++)
			fl_line(x[i], y[i], x[i + 1], y[i + 1]);
		fl_line(x[3], y[3], x[0], y[0]);
	}

	void draw() override
	{
		fl_color(FL_BLUE); // sau fl_color(0, 0, 255);

		float du = 2 * PI / N; //unghiul dintre doua patrate succesive
		float c = cos(du);
		float s = sin(du);

		for (int i = 0; i < N; i++)
		{
			/*
			- se deseneaza patratul curent
			- se calculeaza noi valori pentru x[], y[]
			prin aplicarea unor transformari de translatie / rotatie, dupa caz
			*/

			desen();
			for (int j = 0; j < 4; j++)
			{
				int x_old = x[j] - xc;
				int y_old = y[j] - yc;
				float x_rot = x_old * c - y_old * s;
				float y_rot = x_old * s + y_old * c;
				x[j] = x_rot + xc;
				y[j] = y_rot + yc;
			}


		}
	}
};

