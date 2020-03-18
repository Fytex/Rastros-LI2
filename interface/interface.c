

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

int help_terminal(FILE *file){
    char buf [2];

    fprintf (file, "Comandos disponíveis :\n\n");
    fprintf (file, "  >> gr (Comando que grava o jogo para um ficheiro)\n");
    fprintf (file, "  >> ler (Comando que lê um ficheiro caso exista)\n");
    fprintf (file, "  >> movs (Comando que permite visualizar as jogadas feitas)\n");
    fprintf (file, "  >> Q (Comando que termina o jogo)\n\n");

    fprintf (file, "Pressione Enter se pretender voltar ao jogo!\n");

        if (fgets (buf, 2, stdin))
            return 0;

    return 1;
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
 * Interpreter (Comunication with terminal)
 */

int interpreter(State *state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner, player=get_current_player(state);
    char *command, *argument;


    print_board(state, stdout);
    printf("Player %d (00) >> ", player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        command = strtok(line, " \n");
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
                    return 1;
                }

                player = swap_players(state);
            }
            else
                puts("Introduza Jogada válida");
        }

        else if (!strcmp(command, "q"))
            exit(0);

        else if (!strcmp(command, "gr") && argument)
            write_to_file(state, argument);

        else if (!strcmp(command, "ler") && argument) {
            read_from_file(state, argument); // updates state

            if (get_move_count(state) || get_current_player(state) == 1) // If not first play (current_player corresponds to last player)
                print_last_info(state);
            else
                clear_terminal();

            player = swap_players(state);
            print_board(state, stdout);
        }

        else if (!strcmp(command, "movs")) {

            clear_terminal();
            print_board(state, stdout);
            print_moves(state, stdout);
            puts("\n");

        }

        else if (!strcmp(command, "help")){

            clear_terminal();
            if (!help_terminal(stdout)) {
                clear_terminal();
                print_board(state, stdout);
            }
        }

        else
            puts("Introduza Jogada válida");

        printf("Player %d (%02d) >> ", player, get_move_count(state));
    }

    return 0;
}
