

#ifndef RASTROS_LI2_INTERFACE_H
#define RASTROS_LI2_INTERFACE_H

#include <stdio.h>
#include "../data/state.h"

int interpreter(State *state);
void print_board(State state, FILE *file);

#endif //RASTROS_LI2_INTERFACE_H
