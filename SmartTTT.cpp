/* --- CS141 Tic-Tac-Toe. Created by: Ryan Stewart --- */

#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ctime>

using std::atoi;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::rand;
using std::srand;
using std::string;
using std::stringstream;
using std::stoi;
using std::system;
using std::time;
using std::tolower;
using std::to_string;


//Convert to lowercase
string lower(string input) {
  for (int i = 0; i < input.length(); i++) {
    input[i] = tolower(input[i]);
  }
  return input;
}


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

    //Set this initially to show all possible moves
    string currentBoard = positionBoard;

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
        pos++;
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
    string center(string input, unsigned long len, char dir) {
      string output;
      short padding = len - input.length();

      if (padding <= 0) {
        return input;
      }

      if (padding%1 == 1 && 'l') {
        output += " ";
        padding -= 1;
      }

      for (int i = 0; i < padding; i++) {
        if (i < padding/2) {
          output = " " + output;
        }
        else if (i == padding/2 && dir == 'l') {
          output = " " + output;
          output += input;
        }
        else if (i == padding/2 && dir == 'r') {
          output += output + " ";
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
    void layout(const string TITLE, string gameBoard) {
      unsigned long len = 11;
      stringstream ss;
      if (player1.turn) {
        player1.symbolIndicator = player1.name + ": [X] W:";
        ss << player1.wins;
        player1.symbolIndicator += ss.str() + " L:";
        ss.str("");
        ss << player1.losses;
        player1.symbolIndicator += ss.str() + " T:";
        ss.str("");
        ss << player1.ties;
        player1.symbolIndicator += ss.str();

        player2.symbolIndicator = player2.name + ": [ ] W:";
        ss.str("");
        ss << player2.wins;
        player2.symbolIndicator += ss.str() + " L:";
        ss.str("");
        ss << player2.losses;
        player2.symbolIndicator += ss.str() + " T:";
        ss.str("");
        ss << player2.ties;
        player2.symbolIndicator += ss.str();
      }
      else {
        player1.symbolIndicator = player1.name + ": [ ] W:";
        ss << player1.wins;
        player1.symbolIndicator += ss.str() + " L:";
        ss.str("");
        ss << player1.losses;
        player1.symbolIndicator += ss.str() + " T:";
        ss.str("");
        ss << player1.ties;
        player1.symbolIndicator += ss.str();

        player2.symbolIndicator = player2.name + ": [O] W:";
        ss.str("");
        ss << player2.wins;
        player2.symbolIndicator += ss.str() + " L:";
        ss.str("");
        ss << player2.losses;
        player2.symbolIndicator += ss.str() + " T:";
        ss.str("");
        ss << player2.ties;
        player2.symbolIndicator += ss.str();
      }
      len = player1.symbolIndicator.length();
      len += player2.symbolIndicator.length() + 3;

      if (TITLE.length() > len) {
        len = TITLE.length();
      }

      cout << frame(len) << endl;
      cout << "| " + center(TITLE, len, 'l') + " |" << endl;
      cout << frame(len) << endl;
      cout << gameBoard << endl;
      cout << frame(len) << endl;

      /* TODO Fix centering correctly. This is annoying and hard */
      
      //Attempt to center the player names (probably fail though)
      if (player1.name.length()%2 == 1 && player2.name.length()%2 == 0) {
        cout << "| " + center(player1.symbolIndicator, len/2 - 2, 'l');
        cout << " | " + center(player2.symbolIndicator, len/2 - 1, 'r') + " |" << endl;
      }
      else if (player1.name.length()%2 == 0 && player2.name.length()%2 == 1) {
        cout << "| " + center(player1.symbolIndicator, len/2 - 1, 'l');
        cout << " | " + center(player2.symbolIndicator, len/2 - 2, 'r') + " |" << endl;
      }
      else {
        cout << "| " + center(player1.symbolIndicator, len/2 - 1, 'l');
        cout << " | " + center(player2.symbolIndicator, len/2 - 1, 'r') + " |" << endl;
      }
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

    /* This doesn't get used
    //Returns the scoreboard
    string scoreboard() {
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
      scoreboard += " W: " + ss.str() + space(10) + "|";
      ss.str("");
      ss << player2.wins;
      scoreboard +=" W: " + ss.str() + "\n";
      ss.str("");
      ss << player1.losses;
      scoreboard += " L: " + ss.str() + space(10) + "|";
      ss.str("");
      ss << player2.losses;
      scoreboard +=" L: " + ss.str() + "\n";
      ss.str("");
      ss << player1.ties;
      scoreboard += " T: " + ss.str() + space(10) + "|";
      ss.str("");
      ss << player2.ties;
      scoreboard +=" T: " + ss.str() + "\n";
      ss.str("");

      return scoreboard;
    }
    */
};


//Used to draw onto the screen
Gui gui;


//Create a Game Class
class Game {
  public:

    //Header title
    string title = "CS141 Tic-Tac-Toe. By: Ryan Stewart";

    //Game mode being played
    char gamemode = 's';

    //Check whether the game is over or not
    string status = "playing";

    //Initialize game state
    int gameState[9] = {0};

    //Define a move
    struct Move {
      int pos;
      int row;
      int column;
      bool right;
      bool left;

      //Initialize the values
      Move() {
        pos = 0;
        row = 0;
        column = 0;
        right = false;
        left = false;
      }
    };

    //Define a score
    struct Score{
      int max;
      int min;
      int row[3];
      int column[3];
      int diagonal[2];

      //Initialize the values
      Score() {
        max = 0;
        for (int i = 0; i < 3; i++) {
          row[i] = 0;
          column[i] = 0;
          diagonal[i] = 0;
        }
      }
    };

    //Create them
    Score score;
    Move move;

    bool playAgain() {
      string input;

      cout << "Do you want to keep playing? (Y/n): ";
      getline(cin, input);
      input = lower(input);

      while (true) {
        if (lower(input) == "yes" || lower(input) == "y") {
          return true;
        }
        if (lower(input) == "no" || lower(input) == "n") {
          return false;
        }
        else {
          cout << "Please enter either yes or no: ";
          getline(cin, input);
          input = lower(input);
        }
      }
    }
    //Play the game
    void play() {
      bool keepPlaying = true;
      long random = 0;

      //Make sure the game keeps going unless the players want it to end
      while (keepPlaying) {
        //Choose a random number
        random = rand();

        //Tell both players it's not their turn
        player1.turn = false;
        player2.turn = false;

        //Pick a random player to start
        if (random%10 < 5) {
          player1.turn = true;
        }
        else {
          player2.turn = true;
        }

        //Define a winner string for later
        string winner;

        //Make sure the game is playing again
        status = "playing";

        //Reset all of the spaces on the board
        board.initialize();

        //Reset the game state
        for (int i = 0; i < 9; i++) {
          gameState[i] = 0;
        }

        //Reset the game score and move tracker
        move.pos = 0;
        move.row = 0;
        move.column = 0;
        move.right = false;
        move.left = true;

        score.max = 0;

        for (int i = 0; i < 3; i++) {
          if (i < 2) {
          score.diagonal[i] = 0;
          }
          score.row[i] = 0;
          score.column[i] = 0;
        }

        //Redraw the board
        if (player1.wins + player1.losses + player1.ties != 0) {
          board.currentBoard = board.update(0, ' ');
        }

        //Play the game until it's over
        while (status != "over") {
          //Check whose turn it is and let them take their turn
          if (player1.turn) {
            playTurn(player1);
          }
          else {
            playTurn(player2);
          }

          //Check for a winner
          winner = checkWin(getGameState());

          //If the winner is either of the player's names, it will print that player wins
          if (player1.name == winner) {
            //Update game status and scores
            status = "over";
            player1.wins += 1;
            player2.losses += 1;

            //Redraw the board, state who wins and ask to play again
            system("clear");
            gui.layout(title, board.currentBoard);
            cout << player1.name + " wins" << endl;
            if (!playAgain()) {
              keepPlaying = false;
            }
          }
          else if (player2.name == winner) {
            //Update game status and scores
            status = "over";
            player2.wins += 1;
            player1.losses += 1;

            //Redraw the board, state who wins and ask to play again
            system("clear");
            gui.layout(title, board.currentBoard);
            cout << player2.name + " wins" << endl;
            if (!playAgain()) {
              keepPlaying = false;
            }
          }
          //Otherwise check to see if the game is a tie or still in progress
          else {
            bool okay = true;
            short positions = 0;

            while (okay) {
              //Don't go through too many iterations and seg fault
              if (positions >= 9) {
                okay = false;
              }
              //If the board has a space the game is still in progress
              else if (board.positions[positions] == ' ') {
                okay = false;
              }
              //Check for the next gamespace
              else {
                positions++;
              }
            }
            //The game must be a tie since no spaces existed
            if (positions >= 9) {
              //Update the status and scores
              status = "over";
              player1.ties += 1;
              player2.ties += 1;

              //Redraw the board, state who wins and ask to play again
              system("clear");
              gui.layout(title, board.currentBoard);
              cout << "It was a tie" << endl;
              if (!playAgain()) {
                keepPlaying = false;
              }
            }
          }
        }
      }
    }

    //Check if winner
    string checkWin(int gameState[9]) {
      int row = 0;
      int column = 0;
      int leftDiagonal = 0;
      int rightDiagonal = 0;

      for (short i = 0; i < 3; i++) {
        //Check to see if there are 3 in a row horizontally
        row = gameState[3*i] + gameState[3*i+1] + gameState[3*i+2];
        if (row == 15) {
          return player1.name;
        }
        else if (row == -6) {
          return player2.name;
        }
        cout << row << endl;

        //Check to see if there are 3 in a row vertically
        column = gameState[i] + gameState[i+3] + gameState[i+6];
        if (column == 15) {
          return player1.name;
        }
        else if (column == -6) {
          return player2.name;
        }
      }

      //Check to see if there are 3 in a row diagonal to the right
      rightDiagonal = gameState[0] + gameState[4] + gameState[8];
      if (rightDiagonal == 15) {
        return player1.name;
      }
      else if (rightDiagonal == -6) {
        return player2.name;
      }

      //Check to see if there are 3 in a row diagonal to the left
      leftDiagonal = gameState[2] + gameState[4] + gameState[6];
      if (leftDiagonal == 15) {
        return player1.name;
      }
      else if (leftDiagonal == -6) {
        return player2.name;
      }

      return "none";
    }

    //Starts the game
    void start(string mode) {
      system("clear");

      //Define Symbols
      player1.symbol = 'X';
      player2.symbol = 'O';

      if (player1.name == "") {
        //Get Player Names
        cout << "Enter Player 1's Name: ";

        //Get the player's name
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
        play();
      }
      else {
        gamemode = 's';

        //Player 2 is named AI
        player2.name = "AI";

        play();
      }
    }

    //Used to place a move as a player
    void playTurn(Player &player) {
      string loc;
      bool okay = false;

      //Clear the screen, draw the board and ask for movement input
      system("clear");
      gui.layout(title, board.currentBoard);

      if (player.name != "AI") {
        cout << "It is " + player.name + "'s turn" << endl;
        cout << "Type 'p' or 'positions' for help on how to place tiles on the board" << endl;
        cout << "Please enter a location to place your move: ";
        getline(cin, loc);

        //While the input is invalid loop
        while (!okay) {
          if (lower(loc) == "position" || lower(loc) == "positions" || lower(loc) == "p") {
            //Clear the screen, draw the board and ask for movement input
            system("clear");
            gui.layout(title, board.positionBoard);
            cout << "Displaying Positions. Please wait." << endl;
            sleep(2);

            //Clear the screen, draw the board and ask for movement input
            system("clear");
            gui.layout(title, board.currentBoard);
            cout << "It is " + player.name + "'s turn" << endl;
            cout << "Type 'p' or 'positions' for help on how to place tiles on the board" << endl;
            cout << "Please enter a location to place your move: ";
            getline(cin, loc);
          }
          //Make sure the input isn't longer than 1
          else if (loc.length() != 1) {
            cout << "Please enter a valid location to place your move: ";
            getline(cin, loc);
          }
          //Convert the ascii character to an integer
          else if (atoi(loc.c_str()) < 1 || atoi(loc.c_str()) > 9) {
            cout << "Please enter a valid location to place your move: ";
            getline(cin, loc);
          }
          //Check to see if a symbol is already in that spot
          else if (board.positions[atoi(loc.c_str())-1] != ' ') {
            cout << "Please enter a valid location to place your move: ";
            getline(cin, loc);
          }
          //Break the loop
          else {
            okay = true;
          }
        }

        //Tell the player it's not their turn anymore
        player.turn = false;

        //Check to see which player and change the opposite's turn state to true
        if (&player == &player1) {
          player2.turn = true;
        }
        else {
          player1.turn = true;
        }

        //Update the current board to after placing the move
        board.currentBoard = board.update(atoi(loc.c_str()) - 1, player.symbol);
      }
      //Run the turn for the AI
      else {
        player2.turn = false;
        player1.turn = true;
        board.currentBoard = board.update(generateMove(getGameState()), player.symbol);
      }
    }

    int * getGameState() {
      //Check each row and column on the board
      for (int i = 0; i < 9; i++) {
        if (board.positions[i] == player1.symbol) {
          gameState[i] = 5;
        }
        else if (board.positions[i] == player2.symbol) {
          gameState[i] = -2;
        }
      }
      return gameState;
    }

    void getBestScore() {
      //Assign the row and column scores
      for (int i = 0; i < 3; i++) {
        score.row[i] = gameState[3*i] + gameState[3*i+1] + gameState[3*i+2];
        score.column[i] = gameState[i] + gameState[i+3] + gameState[i+6];
      }

      //Assign the diagonal states
      score.diagonal[0] = gameState[0] + gameState[4] + gameState[8];
      score.diagonal[1] = gameState[2] + gameState[4] + gameState[6];

      //Check through scores
      bool okay = true;
      int i = 0;
      while (okay && i < 3) {
        if (i  < 2) {
          //Check to see if it can win
          if (okay && score.diagonal[i] == -4) {
            score.min = score.diagonal[i];
            //Check for right diagonal case
            if (i == 0) {
              move.right = true;
              move.left = false;
              move.row = 0;
              move.column = 0;
            }
            //Check for left diagonal case
            else {
              move.left = true;
              move.right = false;
              move.row = 0;
              move.column = 0;
            }
            okay = false;
          }
          //Check to see if the minimum score is greater than current score for the diagonal
          else if (okay && score.min > score.diagonal[i]) {
            score.min = score.diagonal[i];
            //Check for right diagonal case
            if (i == 0) {
              move.right = true;
              move.left = false;
              move.row = 0;
              move.column = 0;
            }
            //Check for left diagonal case
            else {
              move.left = true;
              move.right = false;
              move.row = 0;
              move.column = 0;
            }
          }
          //If the minumum score on a case is the same as in other cases, don't reset the others
          else if (okay && score.min == score.diagonal[i]) {
            //Check for right diagonal case
            if (i == 0) {
              move.right = true;
            }
            //Check for left diagonal case
            else {
              move.left = true;
            }
          }
          //Check to see if the maximum score is less than current score for the diagonal
          else if (okay && score.max < score.diagonal[i]) {
            score.max = score.diagonal[i];
            //Check for right diagonal case
            if (i == 0) {
              move.right = true;
              move.left = false;
              move.row = 0;
              move.column = 0;
            }
            //Check for left diagonal case
            else {
              move.left = true;
              move.right = false;
              move.row = 0;
              move.column = 0;
            }
          }
          //If the maximum score on a case is the same as in other cases, don't reset the others
          else if (okay && score.max == score.diagonal[i]) {
            //Check for right diagonal case
            if (i == 0) {
              move.right = true;
            }
            //Check for left diagonal case
            else {
              move.left = true;
            }
          }
        }

        //Check to see if it can win
        if (okay && score.row[i] == -4) {
          score.min = score.row[i];
          move.row = i + 1;
          move.column = 0;
          move.right = false;
          move.left = false;
          okay = false;
        }
        //Check to see if the minimum score is less than current score for the row
        else if (okay && score.min > score.row[i]) {
          score.min = score.row[i];
          move.row = i + 1;
          move.column = 0;
          move.right = false;
          move.left = false;
        }
        //If the minumum score on a case is the same as in other cases, don't reset the others
        else if (okay  && score.min == score.row[i]) {
          move.row = i + 1;
        }
        //Check to see if the maximum score is less than current score for the row
        else if (okay  && score.max < score.row[i]) {
          score.max = score.row[i];
          move.row = i + 1;
          move.column = 0;
          move.right = false;
          move.left = false;
        }
        //If the maximum score on a case is the same as in other cases, don't reset the others
        else if (okay  && score.max == score.row[i]) {
          move.row = i + 1;
        }

        //Check to see if it can win
        if (okay && score.row[i] == -4) {
          score.min = score.row[i];
          move.column = i + 1;
          move.row = 0;
          move.right = false;
          move.left = false;
          okay = false;
        }
        //Check to see if the minimum score is less than current score for the row
        else if (okay  && score.min > score.column[i]) {
          score.min = score.column[i];
          move.column = i + 1;
          move.row = 0;
          move.right = false;
          move.left = false;
        }
        //If the minimum score on a case is the same as in other cases, don't reset the others
        else if (okay  && score.min == score.column[i]) {
          move.column = i + 1;
        }
        //Check to see if the maximum score is less than current score for the row
        else if (okay  && score.max < score.column[i]) {
          score.max = score.column[i];
          move.column = i + 1;
          move.row = 0;
          move.right = false;
          move.left = false;
        }
        //If the minimum score on a case is the same as in other cases, don't reset the others
        else if (okay  && score.max == score.column[i]) {
          move.column = i + 1;
        }
        i++;
      }

    }

    int generateMove(int gameState[9]) {
      //Get possible moves to move to
      string possibleMoves;
      int movePosition = 0;
      long random = 0;

      getBestScore();

      //Get possible moves in a row
      if (move.row != 0) {
        for (int i = 3*(move.row-1); i < 3*(move.row-1) + 3; i++) {
          if (board.positions[i] != player1.symbol && board.positions[i] != player2.symbol) {
            possibleMoves += to_string(i);
          }
        }
      }

      //Get possible moves in a column
      if (move.column != 0) {
        for (int i = 0; i < 3; i++) {
          if (board.positions[move.column - 1 + 3*i] != player1.symbol) {
            if (board.positions[move.column - 1 + 3*i] != player2.symbol) {
              possibleMoves += to_string(move.column - 1 + 3*i);
            }
          }
        }
      }

      //Get possible moves for right diagonal
      if (move.right) {
        if (board.positions[0] != player1.symbol && board.positions[0] != player2.symbol) {
            possibleMoves += to_string(0);
        }
        if (board.positions[4] != player1.symbol && board.positions[4] != player2.symbol) {
            possibleMoves += to_string(4);
        }
        if (board.positions[8] != player1.symbol && board.positions[8] != player2.symbol) {
            possibleMoves += to_string(8);
        }
      }

      //Get possible moves for left diagonal
      if (move.left) {
        if (board.positions[2] != player1.symbol && board.positions[2] != player2.symbol) {
            possibleMoves += to_string(2);
        }
        if (board.positions[4] != player1.symbol && board.positions[4] != player2.symbol) {
            possibleMoves += to_string(4);
        }
        if (board.positions[6] != player1.symbol && board.positions[6] != player2.symbol) {
            possibleMoves += to_string(6);
        }
      }

      //If no way to predict moves, just take a random one in an open spot
      if (possibleMoves == "") {
        for (int i = 0; i < 9; i++) {
          if (board.positions[i] != player1.symbol && board.positions[i] != player2.symbol) {
            possibleMoves += to_string(i);
          }
        }
      }

      //Pick a random move in the list
      random = rand()%possibleMoves.length();

      //Set the move position to the character
      //The 0 charachter allows the ascii lines up right with the position on the board
      //It was not working with atoi or stoi for some reason so I did this
      movePosition = possibleMoves[random] - '0';

      return movePosition;
    }
};


int main() {

  //Define the game
  Game TicTacToe;

  //Find which mode to play in
  string gameMode;

  //Get the gamemode
  system("clear");
  cout << "Welcome to CS141 Tic-Tac-Toe by Ryan Stewart" << endl;
  cout << "Which game mode would you like to pick? Single player, or multiplayer? (s/m): ";
  getline(cin, gameMode);

  gameMode = lower(gameMode);
  //Check to see what mode the user wants to play in
  while (gameMode != "s" && gameMode != "m") {
    cout << "That is not a valid option. Please choose (s/m): ";
    getline(cin, gameMode);
  }

  system("clear");

  //Use current time as seed for random number generator
  srand(time(nullptr));

  //Start the game
  TicTacToe.start(gameMode);

  return 0;

}
