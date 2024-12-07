#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <random>
#include <ctime>

// Use the standard namespace to avoid prefixing with std::
using namespace std;

const int dx[] = {-1, 1, 0, 0}; // Directions: up, down, left, right
const int dy[] = {0, 0, -1, 1};

Maze::Maze(int r, int c) : rows(r), cols(c), rng(mt19937(time(0)))
{
    grid.resize(rows, vector<char>(cols, WALL));
    generateMaze();
}

bool Maze::isValid(int x, int y)
{
    return x > 0 && x < rows - 1 && y > 0 && y < cols - 1;
}

void Maze::generateMaze()
{
    stack<Cell> cellStack;
    cellStack.push({1, 1});
    grid[1][1] = PATH;

    while (!cellStack.empty())
    {
        Cell current = cellStack.top();
        cellStack.pop();

        vector<int> directions = {0, 1, 2, 3};
        shuffle(directions.begin(), directions.end(), rng);

        for (int dir : directions)
        {
            int nx = current.x + dx[dir] * 2;
            int ny = current.y + dy[dir] * 2;

            if (isValid(nx, ny) && grid[nx][ny] == WALL)
            {
                grid[current.x + dx[dir]][current.y + dy[dir]] = PATH;
                grid[nx][ny] = PATH;
                cellStack.push({nx, ny});
            }
        }
    }

    grid[1][1] = START;
    grid[rows - 2][cols - 2] = END;
}

void Maze::display() const
{
    for (const auto &row : grid)
    {
        for (char cell : row)
        {
            cout << cell;
        }
        cout << '\n';
    }
}

bool Maze::solveDFS(int x, int y)
{
    if (grid[x][y] == END)
        return true;

    grid[x][y] = VISITED;

    for (int dir = 0; dir < 4; ++dir)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (isValid(nx, ny) && (grid[nx][ny] == PATH || grid[nx][ny] == END))
        {
            if (solveDFS(nx, ny))
                return true;
        }
    }

    grid[x][y] = PATH;
    return false;
}

vector<vector<char>> &Maze::getGrid()
{
    return grid;
}
