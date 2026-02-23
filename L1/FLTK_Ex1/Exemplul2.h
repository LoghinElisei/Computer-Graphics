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
	Exemplul2(int w = 512, int h = 512, int x = 200, int y = 200, const char* title = "SPG")
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

			// se calculeaza noua pozitie a centrului patratului

			// se determina coordonatele varfurilor noului patrat functie de pozitia noului centru
		}
	}
};

