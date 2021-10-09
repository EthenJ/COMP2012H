#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#include "Snake.h"
using namespace std;

const int GRID_SIZE = 20;
const int FRUIT_SIZE = 20; // Number of fruits
const int RNG_SEED = 1;

/**
* Generate random locations on the grid
*/
default_random_engine rng;
uniform_int_distribution<int> dist(0, GRID_SIZE - 1);

/**
* Saves the properties of fruits (x,y)
*/
int fruits[FRUIT_SIZE][2];

/**
* The head of linked list
*/
SnakeBody *snake_head;

//Player score (how long the snake is)
int score = 0;

void print_game_board()
{
    // Clear console
    for (int i = 0; i < 100; i++)
    {
        cout << "\n";
    }

    // Print from top to bottom, left to right
    // Precedence for choosing pixel: Fruit >> Snake >> Empty tile
    for (int y = 0; y < GRID_SIZE; ++y)
    {
        for (int x = 0; x < GRID_SIZE; ++x)
        {
            bool found = false;

            for (int i = 0; i < FRUIT_SIZE; ++i)
            {
                if (x == fruits[i][0] && y == fruits[i][1])
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                cout << "*";
            }
            else
            {

                /**
                * Loops through the entire snake to see if a body is located in the tile
                */
                SnakeBody *body = snake_head;

                while (body != nullptr)
                {
                    if (body->x == x && body->y == y)
                    {
                        found = true;
                        break;
                    }
                    body = body->next;
                }

                if (found)
                {
                    cout << "o";
                }
                else
                {
                    cout << ".";
                }
            }
        }
        cout << "\n";
    }
}

void print_messages()
{
    cout << endl
         << endl;
    cout << "SCORE: " << score << endl;
    cout << "Please move the snake with WASD keys!" << endl;
    cout << "Type 'quit' to exit the game" << endl;
}

char await_user_input()
{
    string str;

    cout << "Input: ";

    // Continually prompt player until there is a valid input
    while (true)
    {
        getline(cin, str);

        if (str.rfind("q") == 0)
        {
            return 'Q';
        }
        else if (str.rfind("w") == 0 || str.rfind("W") == 0)
        {
            return 'W';
        }
        else if (str.rfind("a") == 0 || str.rfind("A") == 0)
        {
            return 'A';
        }
        else if (str.rfind("s") == 0 || str.rfind("S") == 0)
        {
            return 'S';
        }
        else if (str.rfind("d") == 0 || str.rfind("D") == 0)
        {
            return 'D';
        }
        else
        {
            cout << "Invalid command! Please try again: ";
        }
    }
}

/**
* Sets the x and y value to be a empty point on the grid, not intersecting the snake and not having any fruits.
*/
void unique_coordinates(int &x, int &y)
{
    int nx, ny; // Use new variables instead of references to prevent infinite loop (e.g. if x,y are themselves references to the location of fruits).
    do
    {
        nx = dist(rng);
        ny = dist(rng);

        bool needs_reroll = false;
        for (int i = 0; i < FRUIT_SIZE; ++i)
        {
            if (fruits[i][0] == nx && fruits[i][1] == ny)
            {
                needs_reroll = true;
                break;
            }
        }
        if (!needs_reroll)
        {
            SnakeBody *body = snake_head;
            while (body != nullptr)
            {
                if (body->x == nx && body->y == ny)
                {
                    needs_reroll = true;
                    break;
                }
                body = body->next;
            }
        }

        if (!needs_reroll)
        {
            break;
        }
    } while (true);
    x = nx;
    y = ny;
}

void animate_snake_dying(int index)
{
    SnakeBody *b = get_next_body(*snake_head, index);
    SnakeBody *bn = b->next;

    if (b == snake_head)
    {
        if (bn != nullptr)
        {
            if (bn->next != nullptr)
            {
                snake_head = bn->next;
                remove_self(*bn);
                remove_self(*b);
                delete b;
                delete bn;
            }
            else
            {
                delete b;
                delete bn;
                snake_head = nullptr;
            }
        }
        else
        {
            delete b;
            snake_head = nullptr;
        }
    }
    else
    {
        remove_self(*b);
        delete b;
        if (bn != nullptr)
        {
            remove_self(*bn);
            delete bn;
        }
    }
}

/**
* Updates the game according to the player's input
* W = Move Up, S = Move Down, A = Move Left, D = Move Right
* 
* Returns -1 if the game continues. If the player loses, returns the index of the snake body where collision has occurred.
*/
int update_game(char option)
{
    // START OF YOUR IMPLEMENTATION

    // Store the location of the tail now (in case the snake has to grow)
    int tail_x = get_tail(*snake_head)->x;
    int tail_y = get_tail(*snake_head)->y;

    // Handle snake movement -- remove the tail and place it on the front
    // Make sure that the pointer snake_head gets updated!!
    // Also take care of the special case where the snake length = 1
    if ((snake_head->prev == nullptr) && (snake_head->next == nullptr)) // snake length = 1
    {
        if (option == 'W')
        {
            snake_head->y--;
        }
        else if (option == 'S')
        {
            snake_head->y++;
        }
        else if (option == 'A')
        {
            snake_head->x--;
        }
        else if (option == 'D')
        {
            snake_head->x++;
        }
    }
    else
    {
        SnakeBody *tail = get_tail(*snake_head);
        SnakeBody *head = get_head(*snake_head);
        // cout << head->x << " 1 " << head->y << endl;
        // cout << tail->x << " 2 " << tail->y << endl;
        if (option == 'W')
        {
            tail->y = head->y - 1;
            tail->x = head->x;
        }
        else if (option == 'S')
        {
            tail->y = head->y + 1;
            tail->x = head->x;
        }
        else if (option == 'A')
        {
            tail->x = head->x - 1;
            tail->y = head->y;
        }
        else if (option == 'D')
        {
            tail->x = head->x + 1;
            tail->y = head->y;
        }
        remove_self(*tail);
        insert_into_previous(*head, tail);
        // cout << tail->x << " : " << tail->y << endl;
        // cout << tail->next->x << " : " << tail->next->y << endl;
    }
    
    // If the snake head is out of bounds (hits the wall), the player loses. Returns 0 (the index of the head of the snake)
    // if that happens.
    snake_head = get_head(*snake_head);
    // cout << head->x << " : " << head->y << endl;
    if (snake_head->next != nullptr)
    {
        // SnakeBody *tail = get_tail(*snake_head);
        // cout << tail->x << " " << tail->y << endl;
        // cout << tail->next->x << tail->next->y << endl;
        // cout << tail->next->next->x << tail->next->next->y << endl;
        if ((snake_head->x < 0) || (snake_head->x > GRID_SIZE - 1) || (snake_head->y < 0) || (snake_head->y > GRID_SIZE - 1))
            return 0;
    }

    // If the snake head hits its body, the player loses.
    // If that happens, return the index of the body which is currently intersecting the head.
    int i = 0;
    for (SnakeBody *body = snake_head->next; body != nullptr; body = body->next, i++)
    {
        if ((snake_head->x == body->x) && (snake_head->y == body->y))
        {
            // cout << snake_head->x << " " << snake_head->y << endl;
            // cout << get_tail(*snake_head)->x << " " << get_tail(*snake_head)->y << endl;
            // cout << "gg" << endl;
            return i;
        }
    }
    // If the snake head hits a fruit, the snake grows, and the player gains one point.
    // The tail of the snake should be in the previous location (i.e. the stored location at the beginning)
    // Use the function unique_coordinates(fruits[i][0], fruits[i][1]) to reset the location
    // of the fruit. Make sure to use the function only once so the new fruit location matches
    // the one in the modal answer, for automated grading.
    for (int i = 0; i < FRUIT_SIZE; i++)
    {
        if ((snake_head->x == fruits[i][0]) && (snake_head->y == fruits[i][1]))
        {
            SnakeBody *tail = new SnakeBody;
            tail->x = tail_x;
            tail->y = tail_y;
            insert_into_next(*get_tail(*snake_head), tail);
            snake_head = get_head(*snake_head);
            unique_coordinates(fruits[i][0], fruits[i][1]);
            score++;
            break;
        }
    }
    // SnakeBody *tail = get_tail(*snake_head);
    //     cout << head->x << " m " << head->y << endl;
    //     cout << tail->x << " n " << tail->y << endl;
    // Snake hasn't died yet here, return -1.
    return -1;
    // END OF YOUR IMPLEMENTATION
}

int main()
{
    // Fixed seed, useful for debug and automated grading
    rng.seed(RNG_SEED);

    // Create the head of the snake with random location on the grid
    snake_head = new SnakeBody{};
    snake_head->x = dist(rng);
    snake_head->y = dist(rng);

    for (int i = 0; i < FRUIT_SIZE; ++i)
    {
        fruits[i][0] = -1;
        fruits[i][1] = -1;
    }

    for (int i = 0; i < FRUIT_SIZE; ++i)
    {
        unique_coordinates(fruits[i][0], fruits[i][1]);
    }

    //Main Loop
    while (true)
    {
        print_game_board();
        print_messages();
        char option = await_user_input();

        if (option == 'Q')
        {
            cout << "Game closing.... " << endl;
            // Deallocate entire snake here
            while (snake_head != nullptr)
            {
                SnakeBody *next = snake_head->next;
                delete snake_head;
                snake_head = next;
            }
            break;
        }

        int index = update_game(option);
        if (index != -1)
        {
            while (snake_head != nullptr)
            {
                animate_snake_dying(index);
                print_game_board();
                for (int i = 0; i < 5; i++)
                {
                    cout << endl;
                }
                this_thread::sleep_for(chrono::milliseconds(100));

                if (index > 0)
                {
                    --index;
                }
            }
            cout << endl;
            cout << "Game Over! Final score: " << score << endl;
            cout << endl;
            return 0;
        }
    }
    return 0;
}
