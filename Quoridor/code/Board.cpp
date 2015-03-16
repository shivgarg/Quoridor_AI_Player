#include "Board.h"



void Board::implement_move(Player *p,Move m)
{
	if(m.type==0)
	{
		p->p.x=m.p.x;
		p->p.y=m.p.y;
	}
	else 
	{
		walls[m.p.y][m.p.x]=m.type;
		p->walls--;
	}
}

int Board::maxval(int alpha,int beta,int depth)
{
	if(depth==0 || my->p.y==my_target)
	{
		return utility();
	}
	else{
		vector<Move> lis=get_move(my->p.x,my->p.y);
		if(my->walls>0){
			for(int i=2;i<=m;i++)
				for(int j=2;j<=n;j++)
				{
					if(legal_w(Position(i,j),1))
						lis.push_back(Move(Position(i,j),1));
					if(legal_w(Position(i,j),2))
						lis.push_back(Move(Position(i,j),2));
				}
		}
		int l=lis.size();
		Position prev=my->p;
		int curbest=-10000;
		int curbestind=-1;
		for(int i=0;i<l;i++)
		{
			implement_move(my,lis[i]);
			int tmp=minval(alpha,beta,depth-1);
			curbest=max(curbest,tmp);
			if(curbest==tmp)
				curbestind=i;
			alpha=max(alpha,tmp);
			if(lis[i].type==0)
				implement_move(my,Move(prev,0));
			else
			{
				walls[lis[i].p.y][lis[i].p.x]=0;
				my->walls++;
			}
			if(alpha>=beta)
			{
				move[0]=lis[i].type;
				move[1]=lis[i].p.y;
				move[2]=lis[i].p.x;
				return tmp;
			}
		}
		move[0]=lis[curbestind].type;
		move[1]=lis[curbestind].p.y;
		move[2]=lis[curbestind].p.x;
		return curbest;
	}

}


int Board::utility()
{
	return 1;
}

int Board::minval(int alpha,int beta,int depth)
{
	if(depth==0 || oppo->p.y==oppo_target)
	{
		return utility();
	}
	else{
		vector<Move> lis=get_move(oppo->p.x,oppo->p.y);
		if(oppo->walls>0){
			for(int i=2;i<=m;i++)
				for(int j=2;j<=n;j++)
				{
					if(legal_w(Position(i,j),1))
						lis.push_back(Move(Position(i,j),1));
					if(legal_w(Position(i,j),2))
						lis.push_back(Move(Position(i,j),2));
				}
		}
		int l=lis.size();
		Position prev=oppo->p;
		int curbest=-10000;
		for(int i=0;i<l;i++)
		{
			implement_move(oppo,lis[i]);
			int tmp=maxval(alpha,beta,depth-1);
			curbest=min(curbest,tmp);
			beta=min(beta,tmp);
			if(lis[i].type==0)
				implement_move(oppo,Move(prev,0));
			else
			{
				walls[lis[i].p.y][lis[i].p.x]=0;
				oppo->walls++;
			}
			if(alpha>=beta)
				return tmp;
		}
		return curbest;
	}

}


void Board::set_move()
{
	maxval(-100000000,100000000,1);
	if(move[0]==0)
	{
		my->p.x=move[2];
		my->p.y=move[1];
	}
	else
	{
		walls[move[1]][move[2]]=move[0];
		my->walls--;
	}

}

vector<Move> Board::get_move(int x,int y)
{
		//cout << "gots x  "<< x <<" "<<y << endl; 
		vector<Move> lis;
		if(onboard(x+1,y) )
		{
			if(east(x,y))
				{
					if(oppo->p.x==x+1 && oppo->p.y==y)
					{
						if(onboard(x+2,y))
						{
							if(east(x+1,y))
								lis.push_back(Move(Position(x+2,y),0));
							else
							{
								if(onboard(x+1,y+1))
								{
									if(south(x+1,y))
										lis.push_back(Move(Position(x+1,y+1),0));

								}
								if(onboard(x+1,y-1))
								{
									if(north(x+1,y))
										lis.push_back(Move(Position(x+1,y-1),0));
								}
							}
						}
						else
						{
							if(onboard(x+1,y+1))
								{
									if(south(x+1,y))
										lis.push_back(Move(Position(x+1,y+1),0));

								}
								if(onboard(x+1,y-1))
								{
									if(north(x+1,y))
										lis.push_back(Move(Position(x+1,y-1),0));
								}
						}
					}
					else
					{
						lis.push_back(Move(Position(x+1,y),0));
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
								lis.push_back(Move(Position(x-2,y),0));
							}
							else
							{
								if(onboard(x-1,y+1))
								{
									if(south(x-1,y))
										lis.push_back(Move(Position(x-1,y+1),0));
								}
								if(onboard(x-1,y-1))
								{
									if(north(x-1,y))
										lis.push_back(Move(Position(x-1,y-1),0));
								}
							}
						}
						else
						{
							if(onboard(x-1,y+1))
								{
									if(south(x-1,y))
										lis.push_back(Move(Position(x-1,y+1),0));
								}
								if(onboard(x-1,y-1))
								{
									if(north(x-1,y))
										lis.push_back(Move(Position(x-1,y-1),0));
								}
						}
					}
					else
						lis.push_back(Move(Position(x-1,y),0));
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
								lis.push_back(Move(Position(x,y+2),0));
							}
							else
							{
								if(onboard(x-1,y+1))
								{
									if(west(x,y+1))
										lis.push_back(Move(Position(x-1,y+1),0));
								}
								if(onboard(x+1,y+1))
								{
									if(east(x,y+1))
										lis.push_back(Move(Position(x+1,y+1),0));
								}
							}
						}
						else
						{
							if(onboard(x-1,y+1))
								{
									if(west(x,y+1))
										lis.push_back(Move(Position(x-1,y+1),0));
								}
								if(onboard(x+1,y+1))
								{
									if(east(x,y+1))
										lis.push_back(Move(Position(x+1,y+1),0));
								}
						}
					}
					else
						lis.push_back(Move(Position(x,y+1),0));
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
								lis.push_back(Move(Position(x,y-2),0));
							}
							else
							{
								if(onboard(x-1,y-1))
								{
									if(west(x,y-1))
										lis.push_back(Move(Position(x-1,y-1),0));
								}
								if(onboard(x+1,y-1))
								{
									if(east(x,y-1))
										lis.push_back(Move(Position(x+1,y-1),0));
								}
							}
						}
						else
						{
							if(onboard(x-1,y-1))
								{
									if(west(x,y-1))
										lis.push_back(Move(Position(x-1,y-1),0));
								}
								if(onboard(x+1,y-1))
								{
									if(east(x,y-1))
										lis.push_back(Move(Position(x+1,y-1),0));
								}
						}
					}
					else
						lis.push_back(Move(Position(x,y-1),0));
				}
		}
		int p=lis.size();
		cout << "first "<< endl;
		for(int j=0;j<p;j++)
		{
			cout << lis[j].type<<" "<< lis[j].p.y<< " "<< lis[j].p.x<< endl;
		}
		return lis;
}

