#pragma once
#define WIN32 // doar in Windows
#include <iostream>
#include <FL/FL.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <cmath>
#define PI 3.141592f

class MyWidget : public Fl_Window
{
	float XFm, XFM, YFm, YFM;
	int XPm, XPM, YPm, YPM;
	int tip_tran; //tip_tran == 0 -> scalare neuniforma, tip_tran != 0 -> scalare uniforma
	float sx, sy, tx, ty;

	int width, height;

	typedef float(*MyFuncPtrType)(float);
public:
	MyWidget(int width = 512, int height = 512)
		: Fl_Window(200, 200, width, height, "SPG Lab2"), width(width), height(height)
	{
	}

	void init_grafic()
	{
		XFm = YFm = XFM = YFM = 0;
		XPm = YPm = XPM = YPM = 0;
		tip_tran = 0;
		sx = sy = tx = ty = 0;
	}
	void calctran()
	{
		if (XFM > XFm && YFM > YFm)
		{
			//se determina sx, sy, tx, ty
			this->sx = (XPM - XPm) / (XFM - XFm);
			this->sy = (YPM - YPm) / (YFM - YFm);
	

			if (tip_tran != 0)
			{
				float s = min(sx, sy);
				sx = sy = s;
			}
			this->tx = XPm - sx * XFm;
			this->ty = YPm - sy * YFm;
		}
		else
			sx = sy = tx = ty = 0;
	}
	int XDisp(float xf)
	{
		//transformarea fereastra-poarta pt coordonata x
		return xf * sx + tx;

	}
	int YDisp(float yf)
	{
		//transformarea fereastra-poarta pt coordonata y
		return int(YPM - sy * (yf - YFm));
		
	}
	void cadru_poarta()
	{
		fl_line(XPm, YPm, XPm, YPM);
		fl_line(XPm, YPM, XPM, YPM);
		fl_line(XPM, YPM, XPM, YPm);
		fl_line(XPM, YPm, XPm, YPm);
	}
	static float f1(float x)
	{
		return sin(10*x);
	}

	static float f2(float x)
	{
		return tan(x);

	}
	static float f3(float x)
	{
		return x * sin(10*x);
	}
	static float f4(float x)
	{
		return (x * x - 2) * (x + 3);
	}
	
	void grafic(float xmin, float xmax, float pas, MyFuncPtrType f)
	{
		XFm = xmin;
		XFM = xmax;
		// se determina YFm si YFM ca fiind valoarea minima, respectiv maxima a
        // functiei f in intervalul XFm, XFM
		for (float x = xmin; x < xmax - pas; x += pas)
		{
			float valFun = f(x);
			if (isinf(valFun) || isnan(valFun)) continue;
			if (YFm > valFun)
				YFm = valFun;
			if (YFM < valFun)
				YFM = valFun;
		}
	    
		cadru_poarta();
		calctran();
		//trasarea axei x
		if (YFm < 0 && YFM > 0)
			// ...
			fl_line(XDisp(XFm), YDisp(0), XDisp(XFM), YDisp(0));
			//trasarea axei y
			if (XFm < 0 && XFM > 0)
				// ...
				//trasare grafic
				fl_line(XDisp(0), YDisp(YFm), XDisp(0), YDisp(YFM));

				for (float x = xmin; x < xmax - pas; x += pas)
				{
					float xf = x;
					float yf = f(x);
					float xP1 = XDisp(xf);
					float yP1 = YDisp(yf);
					float xP2 = XDisp(xf + pas);
					float yP2 = YDisp(f(xf + pas));

					fl_line(xP1, yP1, xP2, yP2);
				}
	}

	void text(const char* str)
	{
		fl_draw(str, XPm, YPM + 12);
	}

	void draw() override
	{
		fl_color(FL_BLUE);

		int xmaxe, ymaxe, stg = 50, drt = 50;
		float pas = 0.1;
		init_grafic();
		
		xmaxe = width;
		ymaxe = height;
		
		XPm = stg;
		XPM = xmaxe / 2 - drt / 2;
		YPm = stg;
		YPM = ymaxe / 2 - drt / 2;

		grafic(-5, 5, pas, f1);
		text("sin(10x)");

		stg = 100;
		drt = 100;
		float diff;
		diff = XPM - XPm;
		XPm = XPm + XPM;
		XPM = XPm + diff;
		grafic(-5, 5, pas, f2);
		text("tan(x)");


		diff = YPM - YPm;
		YPm = YPm + YPM;
		YPM = YPm + diff;
		grafic(-5, 5, pas, f3);
		text("xsin(10x)");

		diff = XPM - XPm;
		XPm = XPm - diff - stg/2;
		XPM = XPm + diff;
		grafic(-5, 5, pas, f4);
		text("(x^2-2)(x+3)");
	}
};
