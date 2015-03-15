#include "Board.h"



void Board::implement_move(int type,int x,int y)
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


void Board::set_move()
{

}

vector<Position> Board::get_move(int x,int y)
{
		vector<Position> lis;
		if(onboard(x+1,y) )
		{
			if(east(x,y))
				{
					if(oppo->p.x==x+1 && oppo->p.y==y)
					{
						if(onboard(x+2,y))
						{
							if(east(x+1,y))
								lis.push_back(Position(x+2,y));
							else
							{
								if(onboard(x+1,y+1))
								{
									if(south(x+1,y))
										lis.push_back(Position(x+1,y+1));

								}
								if(onboard(x+1,y-1))
								{
									if(north(x+1,y))
										lis.push_back(Position(x+1,y-1));
								}
							}
						}
					}
					else
					{
						lis.push_back(Position(x+1,y));
					}
				}
		}
		if(onboard(x-1,y))
		{
			if(west(x,y))
				{
					if(oppo->p.x==x-1 && oppo->p.y==y)
					{
						if(onboard(x-2,y))
						{
							if(west(x-1,y))
							{
								lis.push_back(Position(x-2,y));
							}
							else
							{
								if(onboard(x-1,y+1))
								{
									if(south(x-1,y))
										lis.push_back(Position(x-1,y+1));
								}
								if(onboard(x-1,y-1))
								{
									if(north(x-1,y))
										lis.push_back(Position(x-1,y-1));
								}
							}
						}
					}
					else
						lis.push_back(Position(x-1,y));
				}
		}
		if(onboard(x,y+1))
		{
			if(south(x,y))
				{
					if(oppo->p.x==x && oppo->p.y==y+1)
					{
						if(onboard(x,y+2))
						{
							if(south(x,y+1))
							{
								lis.push_back(Position(x,y+2));
							}
							else
							{
								if(onboard(x-1,y+1))
								{
									if(west(x,y+1))
										lis.push_back(Position(x-1,y+1));
								}
								if(onboard(x+1,y+1))
								{
									if(east(x,y+1))
										lis.push_back(Position(x+1,y+1));
								}
							}
						}
					}
					else
						lis.push_back(Position(x,y+1));
				}
		}
		if(onboard(x,y-1))
		{
			if(north(x,y))
				{
					if(oppo->p.x==x && oppo->p.y==y-1)
					{
						if(onboard(x,y-2))
						{
							if(north(x,y-1))
							{
								lis.push_back(Position(x,y-2));
							}
							else
							{
								if(onboard(x-1,y-1))
								{
									if(west(x,y-1))
										lis.push_back(Position(x-1,y-1));
								}
								if(onboard(x+1,y-1))
								{
									if(east(x,y-1))
										lis.push_back(Position(x+1,y-1));
								}
							}
						}
					}
					else
						lis.push_back(Position(x,y-1));
				}
		}
		return lis;
}

