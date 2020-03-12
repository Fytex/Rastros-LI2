

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "interface.h"
#include "../data/state.h"
#include "../logic/game.h"

#define BUF_SIZE 1024

/*
 * Recebe uma casa e imprime no ecrã
 */

void type_space(Space p) {

    switch(p) {

        case (Black):
            printf("# ");
            break;

        case (White):
            printf("* ");
            break;

        default: printf(". ");
    }
}

/*
 * Limpa o ecrã e imprime informações sobre a última jogada
 */

void print_last_info(State state) {

    // Executar comando no terminal para o limpar (Compatível com Win e *nix)
    system("cls || clear");

    printf("Last Play:\n\tPlayer: %d\n\tRow: %d\n\tColumn: %c\n\n",
           state.current_player, state.last_play.row + 1, state.last_play.column + 'a');
}

/*
 * Imprime o tabuleiro
 */

void print_board(State state) {

    for(int row = 0; row < 8; row++) {
        printf("%d\t", row + 1);

        if (row == 7) {
            if (state.last_play.row == 7 && state.last_play.column == 0)
                type_space(White);
            else
                printf("1 ");
        }

        for(int col = 0; col < 8; col++)
            if (abs(row - col) != 7)
                type_space(state.board[row][col]);

        if (row == 0) {
            if (state.last_play.row == 0 && state.last_play.column == 7)
                type_space(White);
            else
                printf("2");
        }

        puts(""); // New line
    }

    printf("\n\t");

    for(int i = 0; i < 8; i++)
        printf("%c ", 'a' + i);

    puts("\n"); // New Line
}

/*
 * Interpretador (Comunicação com o terminal)
 */

int interpreter(State *state) {
    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner;

    print_board(*state);
    printf("Player %d >> ", state->current_player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        if (strlen(line) == 3 && sscanf(line, "%[a-hA-H]%[1-8]", col, row) == 2) {
            Position pos = {tolower(*col) - 'a', *row - '1'};

            if (play(state, pos)) {
                print_last_info(*state);
                print_board(*state);

                winner = game_finished(*state);

                if (winner) {
                    printf("Congrats Player %d\n", winner);
                    return 1;
                }

                swap_players(state);
            }
            else
                puts("Introduza Jogada válida");
        } else
            puts("Introduza Jogada válida");

        printf("Player %d >> ", state->current_player);
    }

    return 0;
}
