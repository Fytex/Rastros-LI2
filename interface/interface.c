#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../data/state.h"
#include "../logic/game.h"
#include "../data/file.h"
#include "board.h"

#define BUF_SIZE 1024

/*
 * Converts string to lowercase
 */

void lower_string(char* s) {
    for ( ; *s; ++s) *s = (char) tolower(*s);
}


/*
 * Clears the terminal
 */

void clear_terminal() {

    // Executes command in terminal to clear (Compatible with Win and *nix)
    system("cls || clear");

}


/*
 * Clears the stdin buffer
 */

void clear_stdin_buffer() {
    while ((getchar()) != '\n');
}


/*
 * Help command that shows available commands
 */

void help_terminal(){

    puts("Available Commands :\n\n"
    "  >> gr <file>\t(Saves the current game to a file)\n"
    "  >> ler <file>\t(Load the game from the file)\n"
    "  >> movs\t(Lists all the plays)\n"
    "  >> list\t(Lists all saved files)\n"
    "  >> Q\t(Ends the game)\n");

}


/*
 * Prints out information about last play
 */

void print_last_info(const State* const state) {
    const Position last_play=get_last_play(state);
    clear_terminal();

    printf("Last Play:\n\tPlayer: %d\n\tRow: %d\n\tColumn: %c\n\n",
           get_current_player(state), 8 - last_play.row, last_play.column + 'a');
}


/*
 * Displays something in terminal
 * Clears terminal, calls the given function and after an input from the user it goes back to the game
 */

void display_in_terminal(const State* const state, void (* const func)()) {
    clear_terminal();

    func();
    printf("\nPress Enter to go back to the game...");
    clear_stdin_buffer();

    clear_terminal();

    if (get_move_count(state) || get_current_player(state) == 2) // If neither first play nor first player
        print_last_info(state);

    print_board(state, stdout);
}


/*
 * Changes the state of the game to a previously done move, where we can start playing from.
 */
void print_pos(State* const state, const char* pos) {
    long int npos = strtol(pos,NULL,10);
    int nnpos = (int) npos;
    Position board_position;
    int i;

    for(i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {
            board_position.row = i;
            board_position.column = j;
            edit_position_space(state, board_position, Blank);
        }


    if (nnpos >= state->move_count || nnpos < 0)
        printf("Not a valid play.\n");

    else {
        if (nnpos == 0) {
            board_position.row = 3;
            board_position.column = 4;
            edit_position_space(state, board_position, White);
            edit_last_play(state, board_position);
        }
        else {
            board_position.row = 3;
            board_position.column = 4;
            edit_position_space(state, board_position, Black);

            for (i = 0; i < nnpos - 1; i++) {
                board_position.row = state->moves[i].player1.row;
                board_position.column = state->moves[i].player1.column;
                edit_position_space(state, board_position, Black);
                board_position.row = state->moves[i].player2.row;
                board_position.column = state->moves[i].player2.column;
                edit_position_space(state, board_position, Black);
            }
            board_position.row = state->moves[i].player1.row;
            board_position.column = state->moves[i].player1.column;
            edit_position_space(state, board_position, Black);
            board_position.row = state->moves[i].player2.row;
            board_position.column = state->moves[i].player2.column;
            edit_position_space(state, board_position, White);
            edit_last_play(state, board_position);
        }

        edit_move_count(state, nnpos);

        edit_current_player(state, 1);

        clear_terminal();

        if (get_move_count(state) || get_current_player(state) == 2) // If neither first play nor first player
            print_last_info(state);

        print_board(state, stdout);
    }
}

/*
 * Interpreter (Communication with terminal)
 */

unsigned int interpreter(State* const state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner=0, player=get_current_player(state);
    char *command, *argument;


    print_board(state, stdout);
    puts("\tType 'Help' to show available commands!\n");
    printf("Player %d (1) >> ", player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        command = strtok(line, " \n");

        if (command) {
            lower_string(command);

            argument = strtok(NULL, " \n");

            if (!argument && sscanf(command, "%[a-h]%[1-8]", col, row) == 2) {
                Position pos = {*col - 'a', '8' - *row};

                if (play(state, pos)) {
                    print_last_info(state);
                    print_board(state, stdout);

                    winner = game_finished(state);

                    if (winner) {
                        printf("Congrats Player %d\n\nPress enter to go back to menu...", winner);
                        clear_stdin_buffer();
                        break;
                    }

                    player = swap_players(state);
                } else
                    puts("Insert a valid play\n");
            }

            else if (!strcmp(command, "q"))
                break;

            else if (!strcmp(command, "gr") && argument)
                write_to_file(state, argument);

            else if (!strcmp(command, "ler") && argument) {

                if (read_from_file(state, argument)) { // updates state

                    if (get_move_count(state) ||
                        get_current_player(state) == 1) // If neither first play nor last player was first player
                        print_last_info(state);
                    else
                        clear_terminal();

                    player = swap_players(state);
                    print_board(state, stdout);
                } else
                    puts("File Not Found\n");

            }

            else if (!strcmp(command, "movs")) {

                clear_terminal(); // Objective: Clear last play info
                print_board(state, stdout);
                print_moves(state, stdout);
                puts("\n");

            }

            else if (!strcmp(command, "help"))
                display_in_terminal(state, help_terminal);

            else if (!strcmp(command, "list"))
                display_in_terminal(state, print_dir_contents);

            else if (!strcmp(command, "pos") && argument)
                print_pos(state, argument);

            else
                puts("Introduza Jogada válida");
        }

        printf("Player %d (%d) >> ", player, get_move_count(state) + 1);
    }

    return winner;
}
