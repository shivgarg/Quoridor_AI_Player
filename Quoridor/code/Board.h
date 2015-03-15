#include <utility>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define HORIZONTAL 1
#define VERTICAL 2


struct Position{
	int x,y;
	Position(){};
	Position( int x1 , int y1) : x(x1) ,y(y1) {};
	bool operator==( const Position & d ) const {  return (x==d.x) && (y==d.y);}
};



struct Player{
	Position p;
	int walls;
	Player(){};
	Player(Position o,int w)
	{
		walls=w;
		p=o;
	}
};
class Board{

public:
	int n,m,k;
	Player p1,p2;
	Player* my,*oppo;
	int my_target;
	int oppo_target;
	int **walls;
	int move[3];
	void implement_move(int type,int x,int y);
	void set_move();

	Board(int x,int y, int z)
	{
		n=x;m=y;k=z;
		p1=Player(Position((m+1)/2,1),k);
		p2=Player(Position((m+1)/2,n),k);
		walls=(int **)malloc((n+2)*sizeof(int*));
		for(int i=0;i<n+2;i++)
		{
			walls[i]=(int*)malloc((m+2)*sizeof(int));
			memset(walls[i],0,sizeof(int)*(m+2));
		}

	}

	bool legal_p(Position p)
	{
		if(p.x>m || p.x<0 || p.y<0 || p.y>n || p==p1.p || p==p2.p)
			return false;
		else
			return true;
	}
	// to add path blocking criteria 
	//1 for horizontal 2 vice
	bool legal_w(Position p,int type)
	{
			if(p.x<=1 || p.x>=m+1 || p.y<=1 || p.y>=n+1)
				return false;
			if(walls[p.y][p.x]!=0)
			{
					return false;
			}
			else
			{
				if(type==HORIZONTAL && (walls[p.y][p.x-1]==HORIZONTAL || walls[p.y][p.x+1]==HORIZONTAL))
					return false;
				else if(type==VERTICAL && (walls[p.y-1][p.x]==VERTICAL || walls[p.y+1][p.x]==VERTICAL))
					return false;
			}
			return true;
	}
			


};