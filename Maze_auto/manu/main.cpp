#include <iostream>
#include "Maze.h"
#include "Player.h"
//g++ main.cpp Maze.cpp Player.cpp -o maze
//./maze
// Use the standard namespace to avoid prefixing with std::
using namespace std;

int main()
{
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    // Display the generated maze before asking for the mode
    cout << "Generated Maze:\n";
    maze.display();

    cout << "Choose mode:\n1. Manual (play with WASD keys)\n2. Automatic (system solves the maze)\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        Player player(maze);
        player.play();
    }
    else if (choice == 2)
    {
        if (maze.solveDFS(1, 1))
        {
            cout << "Maze solved automatically:\n";
            maze.display();
        }
        else
        {
            cout << "No solution found!\n";
        }
    }
    else
    {
        cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}
