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

    int y = 0, x = 0, matched_cells = 0, head, tail, difference;

    while (y < HEIGHT) // down => up
    {
        head = 0, tail = 1, difference = 0;
        while (tail < WIDTH) // left => right
        {
            if ((map[y][head] == map[y][tail]) && (map[y][head] != 0))
            {
                difference = tail++ - head;
            }
            else
            {
                head = tail++;
                difference = 0;
            }

            if (difference >= 2)
            {
                for (int i = 0; i <= difference; i++)
                {
                    matches[y][head + i] = true;
                }
            }
        }
        y++;
    }

    while (x < WIDTH) // left => right
    {
        head = 0, tail = 1, difference = 0;
        while (tail < HEIGHT) // down => up
        {
            if ((map[head][x] == map[tail][x]) && (map[head][x] != 0))
            {
                difference = tail++ - head;
            }
            else
            {
                head = tail++;
                difference = 0;
            }

            if (difference >= 2)
            {
                for (int i = 0; i <= difference; i++)
                {
                    matches[head + i][x] = true;
                }
            }
        }
        x++;
    }

    for (int i = 0; i < HEIGHT; i++) // Count all matched cells
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (matches[i][j] == true)
            {
                matched_cells++;
            }
        }
    }

    return matched_cells;
}

/***********************************************************************
 * TODO 2: Remove all tiles that are matched with 3 others of the same
 * type horizontally or vertically, and update the game grid accordingly
 ***********************************************************************/
int processMatches(int map[][WIDTH])
{
    bool matches[HEIGHT][WIDTH] = {};
    int score_increased = 0;
    score_increased = findMatches(map, matches);

    for (int y = HEIGHT - 1; y >= 0; y--) // up => down
    {
        for (int x = 0; x < WIDTH; x++) // left => right
        {
            if (matches[y][x] == true)
            {
                for (int i = y; i < MAX_ROWS - 1; i++)
                {
                    map[i][x] = map[i + 1][x];
                }
                map[MAX_ROWS - 1][x] = 0;
            }
        }
    }

    if (score_increased)
    {
        return (score_increased + processMatches(map)); // Recursion
    }

    return score_increased;
}

/***********************************************************************
 * TODO 3: Swap the tiles at the specified locations
 ***********************************************************************/
void swapTiles(int map[][WIDTH], int x1, int y1, int x2, int y2)
{
    map[y1][x1] = map[y1][x1] ^ map[y2][x2];
    map[y2][x2] = map[y1][x1] ^ map[y2][x2];
    map[y1][x1] = map[y1][x1] ^ map[y2][x2];
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
    int temp_num_candidate_moves = 0;
    int map_copy[MAX_ROWS][WIDTH];

    // get all possible moves
    for (int row = 0; row < HEIGHT; row++) // down => up
    {
        for (int col = 0; col < WIDTH - 1; col++) // left => right
        {
            copyMap(map, map_copy, MAX_ROWS);
            swapTiles(map_copy, col, row, col + 1, row);
            int score_gained = processMatches(map_copy);
            if (score_gained >= max_score_gained)
            {
                if (score_gained > max_score_gained)
                {
                    temp_num_candidate_moves = 0;
                    max_score_gained = score_gained;
                }
                candidate_moves[temp_num_candidate_moves][0] = col;
                candidate_moves[temp_num_candidate_moves][1] = row;
                candidate_moves[temp_num_candidate_moves][2] = col + 1;
                candidate_moves[temp_num_candidate_moves++][3] = row;
            }
        }
    }

    for (int col = 0; col < WIDTH; col++) // left => right
    {
        for (int row = 0; row < HEIGHT - 1; row++) // down => up
        {
            copyMap(map, map_copy, MAX_ROWS);
            swapTiles(map_copy, col, row, col, row + 1);
            int score_gained = processMatches(map_copy);

            if (score_gained >= max_score_gained)
            {
                if (score_gained > max_score_gained)
                {
                    temp_num_candidate_moves = 0;
                    max_score_gained = score_gained;
                }
                candidate_moves[temp_num_candidate_moves][0] = col;
                candidate_moves[temp_num_candidate_moves][1] = row;
                candidate_moves[temp_num_candidate_moves][2] = col;
                candidate_moves[temp_num_candidate_moves++][3] = row + 1;
            }
        }
    }

    num_candidate_moves = temp_num_candidate_moves;

    return max_score_gained;
}

/***********************************************************************
 * TODO 5: Implement the solver
 ***********************************************************************/
int solver(int map[][WIDTH], int return_coordinates[4])
{
    int candidate_moves[HEIGHT * (WIDTH - 1) + (HEIGHT - 1) * WIDTH][4];
    //int highest_candidate_moves[4] = {};
    int num_candidate_moves = 0, score_gained = 0, highest_score_gained = 0;
    score_gained = considerMoves(map, candidate_moves, num_candidate_moves);
    //cout << "bbbbb" << endl;

    // for (int i = 0; i < num_candidate_moves; i++)
    // {
    //     cout << candidate_moves[i][0] << candidate_moves[i][1] << candidate_moves[i][2] << candidate_moves[i][3] << endl;
    // }

    if (num_candidate_moves == 0)
    {
        return 0;
    }
    else if (num_candidate_moves == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            return_coordinates[i] = candidate_moves[0][i];
        }
        return score_gained;
    }
    else
    {
        int map_copy[MAX_ROWS][WIDTH] = {};
        //cout << ".." << endl;
        for (int i = 0; i < num_candidate_moves; i++)
        {
            int current_score = 0;
            copyMap(map, map_copy, MAX_ROWS);
            swapTiles(map_copy, candidate_moves[i][0], candidate_moves[i][1], candidate_moves[i][2], candidate_moves[i][3]);
            processMatches(map_copy);
            current_score = score_gained + solver(map_copy);
            //cout << current_score << " " << highest_score_gained << endl;
            if (current_score > highest_score_gained)
            {
                //cout << current_score << " " << highest_score_gained << endl;
                highest_score_gained = current_score;
                return_coordinates[0] = candidate_moves[i][0];
                return_coordinates[1] = candidate_moves[i][1];
                return_coordinates[2] = candidate_moves[i][2];
                return_coordinates[3] = candidate_moves[i][3];
            }
        }
        return highest_score_gained;
    }
    return 0;
}

// overloaded solver() used when returning the optimal move is not required
int solver(int map[][WIDTH])
{
    int dummy[4];
    return solver(map, dummy);
}
