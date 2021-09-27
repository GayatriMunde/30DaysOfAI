#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define size 9
#define AIwins 99
#define max(a,b) (((a) > (b)) ? (a) : (b))
char HUMAN, AI;

void printBoard(int board[], char player1, char player2){
    int row = sqrt(size), idx = 0;
    char ch;
    
    for (int i = 0; i < row; i++){
        for (int j = 0; j < row; j++){
            ch = board[idx] == 0 ? '_' : (board[idx] == 1) ? player1 : player2;
            printf ("%c ", ch);
            idx++;
        }
        printf("\n");
    }
}

int isWinner(int board[]){
    int row = sqrt(size);
    for (int i = 0; i < row; i += row){
        if ((board[i] == board[i+1]) && (board[i] == board[i+2]))
            return board[i];
    }

    for (int i = 0; i < row; i++){
        if ((board[i] == board[i+row]) && (board[i] == board[i+row+row]))
            return board[i];
    }

    if ((board[0] == board[4]) &&(board[8] == board[0]))
        return board[4];

    if ((board[2] == board[4]) && (board[6] == board[4]))
        return board[4];    

    return 0;
}


int isDraw(int board[]){
    for (int i = 0; i < size; i++){
        if (board[i] == 0)
            return 0;
    }

    return 1;
}
int humanMoves(int board[]){
    int idx;
    printf("\nEnter your choice: ");
    getchar();
    scanf("%d", &idx);

    if (board[idx-1] != 0 && (idx > 0 && idx <= 9)){
        printf("\nEnter valid index.\n");
        return humanMoves(board);
    }
    return idx-1;
}


int minimax(int board[], char player, int player1, int player2){
    int n = player == 'X' ? 1 : 2;
    int winner = isWinner(board);
    if (winner != 0){
        printBoard(board, player1, player2);
        return winner;
    }

    if (isDraw(board)){
        return 0;
    }

    int val, maxVal = INT_MIN, minVal = INT_MAX;
    int idx = -1;
    for (int i = 0; i < size; i++){
        if (board[i] == 0){
            board[i] = n;
            if (player == AI)
                val = minimax(board, HUMAN, player1, player2);
            else 
                val = minimax(board, AI, player1, player2);
            /*
            if (val > maxVal){
                maxVal = val, idx = i;
            }*/
            if(player == AI && val > maxVal)
                maxVal = val, idx = i; 
            if(player == HUMAN && val < minVal)
                minVal = val, idx = i;           
            board[i] = 0;
        }
    }

    printf("Max value: %d, Min value: %d\n", maxVal, minVal);
    if (idx == -1)
        return 0;
    return player == AI ? maxVal : minVal;
}

int AImoves(int board[], int moves, int player1, int player2){
    printf("\nComputer is playing...\n");
    int idx = -1, bestVal = INT_MIN;
    int val;
    int num = AI == 'X' ? 1 : 2;

    for (int i = 0; i < size; i++){
        //printf("IN\n");
        if (board[i] == 0){
            board[i] = num;
            val = minimax(board, AI, player1, player2);
            board[i] = 0;
            if (bestVal < val){
                bestVal = val;
                idx = i;
                printBoard(board, player1, player2);
                printf("Main: %d\n", bestVal);
            }
        }
    }

    printf("Main: %d\n", bestVal);
    return idx;
}

int getMoves(int board[], char player, int moves, int player1, int player2){
    return player == HUMAN ? humanMoves(board) : AImoves(board, moves, player1, player2);
}

char initGame(char player1, char player2){
    int board[size] = { 0 };
    int moves = 0, idx;

    while (moves < size){
        int winner = isWinner(board);
        if (winner != 0){
            printBoard(board, player1, player2);
            return player2;
        }
        printBoard(board, player1, player2);
        idx = getMoves(board, player1, moves, player1, player2);
        board[idx] = 1;
        moves++;

        if (moves == 9){
            printBoard(board, player1, player2);
            return '#';
        }

        winner = isWinner(board);
        if (winner != 0){
            printBoard(board, player1, player2);
            return player1;
        }
        printBoard(board, player1, player2);
        idx = getMoves(board, player2, moves, player1, player2);
        board[idx] = 2;
        moves++;      
    }

    return '#';
}

int main(){
    char player1, player2;
    int choice;

    printf("Choose:\n1. 'X'\n2. 'O'\nEnter your choice(1/2): ");
    scanf("%d", &choice);

    if (choice == 1){
        HUMAN = 'X', AI = 'O';
        player1 = HUMAN, player2 = AI;
    }
    else{
        HUMAN = 'O', AI = 'X';
        player1 = AI, player2 = HUMAN;
    }

    char winner = initGame(player1, player2);
    //printf("Winner: %c\n", winner);
    if (winner == '#')
        printf("\nIt's a draw!\nUp for another one?\n");
    else if (winner == HUMAN)
        printf("\nHey, You won!\n");
    else
        printf("\nHAHA, better luck next time :P\n");

    return 0;
}