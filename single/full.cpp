#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <ctime>
#include <algorithm>

// Constants for the maze
#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'
#define VISITED '.'

// Directions for moving in the maze (up, down, left, right)
const int dx[] = {-1, 1, 0, 0}; 
const int dy[] = {0, 0, -1, 1};

// Cell structure to store coordinates
struct Cell
{
    int x, y;
};

// Maze class definition
class Maze
{
private:
    int rows, cols;                      // Maze dimensions
    std::vector<std::vector<char>> grid;  // Maze grid
    std::mt19937 rng;                    // Random number generator

    bool isValid(int x, int y);           // Check if a cell is valid

public:
    Maze(int r, int c);                   // Constructor
    void generateMaze();                  // Maze generation logic
    void display() const;                 // Display the maze
    bool solveDFS(int x, int y);          // Solve the maze using DFS
    std::vector<std::vector<char>>& getGrid(); // Access the grid
};

// Maze constructor
Maze::Maze(int r, int c) : rows(r), cols(c), rng(std::mt19937(std::time(0)))
{
    grid.resize(rows, std::vector<char>(cols, WALL)); // Initialize maze with walls
    generateMaze();  // Generate the maze
}

// Check if a cell is within bounds and is not a wall
bool Maze::isValid(int x, int y)
{
    return x > 0 && x < rows - 1 && y > 0 && y < cols - 1;
}

// Generate the maze using depth-first search (DFS)
void Maze::generateMaze()
{
    std::stack<Cell> cellStack;
    cellStack.push({1, 1});
    grid[1][1] = PATH;  // Mark starting point as path

    while (!cellStack.empty())
    {
        Cell current = cellStack.top();
        cellStack.pop();

        std::vector<int> directions = {0, 1, 2, 3};  // Directions: up, down, left, right
        std::shuffle(directions.begin(), directions.end(), rng);  // Shuffle directions for randomness

        for (int dir : directions)
        {
            int nx = current.x + dx[dir] * 2;
            int ny = current.y + dy[dir] * 2;

            // If the new cell is within bounds and is a wall, carve a path
            if (isValid(nx, ny) && grid[nx][ny] == WALL)
            {
                grid[current.x + dx[dir]][current.y + dy[dir]] = PATH;
                grid[nx][ny] = PATH;
                cellStack.push({nx, ny});  // Push the new cell onto the stack
            }
        }
    }

    grid[1][1] = START;  // Set start point
    grid[rows - 2][cols - 2] = END;  // Set end point
}

// Display the maze, clearing the screen first
void Maze::display() const
{
    // Clear the console screen before displaying the maze
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Unix-based systems
    #endif

    // Display the maze
    for (const auto& row : grid)
    {
        for (char cell : row)
        {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

// Solve the maze using DFS
bool Maze::solveDFS(int x, int y)
{
    if (grid[x][y] == END)
        return true;

    grid[x][y] = VISITED;  // Mark the current cell as visited

    // Try all four directions (up, down, left, right)
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

    grid[x][y] = PATH;  // Backtrack by resetting the current cell
    return false;
}

// Access the grid
std::vector<std::vector<char>>& Maze::getGrid()
{
    return grid;
}

// Player class definition for manual control
class Player
{
private:
    Maze& maze;                  // Reference to the maze
    std::vector<std::vector<char>>& grid;  // Reference to the grid in the maze
    int x, y;                    // Current position of the player

public:
    Player(Maze& m);             // Constructor
    void play();                 // Method to handle player movement and game logic
};

// Player constructor
Player::Player(Maze& m) : maze(m), grid(m.getGrid()), x(1), y(1) {}

void Player::play()
{
    char input;
    while (true)
    {
        maze.display();  // Display the current maze state
        std::cout << "Use WASD to move: ";
        std::cin >> input;

        int nx = x, ny = y;
        if (input == 'w') nx--;
        else if (input == 's') nx++;
        else if (input == 'a') ny--;
        else if (input == 'd') ny++;

        // Check if the move is valid (either on a path or the end)
        if (grid[nx][ny] == PATH || grid[nx][ny] == END)
        {
            grid[x][y] = PATH;  // Reset old position
            x = nx, y = ny;
            grid[x][y] = START;  // Update new position

            if (grid[x][y] == END)  // If the player reaches the end
            {
                std::cout << "You reached the end! Congratulations!\n";
                break;
            }
        }
    }
}

// Main function that ties everything together
int main()
{
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    // Display the generated maze before asking for the mode
    std::cout << "Generated Maze:\n";
    maze.display();

    std::cout << "Choose mode:\n1. Manual (play with WASD keys)\n2. Automatic (system solves the maze)\n";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        Player player(maze);
        player.play();
    }
    else if (choice == 2)
    {
        if (maze.solveDFS(1, 1))
        {
            std::cout << "Maze solved automatically:\n";
            maze.display();
        }
        else
        {
            std::cout << "No solution found!\n";
        }
    }
    else
    {
        std::cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}

