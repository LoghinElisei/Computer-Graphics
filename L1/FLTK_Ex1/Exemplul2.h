#pragma once

#define WIN32
#include <iostream>
#include <FL/FL.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#define PI 3.141592

class Exemplul2 : public Fl_Window
{
	int xc, yc; // centrul ferestrei
	float x[4], y[4]; // coordonatele varfurilor unui patrat
	float xcp, ycp; // coordonatele centrului patratului
	int raza, latura;
	int N; // nr de patrate

public:
	Exemplul2(int w = 512, int h = 512, int x = 300, int y = 200, const char* title = "SPG")
		: Fl_Window(x, y, w, h, title)
	{
		xc = this->w() / 2;
		yc = this->h() / 2;
		N = 10;
		init_obiect(100, 80);
	}

	void init_obiect(int _raza, int _latura)
	{
		// functie ce calculeaza coordonatele varfurilor in pozitia initiala
		raza = _raza;
		latura = _latura;
		float half = latura / 2.0;
		xcp = xc + raza;
		ycp = yc;

		x[0] = xc - half;
		y[0] = yc - half;
		x[1] = xc  + half;
		y[1] = yc - half;
		x[2] = xc  + half;
		y[2] = yc + half;
		x[3] = xc - half;
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
		fl_color(FL_BLUE);

		float du = 2 * PI / N;  // unghiul dintre doua patrate succesive
		float c = cos(du);
		float s = sin(du);

		for (int i = 0; i < N; i++)
		{
			// se deseneaza patratul curent
			desen();

			// Calculăm următoarea poziție prin rotirea vârfurilor 
			// în jurul centrului ferestrei (xc, yc)
			// se determina coordonatele varfurilor noului patrat functie de pozitia noului centru
			float u = (i + 1) * du;
			float next_xcp = xc + raza * cos(u);
			float next_ycp = yc + raza * sin(u);

			float dx = next_xcp - xcp;
			float dy = next_ycp - ycp;

			for (int j = 0; j < 4; j++)
			{
				x[j] += dx;
				y[j] += dy;
			}

			xcp = next_xcp;
			ycp = next_ycp;
		}
	}
};

