#ifndef PLAYER_H
#define PLAYER_H

#include "Maze.h"
using namespace std;
class Player
{
private:
    Maze &maze;
    vector<vector<char>> &grid;
    int x, y;

public:
    Player(Maze &m);
    void play();
};

#endif
