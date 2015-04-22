#include "Board.h"

FILE *p;
ofstream fout;
vector<Position> path_cells;
vector< pair<int,Move> > curbestmoves;


void Board::implement_move(Player *p,Move m)
{
	if(m.p.x==0 || m.p.y==0){}
	else if(m.type==0 )
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

bool compare(pair<int,Move> a,pair<int,Move> b )
{
	return a.first<b.first;
}

pair<double,int> Board::maxval(double alpha,double beta,int depth)
{
	if(depth==0)
	{
		// cout<<"my->p.x="<<my->p.x<<" "<<"my->p.y="<<my->p.y<<" "<<"oppo->p.x="<<oppo->p.x<<" "<<"oppo->p.y="<<oppo->p.y<<" "<<"utility = "<<utility()<<endl;
		//cout << "return here "<< endl;
		//if(depth!=0)
		//	cout << "yay"<< endl;
		//fout << "IN MAXVAL IF CASE "<<utility().first <<endl;
		return utility();
	}
	else{
		vector<Move> lis;
		bool wall_considered[311];
		memset(wall_considered,false,sizeof(bool)*311);

		if(my->p.y!=my->target)
			lis=get_move(my->p.x,my->p.y,oppo);

		path_cells.clear();
		// if(((double) rand() / (RAND_MAX))<0.5 ||moves_cnt>15){
		if(my->walls > 0){
			set_parents(oppo->p.x,oppo->p.y,oppo->target);
			// cout<<"PATH_CELLS SIZE="<<path_cells.size()<<endl;

			for (int i = 0; i < path_cells.size(); ++i)
			{
				if(!wall_considered[100+path_cells[i].x*10+path_cells[i].y] && legal_w(Position(path_cells[i].x,path_cells[i].y),1)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),1));
					wall_considered[100+path_cells[i].x*10+path_cells[i].y]=true;
				}
				if(!wall_considered[200+path_cells[i].x*10+path_cells[i].y] && legal_w(Position(path_cells[i].x,path_cells[i].y),2)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),2));
					wall_considered[200+path_cells[i].x*10+path_cells[i].y]=true;
				}



				if(!wall_considered[100+(path_cells[i].x+1)*10+path_cells[i].y] && legal_w(Position(path_cells[i].x+1,path_cells[i].y),1)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),1));
					wall_considered[100+(path_cells[i].x+1)*10+path_cells[i].y]=true;
				}
				if(!wall_considered[200+(path_cells[i].x+1)*10+path_cells[i].y] && legal_w(Position(path_cells[i].x+1,path_cells[i].y),2)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),2));
					wall_considered[200+(path_cells[i].x+1)*10+path_cells[i].y]=true;
				}


				
				if(!wall_considered[100+path_cells[i].x*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x,path_cells[i].y+1),1)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),1));
					wall_considered[100+path_cells[i].x*10+(path_cells[i].y+1)]=true;
				}

				if(!wall_considered[200+path_cells[i].x*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x,path_cells[i].y+1),2)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),2));
					wall_considered[200+path_cells[i].x*10+(path_cells[i].y+1)]=true;
				}
				

				if(!wall_considered[100+(path_cells[i].x+1)*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),1)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),1));
					wall_considered[100+(path_cells[i].x+1)*10+(path_cells[i].y+1)]=true;
				}
				if(!wall_considered[200+(path_cells[i].x+1)*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),2)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),2));
					wall_considered[200+(path_cells[i].x+1)*10+(path_cells[i].y+1)]=true;
				}
			}
		}

		int l=lis.size();
		if(l==0){
			lis.push_back(Move(Position(0,0),0));l++;
		}
		//cout<<"MOVES SIZE="<<l<<endl;
		Position prev=my->p;
		pair<double,int> curbest=make_pair(-10000.0,-1);
		int curbestind=-1;
		//fout << "IN MAXVAL ELSE CASE"<< endl;
		for(int i=0;i<l;i++)
		{
			implement_move(my,lis[i]);
			//fout << "Move under consideration "<< lis[i].type << " y "<<lis[i].p.y<< " x "<< lis[i].p.x<< endl;
			pair<double,int> tmp=minval(alpha,beta,depth-1);

				//fout << "in max !!!!!! "<< tmp.first << endl;
			//fout << lis[i].type << " y "<<lis[i].p.y<< " x "<< lis[i].p.x<< endl;
			if(lis[i].p.x==0 && lis[i].p.y==0 && lis[i].type==0 ){
				//fout << "inc tmp"<<endl;
				tmp.first++;
			}
			//fout << "COST OF MOVE "<< tmp.first << " in "<<  lis[i].type << " y "<<lis[i].p.y<< " x "<< lis[i].p.x<< endl;
			//fout << endl;
			if(lis[i].type==0 && depth==DEPTH){
				 //fout<<"\t"<<lis[i].p.y<<" "<<lis[i].p.x<<" "<<tmp.first<<endl;
			}
			if(curbest.first==tmp.first && depth==DEPTH){
				//int tp=bfs(my->p.x,my->p.y,my->target);
				curbestmoves.push_back(make_pair(tmp.second,lis[i]));
			}
			else if(curbest.first<tmp.first)
			{	
				curbest=tmp;
				if(depth==DEPTH)
					{
						curbestmoves.clear();
						//int tp=bfs(my->p.x,my->p.y,my->target);
						curbestmoves.push_back(make_pair(tmp.second,lis[i]));
					}
			}
			// curbest=max(curbest,tmp.first);
			// if(curbest==tmp.first)
			// 	curbestind=i;
			alpha=max(alpha,tmp.first);
			if(lis[i].p.x==0 && lis[i].p.y==0 && lis[i].type==0){}
			else if(lis[i].type==0 )
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
			//curbestind=rand()%(curbestmoves.size());
			sort(curbestmoves.begin(),curbestmoves.end(),compare);
			int count=1;
			int best_d=curbestmoves[0].first;
			while(count<curbestmoves.size() && curbestmoves[count].first==best_d)
				count++;
			curbestind=rand()%count;
			move[0]=curbestmoves[curbestind].second.type;
			move[1]=curbestmoves[curbestind].second.p.y;
			move[2]=curbestmoves[curbestind].second.p.x;	
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


pair<double,int> Board::f1()
{	
	int ret1 = bfs(my->p.x,my->p.y,my->target);
	int ret2 = bfs(oppo->p.x,oppo->p.y,oppo->target);
	// return 10/(ret2+1)-5/(ret1+1)+(my->walls-oppo->walls);
	// return -2*ret1+my->walls;
	return make_pair((1.1*ret2*ret2-ret1*ret1),ret1);
		//-100/((ret2+1)*(ret2+1))+100/((ret1+1)*(ret1+1))),ret1);
}

pair<double,int> Board::utility()
{
	return f1();
}

pair<double,int> Board::minval(double alpha,double beta,int depth)
{
	if(depth==0 )
	{
		////cout << "should not return here "<< depth<<endl;
		// if(depth!=0)
		// 	//cout << "yay"<< endl;
	
		return utility();
	}
	else{
		vector<Move> lis;
		bool wall_considered[311];
		memset(wall_considered,false,sizeof(bool)*311);

		if(oppo->target!=oppo->p.y)
			lis=get_move(oppo->p.x,oppo->p.y,my);
		//set parent vector
	

		path_cells.clear();
		// if(((double) rand() / (RAND_MAX))<0.5 || moves_cnt>15){
		if(oppo->walls > 0){
			set_parents(my->p.x,my->p.y,my->target);
			// cout<<"PATH_CELLS SIZE="<<path_cells.size()<<endl;

			for (int i = 0; i < path_cells.size(); ++i)
			{
				if(!wall_considered[100+path_cells[i].x*10+path_cells[i].y] && legal_w(Position(path_cells[i].x,path_cells[i].y),1)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),1));
					wall_considered[100+path_cells[i].x*10+path_cells[i].y]=true;
				}
				if(!wall_considered[200+path_cells[i].x*10+path_cells[i].y] && legal_w(Position(path_cells[i].x,path_cells[i].y),2)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y),2));
					wall_considered[200+path_cells[i].x*10+path_cells[i].y]=true;
				}



				if(!wall_considered[100+(path_cells[i].x+1)*10+path_cells[i].y] && legal_w(Position(path_cells[i].x+1,path_cells[i].y),1)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),1));
					wall_considered[100+(path_cells[i].x+1)*10+path_cells[i].y]=true;
				}
				if(!wall_considered[200+(path_cells[i].x+1)*10+path_cells[i].y] && legal_w(Position(path_cells[i].x+1,path_cells[i].y),2)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y),2));
					wall_considered[200+(path_cells[i].x+1)*10+path_cells[i].y]=true;
				}


				
				if(!wall_considered[100+path_cells[i].x*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x,path_cells[i].y+1),1)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),1));
					wall_considered[100+path_cells[i].x*10+(path_cells[i].y+1)]=true;
				}

				if(!wall_considered[200+path_cells[i].x*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x,path_cells[i].y+1),2)){
					lis.push_back(Move(Position(path_cells[i].x,path_cells[i].y+1),2));
					wall_considered[200+path_cells[i].x*10+(path_cells[i].y+1)]=true;
				}
				

				if(!wall_considered[100+(path_cells[i].x+1)*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),1)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),1));
					wall_considered[100+(path_cells[i].x+1)*10+(path_cells[i].y+1)]=true;
				}
				if(!wall_considered[200+(path_cells[i].x+1)*10+(path_cells[i].y+1)] && legal_w(Position(path_cells[i].x+1,path_cells[i].y+1),2)){
					lis.push_back(Move(Position(path_cells[i].x+1,path_cells[i].y+1),2));
					wall_considered[200+(path_cells[i].x+1)*10+(path_cells[i].y+1)]=true;
				}
			}
		}
		int l=lis.size();
		if(l==0){
			lis.push_back(Move(Position(0,0),0));l++;
		}
		// cout<<"MOVES SIZE="<<l<<endl;
		Position prev=oppo->p;
		pair<double,int> curbest=make_pair(10000,-1);
		for(int i=0;i<l;i++)
		{
			implement_move(oppo,lis[i]);
			//fout << "Move under consideration "<< lis[i].type << " y "<<lis[i].p.y<< " x "<< lis[i].p.x<< endl;
			pair<double,int> tmp=maxval(alpha,beta,depth-1);
			// if(lis[i].p.x==0 && lis[i].p.y==0 && lis[i].type==0){
			// 	tmp.first-=1000;
			// }
			//fout << "COST OF MOVE "<< tmp.first <<" in "<< lis[i].type << " y "<<lis[i].p.y<< " x "<< lis[i].p.x<< endl;
			//fout << endl;
			if(curbest.first>tmp.first)
				curbest=tmp;
			beta=min(beta,tmp.first);
			if(lis[i].p.x==0 && lis[i].p.y==0){}
			else if(lis[i].type==0 )
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
	stringstream ss;
	if(my->target==1)
		ss<<"2/"<<moves_cnt;
	else
		ss<<"1/"<<moves_cnt;
	//p=fopen(ss.str().c_str(),'w');
	//fout.open(ss.str().c_str());
	curbestmoves.clear();
	maxval(-100000000,100000000,DEPTH);
	//fclose(p);
	//fout.close();
	if(move[2]==0 || move[1]==0){}
	else if(move[0]==0)
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

vector<Move> Board::get_move(int x,int y,Player * opponent)
{
		//cout << "gots x  "<< x <<" "<<y << endl; 
		vector<Move> lis;
		if(onboard(x+1,y) )
		{
			if(east(x,y))
				{
					
					if(opponent->p.x==x+1 && opponent->p.y==y && opponent->p.y!=opponent->target)
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
					if(opponent->p.x==x-1 && opponent->p.y==y && opponent->p.y!=opponent->target)
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
		if(onboard(x,y-1))
		{
			if(north(x,y))
				{
					if(opponent->p.x==x && opponent->p.y==y-1 && opponent->p.y!=opponent->target)
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
		if(onboard(x,y+1))
		{
			if(south(x,y))
				{
					if(opponent->p.x==x && opponent->p.y==y+1 && opponent->p.y!=opponent->target)
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
		int p=lis.size();
		// cout << "first "<< endl;
		for(int j=0;j<p;j++)
		{
			// cout << lis[j].type<<" "<< lis[j].p.y<< " "<< lis[j].p.x<< endl;
		}
		return lis;
}

