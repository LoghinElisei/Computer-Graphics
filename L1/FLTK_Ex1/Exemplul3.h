#pragma once

#define WIN32
#include <iostream>

#include <chrono>
#include <thread>

#include <FL/FL.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Timer.H>
#include <FL/fl_draw.H>
#define PI 3.141592

typedef struct
{
	float x, y;
} Coord2D;

class Exemplul3 : public Fl_Window
{
	static const int np = 14; // nr puncte din care e format avionul
	// descrierea avionului
	const Coord2D avionPrototip[np] = { {-30,0},{-5,30},{-5,40},{0,45},{5,40},{5,30},
	{30,0},{5,20},{5,-30},{15,-40},{0,-35},
	{-15,-40},{-5,-30},{-5,20} };
	Coord2D avionRot[np]; // avionul care se roteste
	bool firstTime;
	int w, h;

	// callback utilizat pentru timerul cu care se face rotatia avionului
	static void Timer_CB(void *userdata) {
		Fl_Window *o = (Fl_Window*)userdata;
		o->redraw();
		Fl::repeat_timeout(0.1, Timer_CB, userdata);
	}

public:
	Exemplul3(int w = 512, int h = 512, int x = 200, int y = 200, const char* title = "SPG")
		: Fl_Window(x, y, w, h, title), firstTime(true), w(w), h(h)
	{
		// timer pentru afisarea avionului intr-o noua pozitie
		Fl::add_timeout(0.1, Timer_CB, (void*)this);
	}

	void afisare(const Coord2D avion[])
	{
		// deseneaza avionul primit ca parametru.
	}

	// determina laturile dreptunghiului de incadrare a obiectului
	void extensie(const Coord2D avion[], int np, float &latx, float &laty)
	{
		float xmin, ymin, xmax, ymax;
		xmin = xmax = avion[0].x;
		ymin = ymax = avion[0].y;
		for (int i = 1; i < np; i++)
		{
			if (avion[i].x < xmin) xmin = avion[i].x;
			if (avion[i].x > xmax) xmax = avion[i].x;
			if (avion[i].y < ymin) ymin = avion[i].y;
			if (avion[i].y > ymax) ymax = avion[i].x;
		}
		latx = xmax - xmin;
		laty = ymax - ymin;
	}

	// instantierea prin transformarea fata de originea sistemului de coordonate a obiectului avionPrototip
	void instantiere(Coord2D avion[], float u, float scal, int tx, int ty)
	{
		// u - unghiul de rotatie
		// scal - factorul de scalare
		// tx, ty - componentele vectorului de translatie
	}

	void draw() override
	{
		fl_draw_box(FL_FLAT_BOX, 0, 0, w, h, FL_WHITE);
		fl_color(FL_BLUE); // sau fl_color(0, 0, 255);

		int xc = w / 2;
		int yc = h / 2;
		float c, s, latx, laty, scal;
		
		extensie(avionPrototip, np, latx, laty);
		scal = (latx > laty) ? 50 / latx : 50 / laty;
		
		Coord2D avion[np];
		//avion orientat dreapta
		instantiere(avion, -PI / 2, scal, xc + 50, yc);
		afisare(avion);

		//avion orientat sus
		//instantiere(avion, ...);
		//afisare(avion);
		
		//avion orientat stanga
		

		//avion orientat jos
		

		if (firstTime)
		{
			//calculeaza coordonatele initiale ale avionului care se roteste
			instantiere(avionRot, (latx > laty) ? 50 / latx : 50 / laty, -PI / 2, xc, yc + 150);
			//desenare in pozitia initiala
			afisare(avionRot);
			firstTime = false;
		}
		else
		{
			//calculeaza sin/cos de 3 grade
			c = cos(PI / 60);
			s = -sin(PI / 60);
			//actualizeaza coordonatele varfurilor avionului care se roteste
			for (int i = 0; i < np; i++)
			{
				float xx = avionRot[i].x;
				avionRot[i].x = xx * c - avionRot[i].y*s + xc - xc * c + yc * s;
				avionRot[i].y = xx * s + avionRot[i].y*c + yc - xc * s - yc * c;
			}
			//desenare in noua pozitie
			afisare(avionRot);
		}
	}
};

