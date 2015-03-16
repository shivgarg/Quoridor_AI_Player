#include <utility>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

#define HORIZONTAL 1
#define VERTICAL 2


struct Position{
	int x,y;
	Position(){};
	Position( int x1 , int y1) : x(x1) ,y(y1) {};
	bool operator==( const Position & d ) const {  return (x==d.x) && (y==d.y);}
};

struct Move{
	Position p;
	int type;
	Move(){};
	Move(Position t,int t1): p(t),type(t1){};
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
	void implement_move(Player*,Move);
	vector<Move> get_move(int x,int y);
	void set_move();
	int maxval(int,int,int);
	int minval(int,int,int);
	int utility();

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

	bool onboard(int x,int y)
	{	
		if(x>m || x<=0 || y<=0 || y>n )
			return false;
		else
			return true;
	}
	
	bool south(int x,int y)
	{
			if (walls[y+1][x]==1 || walls[y+1][x+1]==1)
				return false;
			else 
				return true;
	}
	bool north(int x,int y)
	{
		if (walls[y][x]==1 || walls[y][x+1]==1)
				return false;
			else 
				return true;
	}
	bool east(int x,int y)
	{
		if (walls[y][x+1]==2 || walls[y+1][x+1]==2)
				return false;
			else 
				return true;
	}
	bool west(int x,int y)
	{
		if (walls[y][x]==2 || walls[y+1][x]==2)
				return false;
			else 
				return true;
	}
		

	// to add path blocking criteria 
	//1 for horizontal 2 vice


bool isNotPath(int x1,int y1,int tar)
{
			bool visited[m+1][n+1];
			memset(visited,false,sizeof(bool)*(m+1)*(n+1));
			visited[x1][y1]=true;
			queue< pair<int,int> > bfs_q;
			bfs_q.push(make_pair(x1,y1));
			bool isblock=true;
			while(!bfs_q.empty())
			{
				int x=bfs_q.front().first;
				int y=bfs_q.front().second;
				
				bfs_q.pop();
				if(onboard(x+1,y) && !visited[x+1][y])
				{
					if(east(x,y))
						{
							bfs_q.push(make_pair(x+1,y));
							visited[x+1][y]=true;
							if(y==tar)
							{
								isblock=false;
								break;
							}

						}
				}
				if(onboard(x-1,y) && !visited[x-1][y])
				{
					if(west(x,y))
						{
							bfs_q.push(make_pair(x-1,y));
							visited[x-1][y]=true;
							if(y==tar)
							{
								isblock=false;
								break;
							}
						}
				}
				if(onboard(x,y+1) && !visited[x][y+1])
				{
					if(south(x,y))
					{
						bfs_q.push(make_pair(x,y+1));
						visited[x][y+1]=true;
						if(y+1==tar)
						{
							isblock=false;
							break;
						}

					}
				}
				if(onboard(x,y-1) && !visited[x][y-1])
				{
					if(north(x,y))
					{
						bfs_q.push(make_pair(x,y-1));
						visited[x][y-1]=true;
						if(y-1==tar)
						{
							isblock=false;
							break;
						}
					}
				}

			}
			return isblock;
}



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
			walls[p.y][p.x]=type;
			bool isblock=isNotPath(p1.p.x,p1.p.y,n);
			if(isblock)
			{	
				walls[p.y][p.x]=0;
				return false;
			}
			else
			{
				isblock=isNotPath(p2.p.x,p2.p.y,1);
				walls[p.y][p.x]=0;
				return isblock;
			}

		
	}
	
			


};