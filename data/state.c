

#include <stdlib.h>
#include "state.h"

/*
 * Função que inicializa o Estado.
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
 * Altera as casas de cada jogada e adiciona a jogada ao array de jogadas
 */
void make_move(State* state, Position pos){

        // Altera a casa da última jogada para preta
        state->board[state->last_play.row][state->last_play.column] = Black;

        // Altera a casa da nova jogada para branca
        state->board[pos.row][pos.column] = White;

        if (state->current_player == 2) {
            Move move = {state->last_play, pos};
            state->moves[state->move_count++] = move;
        }

        state->last_play = pos;
}

/*
 * Troca o jogador atual (current_player)
 */

void swap_players(State* state) {

    // XOR (Operação Binária para trocar 1 por 2 e vice-versa mais eficaz e simples)
    state->current_player = state->current_player ^ (unsigned) 3;

}