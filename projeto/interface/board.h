/**
@file board.h
Definição das funções que imprimem o estado do jogo
*/

#ifndef RASTROS_LI2_BOARD_H
#define RASTROS_LI2_BOARD_H

#include <stdio.h>
#include "../data/state.h"
#include "../linked_lists/linked.h"

/**
\brief Imprime o tabuleiro
@param state Apontador para o estado
@param file Apontador para o tipo de ficheiro aonde irá imprimir
*/
void print_board(const State* state, FILE* file);

/**
\brief Imprime as jogadas.
@param state Apontador para o estado
@param file Apontador para o tipo de ficheiro aonde irá imprimir
*/
void print_moves(const State* state, FILE* file);

/**
\brief Edita do estado do jogo para uma jogada anterior de onde podemos começar a jogar
@param state Apontador para o estado
@param move_count Número de uma jogada para onde se tenciona alterar o estado
*/
void edit_state_from_move(State* state, int move_count);

/**
\brief Dá print de um espaço no ecrã
@param state Apontador para o estado
@param file Apontador para o tipo de ficheiro aonde irá imprimir
*/
void type_space(const Space p, FILE* const file);

#endif //RASTROS_LI2_BOARD_H
