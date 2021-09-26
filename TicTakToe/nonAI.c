#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define size 9
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

int isValid(int idx, int board[]){
    return (board[idx] == 0 && (idx >= 0 && idx < size)
    );
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

int humanMoves(int board[]){
    int idx;
    printf("\nEnter your choice: ");
    getchar();
    scanf("%d", &idx);

    if (idx <= 0 || idx > 9 || board[idx-1] != 0){
        printf("\nEnter valid index.\n");
        return humanMoves(board);
    }
    return idx-1;
}

int canWin(int board[], char ch){
    int player = ch == 'X' ? 1: 2;
    int row = sqrt(size);
    for (int i = 0; i < row; i += row){
        if ((board[i] == board[i+1]) && (board[i+2] == 0) && (board[i] == player))
            return i+2;
        if ((board[i] == board[i+2]) && (board[i+1] == 0) && (board[i] == player))
            return i+1;
        if ((board[i+2] == board[i+1]) && (board[i] == 0) && (board[i+1] == player))
            return i; 
    }

    for (int i = 0; i < row; i++){
        if ((board[i] == board[i+row]) && (board[i+row+row] == 0) && (board[i] == player))
            return i+row+row;
        if ((board[i+row+row] == board[i+row]) && (board[i] == 0) && (board[i+row] == player))
            return i;
        if ((board[i] == board[i+row+row]) && (board[i+row] == 0) && (board[i] == player))
            return i+row;
    }

    if ((board[0] == board[4]) && (board[0] == player) &&(board[8] == 0))
        return 8;

    if ((board[0] == board[8]) && (board[0] == player) &&(board[4] == 0))
        return 4;

    if ((board[8] == board[4]) && (board[8] == player) &&(board[0] == 0))
        return 0;

    if ((board[2] == board[4]) && (board[2] == player) && (board[6] == 0))
        return 6; 

    if ((board[2] == board[6]) && (board[2] == player) && (board[4] == 0))
        return 4; 

    if ((board[6] == board[4]) && (board[4] == player) && (board[0] == 0))
        return 0; 

    return -1;  
}

int AImoves(int board[], int moves){
    printf("\nComputer is playing...\n");
    int idx = canWin(board, AI), idx2 = canWin(board, HUMAN);
    if (moves == 0 && board[4] == 0)
        return 4;
    if (idx != -1)
        return idx;
    else if (idx2 != -1)
        return idx2;
    else{
        int i = rand()%8 + 1;
        //printf("i: %d\n", i);
        while (!isValid(i, board)){
            //printf("i: %d", i);
            i = rand()%8 + 1;
        } 
       return i;
    }
}

int getMoves(int board[], char player, int moves){
    return player == HUMAN ? humanMoves(board) : AImoves(board, moves);
}

char initGame(char player1, char player2){
    int board[size] = { 0 };
    int moves = 0, idx;

    while (moves < size){
        int winner = isWinner(board);
        if (winner != 0){
            printBoard(board, player1, player2);
            return winner;
        }
        printBoard(board, player1, player2);
        idx = getMoves(board, player1, moves);
        board[idx] = 1;
        moves++;

        if (moves == 9){
            printBoard(board, player1, player2);
            return '#';
        }

        if (winner != 0){
            printBoard(board, player1, player2);
            return winner;
        }
        printBoard(board, player1, player2);
        idx = getMoves(board, player2, moves);
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

    if (winner == '#')
        printf("It's a draw!\nUp for another one?\n");
    else if (winner == HUMAN)
        printf("Hey, Winner!\n");
    else
        printf("HAHA, better luck next time :P\n");

    return 0;
}