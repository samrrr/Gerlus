#include "gameplay.h"

namespace GP
{



void init(DRAWS);
void start(char* level_file);
void upd(MOUSEINFO &_mouse, KEYBOARDINFO &_keyboard);
void draw(int,int);





void(*line)(POS, POS);
void(*setcolor)(float, float, float, float);

STRUCTURE_INFO str_info[256];

STRUCTURE_DATA structure[1024];
int lspid;



void clear()
{
	int i, r, o, j, a, b, c, d;

	lspid = 0;
	for (i = 0; i < 1024; i++)
		structure[i].t = -1;
}

void init(DRAWS _draws)
{
	int i, r, o, j, a, b, c, d;

	line = _draws.line;
	setcolor = _draws.setcolor;

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
	i = 0;

	str_info[i].type = 0;
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
	int i, r, o, j;
	for (i = 0; i < 1024 && structure[i].t != -1; i++)
	{
		lspid = (lspid + 1) % 1024;
	}

	if (structure[lspid].t != -1)
		return false;

	structure[lspid].t = _t;
	structure[lspid].type = str_info[_t].type;

	structure[lspid].hp.max = str_info[_t].hp;
	structure[lspid].hp.val = str_info[_t].hp;

	structure[lspid].en.max = str_info[_t].energymax;
	structure[lspid].en.val = 0;

	structure[lspid].col = _col;
	structure[lspid].pos = _p;
	structure[lspid].r = str_info[_t].r;

	if (structure[lspid].type == 0)
	{

	}

	return true;
}

void start(char* level_file)
{
	int i, r, o, j, a, b, c, d;

	clear();


}

void upd(MOUSEINFO &_mouse, KEYBOARDINFO &_keyboard)
{

}

void draw(int _razokx,int _razoky)
{
	setcolor(1, 1, 0, 1);
	line(POS(10, 10), POS(0, 0));
	line(POS(0, 10), POS(0, 0));
	line(POS(10, 0), POS(0, 0));
	line(POS(150, 50), POS(150, 60));
	line(POS(151, 60), POS(151, 50));
}



};