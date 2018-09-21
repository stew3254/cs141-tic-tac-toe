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


//Create a Game Object
class Game {
    public:
        Player Player1;
        Player Player2;

        //Set up the game board
        string board()
        {
            //The tic tac toe board in string form. (Maybe will make this an array later)
            string starting_board = "   |   |   \n---|---|---\n   |   |   \n---|---|---\n   |   |   ";

            return starting_board;
        }

        //Set up the layout
        void layout(const string &TITLE)
        {
            //Frame Details
            string frame;

            //Used to generate a nice border box around the title and game content
            for (short int i=0; i<TITLE.length(); i++)
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
            cout << board() << endl;
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