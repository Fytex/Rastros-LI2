/**
@file game.h
Definição das funções para jogar e terminar o jogo.
*/

#ifndef RASTROS_LI2_GAME_H
#define RASTROS_LI2_GAME_H

#include "../data/state.h"

/**
\brief Função para jogar o jogo
@param state Apontador para o estado
@param pos Coordenadas de uma jogada a realizar
@returns Se foi realizada a jogada ou não
*/
int play(State *state, Position pos);

/**
\brief Função para verificar se o jogo está terminado e quem ganhou
@param state Apontador para o estado
@returns O vencedor, 0 se ainda não terminou
*/
unsigned int game_finished(State *state);

#endif //RASTROS_LI2_GAME_H
