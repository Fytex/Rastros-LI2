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

    for (int row=0; row < 8; ++row)
        for (int column=0; column < 8; ++column) {

            if (row == 3 && column == 4)
                state->board[row][column] = White;
            else
                state->board[row][column] = Blank;

        }

    return state;
}


/*
 * Returns last play of the state
 */

Position get_last_play(State *state) {
    return state->last_play;
}


/*
 * Edits last play of the state
 */

void edit_last_play(State *state, Position pos) {
    state->last_play = pos;
}


/*
 * Returns the move in that index position from moves' array
 */

Move get_move(State *state, int idx) {
    return state->moves[idx];
}


/*
 * Edits the move in that index position from moves' array
 */

void edit_move(State *state, int idx, Move move) {
    state->moves[idx] = move;
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
 * Edit the moves' count of the state
 */

void edit_move_count(State *state, int count) {
    state->move_count = count;
}


/*
 * Returns the space in the boarder's position
 */

Space get_position_space(State *state, Position pos){
    return state->board[pos.row][pos.column];
}


/*
 * Edits the space in the boarder's position
 */

void edit_position_space(State *state, Position pos, Space space){
    state->board[pos.row][pos.column] = space;
}


/*
 * Edit current player
 */

void edit_current_player(State *state, unsigned int player) {
    state->current_player = player;
}


/*
 * Swap current player in state and returns new player
 */

unsigned int swap_players(State *state) {

    // XOR (Binary Operation - Simple and efficient way to change from player 1 to 2 and vice-versa)
    unsigned int next_player = state->current_player ^ (unsigned) 3;

    edit_current_player(state, next_player);

    return next_player;

}


/*
 * Add a move to moves' array and increments move_count
 */

void append_move(State *state,  Move move) {
    int count = get_move_count(state);

    edit_move(state, count, move);
    edit_move_count(state, ++count);
}