

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "../data/state.h"

/*
 * Checks if play is valid
 */

int check_move(State *state, Position pos){
    Position last_play = get_last_play(state);

    return pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
        abs(last_play.row - pos.row) <= 1 && abs(last_play.column - pos.column) <= 1 &&
        !get_position_space(state, pos);

}

/*
 * Changes state if played in a valid position
 */

int play(State *state, Position pos) {

    if (!check_move(state, pos))
        return 0;

    make_move(state, pos);

    return 1;
}

/*
 * Checks if game finished and returns the winner
 * Returns 0 in case game not finished yet
 */

unsigned int game_finished(State *state) {

    int sum_row[8] = {1, 1, 1, 0, 0,-1,-1,-1};
    int sum_col[8] = {1, 0,-1, 1,-1, 1, 0,-1};
    Position pos, last_play=get_last_play(state);

    if (last_play.row - last_play.column == 7)
        return 1;
    else if (last_play.column - last_play.row == 7)
        return 2;

    for (int i=0; i < 8; i++) {
        pos.column = get_last_play(state).column + sum_col[i];
        pos.row = get_last_play(state).row + sum_row[i];

        if (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
            get_position_space(state, pos) == Blank)
            return 0; // Game not finished yet
    }

    return get_current_player(state);
}


