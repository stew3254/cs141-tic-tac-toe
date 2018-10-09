/* --- CS141 Multiplayer Tic-Tac-Toe. Created by: Ryan Stewart --- */

#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::isprint;
using std::string;
using std::system;
using std::stringstream;


//Create a Game Object
class Game {
public:

    //Create a Player Structure
    struct Player {
        string name;
        char symbol = ' ';
        short wins = 0;
        short losses = 0;
        short ties = 0;
    };

    //Create our players
    Player Player1;
    Player Player2;

    //Generates the Frame border
    string frame(const unsigned long len)
    {
        //Frame Details
        string border;
        unsigned long pos = 0;

        //Used to generate a nice border box around the title and game content
        for (short i=0; i<len; i++)
        {
            if (i == 0)
            {
                border = "+--";
            }
            else if (i == len - 1)
            {
                border += "--+";
            }
            else
            {
                border += "-";
            }
        }
        return border;
    }

    //Set up the layout
    void layout(const string &title)
    {
        unsigned long len = title.length();
        cout << frame(len) << endl;
        cout << "| " + title + " |" << endl;
        cout << frame(len) << endl;
        cout << update() << endl;
        cout << frame(len) << endl;
        cout << "  " << Player1.name << ", " << Player2.name << endl;
        cout << frame(len) << endl;
    }

    //Just returns spaces
    string space(unsigned long len) {
        string spaces;

        for (int i=0; i<len; i++)
        {
            spaces += " ";
        }
        return spaces;
    }

    //Returns the scoreboard
    string scoreboard()
    {
        stringstream ss;
        string board;
        unsigned long longestName;

        if (Player1.name.length() >= Player2.name.length())
        {
            longestName = Player1.name.length();
        }
        else
        {
            longestName = Player2.name.length();
        }

        board += " " + Player1.name + " | " + Player2.name + "\n";
        for (int i=0; i<Player1.name.length() + 2; i++)
        {
            board += "-";
        }
        board += "|";
        for (int i=0; i<Player2.name.length() + 2; i++)
        {
            board += "-";
        }
        board += "\n";
        ss << Player1.wins;
        board += " Wins: " + ss.str() + space(10);
        return board;
    }

    //Used to replace the values on the board
    string update()
    {
        //Symbol Positions
        char positions[9] = {' '};

        //The tic tac toe board in string form
        string startingBoard = " . | . | . \n---|---|---\n . | . | . \n---|---|---\n . | . | . ";
        short pos = 0;
        string finalBoard = startingBoard;

        //Used to place all of the symbols or spaces onto the board
        while (finalBoard.find('.') >= 0 && finalBoard.find('.') <= finalBoard.length())
        {
            finalBoard[finalBoard.find('.')] = positions[pos];
        }
        return finalBoard;
    }

    //Starts the game
    void start(string &mode) {
        system("clear");

        //Define Symbols
        Player1.symbol = 'X';
        Player2.symbol = 'O';

        //Get Player Names
        cout << "Enter Player 1's Name: ";

        //Two getlines because for some weird reason the first one takes a newline character
        //I have no idea where that character comes from. Need to investigate
        getline(cin, Player1.name);
        getline(cin, Player1.name);

        //Again check length and then make sure they don't have the same name as Player1
        bool nameOkay = false;
        while (!nameOkay)
        {
            if (Player1.name.length() >= 16)
            {
                cout << "Please enter a name that's 16 characters or less: ";
                getline(cin, Player1.name);
            }
            else if (Player1.name == "AI")
            {
                cout << "Please enter a name that's not called 'AI'. Enter a new name: ";
                getline(cin, Player1.name);
            }
            else
            {
                nameOkay = true;
            }
        }
        nameOkay = false;

        if (mode == "m")
        {
            cout << "Enter Player 2's Name: ";
            getline(cin, Player2.name);

            while (!nameOkay)
            {
                if (Player2.name.length() >= 16)
                {
                    cout << "Please enter a name that's 16 characters or less. Enter a new name: ";
                    getline(cin, Player2.name);
                }
                else if (Player1.name == "AI")
                {
                    cout << "Please enter a name that's not called 'AI'. Enter a new name: ";
                    getline(cin, Player2.name);
                }
                else if (Player2.name == Player1.name)
                {
                    cout << "Please don't choose the exact same name as Player1. Enter a new name: ";
                    getline(cin, Player2.name);
                }
                else
                {
                    nameOkay = true;
                }
            }
        }
        else
        {
            Player2.name = "AI";
        }

        system("clear");
        layout("CS141 Multiplayer Tic-Tac-Toe. By: Ryan Stewart");
    }
};

int main()
{
    Game TicTacToe;
    string gameMode;

    system("clear");
    cout << "Welcome to CS141 Tic-Tac-Toe by Ryan Stewart" << endl;
    cout << "Which game mode would you like to pick? Single player, or multiplayer? (s/m): ";
    cin >> gameMode;

    while (gameMode != "s" && gameMode != "m")
    {
        cout << "That is not a valid option. Please choose (s/m): ";
        cin >> gameMode;
    }
    
    system("clear");
    TicTacToe.start(gameMode);
    return 0;

}
