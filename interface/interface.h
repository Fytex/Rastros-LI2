/**
@file interface.h
Definição da função que comunica com o terminal.
*/

#ifndef RASTROS_LI2_INTERFACE_H
#define RASTROS_LI2_INTERFACE_H

#include <stdio.h>
#include "../data/state.h"

/**
\brief Esta função interage com o terminal.
@param state Apontador para o estado
@returns O vencedor, ou se deu algum erro (caso 0)
*/
int interpreter(State *state);

#endif //RASTROS_LI2_INTERFACE_H
