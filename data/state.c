//
// Created by fytex on 3/9/20.
//

#include <stdlib.h>
#include "state.h"

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