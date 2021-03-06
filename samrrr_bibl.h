#include <math.h>			// Header File For Math Library Routines
#include <stdio.h>			// Header File For Standard I/O Routines
#include <stdlib.h>			// Header File For Standard Library
#include <list>

#pragma once;

using namespace std;

struct PROPERTY
{
	float val;
	float min, max;
	
	void add(float _x)
	{
		if (_x < 0)
		{
			val += _x;
			if (val < min)
				val = min;
		}
		else
		{
			val += _x;
			if (val > max)
				val = max;
		}
	}

	void set(float _x)
	{
		val = _x;
		if (val < min)
			val = min;
		if (val > max)
			val = max;
	}


};

struct POS
{
public:
	float x, y;
	
	POS()
	{
		x = 0; 
		y = 0;
	}

	POS(float _x,float _y)
	{
		x = _x;
		y = _y;
	}
	
	friend POS operator + (POS _a, POS _b)
	{
		return POS(_a.x + _b.x, _a.y + _b.y);
	}

	friend POS operator - (POS _a, POS _b)
	{
		return POS(_a.x - _b.x, _a.y - _b.y);
	}

	friend POS operator / (POS _a, float _b)
	{
		return POS(_a.x / _b, _a.y / _b);
	}

	friend POS operator * (POS _a, float _b)
	{
		return POS(_a.x * _b, _a.y * _b);
	}

	void norm()
	{
		float r = sqrt(x*x+y*y);
		if (r > 0)
		{
			x /= r;
			y /= r;
		}
		else
		{
			x = 1;
			y = 0;
		}
	}
};

struct M_ACTION
{
	int t;//1-lmd 2-lmu 3-rmd 4-rmu 5-mbd 6-mbu 7-scroll(i[0]) 8-move
	int i[2];
};

struct K_ACTION
{
	int key;
	int t;//1-down 0-up
};

class KEYBOARDINFO
{
public:
	bool keys[512];
	bool keysz[512];
	list <K_ACTION> l;
	KEYBOARDINFO()
	{
		for (int i = 0; i < 512; i++)
		{
			keys[i] = 0;
			keysz[i] = 0;
		}
	}
	void addaction(int _key, int _state)
	{
		if (_key < 0 || _key>=512)
			return;
		K_ACTION a;
		a.key = _key;
		a.t = _state;
		l.push_back(a);
	}
	bool use_action()
	{
		if (l.empty())
		{
			return false;
		}
		K_ACTION a=*l.begin();
		keysz[a.key] = keys[a.key];
		keys[a.key] = a.t;
		l.pop_front();
		return true;
	}
};

class MOUSEINFO
{
public:
	list <M_ACTION> l;
	
	int x, y, bl, br, bm, scroll;
	int xz, yz, blz, brz, bmz;

	MOUSEINFO()
	{
		x = 0; 
		y = 0;
		bl = 0;
		br = 0;
		bm = 0;
		scroll = 0;

		xz = 0;
		yz = 0;
		blz = 0;
		brz = 0;
		bmz = 0;
	}

	void addaction(int _t, int _i0,int _i1)//1-lmd 2-lmu 3-rmd 4-rmu 5-mbd 6-mbu 7-scroll(i[0]) 8-move
	{
		M_ACTION a;
		a.t = _t;
		a.i[0] = _i0;
		a.i[1] = _i1;
		l.push_back(a);
	}

	bool use_action()
	{
		if (l.empty())
		{
			return false;
		}

		M_ACTION a = *l.begin();
		
		scroll = 0;
		blz = bl;
		brz = br;
		bmz = bm;
		xz = x;
		yz = y;

		switch (a.t)
		{
		case 1:
			bl = 1;
			break;
		case 2:
			bl = 0;
			break;
		case 3:
			br = 1;
			break;
		case 4:
			br = 0;
			break;
		case 5:
			bm = 1;
			break;
		case 6:
			bm = 0;
			break;
		case 7:
			scroll = a.i[0];
			break;
		case 8:
			x = a.i[0];
			y = a.i[1];
			break;

		}
		l.pop_front();
		return true;
	}
	//max_size
};

void dd(float* x,float* y,float c, float d);
float ss(float x,float y,float x1,float y1);
float ddx(float c, float d);
float ddy(float c, float d);
void roate(float *x,float *y,float x1,float y1,float c);
float ras(float x,float y);
float ricosgr(float plos,float patr);
