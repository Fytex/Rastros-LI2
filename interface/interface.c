#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../data/state.h"
#include "../logic/game.h"
#include "../data/file.h"
#include "../linked_lists/linked.h"
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
    "  >> gr <file>\t\t(Saves the current game to a file)\n"
    "  >> ler <file>\t\t(Load the game from the file)\n"
    "  >> pos <position>\t(Load the game from a previous position)\n"
    "  >> movs\t\t(Lists all the plays)\n"
    "  >> list\t\t(Lists all saved files)\n"
    "  >> Q\t\t\t(Ends the game)\n");

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
 * Interpreter (Communication with terminal)
 */

unsigned int interpreter(State* state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner = 0, player = get_current_player(state);
    char *command, *argument;
    int saved_count = 0;


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
                    saved_count = 0; // Since the play is done we can get rid of the saved_count
                    print_last_info(state);
                    print_board(state, stdout);

                    winner = game_finished(state);

                    if (winner) {
                        printf("\nCongrats Player %d\n\nPress enter to go back to menu...", winner);
                        clear_stdin_buffer();
                        break;
                    }

                    player = swap_players(state);
                }
                else
                    puts("\nInsert a valid play\n");
            }

            else if (!strcmp(command, "q"))
                break;

            else if (!strcmp(command, "gr") && argument) {
                write_to_file(state, argument);
                puts("\nFile created\n");
            }

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
                    puts("\nFile not found\n");

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

            else if (!strcmp(command, "pos") && argument) {
                char* rest;
                const int move_idx = (int) strtol(argument, &rest, 10);

                // Check's move_count from the game that has more moves
                if (!*rest && move_idx >= 0 && move_idx <= (saved_count ? saved_count : get_move_count(state))) {

                    if (!saved_count)
                        saved_count = get_move_count(state);


                    clear_terminal();
                    edit_state_from_move(state, move_idx);

                    if (move_idx)
                        print_last_info(state);

                    print_board(state, stdout);
                }
                else
                    puts("\nInsert a valid position\n");
            }
            else if (!strcmp(command, "jog")){
                List* positions = NULL;
                positions = create_pos_list(state);

                computer_move(state,positions);

                print_last_info(state);
                print_board(state,stdout);

                player = swap_players(state);

                winner = game_finished(state);

                if (winner) {
                    printf("\nCongrats Player %d\n\nPress enter to go back to menu...", winner);
                    clear_stdin_buffer();
                    break;
                }
            }

            else
                puts("\nInsert a valid play\n");
        }

        printf("Player %d (%d) >> ", player, get_move_count(state) + 1);
    }

    return winner;
}
