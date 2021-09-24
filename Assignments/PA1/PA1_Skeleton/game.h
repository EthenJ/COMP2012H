#include <string>

const int WIDTH = 9;
const int HEIGHT = 9;
const int MAX_ROWS = 81;
const int MAX_MOVES = 12;
const std::string INPUT_FILE = "map.txt";

const char tile[] = { ' ', '1' , '2' , '3', '4', '5', '6' };

extern int map[][WIDTH];
extern int score;
extern int remaining_moves;

void readMap(std::string filename, int map[][WIDTH]);
void printMap(int map[][WIDTH]);
void printMatches(bool matches[HEIGHT][WIDTH]);
bool inBounds(int x_pos, int y_pos);
int findMatches(int map[][WIDTH], bool matches[HEIGHT][WIDTH]);
int processMatches(int map[][WIDTH]);
void swapTiles(int map[][WIDTH], int x1, int y1, int x2, int y2);
void copyMap(int map[][WIDTH], int map_copy[][WIDTH], int rows_to_copy);
int considerMoves(int map[][WIDTH], int candidate_moves[][4], int& num_candidate_moves);
int solver(int map[][WIDTH]);
int solver(int map[][WIDTH], int return_coordinates[4]);
