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
    int count = 0;
    const Position last_play = get_last_play(state);
    Move move;

    for ( ; count < move_count; ++count) {
        move = get_move(state, count);

        fprintf(file, "%02d: %c%d %c%d\n", count + 1,
                move.player1.column + 'a', 8 - move.player1.row,
                move.player2.column + 'a', 8 - move.player2.row);
    }

    if (get_current_player(state) == 2)
        fprintf(file, "%02d: %c%d", count + 1,
                last_play.column + 'a', 8 - last_play.row);
}

/*
 * Prints the board of the state
 */


void print_board(const State* const state, FILE* const file) {
    const Position last_play = get_last_play(state);
    Position pos;

    for (pos.row=0; pos.row < 8; ++pos.row) {
        if (file == stdout)
            printf("  %d   ", 8 - pos.row);

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
    } else if (get_move_count(state) || get_current_player(state) == 2) {
        fprintf(file, "\n\n");
        print_moves(state, file);
    }
}


/*
 * Changes the state of the game to a previously done move, where we can start playing from.
 */

void edit_state_from_move(State* const state, const int move_count) {
    Move move;
    Position pos;
    int count = get_move_count(state);

    if (count > move_count) {

        edit_position_space(state, get_last_play(state), Blank);

        for ( ; count > move_count;  count--) {

            move = get_move(state, count - 1);
            edit_position_space(state, move.player1, Blank);
            edit_position_space(state, move.player2, Blank);

        }
        if (count)
            pos = get_move(state, count - 1).player2;
        else
            pos = BEGIN_POS;

        edit_position_space(state, pos, White);
        edit_last_play(state, pos);
    }

    else if (count < move_count) {

        if (!count)
            edit_position_space(state, BEGIN_POS, Black);
        else
            edit_position_space(state, get_move(state, count - 1).player2, Black);

        for ( ; count < move_count;  count++) {

            move = get_move(state, count);
            edit_position_space(state, move.player1, Black);
            edit_position_space(state, move.player2, Black);

        }
        edit_position_space(state, move.player2, White);
        edit_last_play(state, move.player2);
    }

    else if (move_count) {
        move = get_move(state, move_count - 1);
        edit_position_space(state, get_last_play(state), Blank);
        edit_position_space(state, move.player2, White);
        edit_last_play(state, move.player2);
    }
    else {
        edit_position_space(state, get_last_play(state), Blank);
        edit_position_space(state, BEGIN_POS, White);
        edit_last_play(state, BEGIN_POS);
    }

    edit_current_player(state, 1);
    edit_move_count(state, move_count);
}