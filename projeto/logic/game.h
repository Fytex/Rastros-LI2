/**
@file game.h
Definição das funções para jogar e terminar o jogo
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
int play(State* state, Position pos);

/**
\brief Função para verificar se o jogo está terminado e quem ganhou
@param state Apontador para o estado
@returns O vencedor, 0 se ainda não terminou
*/
unsigned int game_finished(const State* state);

/**
\brief Função para o computador fazer uma jogada
@param state Apontador para o estado
*/
void computer_move(State* const state);

/**
\brief Função para o computador fazer uma jogada, estratégia diferente da anterior
@param state Apontador para o estado
*/
void computer_move2(State* const state);

/**
\brief Função que corre o algoritmo flood fill
@param state Apontador para o estado
@param flood_fill_matrix Matriz usada no flood fill
@param player Jogador que irá fazer a jogada
@returns A jogada que será feita
*/
Position flood_fill(State* state, int flood_fill_matrix[][8] ,unsigned int player);

/**
\brief Função que analisa a matriz
@param flood_fill_matrix Matriz usada no flood fill
@param pos Posição da casa objetivo
@param count Distância da posição atual
@returns A jogada que será feita
*/
Position reads_flood_fill_matrix(int flood_fill_matrix[][8], Position pos, int count);

/**
\brief Função que procura a posição adjacente mais próxima do objetivo
@param state Apontador para o estado
@param player Jogador atual
@returns A jogada que será feita
*/
Position arithmeticJog (State* state, unsigned int player);

/**
\brief Função que dá uma posição aleatória adjacente para jogar
@param state Apontador para o estado
@returns A jogada que será feita
*/
Position randomJog (State* state);

/**
\brief Função que faz a jogada
@param state Apontador para o estado
@param pos Posição onde irá jogar
*/
void make_move(State* const state, const Position pos);

/**
\brief Confirma se é uma jogada válida
@param state Apontador para o estado
@param pos Jogada a confirmar
@returns Se é possivel ou não
*/
int check_move(const State* const state, const Position pos);

#endif //RASTROS_LI2_GAME_H
