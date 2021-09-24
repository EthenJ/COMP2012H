#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

void readMap(string filename, int map[][WIDTH])
{
    // the map is 9 cells wide and 81 cells high, but only the bottom 9 rows cells are active.
    // The candies in the higher rows will "drop down" when candies in the "active area" are matched and removed
    ifstream file;
    file.open("map.txt");
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            file >> map[i][j];
        }
    }
}

// for debug
void printIntMap(int map[][WIDTH])
{
    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

void printMap(int map[][WIDTH])
{
    // only the bottom 9 rows of the map are printed
    // rows\cols 0 1 2 3 4 5 6 7 8
    // 8         ...
    // 7         ...
    // ...
    // 0         ...

    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << tile[map[i][j]] << ' ';
        }
        cout << endl;
    }
}

void printMatches(bool matches[HEIGHT][WIDTH])
{
    // prints the positions of all matching candies
    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << matches[i][j] << ' ';
        }
        cout << endl;
    }
}

bool inBounds(int y, int x)
{
    // check if the input coordinates are out of the active 9x9 grid
    if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
    {
        return false;
    }
    return true;
}

/***********************************************************************
 * TODO 1: Find all tiles that are matched with other tiles of the same
 * type in a group of 3 horizontally or vertically
 ***********************************************************************/
int findMatches(int map[][WIDTH], bool matches[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++) // Initialization
    {
        for (int j = 0; j < WIDTH; j++)
        {
            matches[i][j] = false;
        }
    }

    int row = 0, col = 0, head, tail, difference;

    while (row < HEIGHT) // down => up
    {
        head = 0, tail = 1, difference = 0;
        while (tail < WIDTH) // left => right
        {
            if ((map[row][head] == map[row][tail]) && (map[row][head] != 0))
            {
                difference = head - tail++;
            }
            else
            {
                head = tail++;
                difference = 0;
            }

            if (difference >= 3)
            {
                for (int i = 0; i < difference; i++)
                {
                    matches[row][head + i] = true;
                }
            }
        }
        row++;
    }

    while (col < WIDTH) // left => right
    {
        head = 0, tail = 1, difference = 0;
        while (tail < HEIGHT) // down => up
        {
            if ((map[head][col] == map[tail][col]) && (map[head][col] != 0))
            {
                difference = head - tail++;
            }
            else
            {
                head = tail++;
                difference = 0;
            }

            if (difference >= 3)
            {
                for (int i = 0; i < difference; i++)
                {
                    matches[head + i][col] = true;
                }
            }
        }
        col++;
    }

    return 0;
}

/***********************************************************************
 * TODO 2: Remove all tiles that are matched with 3 others of the same
 * type horizontally or vertically, and update the game grid accordingly
 ***********************************************************************/
int processMatches(int map[][WIDTH])
{
    bool matches[HEIGHT][WIDTH] = {};
    findMatches(map, matches);
    int score_increased = 0;

    for (int row = HEIGHT - 1; row >= 0; row--) // up => down
    {
        for (int col = 0; col < WIDTH; col++) // left => right
        {
            if (matches[row][col] == true)
            {
                for (int i = row; i < MAX_ROWS - 1; i++)
                {
                    map[i][col] = map[i + 1][col];
                }
                map[MAX_ROWS][col] = 0;
                score_increased++;
            }
        }
    }

    if (score_increased)
    {
        score_increased += processMatches(map); // Recursion
    }

    return score_increased;
}

/***********************************************************************
 * TODO 3: Swap the tiles at the specified locations
 ***********************************************************************/
void swapTiles(int map[][WIDTH], int x1, int y1, int x2, int y2)
{
    map[x1][y1] = map[x1][y1] ^ map[x2][y2];
    map[x2][y2] = map[x1][y1] ^ map[x2][y2];
    map[x1][y1] = map[x2][y2] ^ map[x1][y1];
}

// copy the contents of the first rows_to_copy rows of map to map_copy
void copyMap(int map[][WIDTH], int map_copy[][WIDTH], int rows_to_copy)
{
    for (int i = 0; i < rows_to_copy; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map_copy[i][j] = map[i][j];
        }
    }
}

/***********************************************************************
 * TODO 4: Consider and calculate the score gain for each possible move
 ***********************************************************************/
int considerMoves(int map[][WIDTH], int candidate_moves[][4], int &num_candidate_moves)
{
    int max_score_gained = 0;

    for (int row = 0; row < HEIGHT; row++) // down => up
    {
        for (int col = 0; col < WIDTH - 1; col++) // left => right
        {
            int map_copy[HEIGHT][WIDTH];
            bool matches[HEIGHT][WIDTH] = {};
            int score_gained = 0;
            copyMap(map, map_copy, HEIGHT);
            swapTiles(map_copy, row, col, row, col + 1);
            score_gained = processMatches(map_copy);

            if (score_gained)
            {
                candidate_moves[num_candidate_moves++, row, col, row, col + 1];
            }

            if (score_gained > max_score_gained)
            {
                max_score_gained = score_gained;
            }
        }
    }

    for (int col = 0; col < WIDTH; col++) // left => right
    {
        for (int row = 0; row < HEIGHT - 1; row++) // down => up
        {
            int map_copy[HEIGHT][WIDTH];
            bool matches[HEIGHT][WIDTH] = {};
            int score_gained = 0;
            copyMap(map, map_copy, HEIGHT);
            swapTiles(map_copy, row, col, row + 1, col);
            score_gained = processMatches(map_copy);

            if (score_gained)
            {
                candidate_moves[num_candidate_moves++, row, col, row + 1, col];
            }

            if (score_gained > max_score_gained)
            {
                max_score_gained = score_gained;
            }
        }
    }

    return max_score_gained;
}

/***********************************************************************
 * TODO 5: Implement the solver
 ***********************************************************************/
int solver(int map[][WIDTH], int return_coordinates[4])
{

    return 0;
}

// overloaded solver() used when returning the optimal move is not required
int solver(int map[][WIDTH])
{
    int dummy[4];
    return solver(map, dummy);
}
