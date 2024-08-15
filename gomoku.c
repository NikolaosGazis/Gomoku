// Headers //
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int player_wins = 0, draws = 0, computer_wins = 0;
    char board[BOARD_SIZE][BOARD_SIZE];
    size = BOARD_SIZE;
    play = 1; // To enter the while loop.

    // Seed the random number generator //
    srand(time(NULL));

    // Game Loop //
    while(play) {
        printf("--- G O M O K U ---\n");

        init_board(board, size);
        print_stats(player_wins, draws, computer_wins);
        print_board(board, size);

        turn = 1;
        while(winner(board, size, turn, &result) == 0) {
            if (next_turn(turn) == 1) {
                player(board, size, &row, &col);
                board[row][col] = PLAYER;
            } else {
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

// Functions Implementation //
void init_board(char board[BOARD_SIZE][BOARD_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { 
            board[i][j] = '+'; 
        }
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE], int size) {
    printf("----------------------------------------------------------------\n");
    for(int i = 0; i < size; i++) {
        printf("|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |\n");
        printf("|---");
        for (int j = 0; j < size; j++ ) { printf("%c---", board[i][j]); }
        printf("|\n");
    }
    printf("|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |\n");
    printf("----------------------------------------------------------------\n");
}

void print_stats(int player_wins, int draws, int computer_wins) {
    printf("Current Sessions results!\n"
            "-------------------------\n"
            "Player Wins: %d\n"
            "Draws: %d\n"
            "Computer Wins: %d\n"
            "-------------------------\n",
            player_wins, draws, computer_wins);
}

void update_stats(int result, int *player_wins, int *draws, int *computer_wins) {  
    if (result == 1) { 
        *player_wins += 1; 
    } else if (result == 2) { 
        *computer_wins += 1; 
    } else if (result == -1) { 
        *draws += 1; 
    }
}

void print_result(int result) {    
    if (result == 1) { 
        printf("Congratulations! You win!\n"); 
    } else if (result == 2) { 
        printf("Computer takes this one.\n"); 
    } else if (result == -1) { 
        printf("No winner. Its a draw!\n"); 
    }
}

int next_turn(int turn) {
    return (turn % 2) + 1;
}

int winner(char board[BOARD_SIZE][BOARD_SIZE], int size, int turn, int *result) {
    // Variables //
    int con_row, con_col, found;
    int spaces = 225;
    found = 0;

    if ((turn%2) == 1) { // User.
        con_row = 0;
        con_col = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == PLAYER) {
                    con_row++;
                    if (con_row == CHAIN) { 
                        found = 1; 
                    }
                } else { 
                    con_row = 0; 
                }
            }
        }
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                if (board[i][j] == PLAYER) {
                    con_col++;
                    if (con_col == CHAIN) { 
                        found = 1; 
                    } else { 
                        con_col = 0; 
                    }
                }
            }
        }
    }
    
    spaces -= 1;
    if (spaces != 0) { // Computer.
        if ((turn % 2) == 0) {
            con_row = 0;
            con_col = 0;

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] == COMPUTER) {
                        con_row++;
                        if (con_row == CHAIN) { 
                            found = 1; 
                        }
                    } else { 
                        con_row = 0; 
                    }
                }
            }
            for (int j = 0; j < size; j++){
                for (int i = 0; i < size; i++) {
                    if (board[i][j] == COMPUTER) {
                        con_col++;
                        if (con_col == CHAIN) { 
                            found = 1; 
                        } else { 
                            con_col = 0; 
                        }
                    }
                }
            }
            spaces--;
        }
    }

    if (found == 1) { // Winner.
        if ((turn % 2) == 1) { // Player.
            *result = 1; 
        } else { // Computer.
            *result = 2; 
        }
    }
    else if (found == 0) { // Draw.
        if (spaces == 0) { 
            *result = -1; 
        } else { // Continue.
            *result = 0;
        }
    }
    return *result;
}

void player(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col) {
    do {
        do { // Row.
            printf("Give the Row you want to place the X: ");
            scanf("%d", row);
        } while (*row < 1 || *row > size);

        do { // Column.
            printf("Give the Column you want to place the X: ");
            scanf("%d", &col);
        } while (*col < 1 || *col > size);

        (*row)--;
        (*col)--;
    } while (board[*row][*col] != '+');
}

void computer(char board[BOARD_SIZE][BOARD_SIZE], int size, int *row, int *col) {
    do {
        *row = rand() % size;
        *col = rand() % size;

    } while (board[*row][*col] != '+');
}

int play_again() {
    char question;
    printf("Do you want to play again? (y/n)\n--> ");
    scanf("%c", &question);
    CLEAR_BUFFER;
    return (question == 'y' || question == 'Y'); // Casse sensitive.
}
