#ifndef MAZE_H
#define MAZE_H

#include<stdlib.h>

class map
{
public:
    map();
    void all_to_0();
    void set_to_1(int x,int y);
    void set_to_0(int x,int y);
    void set_to_n1(int x,int y);
    void set_to_n2(int x,int y);
    int get_value(int x,int y);
private:
    int maze[20][20];
};

#endif // MAZE_H
