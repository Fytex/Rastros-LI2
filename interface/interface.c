

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../data/state.h"
#include "../logic/game.h"
#include "board.h"
#include "file.h"

#define BUF_SIZE 1024


/*
 * Limpa o ecrã e imprime informações sobre a última jogada
 */

void print_last_info(State *state) {

    // Executar comando no terminal para o limpar (Compatível com Win e *nix)
    system("cls || clear");

    printf("Last Play:\n\tPlayer: %d\n\tRow: %d\n\tColumn: %c\n\n",
           state->current_player, state->last_play.row + 1, state->last_play.column + 'a');
}




/*
 * Interpretador (Comunicação com o terminal)
 */

int interpreter(State *state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner;
    char *command, *argument;


    print_board(state, stdout);
    printf("Player %d >> ", state->current_player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        command = strtok(line, " \n");
        argument = strtok(NULL, " \n");

        if (!argument && sscanf(command, "%[a-hA-H]%[1-8]", col, row) == 2) {
            Position pos = {tolower(*col) - 'a', *row - '1'};

            if (play(state, pos)) {
                print_last_info(state);
                print_board(state, stdout);

                winner = game_finished(state);

                if (winner) {
                    printf("Congrats Player %d\n", winner);
                    return 1;
                }

                swap_players(state);
            }
            else
                puts("Introduza Jogada válida");
        }

        else if (!strcmp(command, "Q"))
            exit(0);

        else if (!strcmp(command, "gr") && argument)
            write_to_file(state, argument);

        else
            puts("Introduza Jogada válida");

        printf("Player %d >> ", state->current_player);
    }

    return 0;
}
