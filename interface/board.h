/**
@file board.h
Definição das funções que imprimem o estado do jogo.
*/

#ifndef RASTROS_LI2_BOARD_H
#define RASTROS_LI2_BOARD_H

#include <stdio.h>
#include "../data/state.h"
#include "../linked_lists/linked.h"

/**
\brief Esta função imprime o tabuleiro.
@param state Apontador para o estado
@param file Apontador para o tipo de ficheiro aonde irá imprimir
*/
void print_board(const State* state, FILE* file);

/**
\brief Esta função imprime as jogadas.
@param state Apontador para o estado
@param file Apontador para o tipo de ficheiro aonde irá imprimir
*/
void print_moves(const State* state, FILE* file);

void edit_state_from_move(State* state, int move_count);

#endif //RASTROS_LI2_BOARD_H
