#include<iostream>
#include<string>

/* --- Defined imports from the standard library --- */

using std::cin;
using std::cout;
using std::endl;
using std::string;


// Used to clear the screen
void clear()
{
    cout << "\033[2J\033[1;1H";
}

//Create a Player Structure
struct Player {
    string name;
    char symbol = ' ';
};

class Board {
public:
    //Symbol Positions
    char positions[9] = {' '};

    //The tic tac toe board in string form
    string starting_board = " . | . | . \n---|---|---\n . | . | . \n---|---|---\n . | . | . ";

    //Used to replace the values on the board
    string update(const bool initial=false)
    {
        short pos = 0;
        string final_board;
        if (initial)
        {
            for (char c : positions)
            {
                c = ' ';
            }
        }
        for (char c : starting_board)
        {
            if (c == '.')
            {
                c = positions[pos];
            }
            final_board += c;
        }
        return final_board;
    }
};

//Create a Game Object
class Game {
public:
    Board Game_Board;
    Player Player1;
    Player Player2;

    //Set up the layout
    void layout(const string &TITLE)
    {
        //Frame Details
        string frame;

        //Used to generate a nice border box around the title and game content
        for (short i=0; i<TITLE.length(); i++)
        {
            if (i == 0)
            {
                frame = "+--";
            }
            else if (i == TITLE.length() - 1)
            {
                frame += "--+";
            }
            else
            {
                frame += "-";
            }
        }

        cout << frame << endl;
        cout << "| " + TITLE + " |" << endl;
        cout << frame << endl;
        cout << Game_Board.update(true) << endl;
        cout << frame << endl;
        cout << "  " << Player1.name << ", " << Player2.name << endl;
        cout << frame << endl;
    }

    void start() {
        clear();
        cout << "Enter Player 1's Name: ";
        cin >> Player1.name;
        cout << "Choose your symbol " + Player1.name + ": ";
        cin >> Player1.symbol;

        cout << "Enter Player 2's Name: ";
        cin >> Player2.name;
        cout << "Choose your symbol " + Player2.name + ": ";
        cin >> Player2.symbol;
        clear();
        layout("CS141 Multiplayer Tic-Tac-Toe. By: Ryan Stewart");
    }
};

int main()
{
    Game TicTacToe;
    TicTacToe.start();
    return 0;

}