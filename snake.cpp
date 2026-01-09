#include <bits/stdc++.h>
#include <conio.h>   // header file for keyboard inputs
#include <windows.h> // for sleep funtion
using namespace std;

// Credits to YouTube Channel: NVitanovic
// Tutorial link:
// https://www.youtube.com/watch?v=E_-lMZDi7Uw&list=PLrjEQvEart7dPMSJiVVwTDZIHYq6eEbeL

// game state
bool game_over = false;

// game dimensions
const int game_width = 20;
const int game_height = 20;

// snake head position
int snake_x, snake_y;

// fruit position
int fruit_x, fruit_y;

// player's score
int game_score;

// snake direction variables
enum eDirection
{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
eDirection snake_direction;

// tail variables
int tail_x[100];
int tail_y[100];
int tail_length = 0;

void Setup()
{
    game_over = false;
    snake_direction = STOP;
    snake_x = game_width / 2;
    snake_y = game_height / 2;
    srand(time(0)); // srand to disturb psuedo-randomness
    fruit_x = rand() % game_width;
    fruit_y = rand() % game_height;
    game_score = 0;
}

void Draw()
{
    // system clear screen
    system("cls");

    // draw top wall
    for (int i = 0; i < game_width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    // draw game map
    for (int i = 0; i < game_height; i++)
    {
        for (int j = 0; j < game_width; j++)
        {
            // draw left side wall
            if (j == 0)
            {
                cout << "#";
            }

            // draw game logic
            if (i == snake_y && j == snake_x)
            {
                // Snake Head
                cout << "O";
            }
            else if (i == fruit_y && j == fruit_x)
            {
                cout << "F";
            }
            else
            {
                bool print_tail = false;
                for (int k = 0; k < tail_length; k++)
                {
                    if (j == tail_x[k] && i == tail_y[k])
                    {
                        cout << "o";
                        print_tail = true;
                    }
                }
                if (!print_tail)
                {
                    cout << " ";
                }
            }

            // draw right side wall
            if (game_width - 1 == j)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    // draw bottom wall
    for (int i = 0; i < game_width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    // print game score
    cout << "Your score: " << game_score << endl;
}

void Input()
{
    if (_kbhit())
    { // true if keyboard is pressed

        // W A S D keys
        // w is UP
        // a is left
        // s is down
        // d is right

        switch (_getch())
        {
        case 'w':
            snake_direction = UP;
            break;
        case 'a':
            snake_direction = LEFT;
            break;
        case 's':
            snake_direction = DOWN;
            break;
        case 'd':
            snake_direction = RIGHT;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void Logic()
{
    // snake tail logic
    int previous_tail_x = tail_x[0];
    int previous_tail_y = tail_y[0];

    int temp_tail_x;
    int temp_tail_y;

    tail_x[0] = snake_x;
    tail_y[0] = snake_y;

    for (int i = 1; i < tail_length; i++)
    {

        temp_tail_x = tail_x[i];
        temp_tail_y = tail_y[i];

        tail_x[i] = previous_tail_x;
        tail_y[i] = previous_tail_y;

        previous_tail_x = temp_tail_x;
        previous_tail_y = temp_tail_y;
    }

    // snake direction logic from Input()
    switch (snake_direction)
    {
    case UP:
        snake_y--;
        break;
    case LEFT:
        snake_x--;
        break;
    case DOWN:
        snake_y++;
        break;
    case RIGHT:
        snake_x++;
        break;
    default:
        break;
    }

    // snake out of bounds, game over
    // if (snake_x > game_width || snake_x < 0 || snake_y < 0 || snake_y > game_height)
    // {
    //     game_over = true;
    // }

    // make game more fun, with snake coming out of opposite wall
    if(snake_x >= game_width) {
        snake_x = 0;
    } else if(snake_x < 0) {
        snake_x = game_width - 1;
    }

    if(snake_y >= game_height) {
        snake_y = 0;
    } else if(snake_y < 0) {
        snake_y = game_height - 1;
    }

    // if snake tail comes into contact with snake head, game over
    for(int i = 0; i < tail_length; i++) {
        if(tail_x[i] == snake_x && tail_y[i] == snake_y) {
            game_over = true;
        }
    }

    // eat fruit
    if (snake_x == fruit_x && snake_y == fruit_y)
    {
        // increase game score
        game_score += 10;

        // generate new fruit at random position
        srand(time(0)); // srand to disturb psuedo-randomness
        fruit_x = rand() % game_width;
        fruit_y = rand() % game_height;

        // increase tail length by 1
        tail_length++;
    }

    
}

int main()
{
    Setup();
    while (!game_over)
    {
        Draw();
        Input();
        Logic();
        Sleep(225);
    }
    return 0;
}