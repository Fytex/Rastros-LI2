#include <stdio.h>
#include <stdlib.h>
#include "../data/state.h"

/*
 * Receives a space and prints it in terminal
 */

void type_space(const Space p, FILE* const file) {
    putc(p, file);

    if (file == stdout)
        putchar(' ');

}

void print_moves(const State* const state, FILE* const file){
    const int move_count = get_move_count(state);
    int i = 0;
    const Position last_play = get_last_play(state);
    Move move;

    for ( ; i < move_count; ++i) {
        move = get_move(state, i);

        fprintf(file, "%02d : %c%d %c%d\n", i,
                move.player1.column + 'a', move.player1.row + 1,
                move.player2.column + 'a', move.player2.row + 1);
    }

    if (get_current_player(state) == 2)
        fprintf(file, "%02d : %c%d", i, last_play.column + 'a',
                last_play.row + 1);
}

/*
 * Prints the board of the state
 */


void print_board(const State* const state, FILE* const file) {
    const Position last_play = get_last_play(state);
    Position pos;

    for (pos.row=0; pos.row < 8; ++pos.row) {
        if (file == stdout)
            printf("  %d   ", pos.row + 1);

        if (pos.row == 7) {
            if (last_play.row == 7 && last_play.column == 0)
                type_space(White, file);
            else
                fprintf(file, (file == stdout) ? "1 " : "1");
        }

        for (pos.column=0; pos.column < 8; ++pos.column)
            if (abs(pos.row - pos.column) != 7)
                type_space(get_position_space(state, pos), file);

        if (pos.row == 0) {
            if (last_play.row == 0 && last_play.column == 7)
                type_space(White, file);
            else
                putc('2', file);
        }

        if (pos.row != 7)
            fprintf(file, "\n"); // New line
    }


    if (file == stdout) {
        printf("\n\n      ");

        for (int i = 0; i < 8; ++i)
            printf("%c ", 'a' + i);

        puts("\n"); // New Line
    } else if (get_move_count(state)) {
        fprintf(file, "\n\n");
        print_moves(state, file);
    }
}
