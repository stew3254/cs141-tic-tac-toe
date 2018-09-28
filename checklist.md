# CS141 – Term Project
Due Monday December 10 at 11:59PM 

----

## OBJECTIVE:
For your term project you will build a tic tac toe game called SmartTTT. If you are not familiar with the tic tac toe game, you can read this Wikipedia article: https://en.wikipedia.org/wiki/Tictactoe

### Your tic tac toe game must meet the following criteria:
- [ ] When your program starts you must allow two types of games:
	1. Game 1: Player vs Player. In this version the user can play against another user using your game. In this version of the game, player 1 will use X and player 2 will use O.
	2. Game 2: Player vs AI. In this version the user will be playing against the AI that you create. In this version of the game, player 1 will use X and the AI you create will use O.
- [X] Your game must use the standard tic tac toe board, i.e. there will be 9 empty spaces on the board.
- [X] You must draw the game board on the screen, you can use simple _ or – symbols to draw the game board. 
- [X] Your game board and player moves must be stored in an appropriate data structure, for example a 2D array can be used to store both the game boardand player moves.
- [ ] Your game must not allow a player or the AI to enter two X’s or two O’s in a row, as this means one player has not made a turn. If a user enters a letter other than X, x, O, or o then you must indicate that you do not recognize the command. 
- [ ] After each move is made, your game must display the current board with the moves in place. You  must  show  a  label  on  the  screen  to  indicate  what  shape  is  being  used  by which player.
- [ ] When  playing  in  Game  2  mode,  i.e. Player  vs AI  you  must  implement  an intelligent algorithm that decides the best move for the AI. Your AI is trying to win, so don’t make the AI too easy.
- [ ] Your  game must evaluate  if  the  win  criteria  has  been metafter  each  move,  if the  win criteria has not been met then the game proceeds. If the win criteria has been met, then the game is over and you must show the winner. This could be Player 1 or Player 2 in Game 1, or Player 1 or AI in Game 2. If no win criteria has been met, and there are no spaces left then the game is over. If the game is over, ask the user if they want to play again. If the user wishes to play again, then go back to Step 1 above. 
- [ ] Your  program  must  have  functions  and  data  structures  to  facilitate  the  game  play. Programs with no functions or data structures will be given a 0. 

----

## GRADING CRITERIA:
The programming project is worth 10% of thecourse gradeand will be graded out of 100 points.

The grading will be done using the following scheme:
**Criteria** | **Points out of 100**
---- | ----
Game AI algorithm | 25
Data structure and functions | 20
Descriptive comments to describe program flow and function descriptions provide input, output, and error states | 10
Compiles with no errors | 20
Compiles with no warnings | 5
Gracefully handles errors and does not crash the program | 10
User friendly interface for playing the game. | 10
Total | 100

**SUBMISSION INSTRUCTIONS:**

Your program must be submitted via Polaris as follows:
1. Make sure your game is called SmartTTT.cpp.
2. Type the following to submit your game: `cp SmartTT.cpp /afs/cu/class/cs141/f18/clarksonid` where clarksonid is your Clarkson username
