/**
@file interface.h
Definição da função que comunica com o terminal
*/

#ifndef RASTROS_LI2_INTERFACE_H
#define RASTROS_LI2_INTERFACE_H

#include <stdio.h>
#include "../data/state.h"


/** Tamanho do buffer */
#define BUF_SIZE 1024

/**
\brief Esta função interage com o terminal
@param state Apontador para o estado
@returns O vencedor, ou se deu algum erro (caso 0)
*/
void interpreter(State* state);

/**
\brief Limpa a janela do terminal
*/
void clear_terminal();

/**
\brief Limpa o stdin
*/
void clear_stdin_buffer();

/**
\brief Mostra algo no terminal
@param state Apontador para o estado
@param func Função a ser executada no terminal
*/
void display_in_terminal(const State* const state, void (* const func)());

/**
\brief Mostra a última informação no ecrã
@param state Apontador para o estado
*/
void print_last_info(const State* const state);

/**
\brief Mostra a ajuda no ecrã
*/
void help_terminal();

/**
\brief Converte uma letra maiúscula e em minúscula
@param s Letra a converter em minúscula
*/
void lower_string(char* s);

#endif //RASTROS_LI2_INTERFACE_H
