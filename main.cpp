/* --- CS141 Multiplayer Tic-Tac-Toe. Created by: Ryan Stewart --- */

#include<iostream>
#include<string>
#include<cctype>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::isprint;
using std::string;


// Used to clear the screen
void clear()
{
    cout << "\033[2J\033[1;1H";
}

//Create a Player Structure
struct Player {
    string name;
    string symbol = " ";
};

//Create the Game Board
class Board {
public:
    //Symbol Positions
    char positions[9] = {' '};

    //The tic tac toe board in string form
    string startingBoard = " . | . | . \n---|---|---\n . | . | . \n---|---|---\n . | . | . ";

    //Used to replace the values on the board
    string update()
    {
        short pos = 0;
        string finalBoard = startingBoard;

        //Used to place all of the symbols or spaces onto the board
        while (finalBoard.find('.') >= 0 && finalBoard.find('.') <= finalBoard.length())
        {
            finalBoard[finalBoard.find('.')] = positions[pos];
        }
        return finalBoard;
    }
};

//Create a Game Object
class Game {
public:
    Board GameBoard;
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
        cout << GameBoard.update() << endl;
        cout << frame << endl;
        cout << "  " << Player1.name << ", " << Player2.name << endl;
        cout << frame << endl;
    }

    void start() {
        clear();

        //Get Player Names and Symbols
        cout << "Enter Player 1's Name: ";
        getline(cin, Player1.name);

        //Make sure the name isn't too long
        while (Player1.name.length() >= 20)
        {
            cout << "Please enter a name that's 20 characters or less: ";
            getline(cin, Player1.name);
        }
        cout << "Choose your symbol " + Player1.name + ": ";
        getline(cin, Player1.symbol);

        //Check to make sure that the symbol is printable
        bool symbolOkay = false;
        while (!symbolOkay)
        {
            if (Player1.symbol.length() != 1)
            {
                cout << "Symbol must be only one character. Enter a new symbol: ";
                getline(cin, Player1.symbol);
            }
            else if (!isprint(Player1.symbol[0]))
            {
                cout << "Symbol must be a printable character. Enter a new symbol: ";
                getline(cin, Player1.symbol);
            }
            else if (Player1.symbol == " ")
            {
                cout << "Symbol cannot be a space. Enter a new symbol: ";
                getline(cin, Player1.symbol);
            }
            else
            {
                symbolOkay = true;
            }
        }

        cout << "Enter Player 2's Name: ";
        getline(cin, Player2.name);

        //Again check length and then make sure they don't have the same name as Player1
        bool nameOkay = false;
        while (!nameOkay)
        {
            if (Player2.name.length() >= 20)
            {
                cout << "Please enter a name that's 20 characters or less. Enter a new name: ";
                getline(cin, Player2.name);
            }
            else if (Player2.name == Player1.name)
            {
                cout << "Please don't choose the same name as Player1. Enter a new name: ";
                getline(cin, Player2.name);
            }
            else
            {
                nameOkay = true;
            }
        }
        cout << "Choose your symbol " + Player2.name + ": ";
        getline(cin, Player2.symbol);

        //Check to make sure that the symbol is printable and not the same as the other player's
        symbolOkay = false;
        while (!symbolOkay)
        {
            if (Player2.symbol.length() != 1)
            {
                cout << "Symbol must be only one character. Enter a new symbol: ";
                getline(cin, Player2.symbol);
            }
            else if (!isprint(Player2.symbol[0]))
            {
                cout << "Symbol must be a printable character. Enter a new symbol: ";
                getline(cin, Player2.symbol);
            }
            else if (Player2.symbol == " ")
            {
                cout << "Symbol cannot be a space. Enter a new symbol: ";
                getline(cin, Player2.symbol);
            }
            else if (Player2.symbol == Player1.symbol)
            {
                cout << "Symbol cannot be the same as the other player. Enter a new symbol: ";
                getline(cin, Player2.symbol);
            }
            else
            {
                symbolOkay = true;
            }
        }
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