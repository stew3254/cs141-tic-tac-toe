/* --- CS141 Multiplayer Tic-Tac-Toe. Created by: Ryan Stewart --- */

#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>

using std::atoi;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::system;
using std::stringstream;
using std::tolower;


//Create a Player Structure
struct Player {
	string name;
	string symbolIndicator;
	bool turn;
	char symbol = ' ';
	short wins = 0;
	short losses = 0;
	short ties = 0;
};


//Create a Board class
class Board {
public:

	//Symbol Positions
	char positions[9];

	//The tic tac toe board in string form
	string startingBoard = " . | . | . \n---|---|---\n . | . | . \n---|---|---\n . | . | . ";
	string positionBoard = " 1 | 2 | 3 \n---|---|---\n 4 | 5 | 6 \n---|---|---\n 7 | 8 | 9 ";

	//Initialize all of the contents of positions (or clear the board)
	void initialize() {
		for (int i = 0; i < 9; i++) {
			positions[i] = ' ';
		}
	}

	//Used to replace the values on the board
	string update(short loc, char symbol) {
		positions[loc] = symbol;
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

	//Game mode being played
	char gamemode = 's';

    //Starts the game
    void start(string mode) {
        system("clear");

        //Define Symbols
        player1.symbol = 'X';
        player2.symbol = 'O';

		if (player1.name == "") {
			//Get Player Names
			cout << "Enter Player 1's Name: ";

			//Two getlines because for some weird reason the first one takes a newline character
			//I have no idea where that character comes from. Need to investigate
			getline(cin, player1.name);
			getline(cin, player1.name);

			//Check the name length
			//Make sure the player doesn't have the exact same name as the AI
			//Make sure the player actually enters a name (they can still do spaces though)
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
				else if (player1.name == "") {
					cout << "Please enter a real name: ";
					getline(cin, player1.name);
				}
				else {
					nameOkay = true;
				}
			}
		}

		//Initialize all of the board positions
		board.initialize();

        //Check to see if the game mode is multiplayer
        if (mode == "m") {
			bool nameOkay;
			gamemode = 'm';

			system("clear");
			cout << "Enter Player 2's Name: ";
			getline(cin, player2.name);

			//Again check the name length
			//Make sure the player doesn't have the exact same name as the AI
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
					cout << "Please don't choose the exact same name as player1. ";
					cout << "Enter a new name: ";
					getline(cin, player2.name);
				}
				else {
					nameOkay = true;
				}
			}
		}
		else {
			gamemode = 's';

			//Player 2 is named AI
			player2.name = "AI";

			playTurn(player1);
		}
	}

	//Used to place a move as a player
	void playTurn(Player &player) {
		string loc;
		bool okay;

		//Clear the screen, draw the board and ask for movement input
		system("clear");
		gui.layout(title);

		if (player.name != "AI") {
			cout << "It is " + player.name + "'s turn" << endl;
			cout << "Please enter a location to place your move: ";
			cin >> loc;

			//While the input is invalid loop
			while (!okay) {
				//Make sure the input isn't longer than 1
				if (loc.length() != 1) {
					cout << "Please enter a valid location to place your move: ";
					cin >> loc;
				}
				//Convert the ascii character to an integer
				else if (atoi(loc.c_str()) < 1 || atoi(loc.c_str()) > 9) {
					cout << "Please enter a valid location to place your move: ";
					cin >> loc;
				}
				//Check to see if a symbol is already in that spot
				else if (board.positions[atoi(loc.c_str())-1] != ' ') {
					cout << "Please enter a valid location to place your move: ";
					cin >> loc;
				}
				//Break the loop
				else {
					okay = true;
				}
			}

			//Place the symbol on the board
			board.update(atoi(loc.c_str()), player.symbol);

			//Tell the player it's not their turn anymore
			player.turn = false;

			//Check to see which player and change the opposite's turn state to true
			if (&player == &player1) {
				player2.turn = true;
			}
			else {
				player1.turn = true;
			}
		}
		//Run the turn for the AI
		else {
			player2.turn = false;
			player1.turn = true;
		}
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

	for (int i = 0; i < gameMode.length(); i++) {
		gameMode[i] = tolower(gameMode[i]);
	}
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
