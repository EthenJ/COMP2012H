#include <iostream>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;

const int PATTERN_SIZE = 8;
const int WIDTH = 60;
const int HEIGHT = 15;

int initialState[WIDTH];    // the initial state
int grid[HEIGHT][WIDTH];    // the grid for display
int rule[PATTERN_SIZE];     // the rule in binary, 1 bit per array element
int curRow;                 // current row
int curStep;                // current step
int ruleNum;                // rule number in decimal


const unsigned long MAX_RAND = 0x80000000;
static unsigned long rng_lab1 = 0;
static void _srand(unsigned long seed) {
    rng_lab1 = seed;
}

static unsigned long _rand() {
    rng_lab1 = (1103515245 * rng_lab1 + 12345) % (1 << 31);
    return rng_lab1 & 0x7FFFFFFF;
}

int getRandNum(double probability) {
    unsigned long threshold = probability * MAX_RAND;
    return _rand() < threshold ? 1 : 0;
}

void initRule() {

    //
    // TODO: task 1.1, initialize the rule
    // Ask the user to input the decimal rule number.
    // Check whether the number is in between 0 and 255, inclusive
    // If not, ask the user to retry
    // Otherwise, convert the number to binary and store the bits into rule[]
    //
    // Your code here
    //

}

void initStateFromInput() {

    //
    // TODO: task 1.2, initialize the initial state from user input
    // Ask the user to input the number of initially living cells and their positions
    // Report error if the number or the positions are invalid
    // Initialize grid[][] and initialState[] accordingly
    //
    // Your code here
    //

}

void initStateRandomly() {

    //
    // TODO: task 1.3, initialize the initial state randomly
    // Ask the user for a fill rate and use it as the probability to generate random 0 and 1s
    // using getRandNum(). Fill in initialState[] and grid[][] accordingly
    //
    // Your code here
    //

}

int getNeighbourState(int row, int col) {

    // 
    // TODO: task 2.1, get a decimal number repersenting the current state of the neighbours
    // Compute the state of the neighbours with respect to the given row and col
    // Wrap around the boundaries if necessary
    //
    // Your code here
    //

    return 0;
}

void update() {

    //
    // TODO: task 2.2, update to the next state
    // Compute the next state according to the current state and the rule
    // Update grid[][], curRow and curStep correspondingly
    // Wrap around the boundaries if needed
    //
    // Your code here
    //

}

void getState(int step) {

    //
    // TODO: task 2.3, get the state of the automaton after given steps
    // Modify grid[][] so that its content represents the state of the automaton
    // after the given number of steps
    // 
    // Your code here
    //

}

void initState() {
    cout << "Please specify the initial state. 'R' for random generation, 'M' for manual input." << endl;
    char mode;
    cin >> mode;
    while (mode != 'R' && mode != 'M') {
        cout << "Invalid mode, please enter 'R' or 'M':" << endl;
        cin >> mode;
    }

    if (mode == 'R') {
        initStateRandomly();
    } else {
        initStateFromInput();
    }
}

void displayGrid() {
    cout << "State of rule " << ruleNum << " after " << curStep << " steps:" << endl;
    cout << std::string(WIDTH, '=') << endl;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << (grid[i][j] ? '@' : ' ');
        }
        cout << endl;
    }

    cout << std::string(WIDTH, '=') << endl;
}

int main() {
    _srand(2012);

    cout << "Elementary Cellular Automaton" << endl;
    initRule();
    initState();
    displayGrid();

    while (true) {
        cout << "Please specify the number of steps" << endl;
        int step;
        cin >> step;

        if (step == -1) {
            break;
        }

        if (step < 0) {
            cout << "Invalid step" << endl;
            continue;
        }

        getState(step);
        displayGrid();
    }
}
