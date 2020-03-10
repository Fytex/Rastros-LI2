

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "../data/state.h"

/*
 * Função que verifica se uma Jogada é válida.
 */

int check_move(State state, Position pos){

    return pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
        abs(pos.row) <= 1 && abs(pos.column) <= 1 &&
        state.board[pos.row][pos.column] == Blank;

}

/*
 * Função que modifica o estado ao jogar na casa correta se a jogada for válida.
 */

int play(State *state, Position pos) {

    if (!check_move(*state, pos)) {
        puts ( "Introduza uma jogada válida!");
        return 0;
    }

    edit_space(state, state->last_play, Black);
    edit_space(state, pos, White);
    printf("Jogada efetuada %d %d\n", pos.column, pos.row);

    return 1;

}


