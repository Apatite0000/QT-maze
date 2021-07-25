#include "map.h"

map::map()
{
    for(int i=0;i!=20;i++)
        for(int j=0;j!=20;j++)
            maze[i][j] = 0;
}
void map::all_to_0()
{
    for(int i=0;i!=20;i++)
        for(int j=0;j!=20;j++)
        {
            maze[i][j] = 0;
            int n1 = rand()%10;
            if(n1 == 1) maze[i][j] = -1;
            if(n1 == 2) maze[i][j] = -2;
        }
}

void map::set_to_1(int x,int y)
{
    maze[x][y] = 1;
}

void map::set_to_0(int x,int y)
{
    maze[x][y] = 0;
}

void map::set_to_n1(int x,int y)
{
    maze[x][y] = -1;
}

void map::set_to_n2(int x,int y)
{
    maze[x][y] = -2;
}

int map::get_value(int x,int y)
{
    return maze[x][y];
}
