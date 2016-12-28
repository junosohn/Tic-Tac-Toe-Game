/* 

VCC CMPT 1010 - Assignment 3
11/22/15
Junho Sohn & Justin Sze

Tic-Tac-Toe Game
Using arrays and multiple functions, lets user play
games of Tic-Tac-Toe against a computer.

*/

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <ctime>

using namespace std;

//"Slots" in the tic-tac-toe board
char place[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

//Display messages (intro, player, board, win, draw)
void intro_message();
void player_display(int);
void display_board();
void winning_message(char);
void draw_message();

//Input functions
char get_char_input();
int get_int_input(const int, const int);
int random_input();

int winner_check();
bool replay_check();
void replay_reset();
bool overlap_check(int, char[]);


int main()
{
    char p;
    int decide_player=1;
    int input, w;
    int play_count=0; //opponent move display
    int replay=0;
    char replay_ans;

    intro_message();
    get_char_input();

    do //Replay question runs after first game
    {
        decide_player=1; //Make sure the user always goes first
        play_count=0;    //Play count is also set to 0 so it skips the "Player X picked slot" message
        replay_reset();

        do //Needs to run at least once since Player O (user) goes first
        {
            if(decide_player==1)
            {
                display_board();

                if(play_count>0) //displays what the opponent picked AFTER the first move
                    cout << "Player X picked slot " << input << ".";

                player_display(decide_player);
                input = get_int_input(0,8);

                //Checks if the slot's been taken already
                while(!overlap_check(input,place))
                {
                    cout << "Spot's already taken. Re-enter: ";
                    input = get_int_input(0,8);
                }

                place[input] = 'O';
                p='O';
                decide_player++;
            }

            else
            {
                w=winner_check();
                if(w==1 || w==2)
                    break;

                display_board();
                player_display(decide_player);

                //Randomize opponent's placement
                do
                {
                    input = random_input();
                }
                while(!overlap_check(input,place));

                place[input] = 'X';
                p='X';
                decide_player--;
            }

            play_count++;
            w=winner_check();
        }
        while(w!=1);

//Redisplay board in play to include last player's move in case either wins or draws
        display_board();

///***********************///
///* WIN OR DRAW MESSAGE *///
///***********************///
        if(w==1)
            winning_message(p);
        else if(w==2)
            draw_message();
    }
    while (replay_check());


    cout << endl << "Thanks for playing!" << endl;

    return 0;
}

//Checks if there is a winner
//PRE: Checks if slots are filled with char or ' '
//POST: Returns 1 for a win, 2 for a draw
int winner_check()
{
    if ((place[0] == place[1] && place[1] == place[2] && place[0]!=' ') ||
        (place[3] == place[4] && place[4] == place[5] && place[3]!=' ') ||
        (place[6] == place[7] && place[7] == place[8] && place[6]!=' ') ||
        (place[0] == place[3] && place[3] == place[6] && place[0]!=' ') ||
        (place[1] == place[4] && place[4] == place[7] && place[1]!=' ') ||
        (place[2] == place[5] && place[5] == place[8] && place[2]!=' ') ||
        (place[0] == place[4] && place[4] == place[8] && place[0]!=' ') ||
        (place[2] == place[4] && place[4] == place[6] && place[2]!=' '))
        return 1;

    else if (place[0] != ' ' && place[1] != ' ' && place[2] != ' ' &&
             place[3] != ' ' && place[4] != ' ' && place[5] != ' ' &&
             place[6] != ' ' && place[7] != ' ' && place[8] != ' ')
        return 2;

    else
        return 0;
}

//Checks if the slot the player picked has already been taken (Can't overlap!)
//PRE: Slot has either 'O', 'X', or ' '
//POST: returns true if it is ' ' (empty), false if 'O' or 'X'
bool overlap_check(int input_overlap, char overlap[9])
{
    if (overlap[input_overlap] != 'O' && overlap[input_overlap] != 'X')
        return true;
    else
        return false;
}

//Gets input that is >=0 and <=8
//PRE: integer slot for the board
//POST: returns int if it is >=0 or <=8. If not, re-enter
int get_int_input(int min, int max)
{
    int num;
    cin.unsetf(ios::skipws);
    while ( !(cin >> num) || ( cin.get() != '\n') ||  (num > max) || (num < min) )
    {
        cout << "Please enter an integer in the range " << min << " - " << max << ": ";
        cin.clear(); // unset failbit
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.setf(ios::skipws);
    return num;
}

//Gets random input for opponent (0 <= input <= 8)
//PRE: int within 0-8
//POST: Random value >=0 or <=8
int random_input()
{
    srand(time(0));
    int random = rand()%9;
    return random;
}

//Displays board in play.
//PRE: Board display
//POST: Clears previous board, place picked by player is filled with corresponding letter (X/O)
void display_board()
{
    system("cls");
    cout << "*******************" << endl;
    cout << "*                 *" << endl;
    cout << "*  BOARD IN PLAY  *" << endl;
    cout << "*                 *" << endl;
    cout << "*******************" << endl << endl;

    cout << " " << place[0] << " | " << place[1] << " | " << place[2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << place[3] << " | " << place[4] << " | " << place[5] << endl;
    cout << "---|---|---" << endl;
    cout << " " << place[6] << " | " << place[7] << " | " << place[8] << endl;
    cout << endl;
}

//Displays message to show what player's turn it is
//PRE: value for player (1/2) is sent
//POST: Displays which player's turn it is
void player_display(int check_player)
{
    char playa;
    if(check_player==1)
        playa = 'O';
    else
        playa = 'X';

    cout << "\n\nPLAYER " << playa << " TURN" << endl << endl;
    if(playa=='O')
        cout << "Select place on board: ";
}

//Intro message
//PRE: None
//POST: Display intro message
void intro_message()
{
    cout << "**************************************" << endl;
    cout << "*                                    *" << endl;
    cout << "*  Welcome to the Tic-Tac-Toe game!  *" << endl;
    cout << "*                                    *" << endl;
    cout << "*   Player 1: O   |   Player 2: X    *" << endl;
    cout << "*                                    *" << endl;
    cout << "*                                    *" << endl;
    cout << "*  Slots for the Tic-Tac-Toe board:  *" << endl;
    cout << "*                                    *" << endl;
    cout << "*             0 | 1 | 2              *" << endl;
    cout << "*            ---|---|---             *" << endl;
    cout << "*             3 | 4 | 5              *" << endl;
    cout << "*            ---|---|---             *" << endl;
    cout << "*             6 | 7 | 8              *" << endl;
    cout << "*                                    *" << endl;
    cout << "*                                    *" << endl;
    cout << "*        PRESS ENTER TO BEGIN        *" << endl;
    cout << "*                                    *" << endl;
    cout << "**************************************" << endl << endl;
}

//Win or draw message
//PRE: Sends winner (X/O)
//POST: Displays winner (if there is one), if not show DRAW
void winning_message(char p2)
{
    cout << "********************" << endl;
    cout << "*                  *" << endl;
    cout << "*  PLAYER " << p2 << " WINS!  *" << endl;
    cout << "*                  *" << endl;
    cout << "********************" << endl;
}
void draw_message()
{
    cout << "***********" << endl;
    cout << "*         *" << endl;
    cout << "*  DRAW!  *" << endl;
    cout << "*         *" << endl;
    cout << "***********" << endl;
}


//Gets input to begin the game
//PRE: cin is in good state
//POST: Any entered char is returned (including '\n')
char get_char_input()
{
    char inp;
    string line;
    getline (cin,line);
    return line[0];
}

//Checks if the user wants to play again
//PRE: Game is paused until input
//POST: Returns true/false depending on y/Y or n/N input
bool replay_check()
{
    char ch;
    do
    {
        cout << endl << "Do you want to play again? (Y/N) ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (!(ch=='y' || ch=='n' || ch=='Y' || ch=='N'));

    if(ch=='y' || ch=='Y')
        return true;
    else
        return false;
}

//Resets board
//PRE: Board is the same as it ended
//POST: All slots are reset back to ' '
void replay_reset()
{
    for (int reset=0; reset<9; reset++)
    {
        place[reset]=' ';
    }
}
