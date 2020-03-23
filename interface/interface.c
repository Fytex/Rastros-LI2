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

void lower_string(char *s) {
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
 * Help command that shows available commands
 */

void help_terminal(){

    puts("Available Commands :\n");
    puts("  >> gr <file>\t(Saves the current game to a file)");
    puts("  >> ler <file>\t(Load the game from the file)");
    puts("  >> movs\t(Lists all the plays)");
    puts("  >> list\t(Lists all saved files)");
    puts("  >> Q\t(Ends the game)\n");

}



/*
 * Prints out information about last play
 */

void print_last_info(State *state) {
    Position last_play=get_last_play(state);
    clear_terminal();

    printf("Last Play:\n\tPlayer: %d\n\tRow: %d\n\tColumn: %c\n\n",
           get_current_player(state), last_play.row + 1, last_play.column + 'a');
}


/*
 * Displays something in terminal
 * Clears terminal, calls the given function and after an input from the user it goes back to the game
 */

void display_in_terminal(State *state, void func()) {
    clear_terminal();

    func();
    puts("Press Enter to go back to the game!");
    while ((getchar()) != '\n'); // Waits for an enter and clears the buffer

    clear_terminal();

    if (get_move_count(state) || get_current_player(state) == 2) // If neither first play nor first player
        print_last_info(state);

    print_board(state, stdout);
}

/*
 * Interpreter (Communication with terminal)
 */

unsigned int interpreter(State *state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner, player=get_current_player(state);
    char *command, *argument;


    print_board(state, stdout);
    printf("Player %d (0) >> ", player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        command = strtok(line, " \n");

        if (command) {
            lower_string(command);

            argument = strtok(NULL, " \n");

            if (!argument && sscanf(command, "%[a-h]%[1-8]", col, row) == 2) {
                Position pos = {*col - 'a', *row - '1'};

                if (play(state, pos)) {
                    print_last_info(state);
                    print_board(state, stdout);

                    winner = game_finished(state);

                    if (winner) {
                        printf("Congrats Player %d\n", winner);
                        return winner;
                    }

                    player = swap_players(state);
                } else
                    puts("Introduza Jogada válida");
            }

            else if (!strcmp(command, "q"))
                exit(0);

            else if (!strcmp(command, "gr") && argument)
                write_to_file(state, argument);

            else if (!strcmp(command, "ler") && argument) {

                if (read_from_file(state, argument)) { // updates state

                    if (get_move_count(state) ||
                        get_current_player(state) == 2) // If neither first play nor first player
                        print_last_info(state);
                    else
                        clear_terminal();

                    player = get_current_player(state);
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

            else
                puts("Introduza Jogada válida");
        }

        printf("Player %d (%d) >> ", player, get_move_count(state));
    }

    return 0;
}
