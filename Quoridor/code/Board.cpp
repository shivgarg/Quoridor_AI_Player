#include "Board.h"



void implement_move(int type,int x,int y)
{
	if(type==0)
	{
		oppo->p.x=x;
		oppo->p.y=y;
	}
	else 
	{
		walls[y][x]=type;
	}
}

void set_move()
{
	
}