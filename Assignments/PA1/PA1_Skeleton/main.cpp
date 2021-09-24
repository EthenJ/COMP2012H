#include <iostream>
#include <string>
#include <limits>
#include "game.h"

using namespace std;

int gameIteration(int map[][WIDTH], int& remaining_moves, int& score) {
    // return values:
    // -1 invalue input
    //  0 game quit or finished
    //  1 valid input
    //  2 used solver

    if( remaining_moves <= 0 ) {
        cout<<"Game Finished!\n";
        cout<<"Final Score: "<<score<<"\n";
        return 0;
    }

    cout<<"\n";
    cout<<"Swap tile:           swap x_pos y_pos directions(up/down/left/right)     \n";
    cout<<"Automatic solver:    solve                                               \n";
    cout<<"Quit:                quit                                                \n";
    cout<<">>";
    string input;
    cin>>input;
    cout<<"\n";

    if( input == "swap") {
        int x, y;
        string direction;
        // invalid input checking
        if(!(cin >> x >> y) || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT ) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Invalid input: please input an integer between 0 and 8 inclusive for x and y\n";
            return -1;
        }
        cin >> direction;
        if ( direction != "up" && direction != "down" && direction != "left" && direction != "right") {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Invalid input: please input up/down/left/right for direction\n";
            return -1;            
        }
        if(( y == 0 && direction == "down" ) || ( y == HEIGHT - 1 && direction == "up")
                || ( x == 0 && direction == "left") || ( x == WIDTH - 1 && direction == "right") ) {
            cout<<"Invalid input: out of bounds\n";
            return -1;
        }

        int x2, y2;
        if ( direction == "left" ) {
            x2 = x - 1;
            y2 = y;
        } else if ( direction == "right" ) {
            x2 = x + 1;
            y2 = y;
        } else if ( direction == "up" ) {
            x2 = x;
            y2 = y + 1;
        } else if ( direction == "down" ) {
            x2 = x;
            y2 = y - 1;
        }

        swapTiles(map, x, y, x2, y2);
        score += processMatches(map);
        remaining_moves--;

        printMap(map);
        cout<<"Remaining Moves: "<<remaining_moves<<"\n";
        cout<<"Score: "<<score<<"\n";
        return 1;
    } else if( input == "solve") {
        int solver_return_coordinates[4];
        solver(map, solver_return_coordinates);
        cout<<"Solver output: swap ("<<solver_return_coordinates[0]<<", "<<solver_return_coordinates[1]<<") ("<<solver_return_coordinates[2]<<", "<<solver_return_coordinates[3]<<")\n";
        swapTiles( map, solver_return_coordinates[0], solver_return_coordinates[1], solver_return_coordinates[2], solver_return_coordinates[3] );
        score += processMatches(map);
        remaining_moves--;
        printMap(map);
        cout<<"Remaining Moves: "<<remaining_moves<<"\n";
        cout<<"Score: "<<score<<"\n";
        return 2;
    } else if( input == "quit") {
        return 0;
    } else {
        cout<<"Invalid input\n";
        return -1;
    }
}

int main() {
    int map[MAX_ROWS][WIDTH];
    int score = 0;
    int remaining_moves = MAX_MOVES;

    readMap(INPUT_FILE, map);

    // get rid of all existing matches first in order to present the player with a board with no pre-existing three-in-a-rows
    processMatches(map);

    printMap(map);
    cout<<"Remaining Moves: "<<remaining_moves<<"\n";
    cout<<"Score: "<<score<<"\n";
    cout<<endl;


    while( true ) {
        if( gameIteration(map, remaining_moves, score) == 0) {
            break;
        }
    }

    return 0;
}