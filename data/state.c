#include <stdlib.h>
#include "state.h"

const Position BEGIN_POS = {.row = 3, .column = 4};


/*
 * Returns last play of the state
 */

Position get_last_play(const State* const state) {
    return state->last_play;
}


/*
 * Edits last play of the state
 */

void edit_last_play(State* const state, const Position pos) {
    state->last_play = pos;
}


/*
 * Returns the move in that index position from moves' array
 */

Move get_move(const State* const state, const int idx) {
    return state->moves[idx];
}


/*
 * Edits the move in that index position from moves' array
 */

void edit_move(State* const state, const int idx, const Move move) {
    state->moves[idx] = move;
}


/*
 * Returns current player of the state
 */

unsigned int get_current_player(const State* const state) {
    return state->current_player;
}


/*
 * Returns the moves' count of the state
 */

int get_move_count(const State* const state) {
    return state->move_count;
}


/*
 * Edit the moves' count of the state
 */

void edit_move_count(State* const state, const int count) {
    state->move_count = count;
}


/*
 * Returns the space in the boarder's position
 */

Space get_position_space(const State* const state, const Position pos){
    return state->board[pos.row][pos.column];
}


/*
 * Edits the space in the boarder's position
 */

void edit_position_space(State* const state, const Position pos, const Space space){
    state->board[pos.row][pos.column] = space;
}


/*
 * Edit current player
 */

void edit_current_player(State* const state, const unsigned int player) {
    state->current_player = player;
}


/*
 * Swap current player in state and returns new player
 */

unsigned int swap_players(State* const state) {

    // XOR (Binary Operation - Simple and efficient way to change from player 1 to 2 and vice-versa)
    const unsigned int next_player = state->current_player ^ (unsigned) 3;

    edit_current_player(state, next_player);

    return next_player;

}


/*
 * Add a move to moves' array and increments move_count
 */

void append_move(State* const state, const Move move) {
    int count = get_move_count(state);

    edit_move(state, count, move);
    edit_move_count(state, ++count);
}


/*
 * Sets the value of the given state to their defaults
 */

void set_default_state(State* const state) {
    Position pos;

    edit_current_player(state, 1);
    edit_move_count(state, 0);
    edit_last_play(state, BEGIN_POS);

    for (pos.row = 0; pos.row < 8; ++pos.row)
        for (pos.column = 0; pos.column < 8; ++pos.column)
            edit_position_space(state, pos, Blank);

    edit_position_space(state, BEGIN_POS, White);

}