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