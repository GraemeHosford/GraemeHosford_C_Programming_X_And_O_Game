// Name: Graeme Hosford
// Student ID: R00147327
// C Assignment 02, X's and O's

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define MAX_NAME_LEN 50

enum Bool {False, True};
enum status {P1_TURN, P2_TURN, P1_WON, P2_WON, DRAW};
typedef enum Bool boolean;


struct game {

    char board[3][3];
    char playerNames[2][MAX_NAME_LEN];
    int status;
    boolean finished;

};

void play_game();

void initialise_game(struct game* p_game_info, char* name1, char* name2);

void draw_banner();

void display_board(char board[3][3]);

void print_status(struct game* p_game_info);

void display_board_positions();

void get_row_col(int position, int* row, int* col);

void process_move(struct game* game_info);

boolean game_over(struct game* p_game_info);

boolean check_for_win(struct game* p_game_info);

void show_final_game_state(struct game* game_info);

#endif // GAME_H_INCLUDED
