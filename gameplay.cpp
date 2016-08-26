#include "gameplay.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>    // ???????????? ???? ??? ?????????? OpenGL32
#include <gl\glu.h>   // ???????????? ???? ??? ?????????? GLu32

namespace GP
{



void init(DRAWS);
void start(char* level_file);
void upd(MOUSEINFO &_mouse, KEYBOARDINFO &_keyboard);
void draw(int, int);
void line_rect(POS _p1, POS _p2);
void draw_str(int _x, int _y, int _r, int _t);





void(*line)(POS, POS);
void(*setcolor)(float, float, float, float);
void(*triangle)(POS, POS, POS);

STRUCTURE_INFO str_info[256];

STRUCTURE_DATA structure[1024];
int lspid;
int razokx, razoky;

struct
{
	POS pos;
	float zoom;
}cam;

struct
{
	int x, y;
}mouse;

class
{
public:
	PROPERTY scroll;
	bool is_scrool;

	int selected_struct;
	int state;//0-select 1-info

	void init()
	{
		scroll.min = 0;
		scroll.max = 0;
		scroll.val = 0;
		state = 0;
		selected_struct = -1;
	}

	void upd_m(MOUSEINFO &_mouse)
	{
		for (int i = 0; i < 20; i++)
		{
			int s = 69;
			POS p1, p2;

			p1 = POS(2 + i * (s + 2)          , razoky - 97);
			p2 = POS(2 + i * (s + 2) + (s - 1), razoky - 97 + (s - 1));

			if (!_mouse.bl && _mouse.blz)
			if (_mouse.x > p1.x && _mouse.x < p2.x && _mouse.y > p1.y && _mouse.y < p2.y)
			{
				selected_struct = i;
			}
		}
	}

	void draw()
	{
		setcolor(1, 1, 1, 1);
		line(POS(0, razoky - 1), POS(razokx - 1, razoky - 1));
		line(POS(0, razoky - 100), POS(razokx - 1, razoky - 100));
		//line(POS(0, razoky - 1), POS(0, razoky - 100));
		//line(POS(razokx - 1, razoky - 1), POS(razokx - 1, razoky - 100));

		for (int i = 0; i < 20; i++)
		{
			int s = 69;
			POS p1, p2;

			p1 = POS(2 + i * (s + 2), razoky - 97);
			p2 = POS(2 + (s - 1) + i * (s + 2), razoky - 97 + (s - 1));

			setcolor(1, 1, 1, 1);
			line_rect(p1, p2);

			if (selected_struct == i)
			{
				setcolor(0.5, 1, 1, 1);
				line_rect(p1 - POS(1, 1), p2 + POS(1, 1));
				line_rect(p1 + POS(1, 1), p2 - POS(1, 1));
			}

			draw_str(2 + (s / 2) + i * (s + 2), razoky - 97 + (s/2), s / 2 - 3,i);
		}
	}

}down_bar;

void clear()
{
	int i, r, o, j, a, b, c, d;

	lspid = 0;
	for (i = 0; i < 1024; i++)
		structure[i].t = -1;
}

void circle(float _x, float _y, float _r)
{
	int i, r, o, j, a, b, c, d;
	int x, y;
	POS p,p1, p2;

	x = _x;
	y = _y;
	r = _r;
	p = POS(x,y);

	j = 12;

	if (_r > 20)
		j = 24;
	if (_r > 70)
		j = 36;

	for (i = 0; i <= j; i++)
	{
		c = i * 360 / j;
		p2 = p1;
		dd(&p1.x, &p1.y, c, _r);
		if (i>0)
		line(p+p1,p+p2);
	}
}

void line_rect(POS _p1, POS _p2)
{
	line(_p1, POS(_p2.x, _p1.y));
	line(POS(_p2.x, _p1.y), _p2);
	line(_p2, POS(_p1.x, _p2.y));
	line(POS(_p1.x, _p2.y), _p1);
}

void draw_str(int _x, int _y, int _r,int _t)
{
	if (_t < 0 || _t >= 128)
		return;

	setcolor(1,1,1,1);
	circle(_x, _y, _r);
	POS p1, p2;

	switch (_t)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			int c = i * 360 / 3 + 40;
			dd(&p1.x, &p1.y, c, _r*0.8);
			dd(&p2.x, &p2.y, c + 30, _r*0.8);
			setcolor(0, 0, 1, 1);
			//line(POS(_x, _y), POS(_x + p1.x, _y + p1.y));
			setcolor(0,1,1,1);
			triangle(POS(_x, _y), POS(_x + p1.x, _y + p1.y), POS(_x + p2.x, _y + p2.y));

		}
		break;
	case 1:
		circle(_x, _y, _r*0.8);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void init(DRAWS _draws)
{
	int i, r, o, j, a, b, c, d;

	line = _draws.line;
	setcolor = _draws.setcolor;
	triangle = _draws.triangle;

	for (i = 0; i < 256; i++)
		str_info[i].type = -1;

	for (i = 0; i < 1024; i++)
		structure[i].t = -1;

	i = 0;

	str_info[i].type = 0;
	str_info[i].connectcap = 50;
	str_info[i].connectlength = 50;
	str_info[i].connectone = 0;
	str_info[i].cost = 50;
	str_info[i].energygen = 2;
	str_info[i].energymax = 30;
	str_info[i].energyout = 5;
	str_info[i].hp = 0;
	str_info[i].r = 5;

	i = 1;

	str_info[i].type = 1;
	str_info[i].connectcap = 50;
	str_info[i].connectlength = 50;
	str_info[i].connectone = 0;
	str_info[i].cost = 50;
	str_info[i].energygen = 0;
	str_info[i].energymax = 3000;
	str_info[i].energyout = 5;
	str_info[i].hp = 0;
	str_info[i].r = 7;
}

bool add_structure(POS _p,int _t,int _col,int _build = 0)
{
	int i, r, o, j,a,b,c,d;
	for (i = 0; i < 1024 && structure[lspid].t != -1; i++)
	{
		lspid = (lspid + 1) % 1024;
	}

	j = lspid;

	if (structure[j].t != -1)
		return false;

	for (i = 0; i < 1024; i++)
	if (structure[i].t != -1)
	{
		float v = ras(_p.x - structure[i].pos.x, _p.y - structure[i].pos.y);
		if ( v <= str_info[_t].r + str_info[structure[i].t].r)
		{
			return false;
		}
		if (v <= str_info[structure[i].t].connectlength)
		{
			for (r = 0; r < 20; r++)
			if (structure[i].c[r].id!=-1)
			{
				POS p;
				POS p1 = structure[structure[i].c[r].id].pos;
				POS p2 = structure[i].pos;
				for (o = 0; o < 25; o++)
				{
					p = p1*(1 - o/25.0) + p2*o/25.0;
					if (ras(p.x - _p.x, p.y - _p.y)<str_info[_t].r+1)
						return false;
				}
			}
		}
	}

	structure[j].t = _t;
	structure[j].type = str_info[_t].type;

	structure[j].hp.max = str_info[_t].hp;
	structure[j].hp.val = str_info[_t].hp;

	structure[j].en.max = str_info[_t].energymax;
	structure[j].en.val = 0;

	structure[j].col = _col;
	structure[j].pos = _p;
	structure[j].r = str_info[_t].r;

	for (i = 0; i < 20;i++)
		structure[j].c[i].id = -1;

	r = 0;

	for (i = 0; i < 1024 && r < 20 ; i++)
	if (structure[i].t != -1)
	if (structure[i].col == _col)
	if (ras(structure[i].pos.x - structure[j].pos.x, structure[i].pos.y- structure[j].pos.y) <
		min(str_info[structure[i].t].connectlength, str_info[structure[j].t].connectlength))
	if (i != j)
	{
		POS p;
		POS p1 = structure[i].pos;
		POS p2 = structure[j].pos;

		b = 1;

		for (o = 0; o < 25; o++)
		{
			p = p1*(1 - o / 25.0) + p2*o / 25.0;
			for (a = 0; a < 1024;a++)
			if (structure[a].t!=-1)
			if (a != i && a != j)
			if (ras(p.x - structure[a].pos.x, p.y -structure[a].pos.y)<str_info[structure[a].t].r)
			{
				b = 0;
			}
		}

		if (b)
		{
			a = -1;
			for (o = 0; o < 20; o++)
			if (structure[i].c[o].id == -1)
				a = o;

			if (a != -1)
			{
				structure[i].c[a].id = j;
				structure[j].c[r].id = i;
				r++;
			}
		}
	}

	if (structure[j].type == 0)
	{

	}

	return true;
}

void start(char* level_file)
{
	int i, r, o, j, a, b, c, d;

	clear();


}

void upd_m(MOUSEINFO &_mouse)
{
	if (down_bar.selected_struct >= 0)
	{
		if (!_mouse.bl && _mouse.blz)
			add_structure(POS(_mouse.x, _mouse.y), down_bar.selected_struct, 0);
	}
}

void add_en_line(int _i1, int _i2,float en)
{
	for (int i1 = 0; i1 < 20; i1++)
		if (structure[_i1].c[i1].id == _i2)
		{
			structure[_i1].c[i1].en += en;
		}
	for (int i1 = 0; i1 < 20; i1++)
		if (structure[_i2].c[i1].id == _i1)
		{
			structure[_i2].c[i1].en += en;
		}
}

void upd(MOUSEINFO &_mouse, KEYBOARDINFO &_keyboard)
{
	while (_mouse.use_action())
	{
		if (_mouse.y < razoky - 100)
		{
			upd_m(_mouse);
		}
		else
		{
			down_bar.upd_m(_mouse);
		}
	}
	
	mouse.x = _mouse.x;
	mouse.y = _mouse.y;







	for (int i1 = 0; i1 < 1024; i1++)
	if (structure[i1].t != -1)
	for (int i2 = 0; i2 < 20; i2++)
	if (structure[i1].c[i2].id != -1)
		structure[i1].c[i2].en = 0;


	//reactor-store
	for (int i1 = 0; i1 < 1024; i1++)
	if (structure[i1].t != -1)
	if (structure[i1].type == 0)
	{
		int m[1024];
		for (int i2 = 0; i2 < 1024; i2++)
			m[i2] = -1;

		int poin[1024];
		int fr, la,res;
		fr = 0;
		la = 1;

		poin[0] = i1;
		m[i1] = 0;
		res = 0;

		for (; fr != la;)
		{


			for (int i2 = 0; i2 < 20; i2++)
			if (structure[poin[fr]].c[i2].id != -1)
			if (m[structure[poin[fr]].c[i2].id] == -1)
			{
				m[structure[poin[fr]].c[i2].id] = m[poin[fr]] + 1;
				poin[la] = structure[poin[fr]].c[i2].id;
				la = (la + 1) % 1024;
			}
			if (structure[poin[fr]].type == 1)
			{
				la = fr;
				res = 1;
			}
			else
			{
				fr = (fr + 1) % 1024;
			}
		}

		if (res == 1)
		{
			int st = poin[fr];
			for (int i3 = m[st]+1; i3 >= 0; i3--)
			for (int i2 = 0; i2 < 20; i2++)
			if (structure[st].c[i2].id != -1)
				if (m[st]>m[structure[st].c[i2].id])
			{
				add_en_line(st, structure[st].c[i2].id,1);
				st = structure[st].c[i2].id;
				i2 = 20;
			}
				
		}


	}








}

void draw(int _razokx,int _razoky)
{
	razokx = _razokx;
	razoky = _razoky;

	down_bar.draw();

	setcolor(1, 1, 0, 1);

	circle(mouse.x, mouse.y, 10);

	setcolor(0.2, 0.2, 0.2, 1);

	circle(mouse.x, mouse.y, str_info[down_bar.selected_struct].connectlength);

	for (int i = 0; i < 1024; i++)
	{
		circle(structure[i].pos.x, structure[i].pos.y, 0);
		if (structure[i].t != -1)
		{
			draw_str(structure[i].pos.x, structure[i].pos.y, str_info[structure[i].t].r, structure[i].t);
			for (int r = 0; r < 20;r++)
			if (structure[i].c[r].id != -1)
			{
				int j = structure[i].c[r].id;
				float xx, yy, u;
				POS p1, p2;
				u = ss(structure[i].pos.x, structure[i].pos.y, structure[j].pos.x, structure[j].pos.y);
				dd(&xx, &yy, u, 1);
				p1 = structure[i].pos + POS(xx, yy) * str_info[structure[i].t].r;
				p2 = structure[j].pos - POS(xx, yy) * str_info[structure[j].t].r;

				float v = structure[i].c[r].en/10;

				setcolor(0.3 + 0.7*v, 0.3 + 0.7*v, 0.3 + 0.7*v, 1);

				if (structure[i].c[r].en == 0)
				{
					setcolor(0,1,0, 1);
				}

				line(p1,p2);
			}
		}
	}
}



};