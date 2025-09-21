#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define HUMAN 'X'
#define AI 'O'
#define EMPTY ' '
#define SIZE 6
#define WIN 4
#define MAX_DEPTH 3  // depth-limited minimax

// Function prototypes
void printBoard(char board[SIZE][SIZE]);
int isMovesLeft(char board[SIZE][SIZE]);
int checkWin(char board[SIZE][SIZE], char player);
int countSequences(char board[SIZE][SIZE], char player, int n);
int evaluate(char board[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE], int depth, int isMax);
void findBestMove(char board[SIZE][SIZE], int *bestRow, int *bestCol);
void aiMoveRandom(char board[SIZE][SIZE]);
void playerMove(char board[SIZE][SIZE], char playerName[]);
int isDraw(char board[SIZE][SIZE]);

int main() {
    char playerName[50];
    int difficulty;
    int humanScore=0, aiScore=0, drawScore=0;
    char playAgain='y';

    srand(time(0));

    printf("Welcome to 6x6 Tic-Tac-Toe!\n");
    printf("Enter your name: ");
    scanf(" %[^\n]", playerName);

    printf("Hello %s! You are X, AI is O.\n", playerName);
    printf("Board rows and columns are numbered 0 to %d.\n", SIZE-1);
    printf("Choose difficulty: 1 = Easy (Random AI), 2 = Hard (Smart AI): ");
    while(scanf("%d",&difficulty)!=1 || (difficulty!=1 && difficulty!=2)){
        printf("Invalid input. Enter 1 for Easy or 2 for Hard: ");
        while(getchar()!='\n');
    }

    while(playAgain=='y' || playAgain=='Y'){
        char board[SIZE][SIZE];
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                board[i][j]=EMPTY;

        while(1){
            printBoard(board);
            playerMove(board, playerName);
            if(checkWin(board,HUMAN)){
                printBoard(board);
                printf("Congratulations %s! You win!\n", playerName);
                humanScore++;
                break;
            }
            if(isDraw(board)){
                printBoard(board);
                printf("It's a draw!\n");
                drawScore++;
                break;
            }

            int aiRow, aiCol;
            if(difficulty==1) aiMoveRandom(board);
            else{
                findBestMove(board, &aiRow, &aiCol);
                board[aiRow][aiCol]=AI;
                printf("AI has played at row %d, column %d.\n", aiRow, aiCol);
            }

            if(checkWin(board,AI)){
                printBoard(board);
                printf("AI wins! Better luck next time, %s.\n", playerName);
                aiScore++;
                break;
            }
            if(isDraw(board)){
                printBoard(board);
                printf("It's a draw!\n");
                drawScore++;
                break;
            }
        }

        printf("\nScoreboard:\n%s: %d\nAI: %d\nDraws: %d\n", playerName, humanScore, aiScore, drawScore);
        printf("Do you want to play again? (y/n): ");
        while(getchar()!='\n'); // clear buffer
        scanf("%c",&playAgain);
    }

    printf("Final Scoreboard:\n%s: %d\nAI: %d\nDraws: %d\n", playerName, humanScore, aiScore, drawScore);
    printf("Thanks for playing!\n");
    return 0;
}

// Print board
void printBoard(char board[SIZE][SIZE]){
    printf("\n   ");
    for(int j=0;j<SIZE;j++) printf("%d   ", j);
    printf("\n");
    for(int i=0;i<SIZE;i++){
        printf("%d  ", i);
        for(int j=0;j<SIZE;j++){
            printf("%c", board[i][j]==EMPTY?' ':board[i][j]);
            if(j<SIZE-1) printf(" | ");
        }
        printf("\n");
        if(i<SIZE-1){
            printf("   ");
            for(int j=0;j<SIZE-1;j++) printf("---|");
            printf("---\n");
        }
    }
    printf("\n");
}

// Player move
void playerMove(char board[SIZE][SIZE], char playerName[]){
    int row,col;
    while(1){
        printf("%s, enter your move (row column): ", playerName);
        if(scanf("%d %d",&row,&col)!=2){
            while(getchar()!='\n');
            printf("Invalid input. Use two numbers separated by space.\n");
            continue;
        }
        if(row>=0 && row<SIZE && col>=0 && col<SIZE && board[row][col]==EMPTY){
            board[row][col]=HUMAN;
            break;
        } else printf("Invalid move. Try again.\n");
    }
}

// Random AI move (Easy)
void aiMoveRandom(char board[SIZE][SIZE]){
    int moves[SIZE*SIZE][2], count=0;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(board[i][j]==EMPTY){
                moves[count][0]=i;
                moves[count][1]=j;
                count++;
            }
    if(count>0){
        int choice=rand()%count;
        board[moves[choice][0]][moves[choice][1]]=AI;
        printf("AI has played at row %d, column %d.\n", moves[choice][0], moves[choice][1]);
    }
}

// Check if moves left
int isMovesLeft(char board[SIZE][SIZE]){
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(board[i][j]==EMPTY) return 1;
    return 0;
}

// Check win (4 in a row)
int checkWin(char board[SIZE][SIZE], char player){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<=SIZE-WIN;j++){
            int hor=1, ver=1;
            for(int k=0;k<WIN;k++){
                if(board[i][j+k]!=player) hor=0;
                if(board[j+k][i]!=player) ver=0;
            }
            if(hor || ver) return 1;
        }
    }
    for(int i=0;i<=SIZE-WIN;i++){
        for(int j=0;j<=SIZE-WIN;j++){
            int diag1=1, diag2=1;
            for(int k=0;k<WIN;k++){
                if(board[i+k][j+k]!=player) diag1=0;
                if(board[i+WIN-1-k][j+k]!=player) diag2=0;
            }
            if(diag1 || diag2) return 1;
        }
    }
    return 0;
}

// Draw check
int isDraw(char board[SIZE][SIZE]){
    return !isMovesLeft(board);
}

// Count sequences for heuristic
int countSequences(char board[SIZE][SIZE], char player, int n){
    int count=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<=SIZE-n;j++){
            int k;
            for(k=0;k<n;k++) if(board[i][j+k]!=player) break;
            if(k==n) count++;
        }
    }
    for(int j=0;j<SIZE;j++){
        for(int i=0;i<=SIZE-n;i++){
            int k;
            for(k=0;k<n;k++) if(board[i+k][j]!=player) break;
            if(k==n) count++;
        }
    }
    for(int i=0;i<=SIZE-n;i++){
        for(int j=0;j<=SIZE-n;j++){
            int k;
            for(k=0;k<n;k++) if(board[i+k][j+k]!=player) break;
            if(k==n) count++;
        }
    }
    for(int i=0;i<=SIZE-n;i++){
        for(int j=n-1;j<SIZE;j++){
            int k;
            for(k=0;k<n;k++) if(board[i+k][j-k]!=player) break;
            if(k==n) count++;
        }
    }
    return count;
}

// Heuristic evaluation
int evaluate(char board[SIZE][SIZE]){
    if(checkWin(board,AI)) return 1000;
    if(checkWin(board,HUMAN)) return -1000;
    int score=0;
    score += 10*countSequences(board, AI,2);
    score += 50*countSequences(board, AI,3);
    score += 500*countSequences(board, AI,4);
    score -= 10*countSequences(board, HUMAN,2);
    score -= 50*countSequences(board, HUMAN,3);
    score -= 500*countSequences(board, HUMAN,4);
    return score;
}

// Depth-limited Minimax
int minimax(char board[SIZE][SIZE], int depth, int isMax){
    int score=evaluate(board);
    if(score==1000) return score-depth;
    if(score==-1000) return score+depth;
    if(!isMovesLeft(board) || depth>=MAX_DEPTH) return score;

    if(isMax){
        int best=INT_MIN;
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                if(board[i][j]==EMPTY){
                    board[i][j]=AI;
                    int val=minimax(board,depth+1,0);
                    if(val>best) best=val;
                    board[i][j]=EMPTY;
                }
            }
        }
        return best;
    }else{
        int best=INT_MAX;
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                if(board[i][j]==EMPTY){
                    board[i][j]=HUMAN;
                    int val=minimax(board,depth+1,1);
                    if(val<best) best=val;
                    board[i][j]=EMPTY;
                }
            }
        }
        return best;
    }
}

// Find best move (Hard AI)
void findBestMove(char board[SIZE][SIZE], int *bestRow, int *bestCol){
    int bestVal=INT_MIN;
    *bestRow=-1; 
    *bestCol=-1;

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(board[i][j]==EMPTY){
                board[i][j]=AI;
                int moveVal = minimax(board, 0, 0);
                board[i][j]=EMPTY;
                if(moveVal > bestVal){
                    bestVal = moveVal;
                    *bestRow = i;
                    *bestCol = j;
                }
            }
        }
    }

    // If no best move found (shouldn't happen), pick first empty
    if(*bestRow == -1 || *bestCol == -1){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                if(board[i][j]==EMPTY){
                    *bestRow = i;
                    *bestCol = j;
                    return;
                }
            }
        }
    }
}
