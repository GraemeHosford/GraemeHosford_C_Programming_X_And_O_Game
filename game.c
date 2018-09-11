// Name: Graeme Hosford
// Student ID: R00147327
// C Assignment 02, X's and O's

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include <time.h>

const char SPACE = '-';
const char X_SYMBOL = 'X';
const char O_SYMBOL = 'O';

void play_game() {

    // Show game title and get space for the game struct
    printf("\nX's and O's!\n");
    struct game* p_game_info = (struct game*) malloc(sizeof(struct game));

    // Variables to holdplayer names before game is initialised and they are added to struct
    char p1[MAX_NAME_LEN];
    char p2[MAX_NAME_LEN];

    printf("Enter the name for Player 1: ");
    scanf("%s", p1);

    printf("Enter the name of Player 2: ");
    scanf("%s", p2);

    // Initialises the game struct
    initialise_game(p_game_info, p1, p2);

    // Draws the game banner
    draw_banner();

    // Loops through the game turn by turn until it is finished by a win or a draw
    while(game_over(p_game_info) == False) {

        // Show thee game board
        display_board(p_game_info->board);

        // Show the game status
        print_status(p_game_info);

        // Show the position a player can pick
        display_board_positions();

        // Process a players input
        process_move(p_game_info);

    }

    // Shows the final state of the game
    show_final_game_state(p_game_info);

}

void show_final_game_state(struct game* game_info) {

    // Show the final state of the board
    printf("\n");
    display_board(game_info->board);

    // Print message if game was a draw
    if(game_info->status == DRAW) {
        printf("\nThe game has ended in a draw between player's %s and %s\n", game_info->playerNames[0], game_info->playerNames[1]);
    } else {

        // If the game was not a draw get the winners name based on the status and display the win message
        char winnerName[MAX_NAME_LEN];

        if(game_info->status == P1_WON) {
            strncpy(winnerName, game_info->playerNames[0], MAX_NAME_LEN);
        } else {
            strncpy(winnerName, game_info->playerNames[1], MAX_NAME_LEN);
        }

        printf("\nCongratulations %s, you are the winner!\n", winnerName);
    }

}

void initialise_game(struct game* p_game_info, char* name1, char* name2) {

    srand(time(0));

    // Set the games attributes to their initial states
    p_game_info->finished = False;
    p_game_info->status = P1_TURN;

    if(rand() % 2 == 0) {
        strncpy(p_game_info->playerNames[0], name1, MAX_NAME_LEN);
        strncpy(p_game_info->playerNames[1], name2, MAX_NAME_LEN);
    } else {
        strncpy(p_game_info->playerNames[0], name2, MAX_NAME_LEN);
        strncpy(p_game_info->playerNames[1], name1, MAX_NAME_LEN);
    }

    // Make every space on the board blank to begin with
    int i;
    int j;
    for(i = 0; i < 3; i++) {

        for(j = 0; j < 3; j++) {
            p_game_info->board[i][j] = SPACE;
        }
    }
}

void draw_banner() {

    // Print the game status banner
    printf("\n\n\n");
    printf("-----------\n");
    printf("Game Status\n");
    printf("-----------");
    printf("\n\n\n");

}

void display_board(char board[3][3]) {

    // Show the values currently on the board
    int row;
    int col;

    for(row = 0; row < 3; row++) {

        for(col = 0; col < 3; col++) {

            printf(" %c ", board[row][col]);

            if(col != 2) {
                printf("|");
            }

        }

        if(row != 2) {
            printf("\n-----------\n");
        } else {
            printf("\n\n");
        }

    }

}

void print_status(struct game* p_game_info) {

    // If the game is still ongoing then show which players turn is next
    if(p_game_info->finished == False) {

        if(p_game_info->status == P1_TURN) {
            printf("%s's Turn\n", p_game_info->playerNames[0]);
        } else if(p_game_info->status == P2_TURN) {
            printf("%s's Turn\n", p_game_info->playerNames[2]);
        }

    // If the game is over show the winner, the draw message is handled in the game_over function
    } else if(p_game_info->finished == True ) {

        if(p_game_info->status == P1_WON) {
            printf("Well done %s you have won", p_game_info->playerNames[0]);
        } else if(p_game_info->status == P2_WON) {
            printf("Well done %s you have won", p_game_info->playerNames[1]);
        }

    }

    printf("\n");

}

void display_board_positions() {

    // This method shows all the board places available
    int position = 0;

    int row;
    for(row = 0; row < 3; row++) {

        int col;
        for(col = 0; col < 3; col++) {

            printf(" %d ", position);

            position++;

            if(col != 2) {
                printf("|");
            }

        }

        if(row != 2) {
            printf("\n-----------\n");
        } else {
            printf("\n\n");
        }

    }

}

void get_row_col(int position, int* row, int* col) {

    // Get the row and column to use based on the users position input
    *row = position / 3;
    *col = position % 3;

}

void process_move(struct game* game_info) {

    boolean valid = False;

    // Loop until the user enters a valid input
    while(valid == False) {

        int input = -1;

        // Loop until the user enters a value between 0 - 8
        while((input < 0 || input > 8)) {
            printf("\nEnter a number between 0 - 8: ");
            scanf("%d", &input);
        }

        int row = -1;
        int col = -1;

        // Get the column and row to use based on the input
        get_row_col(input, &row, &col);

        // If the space is free it can be used, if not the user must enter another position number
        if(game_info->board[row][col] == SPACE) {

            // If itis player 1's turn then place an X symbol and change to player 2's turn
            if(game_info->status == P1_TURN) {
                game_info->board[row][col] = X_SYMBOL;
                game_info->status = P2_TURN;
            } else {

                // If it is player 2's turn place an O symbol and change back to player 1's turn
                game_info->board[row][col] = O_SYMBOL;
                game_info->status = P1_TURN;
            }

            // User has entered valid input so leave the loop
            valid = True;

        } else {
            printf("\nThis slot has already been used\n");
        }

    }

}

boolean check_for_win(struct game* p_game_info) {

    // All 8 possible solutions for winning X's and O's
    int winSolutions[8][6] = {{0, 0, 0, 1, 0, 2},
                                {1, 0, 1, 1, 1, 2},
                                {2, 0, 2, 1, 2, 2},
                                {0, 0, 1, 0, 2, 0},
                                {0, 1, 1, 1, 2, 1},
                                {0, 2, 1, 2, 2, 2},
                                {0, 0, 1, 1, 2, 2},
                                {0, 2, 1, 1, 2, 0}};

    boolean gameWon = False;

    // Loop through the possible winning solution, checking the values on the board each time to
    // see if a win has been achieved yet
    int i;
    for(i = 0; i < sizeof(winSolutions) / (sizeof(int) * 6); i++) {

        char first = p_game_info->board[winSolutions[i][0]][winSolutions[i][1]];
        char second = p_game_info->board[winSolutions[i][2]][winSolutions[i][3]];
        char third = p_game_info->board[winSolutions[i][4]][winSolutions[i][5]];

        // If all symbols in a row are equal and not a free space then a win has been achieved
        if(first == second && second == third && first != SPACE) {

            gameWon = True;

            // Checks if player 1 or 2 has won
            if(first == X_SYMBOL) {
                p_game_info->status = P1_WON;
            } else {
                p_game_info->status = P2_WON;
            }

        }

    }

    return gameWon;
}

boolean game_over(struct game* p_game_info) {

    // First checks if theere is a inning solution o the board
    if(check_for_win(p_game_info) == False) {

        // If there is not a winning solution on the board then go through it to check if all spaces have been
        // used in which case the game has ended in a draw
        int usedSpaces = 0;

        int row = -1;
        int col = -1;

        int i;
        for(i = 0; i < 9; i++) {

            get_row_col(i, &row, &col);

            char spaceChar = p_game_info->board[row][col];

            if(spaceChar != SPACE) {
                usedSpaces++;
            }

        }

        // All 9 spaces being used but no win solution means a draw has happened
        if(usedSpaces == 9) {
            p_game_info->finished = True;
            p_game_info->status = DRAW;
        }

    } else {
        // A win solution has been found so the game is over
        p_game_info->finished = True;
    }

    return p_game_info->finished;;
}
