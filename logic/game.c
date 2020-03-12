

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "../data/state.h"

/*
 * Função que verifica se uma Jogada é válida.
 */

int check_move(State state, Position pos){

    return pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
        abs(state.last_play.row - pos.row) <= 1 && abs(state.last_play.column - pos.column) <= 1 &&
        state.board[pos.row][pos.column] == Blank;

}

/*
 * Função que modifica o estado ao jogar na casa correta se a jogada for válida.
 */

int play(State *state, Position pos) {

    if (!check_move(*state, pos))
        return 0;

    make_move(state, pos);

    return 1;
}

/*
 * Verifica se o jogo acabou e retorna o vencedor.
 * Retorna 0 caso o jogo ainda não tenha terminado.
 */

unsigned int game_finished(State state) {

    int sum_row[8] = {1, 1, 1, 0, 0,-1,-1,-1};
    int sum_col[8] = {1, 0,-1, 1,-1, 1, 0,-1};
    int row_test, col_test;

    if (state.last_play.row - state.last_play.column == 7)
        return 1;
    else if (state.last_play.column - state.last_play.row == 7)
        return 2;

    for (int i=0; i < 8; i++) {
        row_test = state.last_play.row + sum_row[i];
        col_test = state.last_play.column + sum_col[i];

        if (row_test >= 0 && row_test < 8 && col_test >= 0 && col_test < 8 &&
            state.board[row_test][col_test] == Blank)
            return 0; // O jogo ainda não acabou
    }

    return state.current_player;
}


