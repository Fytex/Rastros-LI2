//
// Created by fytex on 3/13/20.
//



#include <stdio.h>
#include <stdlib.h>
#include "../data/state.h"

/*
 * Recebe uma casa e imprime no ecrã
 */

void type_space(Space p, FILE *file) {

    switch(p) {

        case (Black):
            fprintf(file, "# ");
            break;

        case (White):
            fprintf(file, "* ");
            break;

        default: fprintf(file, ". ");
    }
}



/*
 * Imprime o tabuleiro
 */


void print_board(State *state, FILE *file) {

    for (int row = 0; row < 8; row++) {
        if (file == stdout)
            printf("%d     ", row + 1);

        if (row == 7) {
            if (state->last_play.row == 7 && state->last_play.column == 0)
                type_space(White, file);
            else
                fprintf(file, "1 ");
        }

        for (int col = 0; col < 8; col++)
            if (abs(row - col) != 7)
                type_space(state->board[row][col], file);

        if (row == 0) {
            if (state->last_play.row == 0 && state->last_play.column == 7)
                type_space(White, file);
            else
                fprintf(file, "2");
        }

        fprintf(file, "\n"); // New line
    }

    fprintf(file, "\n");

    if (file == stdout) {
        printf("      ");

        for (int i = 0; i < 8; i++)
            printf("%c ", 'a' + i);

        puts("\n"); // New Line
    } else {
        int i = 0;

        for ( ; i < state->move_count; i++)

            fprintf(file, "%02d : %c%d %c%d\n", i, state->moves[i].player1.column + 'a',
                    state->moves[i].player1.row + 1, state->moves[i].player2.column + 'a',
                    state->moves[i].player2.row + 1);

        if (state->current_player == 2)
            fprintf(file, "%02d : %c%d", i, state->last_play.column + 'a',
                    state->last_play.row + 1);

    }
}
