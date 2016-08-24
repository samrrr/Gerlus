#include "samrrr_bibl.h"

struct CONNECT
{
	int id;
	float en;
	float maxen;
};

struct STRUCTURE_DATA
{
	POS pos;
	int t;
	int col;
	int r;
	PROPERTY hp, en, rel, build;
	CONNECT c[20];
};

struct STRUCTURE_INFO
{
	float hp;
	int cost;
	float build_time;
	float reload;//seconds
	float r;
	int type;//0-reactor 1-storage 2-laser 3-shooter 4-wawer 5-factory

	float energygen;//
	float energymax;//
	float energyout;//max en out/in

	float connectcap;
	float connectlength;
	int connectone;//true,false

	float shootdamage;//per shoot
	float shootenergy;
	float shootspeed;
	float shootexploderange;
	float shootrange;

	
};

namespace GP
{
	void init();
	void start(char* level_file);
	void upd();
	void draw();
};

