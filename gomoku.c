// Headers //
#include <stdio.h>
#include <stdlib.h>

// Definements //
#define CLEAR_BUFFER while (getchar() != '\n');
#define BOARD_SIZE 15
#define CHAIN 5
#define PLAYER 'X'
#define COMPUTER 'O'

// Functions Initilization //
void init_board(char board[BOARD_SIZE][BOARD_SIZE], int size);
void print_board(char board[BOARD_SIZE][BOARD_SIZE], int size);
void print_stats(int player_wins, int draws, int computer_wins);
void update_stats(int result, int *player_wins, int *draws, int *computer_wins);
void print_result(int result);
int next_turn(int turn);
int winner(char board[BOARD_SIZE][BOARD_SIZE], int size, int turn, int *result);
void player(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col);
void computer(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col);
int play_again();

int main(int agrc, char * argv[]) {
    // Variables  //
    int play, size, turn, row, col, result;
    int player_wins, draws, computer_wins;
    char board[BOARD_SIZE][BOARD_SIZE];

    size = BOARD_SIZE;
    play = 1;
    player_wins = 0;
    draws = 0;
    computer_wins = 0;

    // Game Loop //
    while(play) {
        printf("-- G O M O K U ---\n");

        init_board(board, size);
        print_stats(player_wins, draws, computer_wins);
        print_board(board, size);

        turn = 1;
        while(winner(board, size, turn, &result) == 0) { //    
            if (next_turn(turn) == 1) {
                player(board, size, &row, &col);
                board[row][col] = PLAYER;
            }
            else if (next_turn(turn) == 0) {
                computer(board, size, &row, &col);
                board[row][col] = COMPUTER;            
            }
            
            print_stats(player_wins, draws, computer_wins);
            print_board(board, size);
            turn++;
        }
        update_stats(result, &player_wins, &draws, &computer_wins);
        print_result(result);

        play = play_again();
    }
    return 0;
}

// Functions //
void init_board(char board[BOARD_SIZE][BOARD_SIZE], int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) { board[i][j] = '+'; }
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE], int size) {
    int i,j;

    printf("----------------------------------------------------------------\n");
    for(i = 0; i < size; i++) {
        printf("|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |\n");
        printf("|---");
        for ( j = 0; j < size; j++ ) { printf("%c---", board[i][j]); }
        printf("|\n");
    }
    printf("|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |\n");
    printf("----------------------------------------------------------------\n");
}

void print_stats(int player_wins, int draws, int computer_wins) {
    printf("Current Sessions results!\n"
            "-------------------------\n"
            "Your wins: %d\n"
            "Draws: %d\n"
            "Computer Wins: %d\n"
            "-------------------------\n",
            player_wins, draws, computer_wins);
}

void update_stats(int result, int *player_wins, int *draws, int *computer_wins) {  
    if (result == 1) { *player_wins += 1; }
    else if (result == 2) { *computer_wins += 1; }
    else if (result == -1) { *draws += 1; }
}

void print_result(int result) {    
    if (result == 1) { printf("Congratulations! You win!\n"); }
    else if (result == 2) { printf("Computer takes this one.\n"); }
    else if (result == -1) { printf("No winner. Its a draw!\n"); }
}

int next_turn(int turn) {
    turn = turn % 2; // Either 0 or 1.
    return turn;
}

int winner(char board[BOARD_SIZE][BOARD_SIZE], int size, int turn, int *result) {
    // Variables //
    int con_row, con_col, i, j, found;
    int spaces = 225;
    found = 0;

    if ((turn%2) == 1) { // User.
        con_row = 0;
        con_col = 0;

        for (i=0; i<size; i++) {
            for (j=0; j<size; j++) {
                if (board[i][j] == PLAYER) {
                    con_row += 1;
                    if (con_row == CHAIN) { found = 1; }
                }
                else { con_row = 0; }
            }
        }
        for (j=0; j<size; j++) {
            for (i=0; i<size; i++) {
                if (board[i][j] == PLAYER) {
                    con_col += 1;
                    if (con_col == CHAIN) { found = 1; }
                    else { con_col = 0; }
                }
            }
        }
    }
    
    spaces -= 1;

    if (spaces != 0) { // Computer.
        if ((turn % 2) == 0) {
            con_row = 0;
            con_col = 0;

            for (i=0; i<size; i++) {
                for ( j= 0; j<size; j++) {
                    if (board[i][j] == COMPUTER) {
                        con_row += 1;
                        if (con_row == CHAIN) { found = 1; }
                    }
                    else { con_row = 0; }
                }
            }
            for (j=0; j<size; j++){
                for (i=0; i<size; i++) {
                    if (board[i][j] == COMPUTER) {
                        con_col += 1;
                        if (con_col == CHAIN) { found = 1; }
                        else { con_col = 0; }
                    }
                }
            }
            spaces -= 1;
        }
    }

    if (found == 1) // We have a winner.
    {
        if ((turn % 2) == 1) {*result = 1; } // User.
        else if ((turn % 2) == 0) { *result = 2; } // Computer.
    }
    else if (found == 0) { // Draw.
        if (spaces == 0) { *result = -1; }
        else {*result = 0;} // Continue.
    }

    return *result;
}

void player(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col) {
    // Variables //
    int fun_row, fun_col;

    do {
        do { // Row.
            printf("Give the Row you want to place the X: ");
            scanf("%d", &fun_row);
        } while (fun_row<0 || fun_row>BOARD_SIZE);

        do { // Column.
            printf("Give the Column you want to place the X: ");
            scanf("%d", &fun_col);
        } while (fun_col<0 || fun_col>BOARD_SIZE);

    } while (board[fun_row-1][fun_col-1] != '+');

    *col = fun_col - 1;
    *row = fun_row - 1;
}

void computer(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col) {
    // Variables //
    int fun_row, fun_col;

    do {
        fun_row = rand() % 16;
        fun_col = rand() % 16;

    } while (board[fun_row-1][fun_col-1] != '+');

    *row = fun_row - 1;
    *col = fun_col - 1;
}

int play_again() {
    // Variables //
    char question;
    int play;

    printf("Do you want to play again? (y/n)\n--> ");
    scanf("%c", &question);

    if (question == 'y') { play = 1; }
    else { play = 0; }

    return play;
}