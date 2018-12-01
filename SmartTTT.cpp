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


//Create a Player Structure
struct Player {
	string name;
	string symbolIndicator;
	char symbol = ' ';
	short wins = 0;
	short losses = 0;
	short ties = 0;
};


//Create a Board class
class Board {
public:

	//The tic tac toe board in string form
	string startingBoard = " . | . | . \n---|---|---\n . | . | . \n---|---|---\n . | . | . ";
	string positionBoard = " 1 | 2 | 3 \n---|---|---\n 4 | 5 | 6 \n---|---|---\n 7 | 8 | 9 ";

	//Used to replace the values on the board
	string update() {
		//Symbol Positions
		char positions[9] = {' '};

		string finalBoard = startingBoard;
		short pos = 0;

		//Used to place all of the symbols or spaces onto the board
		while (finalBoard.find('.') >= 0 && finalBoard.find('.') <= finalBoard.length()) {
			finalBoard[finalBoard.find('.')] = positions[pos];
		}

		return finalBoard;
	}
};

//Create our players
Player player1;
Player player2;

//Create the board
Board board;


//Create a Gui Class
class Gui {
public:
	
    //Overall width of the game board. Must be at least 23 characters long
    short width = 23;

	//Centers a string to the specified length
	string center(string input, unsigned long len) {
		string output;
		short padding = len - input.length();

		if (padding <= 0) {
			return input;
		}

		if (padding%1 == 1) {
			output += " ";
			padding -= 1;
		}

		for (int i = 0; i < padding; i++) {
			if (i < padding/2) {
				output = " " + output;
			}
			else if (i == padding/2) {
				output = " " + output;
				output += input;
			}
			else {
				output += " ";
			}
		}

		return output;
	}

    //Generates the Frame border
    string frame(unsigned long len) {
        //Frame Details
        string border;
        unsigned long pos = 0;

        //Used to generate a nice border box around the title and game content
        for (short i=0; i<len; i++) {
            if (i == 0) {
                border = "+--";
            }
            else if (i == len - 1) {
                border += "--+";
            }
            else {
                border += "-";
            }
        }

        if (border.length() > width) {
            width = border.length();
        }

        return border;
    }

    //Set up the layout
    void layout(const string TITLE) {
        unsigned long len;
		player1.symbolIndicator = player1.name + ": [ ]";
		player2.symbolIndicator = player2.name + ": [ ]";
		len = player1.symbolIndicator.length();
		len += player2.symbolIndicator.length();

		if (TITLE.length() > len) {
			len = TITLE.length();
		}

        cout << frame(len) << endl;
        cout << "| " + TITLE + " |" << endl;
        cout << frame(len) << endl;
        cout << board.positionBoard << endl;
        cout << frame(len) << endl;
        cout << " " + player1.symbolIndicator;
        cout << " | " + player2.symbolIndicator + " " << endl;
        cout << frame(len) << endl;
    }

    //Just returns spaces
    string space(unsigned long len) {
        string spaces;

        for (int i=0; i<len; i++) {
            spaces += " ";
        }

        return spaces;
    }

    //Returns the scoreboard
    string scoreboard(Player player1, Player player2, Board board) {
        stringstream ss;
        string scoreboard;
        unsigned long longestName;

        //Grabs the longest name's length
        if (player1.name.length() >= player2.name.length()) {
            longestName = player1.name.length();
        }
        else {
            longestName = player2.name.length();
        }

        //Prints out Player 1's name and then Player 2's name
        scoreboard += " " + player1.name + " | " + player2.name + "\n";

        //Prints dashes under the names to make it look like a tally board
        for (int i=0; i<player1.name.length() + 2; i++) {
            scoreboard += "-";
        }

        scoreboard += "|";

        for (int i=0; i<player2.name.length() + 2; i++) {
            scoreboard += "-";
        }

        scoreboard += "\n";

        //Start to display scores
        ss << player1.wins;
        scoreboard += " Wins: " + ss.str() + space(10);

        return scoreboard;
    }
};


//Used to draw onto the screen
Gui gui;


//Create a Game Class
class Game {
public:

	//Header title
	string title = "CS141 Multiplayer Tic-Tac-Toe. By: Ryan Stewart";

    //Starts the game
    void start(string &mode) {
        system("clear");

        //Define Symbols
        player1.symbol = 'X';
        player2.symbol = 'O';

        //Get Player Names
        cout << "Enter Player 1's Name: ";

        //Two getlines because for some weird reason the first one takes a newline character
        //I have no idea where that character comes from. Need to investigate
        getline(cin, player1.name);
        getline(cin, player1.name);

        //Check the name length and make sure the player doesn't have the exact same name as the AI
        bool nameOkay = false;
        while (!nameOkay) {
            if (player1.name.length() >= 16) {
                cout << "Please enter a name that's 16 characters or less: ";
                getline(cin, player1.name);
            }
            else if (player1.name == "AI") {
                cout << "Please enter a name that's not called 'AI'. Enter a new name: ";
                getline(cin, player1.name);
            }
            else {
                nameOkay = true;
            }
        }
        nameOkay = false;

        //Check to see if the game mode is multiplayer
        if (mode == "m") {
            cout << "Enter Player 2's Name: ";
            getline(cin, player2.name);

            //Again check the name length and make sure the player doesn't have the exact same name as the AI
            //Also check to see that Player 2's name isn't the same name as Player 1.
            while (!nameOkay) {
                if (player2.name.length() >= 16) {
                    cout << "Please enter a name that's 16 characters or less. Enter a new name: ";
                    getline(cin, player2.name);
                }
                else if (player1.name == "AI") {
                    cout << "Please enter a name that's not called 'AI'. Enter a new name: ";
                    getline(cin, player2.name);
                }
                else if (player2.name == player1.name) {
                    cout << "Please don't choose the exact same name as player1. Enter a new name: ";
                    getline(cin, player2.name);
                }
                else {
                    nameOkay = true;
                }
            }
        }
        //The game mode must be single player
        else {
            player2.name = "AI";
        }

        system("clear");
        gui.layout(title);
    }
};

//Define the game
Game TicTacToe;

int main() {
	//Find which mode to play in
	string gameMode;

	system("clear");
	cout << "Welcome to CS141 Tic-Tac-Toe by Ryan Stewart" << endl;
	cout << "Which game mode would you like to pick? Single player, or multiplayer? (s/m): ";
	cin >> gameMode;

	//Check to see what mode the user wants to play in
	while (gameMode != "s" && gameMode != "m") {
		cout << "That is not a valid option. Please choose (s/m): ";
		cin >> gameMode;
	}

	system("clear");

	//Start the game
	TicTacToe.start(gameMode);

	return 0;

}
