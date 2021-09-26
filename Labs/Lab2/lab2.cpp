#include <iostream>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;

const int PATTERN_SIZE = 8;
const int WIDTH = 60;
const int HEIGHT = 15;

int initialState[WIDTH]; // the initial state
int grid[HEIGHT][WIDTH]; // the grid for display
int rule[PATTERN_SIZE];  // the rule in binary, 1 bit per array element
int curRow;              // current row
int curStep;             // current step
int ruleNum;             // rule number in decimal

const unsigned long MAX_RAND = 0x80000000;
static unsigned long rng_lab1 = 0;
static void _srand(unsigned long seed)
{
    rng_lab1 = seed;
}

static unsigned long _rand()
{
    rng_lab1 = (1103515245 * rng_lab1 + 12345) % (1 << 31);
    return rng_lab1 & 0x7FFFFFFF;
}

int getRandNum(double probability)
{
    unsigned long threshold = probability * MAX_RAND;
    return _rand() < threshold ? 1 : 0;
}

void initRule()
{
    //
    // TODO: task 1.1, initialize the rule
    while (true)
    {
        // Ask the user to input the decimal rule number.
        cout << "Please specify the number of steps" << endl;
        cin >> ruleNum;
        // Check whether the number is in between 0 and 255, inclusive
        if (ruleNum > 255 || ruleNum < 0)
        {
            // If not, ask the user to retry
            cout << "Invalid rule number, please retry:" << endl;
            continue;
        }
        break;
    }
    // Otherwise, convert the number to binary and store the bits into rule[]
    for (int i = 0, decimal = ruleNum; i < PATTERN_SIZE; i++)
    {
        rule[i] = decimal % 2;
        decimal /= 2;
    }
}

void initStateFromInput()
{
    //
    // TODO: task 1.2, initialize the initial state from user input
    int number_of_cells_alive = -1;
    while (true)
    {
        // Ask the user to input the number of initially living cells and their positions
        cout << "Please enter the number of cells alive in the initial state:" << endl;
        cin >> number_of_cells_alive;
        if (number_of_cells_alive < 1 || number_of_cells_alive > WIDTH)
        {
            // Report error if the number or the positions are invalid
            cout << "Invalid number of living cells, please retry:" << endl;
            continue;
        }
        break;
    }
    int col = 0, N = 0;
    while (N < number_of_cells_alive)
    {
        cout << "Please enter the column at which the cells are alive:" << endl;
        cin >> col;
        if (col < 0 || col > WIDTH - 1)
        {
            cout << "Column out of bound" << endl;
            continue;
        }
        else if (initialState[col] == 1)
        {
            cout << "Column duplicated" << endl;
            continue;
        }
        initialState[col] = 1;
        grid[0][col] = 1;
        N++;
    }
}

void initStateRandomly()
{
    //
    // TODO: task 1.3, initialize the initial state randomly
    double fill_rate;
    while (true)
    {
        // Ask the user for a fill rate and use it as the probability to generate random 0 and 1s
        cout << "Please enter the fill rate:" << endl;
        cin >> fill_rate;
        if (fill_rate < 0.0 || fill_rate > 1.0)
        {
            cout << "Invalid probability, please retry:" << endl;
            continue;
        }
        break;
    }
    for (int i = 0, fill; i < WIDTH; i++)
    {
        // using getRandNum(). Fill in initialState[] and grid[][] accordingly
        fill = getRandNum(fill_rate);
        grid[0][i] = fill;
        initialState[i] = fill;
    }
}

int getNeighbourState(int row, int col)
{
    //
    // TODO: task 2.1, get a decimal number repersenting the current state of the neighbours
    // Compute the state of the neighbours with respect to the given row and col
    // Wrap around the boundaries if necessary
    return grid[row][(col + WIDTH - 1) % WIDTH]*2*2 + grid[row][col]*2 + grid[row][(col + WIDTH + 1) % WIDTH];
}

void update()
{
    //
    // TODO: task 2.2, update to the next state
    // Compute the next state according to the current state and the rule
    // Update grid[][], curRow and curStep correspondingly
    // Wrap around the boundaries if needed
    //
    // Your code here
    //
}

void getState(int step)
{

    //
    // TODO: task 2.3, get the state of the automaton after given steps
    // Modify grid[][] so that its content represents the state of the automaton
    // after the given number of steps
    //
    // Your code here
    //
}

void initState()
{
    cout << "Please specify the initial state. 'R' for random generation, 'M' for manual input." << endl;
    char mode;
    cin >> mode;
    while (mode != 'R' && mode != 'M')
    {
        cout << "Invalid mode, please enter 'R' or 'M':" << endl;
        cin >> mode;
    }

    if (mode == 'R')
    {
        initStateRandomly();
    }
    else
    {
        initStateFromInput();
    }
}

void displayGrid()
{
    cout << "State of rule " << ruleNum << " after " << curStep << " steps:" << endl;
    cout << std::string(WIDTH, '=') << endl;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cout << (grid[i][j] ? '@' : ' ');
        }
        cout << endl;
    }

    cout << std::string(WIDTH, '=') << endl;
}

int main()
{
    _srand(2012);

    cout << "Elementary Cellular Automaton" << endl;
    initRule();
    initState();
    displayGrid();

    while (true)
    {
        cout << "Please specify the number of steps" << endl;
        int step;
        cin >> step;

        if (step == -1)
        {
            break;
        }

        if (step < 0)
        {
            cout << "Invalid step" << endl;
            continue;
        }

        getState(step);
        displayGrid();
    }
}
