#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "../data/state.h"

/*
 * Checks if play is valid
 */

int check_move(const State* const state, const Position pos){
    const Position last_play = get_last_play(state);

    return pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
        abs(last_play.row - pos.row) <= 1 && abs(last_play.column - pos.column) <= 1 &&
        get_position_space(state, pos) == Blank;

}


/*
 * Changes spaces from each move's position and appends move to moves' array
 */
void make_move(State* const state, const Position pos){
    unsigned int current_player = get_current_player(state);
    Position last_play = get_last_play(state);

    // Changes last move's position in the boarder to Black
    edit_position_space(state, last_play, Black);

    // Changes new move's position in the boarder to White
    edit_position_space(state, pos, White);

    if (current_player == 2) {
        Move move = {.player1 = last_play, .player2 = pos};
        append_move(state, move);
    }

    edit_last_play(state, pos);
}


/*
 * Changes state if played in a valid position
 */

int play(State* const state, const Position pos) {

    if (!check_move(state, pos))
        return 0;

    make_move(state, pos);

    return 1;
}

/*
 * Checks if game finished and returns the winner
 * Returns 0 in case game not finished yet
 */

unsigned int game_finished(const State* const state) {

    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    const Position last_play=get_last_play(state);
    Position pos;

    if (last_play.row - last_play.column == 7)
        return 1;
    else if (last_play.column - last_play.row == 7)
        return 2;

    for (int i=0; i < 8; ++i) {
        pos = (Position) {.row = last_play.row + sum_pos[i][0], .column = last_play.column + sum_pos[i][1]};

        if (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
            get_position_space(state, pos) == Blank)
            return 0; // Game not finished yet
    }

    return get_current_player(state);
}


