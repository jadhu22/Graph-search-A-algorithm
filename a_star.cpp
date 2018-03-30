///////////////////////////////////////////
///////Author: Akash Jadhav //////////////
//////////////////////////////////////////
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define row 9
#define col 9

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > Pair_Pair;

struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};

bool exist(int Row, int Col)
{
	return(Row >= 0) && (Row < row) && (Col >= 0) && (Col < col);
}

bool noObstacle(int grid[row][col], int Row, int Col)
{
	if(grid[Row][Col] == 1)
	    return(true);
	else
	    return(false);
}	

bool reachedGoal(int Row, int Col, Pair goal)
{
	if(Row == goal.first && Col == goal.second)
	     return(true);
	else
	     return(false);
}

double calculateHValue(int Row, int Col, Pair goal)
{
	return ((double)sqrt ((Row-goal.first)*(Row-goal.first) + (Col-goal.second)*(Col-goal.second)));
}

void trace_path(cell cellData[row][col], Pair goal)
{
	cout<<"path is";
	int Row = goal.first;
	int Col = goal.second;
	
	stack<Pair> Path;
	while (!(cellData[Row][Col].parent_i == Row && cellData[Row][Col].parent_j == Col ))
	{
		Path.push(make_pair(Row,Col));
		int temp_row = cellData[Row][Col].parent_i;
		int temp_col = cellData[Row][Col].parent_j;
		Row = temp_row;
		Col = temp_col;
	}
	
	Path.push (make_pair (Row, Col));
    	while (!Path.empty())
    	{
        	pair<int,int> p = Path.top();
        	Path.pop();
		cout<<"("<<p.first<<", "<<p.second<<")"<<endl;
    	}
 
    	return;
}

void find_path(int grid[row][col], Pair source, Pair goal)
{
	if(exist(source.first, source.second) == false || exist(goal.first, goal.second) == false)
	{
		cout<<"source or goal block doesn't exist"<<endl;
		return;
	}
	if(noObstacle(grid, source.first, source.second) == false || noObstacle(grid, goal.first, goal.second) == false)
	{
		cout<<"source or goal block is an obstacle"<<endl;
		return;	
	}
	if(reachedGoal(source.first, source.second, goal) == true)
	{
		cout<<"reached destination"<<endl;
		return;
	}	

	bool closedList[row][col];
	memset(closedList, false, sizeof (closedList));

	cell cellData[row][col];
	
	int i, j;

	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
			cellData[i][j].f = FLT_MAX;
			cellData[i][j].g = FLT_MAX;
			cellData[i][j].h = FLT_MAX;
			cellData[i][j].parent_i = -1;
			cellData[i][j].parent_j = -1;
		}
	}
	i = source.first;
	j=source.second;
	cellData[i][j].f = 0.0;
	cellData[i][j].g = 0.0;
	cellData[i][j].h = 0.0;
	cellData[i][j].parent_i = i;
	cellData[i][j].parent_j = j;

	set<Pair_Pair> openList;
	
	openList.insert(make_pair (0.0, make_pair (i,j)));
	
	bool foundGoal = false;

	while(!openList.empty())
	{
		Pair_Pair p = *openList.begin();
		openList.erase(openList.begin());
		
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double fNew, gNew, hNew;

		//top
		if(exist(i-1, j) == true)
		{
			if(reachedGoal(i-1, j, goal) == true)
			{
				cellData[i-1][j].parent_i = i;
				cellData[i-1][j].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i-1][j] == false && noObstacle(grid, i-1, j) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i-1, j , goal);
				fNew = gNew + hNew;

				if(cellData[i-1][j].f == FLT_MAX || cellData[i-1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i-1, j )));
			
					cellData[i-1][j].f = fNew;
					cellData[i-1][j].g = gNew;
					cellData[i-1][j].h = hNew;
					cellData[i-1][j].parent_i = i;
					cellData[i-1][j].parent_j = j;
				}
			}
		}

		//bottom
		if(exist(i+1, j) == true)
		{
			if(reachedGoal(i+1, j, goal) == true)
			{
				cellData[i-1][j].parent_i = i;
				cellData[i-1][j].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i+1][j] == false && noObstacle(grid, i+1, j) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i+1, j , goal);
				fNew = gNew + hNew;

				if(cellData[i+1][j].f == FLT_MAX || cellData[i+1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i+1, j )));
			
					cellData[i+1][j].f = fNew;
					cellData[i+1][j].g = gNew;
					cellData[i+1][j].h = hNew;
					cellData[i+1][j].parent_i = i;
					cellData[i+1][j].parent_j = j;
				}
			}
		}

		//right
		if(exist(i, j+1) == true)
		{
			if(reachedGoal(i, j+1, goal) == true)
			{
				cellData[i][j+1].parent_i = i;
				cellData[i][j+1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i][j+1] == false && noObstacle(grid, i, j+1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i, j+1 , goal);
				fNew = gNew + hNew;

				if(cellData[i][j+1].f == FLT_MAX || cellData[i][j+1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i, j+1 )));
			
					cellData[i][j+1].f = fNew;
					cellData[i][j+1].g = gNew;
					cellData[i][j+1].h = hNew;
					cellData[i][j+1].parent_i = i;
					cellData[i][j+1].parent_j = j;
				}
			}
		}

		//east
		if(exist(i, j-1) == true)
		{
			if(reachedGoal(i, j-1, goal) == true)
			{
				cellData[i][j-1].parent_i = i;
				cellData[i][j-1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i][j-1] == false && noObstacle(grid, i, j-1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i, j-1 , goal);
				fNew = gNew + hNew;

				if(cellData[i][j-1].f == FLT_MAX || cellData[i][j-1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i, j-1 )));
			
					cellData[i][j-1].f = fNew;
					cellData[i][j-1].g = gNew;
					cellData[i][j-1].h = hNew;
					cellData[i][j-1].parent_i = i;
					cellData[i][j-1].parent_j = j;
				}
			}
		}

		//top_right
		if(exist(i-1, j+1) == true)
		{
			if(reachedGoal(i-1, j+1, goal) == true)
			{
				cellData[i-1][j+1].parent_i = i;
				cellData[i-1][j+1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i-1][j+1] == false && noObstacle(grid, i-1, j+1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i-1, j+1 , goal);
				fNew = gNew + hNew;

				if(cellData[i-1][j+1].f == FLT_MAX || cellData[i-1][j+1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i-1, j+1 )));
			
					cellData[i-1][j+1].f = fNew;
					cellData[i-1][j+1].g = gNew;
					cellData[i-1][j+1].h = hNew;
					cellData[i-1][j+1].parent_i = i;
					cellData[i-1][j+1].parent_j = j;
				}
			}
		}

		//top_left
		if(exist(i-1, j-1) == true)
		{
			if(reachedGoal(i-1, j-1, goal) == true)
			{
				cellData[i-1][j-1].parent_i = i;
				cellData[i-1][j-1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i-1][j-1] == false && noObstacle(grid, i-1, j-1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i-1, j-1 , goal);
				fNew = gNew + hNew;

				if(cellData[i-1][j-1].f == FLT_MAX || cellData[i-1][j-1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i-1, j-1 )));
			
					cellData[i-1][j-1].f = fNew;
					cellData[i-1][j-1].g = gNew;
					cellData[i-1][j-1].h = hNew;
					cellData[i-1][j-1].parent_i = i;
					cellData[i-1][j-1].parent_j = j;
				}
			}
		}

		//bottom_right
		if(exist(i+1, j+1) == true)
		{
			if(reachedGoal(i+1, j+1, goal) == true)
			{
				cellData[i+1][j+1].parent_i = i;
				cellData[i+1][j+1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i+1][j+1] == false && noObstacle(grid, i+1, j+1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i+1, j+1 , goal);
				fNew = gNew + hNew;

				if(cellData[i+1][j+1].f == FLT_MAX || cellData[i+1][j+1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i+1, j+1 )));
			
					cellData[i+1][j+1].f = fNew;
					cellData[i+1][j+1].g = gNew;
					cellData[i+1][j+1].h = hNew;
					cellData[i+1][j+1].parent_i = i;
					cellData[i+1][j+1].parent_j = j;
				}
			}
		}

		//bottom_left
		if(exist(i+1, j-1) == true)
		{
			if(reachedGoal(i+1, j-1, goal) == true)
			{
				cellData[i+1][j-1].parent_i = i;
				cellData[i+1][j-1].parent_j = j;
				cout<<"reached goal"<<endl;
				trace_path(cellData, goal);
				foundGoal = true;
				return;
			}
			else if(closedList[i+1][j-1] == false && noObstacle(grid, i+1, j-1) == true)
			{
				gNew = cellData[i][j].g + 1.0;
				hNew = calculateHValue(i+1, j-1 , goal);
				fNew = gNew + hNew;

				if(cellData[i+1][j-1].f == FLT_MAX || cellData[i+1][j-1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i+1, j-1 )));
			
					cellData[i+1][j-1].f = fNew;
					cellData[i+1][j-1].g = gNew;
					cellData[i+1][j-1].h = hNew;
					cellData[i+1][j-1].parent_i = i;
					cellData[i+1][j-1].parent_j = j;
				}
			}
		}
	}
}

int main()
{
	int grid[row][col]={	{1,0,1,1,1,1,0,1,1},
				{1,1,1,0,1,1,1,0,1},
				{1,1,1,0,1,1,0,1,0},
				{0,0,1,0,1,0,0,0,0},
				{1,1,1,0,1,1,1,0,1},
				{1,0,1,1,1,1,0,1,0},
				{1,0,0,0,0,1,0,0,0},
				{1,0,1,1,1,1,0,1,1},
				{1,1,1,0,0,0,1,0,0}
			   };

	Pair source = make_pair(1,6);
	Pair goal = make_pair(5,0);

	find_path(grid,source,goal);
	return(0);
}
