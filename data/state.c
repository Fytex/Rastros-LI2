

#include <stdlib.h>
#include "state.h"

/*
 * Initialize State
 */

State *initialize_state() {
    State *state = (State *) malloc(sizeof(State));
    state->current_player = 1;
    state->move_count = 0; // Not necessary because it will be assigned 0 when struct is created
    state->last_play.row = 3;
    state->last_play.column = 4;

    for (int row=0; row < 8; row++)
        for (int column=0; column < 8; column++) {

            if (row == 3 && column == 4)
                state->board[row][column] = White;
            else
                state->board[row][column] = Blank;

        }

    return state;
}

/*
 * Changes spaces from each move's position and appends move to moves' array
 */
void make_move(State *state, Position pos){

        // Changes last move's position in the boarder to Black
        state->board[state->last_play.row][state->last_play.column] = Black;

        // Changes new move's position in the boarder to White
        state->board[pos.row][pos.column] = White;

        if (state->current_player == 2) {
            Move move = {state->last_play, pos};
            state->moves[state->move_count++] = move;
        }

        state->last_play = pos;
}


/*
 * Returns last play of the state
 */

Position get_last_play(State *state) {
    return state->last_play;
}


/*
 * Returns the move in that index position from moves' array
 */

Move get_move(State *state, int idx) {
    return state->moves[idx];
}


/*
 * Returns current player of the state
 */

unsigned int get_current_player(State *state) {
    return state->current_player;
}


/*
 * Returns the moves' count of the state
 */

int get_move_count(State *state) {
    return state->move_count;
}


/*
 * Returns the space in the boarder's position
 */

Space get_position_space(State *state, Position pos){
    return state->board[pos.row][pos.column];
}


/*
 * Swap current player in state and returns new player
 */

unsigned int swap_players(State *state) {

    // XOR (Binary Operation - Simple and efficient way to change from player 1 to 2 and vice-versa)
    unsigned int next_player = state->current_player ^ (unsigned) 3;

    state->current_player = next_player;

    return next_player;

}