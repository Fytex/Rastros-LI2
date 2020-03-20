/**
@file file.h
Funções que manipulam ficheiros de texto.
*/

#ifndef RASTROS_LI2_FILE_H
#define RASTROS_LI2_FILE_H

#include "state.h"

/**
\brief Escreve num ficheiro indicado a informacção do estado.
@param state Apontador para o estado
@param filename Apontador para o nome do ficheiro
*/
void write_to_file(State *state, char *filename);

/**
\brief Lê um ficheiro indicado e altera a informação do estado pela do ficheiro.
@param state Apontador para o estado
@param filename Apontador para o nome do ficheiro
*/
void read_from_file(State *state, char *filename);

#endif //RASTROS_LI2_FILE_H