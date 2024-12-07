#include "Player.h"
#include <iostream>
using namespace std;
Player::Player(Maze &m) : maze(m), grid(m.getGrid()), x(1), y(1) {}

void Player::play() {
    char input;
    while (true) {
        maze.display();
        cout << "Use WASD to move: ";
        cin >> input;

        int nx = x, ny = y;
        if (input == 'w') nx--;
        else if (input == 's') nx++;
        else if (input == 'a') ny--;
        else if (input == 'd') ny++;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END) {
            grid[x][y] = PATH; // Reset old position
            x = nx, y = ny;
            grid[x][y] = START; // Update new position

            if (grid[x][y] == END) {
                cout << "You reached the end! Congratulations!\n";
                break;
            }
        }
    }
}
