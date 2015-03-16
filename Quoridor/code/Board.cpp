#include "Board.h"

vector<Position> path_cells;
vector<Move> curbestmoves;
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
		// cout<<"my->p.x="<<my->p.x<<" "<<"my->p.y="<<my->p.y<<" "<<"oppo->p.x="<<oppo->p.x<<" "<<"oppo->p.y="<<oppo->p.y<<" "<<"utility = "<<utility()<<endl;
		return utility();
	}
	else{
		vector<Move> lis=get_move(my->p.x,my->p.y);

		path_cells.clear();
		if(((double) rand() / (RAND_MAX))<0.5 ||moves_cnt>15){
		if(my->walls > 0){
			set_parents(oppo->p.x,oppo->p.y,oppo_target);
			// cout<<"PATH_CELLS SIZE="<<path_cells.size()<<endl;

			for (int i = 0; i < path_cells.size(); ++i)
			{
				if(legal_w(Position(path_cells[i].x,path_cells[i].y),1))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),1));
				if(legal_w(Position(path_cells[i].x,path_cells[i].y),2))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),2));

				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y),1))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),1));
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y),2))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),2));
				
				if(legal_w(Position(path_cells[i].x,path_cells[i].y+1),1))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),1));
				if(legal_w(Position(path_cells[i].x,path_cells[i].y+1),2))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),2));
				
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),1))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),1));
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),2))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),2));
			}
		}
}
		int l=lis.size();

		// cout<<"MOVES SIZE="<<l<<endl;
		Position prev=my->p;
		int curbest=-10000;
		int curbestind=-1;

		for(int i=0;i<l;i++)
		{
			implement_move(my,lis[i]);
			int tmp=minval(alpha,beta,depth-1);
			if(lis[i].type==0 && depth==DEPTH){
				// cout<<"\t"<<lis[i].p.y<<" "<<lis[i].p.x<<" "<<tmp<<endl;
			}
			if(curbest==tmp && depth==DEPTH)
				curbestmoves.push_back(lis[i]);
			else if(curbest<tmp)
			{	
				curbest=tmp;
				if(depth==DEPTH)
					{
						curbestmoves.clear();
						curbestmoves.push_back(lis[i]);
					}
			}
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
		if(depth==DEPTH)
		{
			// cout << "SIZE SIZE "<< curbestmoves.size()<< endl;
			curbestind=rand()%(curbestmoves.size());

			move[0]=curbestmoves[curbestind].type;
			move[1]=curbestmoves[curbestind].p.y;
			move[2]=curbestmoves[curbestind].p.x;	
		}
		
		return curbest;
	}

}



int Board::bfs(int x1,int y1,int tar)
{
	//cout<<"In bfs : x1="<<x1<<" y1="<<y1<<" tar="<<tar<<endl;
			int visited[m+1][n+1];
			for(int i=0;i<m+1;i++)
				for(int j=0;j<n+1;j++)
					visited[i][j]=INF;
			visited[x1][y1]=0;
			queue< pair<int,int> > bfs_q;
			bfs_q.push(make_pair(x1,y1));
			if(y1==tar)
				return 0;
			while(!bfs_q.empty())
			{
				int x=bfs_q.front().first;
				int y=bfs_q.front().second;
				
				bfs_q.pop();
				if(onboard(x+1,y) && visited[x+1][y]==INF)
				{
					if(east(x,y))
						{
							bfs_q.push(make_pair(x+1,y));
							visited[x+1][y]=visited[x][y]+1;
							if(y==tar)
							{
								return visited[x+1][y];
							}

						}
				}
				if(onboard(x-1,y) && visited[x-1][y]==INF)
				{
					if(west(x,y))
						{
							bfs_q.push(make_pair(x-1,y));
							visited[x-1][y]=visited[x][y]+1;
							if(y==tar)
							{
								return visited[x][y]+1;
							}
						}
				}
				if(onboard(x,y+1) && visited[x][y+1]==INF)
				{
					if(south(x,y))
					{
						bfs_q.push(make_pair(x,y+1));
						visited[x][y+1]=visited[x][y]+1;
						if(y+1==tar)
						{
							return visited[x][y]+1;
						}

					}
				}
				if(onboard(x,y-1) && visited[x][y-1]==INF)
				{
					if(north(x,y))
					{
						bfs_q.push(make_pair(x,y-1));
						visited[x][y-1]=visited[x][y]+1;
						if(y-1==tar)
						{
							return visited[x][y]+1;
						}
					}
				}

			}
		return INF;
}


void Board::set_parents(int x1,int y1,int tar)
{
			// cout<<"In set_parents : x1="<<x1<<" y1="<<y1<<" tar="<<tar<<endl;
			bool visited[m+1][n+1];
			Position parents[m+1][n+1];
			for(int i=0;i<m+1;i++)
				for(int j=0;j<n+1;j++)
					visited[i][j]=false;
			visited[x1][y1]=true;
			queue< pair<int,int> > bfs_q;
			bfs_q.push(make_pair(x1,y1));
			if(y1==tar)
				return;
			while(!bfs_q.empty())
			{
				int x=bfs_q.front().first;
				int y=bfs_q.front().second;
				
				bfs_q.pop();
				if(onboard(x+1,y) && visited[x+1][y]==false)
				{

					if(east(x,y))
						{

							bfs_q.push(make_pair(x+1,y));
							visited[x+1][y]=true;
							parents[x+1][y]=Position(x,y);

							if(y==tar)
							{
								int i,j;
								i=x+1;
								j=y;
								while(i!=x1 || j!=y1){
									path_cells.push_back(Position(i,j));
									Position tmp=parents[i][j];
									i=tmp.x;
									j=tmp.y;
								}
								return;
							}

						}
				}
				if(onboard(x-1,y) && visited[x-1][y]==false)
				{
					if(west(x,y))
						{
							bfs_q.push(make_pair(x-1,y));
							visited[x-1][y]=true;
							parents[x-1][y]=Position(x,y);
							if(y==tar)
							{
								int i,j;
								i=x-1;
								j=y;
								while(i!=x1 || j!=y1){
									path_cells.push_back(Position(i,j));
									Position tmp=parents[i][j];
									i=tmp.x;
									j=tmp.y;
								}
								return;
							}
						}
				}
				if(onboard(x,y+1) && visited[x][y+1]==false)
				{
					if(south(x,y))
					{
						bfs_q.push(make_pair(x,y+1));
						visited[x][y+1]=true;
						parents[x][y+1]=Position(x,y);
						if(y+1==tar)
						{

							int i,j;
							i=x;
							j=y+1;
							while(i!=x1 || j!=y1){								
								path_cells.push_back(Position(i,j));
								Position tmp=parents[i][j];
								i=tmp.x;
								j=tmp.y;

							}
							return;
						}
					}
				}
				if(onboard(x,y-1) && visited[x][y-1]==false)
				{
					if(north(x,y))
					{
						bfs_q.push(make_pair(x,y-1));
						visited[x][y-1]=true;
						parents[x][y-1]=Position(x,y);
						if(y-1==tar)
						{	
							int i,j;
							i=x;
							j=y-1;
							while(i!=x1 || j!=y1){
								path_cells.push_back(Position(i,j));
								Position tmp=parents[i][j];
								i=tmp.x;
								j=tmp.y;
							}
							return;
						}
					}
				}

			}
		return;
}


int Board::f1()
{	
	int ret1 = bfs(my->p.x,my->p.y,my_target);
	int ret2 = bfs(oppo->p.x,oppo->p.y,oppo_target);
	//cout<<"RET1 = "<<ret1<<"   RET2 = "<<ret2<<endl;
	// return 10/(ret2+1)-5/(ret1+1)+(my->walls-oppo->walls);
	// return -2*ret1+my->walls;
	return ret2-ret1;
}

int Board::utility()
{
	return f1();
}

int Board::minval(int alpha,int beta,int depth)
{
	if(depth==0 || oppo->p.y==oppo_target)
	{
		return utility();
	}
	else{
		vector<Move> lis=get_move(oppo->p.x,oppo->p.y);
		//set parent vector

		path_cells.clear();
		if(((double) rand() / (RAND_MAX))<0.1 || moves_cnt>20){
		if(oppo->walls > 0){
			set_parents(my->p.x,my->p.y,my_target);
			// cout<<"PATH_CELLS SIZE="<<path_cells.size()<<endl;

			for (int i = 0; i < path_cells.size(); ++i)
			{
				if(legal_w(Position(path_cells[i].x,path_cells[i].y),1))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),1));
				if(legal_w(Position(path_cells[i].x,path_cells[i].y),2))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),2));

				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y),1))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),1));
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y),2))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),2));
				
				if(legal_w(Position(path_cells[i].x,path_cells[i].y+1),1))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),1));
				if(legal_w(Position(path_cells[i].x,path_cells[i].y+1),2))
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),2));
				
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),1))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),1));
				if(legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),2))
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),2));
			}
		}}
		int l=lis.size();
		// cout<<"MOVES SIZE="<<l<<endl;
		Position prev=oppo->p;
		int curbest=10000;
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
	moves_cnt++;
	maxval(-100000000,100000000,DEPTH);
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
		// cout << "first "<< endl;
		for(int j=0;j<p;j++)
		{
			// cout << lis[j].type<<" "<< lis[j].p.y<< " "<< lis[j].p.x<< endl;
		}
		return lis;
}

