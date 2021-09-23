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

int isWinner(int board[], int player){
    int row = sqrt(size);
    for (int i = 0; i < row; i += row){
        if ((board[i] == board[i+1]) && (board[i] == board[i+2]) && (board[i] == player))
            return 1;
    }

    for (int i = 0; i < row; i++){
        if ((board[i] == board[i+row]) && (board[i] == board[i+row+row]) && (board[i] == player))
            return 1;
    }

    if ((board[0] == board[4]) && (board[0] == player) &&(board[8] == board[0]))
        return 1;

    if ((board[2] == board[4]) && (board[2] == player) && (board[6] == player))
        return 1;    

    return 0;
}

int humanMoves(int board[]){
    int idx;
    printf("\nEnter your choice: ");
    getchar();
    scanf("%d", &idx);

    //printf("\nIdx: %d\n", idx);
    if (idx <= 0 || idx > 9 || board[idx-1] != 0){
        printf("\nEnter valid index.\n");
        return humanMoves(board);
    }
    return idx-1;
}

int canWin(int board[], char player){
    int row = sqrt(size);
    for (int i = 0; i < row; i += row){
        //printf("R: %d %d %d\n", board[i], board[i+1],board[i+2]);
        if ((board[i] == board[i+1]) && (board[i+2] == 0) && (board[i] == player))
            return i+2;
        if ((board[i] == board[i+2]) && (board[i+1] == 0) && (board[i] == player))
            return i+1;
        if ((board[i+2] == board[i+1]) && (board[i] == 0) && (board[i+1] == player))
            return i; 
    }

    for (int i = 0; i < row; i++){
        //printf("C: %d %d %d\n", board[i], board[i+row],board[i+row+row]);
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
    if (moves == 0)
        return 4;
    if (idx != -1)
        return idx;
    else if (idx2 != -1)
        return idx;
    else{
       int i = rand()%8 + 1;
       //printf("move %d\n", i);
       while (board[i] != 0){
           //printf("move %d\n", i);
           i = rand()%4 + 1;
       } 
       return i;
    }
}

int getMoves(int board[], char player, int moves){
    //return humanMoves(board);
    return player == HUMAN ? humanMoves(board) : AImoves(board, moves);
}

char initGame(char player1, char player2){
    int board[size] = { 0 };
    int moves = 0, idx;

    while (moves < size){
        printBoard(board, player1, player2);
        //printf("\nPlayer 1");
        idx = getMoves(board, player1, moves);
        //printf("init %d\n", idx);
        board[idx] = 1;
        if (isWinner(board, 1) != 0){
            //printf("isinWin\n");
            printBoard(board, player1, player2);
            return player1;
        }

        printBoard(board, player1, player2);
        //printf("\nPlayer 2");
        idx = getMoves(board, player2, moves);
        printf("\nAI move %d\n", idx);
        board[idx] = 2;
        if (isWinner(board, 2) != 0){
            //printf("isinWin\n");
            printBoard(board, player1, player2);
            return player2;
        }  
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
    printf("\n\nWinner is %c", winner);
    return 0;
}