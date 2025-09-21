# Tic-Tac-Toe-6x6-AI
6x6 Tic-Tac-Toe with Easy/Hard AI — SIT102 H1 something awesome project.

# Video DEMO
https://youtu.be/DsJEWtNo6K8

## Overview
This project extends the classic Tic-Tac-Toe into a **6x6 version**, where players must get **four in a row** to win.  
It includes:
- Easy AI (random moves)
- Hard AI (Minimax with heuristics and depth limit)
- Scoreboard across multiple games
- Player name input and replayability
Instructions
1. Requirements

Clang++ compiler (installed with your development environment).
SplashKit library installed and configured on your system.
A terminal or command prompt to compile and run the game.

2. How to Compile

Download or clone this repository to your computer.
Open a terminal in the project folder.
Compile the program with:clang++ game.cpp -l splashkit -o game

3. How to Run

   In the terminal, type:./game
   
When the game starts:

Enter your name.
Choose the AI difficulty:
1 = Easy (Random AI)
2 = Hard (Minimax AI)

Gameplay flow:

Enter moves as two numbers: row column (e.g., 0 2).
The AI will respond with its move.
The board updates after every turn.
The first player to get four in a row (horizontally, vertically, or diagonally) wins.
If the board fills without a winner, the game ends in a draw.

4. Features to Try

Easy AI: Makes random moves, fun and beatable.
Hard AI: Uses Minimax with heuristics and depth-limiting to make smart moves.
Scoreboard: Tracks wins, losses, and draws across multiple rounds.
Input validation: Try entering invalid moves to see how the game handles errors gracefully.

5. End the Game

At the end of each match, you can choose to play again (y) or exit (n).
