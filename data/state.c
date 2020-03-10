

#include <stdlib.h>
#include "state.h"

/*
 * Função que inicializa o Estado.
 */

State *initialize_state() {
    State *state = (State *) malloc(sizeof(State));
    state->current_player = 1;
    state->move_count = 0; // Not necessary because it will be assigned 0 when struct is created
    state->last_play.row = 4;
    state->last_play.column = 4;

    for (int row=0; row < 8; row++)
        for (int column=0; column < 8; column++) {

            if (row == 4 && column == 4)
                state->board[row][column] = White;
            else
                state->board[row][column] = Blank;

        }

    return state;
}

/*
 * Função que coloca uma Peça numa casa jogada.
 */
void edit_space(State* state, Position pos, Space space){

        state->board[pos.row][pos.column] = space;

}