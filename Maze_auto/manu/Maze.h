#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <random>
#include <ctime>

#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'
#define VISITED '.'
using namespace std;
// 1. Define the Cell structure before the Maze class
struct Cell
{
    int x, y;
};

class Maze
{
private:
    int rows, cols;
    vector<vector<char>> grid;
    mt19937 rng;

    bool isValid(int x, int y);

public:
    Maze(int r, int c);
    void generateMaze();
    void display() const;
    bool solveDFS(int x, int y);
    std::vector<std::vector<char>> &getGrid();
};

#endif
